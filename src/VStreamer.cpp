#include "VStreamer.h"
#include "VStreamerVersion.h"
#include <array>
#include <cstdint>
#include <cstring>
#include <limits>
#include <new>
#include <string>
#include <type_traits>
#include <utility>



namespace
{
// Serialized data and commands store int and float values as raw 4 bytes
// values and bool values as 1 byte.
static_assert(sizeof(int) == 4, "int must be 4 bytes");
static_assert(sizeof(float) == 4, "float must be 4 bytes");
static_assert(sizeof(bool) == 1, "bool must be 1 byte");

/// Data type of an action command.
constexpr uint8_t COMMAND_DATA_TYPE{0x00};
/// Data type of a set param command with a numeric value.
constexpr uint8_t SET_PARAM_DATA_TYPE{0x01};
/// Data type of serialized params.
constexpr uint8_t PARAMS_DATA_TYPE{0x02};
/// Data type of a set param command with a string value.
constexpr uint8_t SET_STRING_PARAM_DATA_TYPE{0x03};
/// Position of the major version in commands and in serialized params. The
/// minor version follows it.
constexpr int VERSION_POS{1};
/// Position of the command or param ID in commands.
constexpr int COMMAND_ID_POS{3};
/// Position of the param value in set param commands.
constexpr int COMMAND_VALUE_POS{7};
/// Size of an int or float value, bytes.
constexpr int VALUE_SIZE{4};
/// Size of a bool value, bytes.
constexpr int FLAG_SIZE{1};
/// Size of an action command, bytes: header and command ID.
constexpr int COMMAND_SIZE{COMMAND_VALUE_POS};
/// Size of a set param command with a numeric value, bytes.
constexpr int SET_PARAM_SIZE{COMMAND_VALUE_POS + VALUE_SIZE};
/// Minimum size of a set param command with a string value, bytes: an empty
/// string is the terminating NUL byte only.
constexpr int SET_STRING_PARAM_MIN_SIZE{COMMAND_VALUE_POS + 1};
/// Position of the mask in serialized params.
constexpr int PARAMS_MASK_POS{3};
/// Size of the mask in serialized params, bytes.
constexpr int PARAMS_MASK_SIZE{10};
/// Size of the header of serialized params: data type, version and mask.
constexpr int PARAMS_HEADER_SIZE{PARAMS_MASK_POS + PARAMS_MASK_SIZE};
/// Minimum buffer size for serialization: the header and the smallest field.
constexpr int PARAMS_MIN_BUFFER_SIZE{PARAMS_HEADER_SIZE + FLAG_SIZE};
/// Number of bits in a mask byte.
constexpr int BITS_PER_BYTE{8};
/// Bit of the first field of a mask byte: the most significant bit.
constexpr unsigned int FIRST_FIELD_BIT{0x80U};
/// Number of VStreamerParams fields: one mask bit per field, the other bits
/// of the mask are reserved and must be 0.
constexpr int FIELDS_NUMBER{69};
/// Number of bits of the mask.
constexpr int MASK_BITS_NUMBER{PARAMS_MASK_SIZE * BITS_PER_BYTE};
static_assert(FIELDS_NUMBER <= MASK_BITS_NUMBER, "mask is too small");
static_assert(sizeof(rapidpixel::VStreamerParamsMask) == FIELDS_NUMBER,
              "every field of VStreamerParamsMask must be in the field table");

/// First action command ID (VStreamerCommand).
constexpr int MIN_COMMAND_ID{
        static_cast<int>(rapidpixel::VStreamerCommand::RESTART)};
/// Last action command ID (VStreamerCommand).
constexpr int MAX_COMMAND_ID{
        static_cast<int>(rapidpixel::VStreamerCommand::GENERATE_KEYFRAME)};
/// First param ID (VStreamerParam).
constexpr int MIN_PARAM_ID{static_cast<int>(rapidpixel::VStreamerParam::MODE)};
/// Last param ID (VStreamerParam).
constexpr int MAX_PARAM_ID{static_cast<int>(
        rapidpixel::VStreamerParam::SERVER_STREAM_MAX_PAYLOAD)};

// VStreamerParams::deserialize(...) assigns the decoded object at the end:
// the assignment must not throw, so the object is never half changed.
static_assert(std::is_nothrow_move_assignable<
              rapidpixel::VStreamerParams>::value,
              "move assignment of VStreamerParams must not throw");



/// Type of a VStreamerParams field in serialized data.
enum class FieldType : uint8_t
{
    /// bool field, 1 byte: 0 - false, any other value - true.
    FLAG,
    /// int or float field, 4 bytes in the byte order of the host.
    VALUE,
    /// std::string field: the characters and a terminating NUL byte.
    TEXT
};



/// Reference to a VStreamerParams field and to its flag in the mask.
struct FieldRef
{
    /// Pointer to the field: bool, int, float or std::string (see type).
    void* value{nullptr};
    /// Type of the field.
    FieldType type{FieldType::FLAG};
    /// Flag of the field in VStreamerParamsMask.
    bool rapidpixel::VStreamerParamsMask::* selected{nullptr};
};



using Mask = rapidpixel::VStreamerParamsMask;



/// Make a reference to a bool field.
FieldRef field(bool& value, bool Mask::* selected)
{
    return {&value, FieldType::FLAG, selected};
}



/// Make a reference to an int field.
FieldRef field(int& value, bool Mask::* selected)
{
    return {&value, FieldType::VALUE, selected};
}



/// Make a reference to a float field.
FieldRef field(float& value, bool Mask::* selected)
{
    return {&value, FieldType::VALUE, selected};
}



/// Make a reference to a string field.
FieldRef field(std::string& value, bool Mask::* selected)
{
    return {&value, FieldType::TEXT, selected};
}



/// Get the table of VStreamerParams fields in the order they are stored in
/// serialized data: field i has bit (7 - i % 8) of mask byte i / 8.
std::array<FieldRef, FIELDS_NUMBER> makeFieldTable(
        rapidpixel::VStreamerParams& p)
{
    return {{
        field(p.enable, &Mask::enable),
        field(p.width, &Mask::width),
        field(p.height, &Mask::height),
        field(p.directStreamIp, &Mask::directStreamIp),
        field(p.rtspPort, &Mask::rtspPort),
        field(p.directStreamPort, &Mask::directStreamPort),
        field(p.webRtcPort, &Mask::webRtcPort),
        field(p.hlsPort, &Mask::hlsPort),
        field(p.srtPort, &Mask::srtPort),
        field(p.rtmpPort, &Mask::rtmpPort),
        field(p.metadataPort, &Mask::metadataPort),
        field(p.rtspEnable, &Mask::rtspEnable),
        field(p.directStreamEnable, &Mask::directStreamEnable),
        field(p.webRtcEnable, &Mask::webRtcEnable),
        field(p.hlsEnable, &Mask::hlsEnable),
        field(p.srtEnable, &Mask::srtEnable),
        field(p.rtmpEnable, &Mask::rtmpEnable),
        field(p.metadataEnable, &Mask::metadataEnable),
        field(p.rtspMulticastIp, &Mask::rtspMulticastIp),
        field(p.rtspMulticastPort, &Mask::rtspMulticastPort),
        field(p.user, &Mask::user),
        field(p.password, &Mask::password),
        field(p.suffix, &Mask::suffix),
        field(p.metadataSuffix, &Mask::metadataSuffix),
        field(p.minBitrateKbps, &Mask::minBitrateKbps),
        field(p.maxBitrateKbps, &Mask::maxBitrateKbps),
        field(p.bitrateKbps, &Mask::bitrateKbps),
        field(p.bitrateMode, &Mask::bitrateMode),
        field(p.fps, &Mask::fps),
        field(p.gop, &Mask::gop),
        field(p.h264Profile, &Mask::h264Profile),
        field(p.jpegQuality, &Mask::jpegQuality),
        field(p.codec, &Mask::codec),
        field(p.fitMode, &Mask::fitMode),
        field(p.cycleTimeUs, &Mask::cycleTimeUs),
        field(p.overlayEnable, &Mask::overlayEnable),
        field(p.type, &Mask::type),
        field(p.custom1, &Mask::custom1),
        field(p.custom2, &Mask::custom2),
        field(p.custom3, &Mask::custom3),
        field(p.rtspKey, &Mask::rtspKey),
        field(p.rtspCert, &Mask::rtspCert),
        field(p.webRtcKey, &Mask::webRtcKey),
        field(p.webRtcCert, &Mask::webRtcCert),
        field(p.hlsKey, &Mask::hlsKey),
        field(p.hlsCert, &Mask::hlsCert),
        field(p.rtmpKey, &Mask::rtmpKey),
        field(p.rtmpCert, &Mask::rtmpCert),
        field(p.rtspEncryption, &Mask::rtspEncryption),
        field(p.webRtcEncryption, &Mask::webRtcEncryption),
        field(p.rtmpEncryption, &Mask::rtmpEncryption),
        field(p.hlsEncryption, &Mask::hlsEncryption),
        field(p.logLevel, &Mask::logLevel),
        field(p.rtspsPort, &Mask::rtspsPort),
        field(p.rtmpsPort, &Mask::rtmpsPort),
        field(p.directStreamType, &Mask::directStreamType),
        field(p.directStreamBitrateKbps, &Mask::directStreamBitrateKbps),
        field(p.directStreamMaxPayloadSize, &Mask::directStreamMaxPayloadSize),
        field(p.directStreamPacingMode, &Mask::directStreamPacingMode),
        field(p.serverStreamType, &Mask::serverStreamType),
        field(p.multicastTtl, &Mask::multicastTtl),
        field(p.securityProfile, &Mask::securityProfile),
        field(p.publicAddress, &Mask::publicAddress),
        field(p.bindAddress, &Mask::bindAddress),
        field(p.rtpPortMin, &Mask::rtpPortMin),
        field(p.rtpPortMax, &Mask::rtpPortMax),
        field(p.webRtcMediaPort, &Mask::webRtcMediaPort),
        field(p.corsAllowedOrigin, &Mask::corsAllowedOrigin),
        field(p.serverStreamMaxPayloadSize, &Mask::serverStreamMaxPayloadSize)
    }};
}



/// Get the index of the mask byte of a field (from the start of the mask).
int maskByteIndex(int fieldIndex)
{
    return fieldIndex / BITS_PER_BYTE;
}



/// Get the bit of a field in its mask byte: the first field of a byte is the
/// most significant bit.
uint8_t maskBit(int fieldIndex)
{
    return static_cast<uint8_t>(
            FIRST_FIELD_BIT >> (fieldIndex % BITS_PER_BYTE));
}



/// Check whether the mask of serialized params has the bit of a field set.
bool isEncoded(const uint8_t* data, int fieldIndex)
{
    return (data[PARAMS_MASK_POS + maskByteIndex(fieldIndex)] &
            maskBit(fieldIndex)) != 0;
}



/// Write a field into serialized data. Return the number of bytes written or
/// 0 if the field is not written: it doesn't fit into the available bytes,
/// or it is a string which contains a NUL character (the receiver would end
/// the string at that character and read the rest of it as the next fields).
int writeField(const FieldRef& field, uint8_t* data, int available)
{
    if (field.type == FieldType::FLAG)
    {
        if (available < FLAG_SIZE)
        {
            return 0;
        }
        data[0] = *static_cast<const bool*>(field.value) ? uint8_t{0x01}
                                                         : uint8_t{0x00};
        return FLAG_SIZE;
    }

    if (field.type == FieldType::VALUE)
    {
        if (available < VALUE_SIZE)
        {
            return 0;
        }
        std::memcpy(data, field.value, VALUE_SIZE);
        return VALUE_SIZE;
    }

    // The string takes its characters and the terminator. The length is
    // compared as size_t: a string longer than INT_MAX is never converted to
    // int before the check.
    const std::string& text = *static_cast<const std::string*>(field.value);
    if (text.size() >= static_cast<size_t>(available) ||
        text.find('\0') != std::string::npos)
    {
        return 0;
    }
    std::memcpy(data, text.c_str(), text.size() + 1);
    return static_cast<int>(text.size()) + 1;
}



/// Read a field from serialized data. Return the number of bytes read or 0 if
/// the field is not complete (a value is cut, a string has no terminator).
/// Throws std::bad_alloc if memory for a string can't be allocated.
int readField(const FieldRef& field, const uint8_t* data, int available)
{
    if (field.type == FieldType::FLAG)
    {
        if (available < FLAG_SIZE)
        {
            return 0;
        }
        // Any byte other than 0 is true: a bool object must not receive the
        // byte as it is.
        *static_cast<bool*>(field.value) = data[0] != 0x00;
        return FLAG_SIZE;
    }

    if (field.type == FieldType::VALUE)
    {
        if (available < VALUE_SIZE)
        {
            return 0;
        }
        std::memcpy(field.value, data, VALUE_SIZE);
        return VALUE_SIZE;
    }

    // The string ends with the first NUL byte, which must be inside the data.
    if (available <= 0)
    {
        return 0;
    }
    const void* end = std::memchr(data, 0, static_cast<size_t>(available));
    if (end == nullptr)
    {
        return 0;
    }
    // The terminator is inside the data: the length is < available and fits
    // into int.
    const size_t length =
            static_cast<size_t>(static_cast<const uint8_t*>(end) - data);
    static_cast<std::string*>(field.value)->assign(
            reinterpret_cast<const char*>(data), length);
    return static_cast<int>(length) + 1;
}



/// Set a field which is not in serialized data to 0, false or empty string.
void clearField(const FieldRef& field)
{
    if (field.type == FieldType::FLAG)
    {
        *static_cast<bool*>(field.value) = false;
    }
    else if (field.type == FieldType::VALUE)
    {
        // All bits 0: int 0 or float 0.0.
        std::memset(field.value, 0, VALUE_SIZE);
    }
    else
    {
        static_cast<std::string*>(field.value)->clear();
    }
}



/// Write the header of a command: data type, version and ID.
void writeCommandHeader(uint8_t* data, uint8_t dataType, int id)
{
    data[0] = dataType;
    data[VERSION_POS] = static_cast<uint8_t>(VSTREAMER_MAJOR_VERSION);
    data[VERSION_POS + 1] = static_cast<uint8_t>(VSTREAMER_MINOR_VERSION);
    std::memcpy(&data[COMMAND_ID_POS], &id, VALUE_SIZE);
}
}



rapidpixel::VStreamer::~VStreamer() = default;



std::string rapidpixel::VStreamer::getVersion()
{
    return VSTREAMER_VERSION;
}



bool rapidpixel::VStreamerParams::serialize(
        uint8_t* data, int bufferSize, int& size, VStreamerParamsMask* mask)
{
    // The size is 0 unless the params are serialized.
    size = 0;

    // Check pointer and buffer size: the buffer must keep the header and the
    // smallest field.
    if (data == nullptr || bufferSize < PARAMS_MIN_BUFFER_SIZE)
    {
        return false;
    }

    // All fields are selected by default.
    const VStreamerParamsMask defaultMask;
    const VStreamerParamsMask& selection =
            mask == nullptr ? defaultMask : *mask;

    // Header: data type, version and mask (set bit by bit below). The
    // version is a part of the format: the receiver accepts only data of its
    // own major and minor version.
    data[0] = PARAMS_DATA_TYPE;
    data[VERSION_POS] = static_cast<uint8_t>(VSTREAMER_MAJOR_VERSION);
    data[VERSION_POS + 1] = static_cast<uint8_t>(VSTREAMER_MINOR_VERSION);
    std::memset(&data[PARAMS_MASK_POS], 0, PARAMS_MASK_SIZE);

    // Serialize the selected fields. A field which is not written doesn't get
    // its mask bit, and the next fields are written if they fit. The
    // position never exceeds the buffer size, so bufferSize - pos doesn't
    // overflow.
    const auto fields = makeFieldTable(*this);
    int pos = PARAMS_HEADER_SIZE;
    for (int i = 0; i < FIELDS_NUMBER; ++i)
    {
        const FieldRef& field = fields[static_cast<size_t>(i)];
        if (!(selection.*field.selected))
        {
            continue;
        }

        const int written = writeField(field, &data[pos], bufferSize - pos);
        if (written == 0)
        {
            continue;
        }
        uint8_t& maskByte = data[PARAMS_MASK_POS + maskByteIndex(i)];
        maskByte = static_cast<uint8_t>(maskByte | maskBit(i));
        pos += written;
    }

    size = pos;

    return true;
}



bool rapidpixel::VStreamerParams::deserialize(uint8_t* data, int dataSize)
{
    // Check pointer and data size: the header must be complete.
    if (data == nullptr || dataSize < PARAMS_HEADER_SIZE)
    {
        return false;
    }

    // Check data type and version. The layout of the data (mask size, order
    // of the fields) belongs to a major and minor version: data of another
    // version would be read with wrong offsets.
    if (data[0] != PARAMS_DATA_TYPE ||
        data[VERSION_POS] != VSTREAMER_MAJOR_VERSION ||
        data[VERSION_POS + 1] != VSTREAMER_MINOR_VERSION)
    {
        return false;
    }

    // Check that the mask has no bits of unknown fields.
    for (int i = FIELDS_NUMBER; i < MASK_BITS_NUMBER; ++i)
    {
        if (isEncoded(data, i))
        {
            return false;
        }
    }

    // Decode into a temporary object: this object is changed only if the
    // whole data is valid. Strings need memory: an allocation failure is
    // reported as a deserialization failure.
    try
    {
        VStreamerParams result;
        const auto fields = makeFieldTable(result);
        int pos = PARAMS_HEADER_SIZE;
        for (int i = 0; i < FIELDS_NUMBER; ++i)
        {
            const FieldRef& field = fields[static_cast<size_t>(i)];
            if (!isEncoded(data, i))
            {
                clearField(field);
                continue;
            }

            // The position never exceeds the data size, so dataSize - pos
            // doesn't overflow.
            const int read = readField(field, &data[pos], dataSize - pos);
            if (read == 0)
            {
                return false;
            }
            pos += read;
        }

        // The move assignment doesn't throw (see static_assert above).
        *this = std::move(result);
    }
    catch (const std::bad_alloc&)
    {
        return false;
    }

    return true;
}



void rapidpixel::VStreamer::encodeSetParamCommand(
        uint8_t* data, int& size, VStreamerParam id, float value)
{
    // The size is 0 unless the command is encoded.
    size = 0;
    if (data == nullptr)
    {
        return;
    }

    writeCommandHeader(data, SET_PARAM_DATA_TYPE, static_cast<int>(id));
    std::memcpy(&data[COMMAND_VALUE_POS], &value, VALUE_SIZE);
    size = SET_PARAM_SIZE;
}



void rapidpixel::VStreamer::encodeSetParamCommand(
        uint8_t* data, int& size, VStreamerParam id, std::string value)
{
    // The size is 0 unless the command is encoded. The size of the command
    // must fit into int, and the value must not contain a NUL character: the
    // decoder ends the string at the first NUL byte and rejects a command
    // with bytes after it.
    size = 0;
    if (data == nullptr ||
        value.size() > static_cast<size_t>(
                std::numeric_limits<int>::max() - SET_STRING_PARAM_MIN_SIZE) ||
        value.find('\0') != std::string::npos)
    {
        return;
    }

    writeCommandHeader(data, SET_STRING_PARAM_DATA_TYPE, static_cast<int>(id));
    std::memcpy(&data[COMMAND_VALUE_POS], value.c_str(), value.size() + 1);
    size = SET_STRING_PARAM_MIN_SIZE + static_cast<int>(value.size());
}



void rapidpixel::VStreamer::encodeCommand(
        uint8_t* data, int& size, VStreamerCommand id)
{
    // The size is 0 unless the command is encoded.
    size = 0;
    if (data == nullptr)
    {
        return;
    }

    writeCommandHeader(data, COMMAND_DATA_TYPE, static_cast<int>(id));
    size = COMMAND_SIZE;
}



int rapidpixel::VStreamer::decodeCommand(uint8_t* data,
                                         int size,
                                         VStreamerParam& paramId,
                                         VStreamerCommand& commandId,
                                         float& value,
                                         std::string& strValue)
{
    // Check pointer, minimum size (header and ID) and version.
    if (data == nullptr || size < COMMAND_SIZE ||
        data[VERSION_POS] != VSTREAMER_MAJOR_VERSION ||
        data[VERSION_POS + 1] != VSTREAMER_MINOR_VERSION)
    {
        return -1;
    }

    int id{0};
    std::memcpy(&id, &data[COMMAND_ID_POS], VALUE_SIZE);

    // Action command: exact size, ID inside the VStreamerCommand range (an
    // unknown ID is not passed to the implementation).
    if (data[0] == COMMAND_DATA_TYPE)
    {
        if (size != COMMAND_SIZE || id < MIN_COMMAND_ID || id > MAX_COMMAND_ID)
        {
            return -1;
        }
        commandId = static_cast<VStreamerCommand>(id);
        value = 0.0f;
        strValue.clear();
        return 0;
    }

    // Set param commands: ID inside the VStreamerParam range.
    if (id < MIN_PARAM_ID || id > MAX_PARAM_ID)
    {
        return -1;
    }

    // Set param command with a numeric value: exact size.
    if (data[0] == SET_PARAM_DATA_TYPE)
    {
        if (size != SET_PARAM_SIZE)
        {
            return -1;
        }
        paramId = static_cast<VStreamerParam>(id);
        std::memcpy(&value, &data[COMMAND_VALUE_POS], VALUE_SIZE);
        strValue.clear();
        return 1;
    }

    // Set param command with a string value: the first NUL byte must be the
    // last byte of the command. Serialized params (data type 0x02) and any
    // other data type are not commands.
    if (data[0] != SET_STRING_PARAM_DATA_TYPE ||
        size < SET_STRING_PARAM_MIN_SIZE)
    {
        return -1;
    }
    const size_t length = static_cast<size_t>(size - SET_STRING_PARAM_MIN_SIZE);
    if (std::memchr(&data[COMMAND_VALUE_POS], 0, length + 1) != &data[size - 1])
    {
        return -1;
    }

    // Copy the string before the output arguments are changed: an allocation
    // failure is reported as a decoding failure. The move assignment doesn't
    // throw.
    try
    {
        const char* begin =
                reinterpret_cast<const char*>(&data[COMMAND_VALUE_POS]);
        std::string text(begin, length);
        strValue = std::move(text);
    }
    catch (const std::bad_alloc&)
    {
        return -1;
    }
    paramId = static_cast<VStreamerParam>(id);
    value = 0.0f;
    return 2;
}



bool rapidpixel::VStreamer::decodeAndExecuteCommand(uint8_t* data, int size)
{
    // Decode command. The decoder checks the size, the version and the IDs.
    VStreamerParam paramId{VStreamerParam::MODE};
    VStreamerCommand commandId{VStreamerCommand::RESTART};
    float value{0.0f};
    std::string strValue;
    const int result =
            decodeCommand(data, size, paramId, commandId, value, strValue);

    // Execute the decoded command.
    if (result == 0)
    {
        return executeCommand(commandId);
    }
    if (result == 1)
    {
        return setParam(paramId, value);
    }
    if (result == 2)
    {
        return setParam(paramId, std::move(strValue));
    }

    return false;
}
