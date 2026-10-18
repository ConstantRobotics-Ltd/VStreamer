#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include "VStreamer.h"
#include "VStreamerVersion.h"



namespace
{
using cr::video::VStreamer;
using cr::video::VStreamerCommand;
using cr::video::VStreamerParam;
using cr::video::VStreamerParams;
using cr::video::VStreamerParamsMask;

/// Size of the header of serialized params: data type, version and mask.
constexpr int HEADER_SIZE{13};
/// Position of the mask in serialized params.
constexpr int MASK_POS{3};
/// Number of VStreamerParams fields (bits of the mask).
constexpr int FIELDS_NUMBER{69};
/// Size of the test buffers, bytes.
constexpr int BUFFER_SIZE{8192};
/// Value of unused bytes of the test buffers.
constexpr uint8_t CANARY{0xA5};
/// Last action command ID.
constexpr int MAX_COMMAND_ID{4};
/// Last param ID.
constexpr int MAX_PARAM_ID{69};
/// Number of samples of the damaged data campaign.
constexpr int DAMAGED_SAMPLES{40000};
/// Name of the JSON file of the test. The file is removed by the test.
const char* const JSON_FILE_NAME{"TestVStreamerParams.json"};

/// State of the test random generator. The tests use own deterministic
/// generator: results must be reproducible on all platforms.
uint32_t g_randomState{20261017U};



/// Get next random number in [0, limit).
int randomInt(int limit)
{
    g_randomState = g_randomState * 1664525U + 1013904223U;
    return static_cast<int>((g_randomState >> 8) %
                            static_cast<uint32_t>(limit));
}



/// Get random 32 bits.
uint32_t randomBits()
{
    const auto low = static_cast<uint32_t>(randomInt(0x10000));
    const auto high = static_cast<uint32_t>(randomInt(0x10000));
    return (high << 16) | low;
}



/// Get bits of a float value.
uint32_t bitsOf(float value)
{
    uint32_t bits{0};
    std::memcpy(&bits, &value, sizeof(bits));
    return bits;
}



/// Get random value of a field.
void randomValue(bool& value, bool)
{
    value = randomInt(2) == 1;
}



/// Get random value of a field.
void randomValue(int& value, bool)
{
    const uint32_t bits = randomBits();
    std::memcpy(&value, &bits, sizeof(value));
}



/// Get random value of a field. A float for a JSON test must be finite: JSON
/// has no NaN and infinity.
void randomValue(float& value, bool printable)
{
    if (printable)
    {
        value = static_cast<float>(randomInt(2000000) - 1000000) / 64.0f;
        return;
    }
    const uint32_t bits = randomBits();
    std::memcpy(&value, &bits, sizeof(value));
}



/// Get random value of a field: random length, no NUL characters. A string
/// for a JSON test is printable ASCII.
void randomValue(std::string& value, bool printable)
{
    const int length = randomInt(8) == 0 ? randomInt(300) : randomInt(24);
    value.clear();
    for (int i = 0; i < length; ++i)
    {
        const int code = printable ? ' ' + randomInt(95) : 1 + randomInt(255);
        value.push_back(static_cast<char>(code));
    }
}



/// Call the visitor for every field of VStreamerParams in the order of the
/// mask bits of the serialized data: visit(name, field, mask flag).
template <class Visitor>
void forEachField(Visitor&& visit)
{
    using P = VStreamerParams;
    using M = VStreamerParamsMask;
    visit("enable", &P::enable, &M::enable);
    visit("width", &P::width, &M::width);
    visit("height", &P::height, &M::height);
    visit("directStreamIp", &P::directStreamIp, &M::directStreamIp);
    visit("rtspPort", &P::rtspPort, &M::rtspPort);
    visit("directStreamPort", &P::directStreamPort, &M::directStreamPort);
    visit("webRtcPort", &P::webRtcPort, &M::webRtcPort);
    visit("hlsPort", &P::hlsPort, &M::hlsPort);
    visit("srtPort", &P::srtPort, &M::srtPort);
    visit("rtmpPort", &P::rtmpPort, &M::rtmpPort);
    visit("metadataPort", &P::metadataPort, &M::metadataPort);
    visit("rtspEnable", &P::rtspEnable, &M::rtspEnable);
    visit("directStreamEnable", &P::directStreamEnable,
          &M::directStreamEnable);
    visit("webRtcEnable", &P::webRtcEnable, &M::webRtcEnable);
    visit("hlsEnable", &P::hlsEnable, &M::hlsEnable);
    visit("srtEnable", &P::srtEnable, &M::srtEnable);
    visit("rtmpEnable", &P::rtmpEnable, &M::rtmpEnable);
    visit("metadataEnable", &P::metadataEnable, &M::metadataEnable);
    visit("rtspMulticastIp", &P::rtspMulticastIp, &M::rtspMulticastIp);
    visit("rtspMulticastPort", &P::rtspMulticastPort, &M::rtspMulticastPort);
    visit("user", &P::user, &M::user);
    visit("password", &P::password, &M::password);
    visit("suffix", &P::suffix, &M::suffix);
    visit("metadataSuffix", &P::metadataSuffix, &M::metadataSuffix);
    visit("minBitrateKbps", &P::minBitrateKbps, &M::minBitrateKbps);
    visit("maxBitrateKbps", &P::maxBitrateKbps, &M::maxBitrateKbps);
    visit("bitrateKbps", &P::bitrateKbps, &M::bitrateKbps);
    visit("bitrateMode", &P::bitrateMode, &M::bitrateMode);
    visit("fps", &P::fps, &M::fps);
    visit("gop", &P::gop, &M::gop);
    visit("h264Profile", &P::h264Profile, &M::h264Profile);
    visit("jpegQuality", &P::jpegQuality, &M::jpegQuality);
    visit("codec", &P::codec, &M::codec);
    visit("fitMode", &P::fitMode, &M::fitMode);
    visit("cycleTimeUs", &P::cycleTimeUs, &M::cycleTimeUs);
    visit("overlayEnable", &P::overlayEnable, &M::overlayEnable);
    visit("type", &P::type, &M::type);
    visit("custom1", &P::custom1, &M::custom1);
    visit("custom2", &P::custom2, &M::custom2);
    visit("custom3", &P::custom3, &M::custom3);
    visit("rtspKey", &P::rtspKey, &M::rtspKey);
    visit("rtspCert", &P::rtspCert, &M::rtspCert);
    visit("webRtcKey", &P::webRtcKey, &M::webRtcKey);
    visit("webRtcCert", &P::webRtcCert, &M::webRtcCert);
    visit("hlsKey", &P::hlsKey, &M::hlsKey);
    visit("hlsCert", &P::hlsCert, &M::hlsCert);
    visit("rtmpKey", &P::rtmpKey, &M::rtmpKey);
    visit("rtmpCert", &P::rtmpCert, &M::rtmpCert);
    visit("rtspEncryption", &P::rtspEncryption, &M::rtspEncryption);
    visit("webRtcEncryption", &P::webRtcEncryption, &M::webRtcEncryption);
    visit("rtmpEncryption", &P::rtmpEncryption, &M::rtmpEncryption);
    visit("hlsEncryption", &P::hlsEncryption, &M::hlsEncryption);
    visit("logLevel", &P::logLevel, &M::logLevel);
    visit("rtspsPort", &P::rtspsPort, &M::rtspsPort);
    visit("rtmpsPort", &P::rtmpsPort, &M::rtmpsPort);
    visit("directStreamType", &P::directStreamType, &M::directStreamType);
    visit("directStreamBitrateKbps", &P::directStreamBitrateKbps,
          &M::directStreamBitrateKbps);
    visit("directStreamMaxPayloadSize", &P::directStreamMaxPayloadSize,
          &M::directStreamMaxPayloadSize);
    visit("directStreamPacingMode", &P::directStreamPacingMode,
          &M::directStreamPacingMode);
    visit("serverStreamType", &P::serverStreamType, &M::serverStreamType);
    visit("multicastTtl", &P::multicastTtl, &M::multicastTtl);
    visit("securityProfile", &P::securityProfile, &M::securityProfile);
    visit("publicAddress", &P::publicAddress, &M::publicAddress);
    visit("bindAddress", &P::bindAddress, &M::bindAddress);
    visit("rtpPortMin", &P::rtpPortMin, &M::rtpPortMin);
    visit("rtpPortMax", &P::rtpPortMax, &M::rtpPortMax);
    visit("webRtcMediaPort", &P::webRtcMediaPort, &M::webRtcMediaPort);
    visit("corsAllowedOrigin", &P::corsAllowedOrigin, &M::corsAllowedOrigin);
    visit("serverStreamMaxPayloadSize", &P::serverStreamMaxPayloadSize,
          &M::serverStreamMaxPayloadSize);
}



/// Check whether two values of a field are equal. Floats are compared by
/// their bits.
bool sameValue(bool a, bool b)
{
    return a == b;
}



/// Check whether two values of a field are equal.
bool sameValue(int a, int b)
{
    return a == b;
}



/// Check whether two values of a field are equal (by bits).
bool sameValue(float a, float b)
{
    return bitsOf(a) == bitsOf(b);
}



/// Check whether two values of a field are equal.
bool sameValue(const std::string& a, const std::string& b)
{
    return a == b;
}



/// Size of a serialized field, bytes.
int serializedSize(bool)
{
    return 1;
}



/// Size of a serialized field, bytes.
int serializedSize(int)
{
    return 4;
}



/// Size of a serialized field, bytes.
int serializedSize(float)
{
    return 4;
}



/// Size of a serialized field, bytes: characters and terminator.
int serializedSize(const std::string& value)
{
    return static_cast<int>(value.size()) + 1;
}



/// Fill params with random values.
void randomParams(VStreamerParams& params, bool printable)
{
    forEachField([&](const char*, auto field, bool VStreamerParamsMask::*)
    {
        randomValue(params.*field, printable);
    });
}



/// Fill mask with random flags. density: 0 - few flags, 1 - most flags,
/// 2 - half of the flags.
void randomMask(VStreamerParamsMask& mask)
{
    const int density = randomInt(3);
    forEachField([&](const char*, auto, bool VStreamerParamsMask::* flag)
    {
        const int value = randomInt(8);
        mask.*flag = density == 0 ? value == 0
                   : density == 1 ? value != 0
                   : value < 4;
    });
}



/// Mask with all flags cleared.
VStreamerParamsMask emptyMask()
{
    VStreamerParamsMask mask;
    forEachField([&](const char*, auto, bool VStreamerParamsMask::* flag)
    {
        mask.*flag = false;
    });
    return mask;
}



/// Compare params: a field selected by the mask must be equal to the input,
/// a field which is not selected must be zero (if zeroUnselected) or is not
/// compared. The names of wrong fields are printed.
bool compareParams(const VStreamerParams& in, const VStreamerParams& out,
                   const VStreamerParamsMask& mask, bool zeroUnselected)
{
    int errors{0};
    forEachField([&](const char* name, auto field,
                     bool VStreamerParamsMask::* flag)
    {
        using T = std::remove_reference_t<decltype(in.*field)>;
        const bool selected = mask.*flag;
        if (!selected && !zeroUnselected)
        {
            return;
        }
        const T expected = selected ? in.*field : T{};
        if (!sameValue(expected, out.*field))
        {
            std::cout << "Mismatch in field " << name << std::endl;
            ++errors;
        }
    });
    return errors == 0;
}



/// Compare all fields of two params objects.
bool sameParams(const VStreamerParams& a, const VStreamerParams& b)
{
    return compareParams(a, b, VStreamerParamsMask{}, true);
}



/// Expected size of serialized params if every selected field fits.
int expectedSize(const VStreamerParams& params,
                 const VStreamerParamsMask& mask)
{
    int size{HEADER_SIZE};
    forEachField([&](const char*, auto field, bool VStreamerParamsMask::* flag)
    {
        if (mask.*flag)
        {
            size += serializedSize(params.*field);
        }
    });
    return size;
}



/// Print a failed check and return false.
bool fail(const std::string& message)
{
    std::cout << message << std::endl;
    return false;
}



/// Run one test and print the result.
bool runTest(const char* title, bool (*test)())
{
    std::cout << title << ":" << std::endl;
    const bool passed = test();
    std::cout << (passed ? "OK" : "ERROR") << std::endl << std::endl;
    return passed;
}



/// Removes a file of the test when it goes out of scope and reports a failed
/// removal.
class FileRemover
{
public:
    /// Constructor. Removes a file left by an earlier run.
    explicit FileRemover(const char* fileName) : m_fileName(fileName)
    {
        static_cast<void>(std::remove(m_fileName));
    }

    /// Destructor. Removes the file.
    ~FileRemover()
    {
        if (std::remove(m_fileName) != 0)
        {
            std::cout << "Can't remove file " << m_fileName << std::endl;
        }
    }

    FileRemover(const FileRemover&) = delete;
    FileRemover(FileRemover&&) = delete;
    FileRemover& operator=(const FileRemover&) = delete;
    FileRemover& operator=(FileRemover&&) = delete;

private:
    /// Name of the file.
    const char* m_fileName{nullptr};
};



/// Video streamer which records the calls of decodeAndExecuteCommand(...).
class RecordingStreamer : public VStreamer
{
public:
    /// Last called method: 0 - none, 1 - executeCommand, 2 - setParam with
    /// a float value, 3 - setParam with a string value.
    int call{0};
    /// Arguments of the last call.
    VStreamerCommand commandId{VStreamerCommand::RESTART};
    VStreamerParam paramId{VStreamerParam::MODE};
    float value{0.0f};
    std::string strValue;

    bool initVStreamer(VStreamerParams&, cr::video::VCodec*,
                       cr::video::VOverlay*) override
    {
        return true;
    }

    bool isVStreamerInit() override
    {
        return true;
    }

    void closeVStreamer() override
    {
    }

    bool sendFrame(cr::video::Frame&, uint8_t*, int) override
    {
        return true;
    }

    bool setParam(VStreamerParam id, float newValue) override
    {
        call = 2;
        paramId = id;
        value = newValue;
        return true;
    }

    bool setParam(VStreamerParam id, std::string newValue) override
    {
        call = 3;
        paramId = id;
        strValue = newValue;
        return true;
    }

    void getParams(VStreamerParams&) override
    {
    }

    bool executeCommand(VStreamerCommand id) override
    {
        call = 1;
        commandId = id;
        return true;
    }
};



bool copyTest()
{
    VStreamerParams in;
    randomParams(in, false);

    // Copy constructor.
    const VStreamerParams copy = in;
    if (!sameParams(in, copy))
    {
        return fail("Copy constructor");
    }

    // Copy assignment.
    VStreamerParams assigned;
    assigned = in;
    if (!sameParams(in, assigned))
    {
        return fail("Copy assignment");
    }
    return true;
}



bool roundTripTest()
{
    std::vector<uint8_t> data(BUFFER_SIZE);
    for (int i = 0; i < 3000; ++i)
    {
        VStreamerParams in;
        randomParams(in, false);
        VStreamerParamsMask mask;
        const bool useMask = i % 3 != 0;
        if (useMask)
        {
            randomMask(mask);
        }

        // Serialize.
        int size{-1};
        if (!in.serialize(data.data(), BUFFER_SIZE, size,
                          useMask ? &mask : nullptr))
        {
            return fail("Params not serialized");
        }
        if (size != expectedSize(in, mask))
        {
            return fail("Wrong size " + std::to_string(size) + ", expected " +
                        std::to_string(expectedSize(in, mask)));
        }

        // Check the mask bits: field i is bit (7 - i % 8) of mask byte i / 8.
        int index{0};
        bool maskOk{true};
        forEachField([&](const char*, auto, bool VStreamerParamsMask::* flag)
        {
            const int bit = 0x80 >> (index % 8);
            const int byte = MASK_POS + index / 8;
            const bool isSet = (data[static_cast<size_t>(byte)] & bit) != 0;
            maskOk = maskOk && isSet == mask.*flag;
            ++index;
        });
        if (!maskOk || data[11] % 8 != 0 || data[12] != 0)
        {
            return fail("Wrong mask");
        }

        // Deserialize into an object with other values.
        VStreamerParams out;
        randomParams(out, false);
        if (!out.deserialize(data.data(), size))
        {
            return fail("Params not deserialized");
        }
        if (!compareParams(in, out, mask, true))
        {
            return fail("Wrong deserialized params");
        }
    }

    // All fields with default values.
    VStreamerParams in;
    int size{0};
    VStreamerParams out;
    randomParams(out, false);
    if (!in.serialize(data.data(), BUFFER_SIZE, size) ||
        !out.deserialize(data.data(), size) || !sameParams(in, out))
    {
        return fail("Default params round trip");
    }
    std::cout << "Serialized size of default params: " << size << " bytes"
              << std::endl;
    return true;
}



bool emptyMaskTest()
{
    // Data with empty mask is the header only: it is valid and resets all
    // fields.
    VStreamerParams in;
    randomParams(in, false);
    VStreamerParamsMask mask = emptyMask();
    uint8_t data[64];
    int size{0};
    if (!in.serialize(data, sizeof(data), size, &mask) || size != HEADER_SIZE)
    {
        return fail("Empty mask not serialized");
    }
    VStreamerParams out;
    randomParams(out, false);
    if (!out.deserialize(data, size) || !compareParams(in, out, mask, true))
    {
        return fail("Empty mask not deserialized");
    }
    return true;
}



bool bufferBoundariesTest()
{
    VStreamerParams in;
    randomParams(in, false);
    std::vector<uint8_t> data(BUFFER_SIZE, CANARY);

    // nullptr and too small buffers: FALSE, size 0, nothing written.
    int size{99};
    if (in.serialize(nullptr, BUFFER_SIZE, size) || size != 0)
    {
        return fail("nullptr buffer accepted");
    }
    for (int bufferSize = -1; bufferSize < 14; ++bufferSize)
    {
        size = 99;
        if (in.serialize(data.data(), bufferSize, size) || size != 0)
        {
            return fail("Too small buffer accepted: " +
                        std::to_string(bufferSize));
        }
    }
    for (const uint8_t value : data)
    {
        if (value != CANARY)
        {
            return fail("Rejected call wrote to the buffer");
        }
    }

    // Exact size: the same data. Nothing is written after the data.
    std::vector<uint8_t> full(BUFFER_SIZE);
    int fullSize{0};
    in.serialize(full.data(), BUFFER_SIZE, fullSize);
    if (!in.serialize(data.data(), fullSize, size) || size != fullSize ||
        std::memcmp(data.data(), full.data(),
                    static_cast<size_t>(fullSize)) != 0)
    {
        return fail("Exact size buffer");
    }
    for (size_t i = static_cast<size_t>(fullSize); i < data.size(); ++i)
    {
        if (data[i] != CANARY)
        {
            return fail("Data written after the end");
        }
    }

    // Every smaller buffer: the fields which don't fit are skipped, the
    // result is valid and nothing is written after the buffer.
    for (int bufferSize = 14; bufferSize < fullSize; ++bufferSize)
    {
        std::fill(data.begin(), data.end(), CANARY);
        if (!in.serialize(data.data(), bufferSize, size) || size > bufferSize)
        {
            return fail("Smaller buffer: " + std::to_string(bufferSize));
        }
        for (size_t i = static_cast<size_t>(bufferSize); i < data.size(); ++i)
        {
            if (data[i] != CANARY)
            {
                return fail("Data written after the buffer");
            }
        }
        VStreamerParams out;
        if (!out.deserialize(data.data(), size))
        {
            return fail("Data of a smaller buffer not deserialized");
        }
    }

    // One byte less than needed: the last field is not serialized.
    VStreamerParamsMask mask = emptyMask();
    mask.enable = true;
    mask.serverStreamMaxPayloadSize = true;
    in.serialize(data.data(), BUFFER_SIZE, size, &mask);
    if (size != HEADER_SIZE + 1 + 4)
    {
        return fail("Wrong size of two fields");
    }
    if (!in.serialize(data.data(), size - 1, size, &mask) ||
        size != HEADER_SIZE + 1 || data[11] != 0)
    {
        return fail("Last field written to a too small buffer");
    }
    return true;
}



bool stringWithNulTest()
{
    // A string with a NUL character is not serialized: the receiver would
    // read the rest of the string as the next fields.
    VStreamerParams in;
    in.user = std::string("ab\0cd", 5);
    in.password = "secret";
    VStreamerParamsMask mask = emptyMask();
    mask.user = true;
    mask.password = true;
    uint8_t data[64];
    int size{0};
    if (!in.serialize(data, sizeof(data), size, &mask) ||
        size != HEADER_SIZE + 7)
    {
        return fail("Wrong size of data with a NUL character in a string");
    }
    VStreamerParams out;
    if (!out.deserialize(data, size) || !out.user.empty() ||
        out.password != "secret")
    {
        return fail("String with a NUL character serialized");
    }

    // Command with such a string is not encoded.
    size = 99;
    VStreamer::encodeSetParamCommand(data, size, VStreamerParam::USER,
                                     std::string("ab\0cd", 5));
    if (size != 0)
    {
        return fail("Command with a NUL character in a string encoded");
    }
    return true;
}



bool invalidDataTest()
{
    VStreamerParams in;
    randomParams(in, false);
    std::vector<uint8_t> valid(BUFFER_SIZE);
    int size{0};
    in.serialize(valid.data(), BUFFER_SIZE, size);
    valid.resize(static_cast<size_t>(size));

    VStreamerParams out;
    randomParams(out, false);
    const VStreamerParams before = out;

    // nullptr, negative and small sizes.
    if (out.deserialize(nullptr, size) || out.deserialize(valid.data(), -1) ||
        out.deserialize(valid.data(), 0) ||
        out.deserialize(valid.data(), HEADER_SIZE - 1))
    {
        return fail("nullptr or small size accepted");
    }

    // Every truncation.
    for (int cut = 0; cut < size; ++cut)
    {
        std::vector<uint8_t> data(valid.begin(), valid.begin() + cut);
        if (out.deserialize(data.data(), cut))
        {
            return fail("Truncated data accepted: " + std::to_string(cut));
        }
    }

    // Every value of the header bytes: data type, major and minor version.
    for (size_t pos = 0; pos < 3; ++pos)
    {
        for (int value = 0; value < 256; ++value)
        {
            std::vector<uint8_t> data = valid;
            if (data[pos] == value)
            {
                continue;
            }
            data[pos] = static_cast<uint8_t>(value);
            if (out.deserialize(data.data(), size))
            {
                return fail("Wrong header accepted");
            }
        }
    }

    // Mask bits of unknown fields.
    for (int bit = FIELDS_NUMBER; bit < 80; ++bit)
    {
        std::vector<uint8_t> data = valid;
        const int byte = MASK_POS + bit / 8;
        uint8_t& maskByte = data[static_cast<size_t>(byte)];
        maskByte = static_cast<uint8_t>(maskByte | (0x80 >> (bit % 8)));
        if (out.deserialize(data.data(), size))
        {
            return fail("Unknown mask bit accepted");
        }
    }

    // A string without terminator.
    {
        VStreamerParams text;
        VStreamerParamsMask mask = emptyMask();
        mask.codec = true;
        uint8_t data[64];
        text.serialize(data, sizeof(data), size, &mask);
        data[size - 1] = 'X';
        if (out.deserialize(data, size))
        {
            return fail("String without terminator accepted");
        }
    }
    if (!sameParams(before, out))
    {
        return fail("Rejected data changed the object");
    }

    // Trailing bytes are ignored.
    std::vector<uint8_t> longer = valid;
    longer.push_back(0x11);
    longer.push_back(0x22);
    if (!out.deserialize(longer.data(), static_cast<int>(longer.size())) ||
        !sameParams(in, out))
    {
        return fail("Trailing bytes");
    }

    // Any byte other than 0 of a bool field is true.
    VStreamerParamsMask mask = emptyMask();
    mask.enable = true;
    mask.metadataEnable = true;
    uint8_t data[64];
    in.serialize(data, sizeof(data), size, &mask);
    for (int value = 0; value < 256; ++value)
    {
        data[HEADER_SIZE] = static_cast<uint8_t>(value);
        data[HEADER_SIZE + 1] = static_cast<uint8_t>(255 - value);
        if (!out.deserialize(data, size) || out.enable != (value != 0) ||
            out.metadataEnable != (value != 255))
        {
            return fail("Wrong bool value");
        }
    }
    return true;
}



bool damagedDataTest()
{
    // Valid samples with random masks.
    std::vector<std::vector<uint8_t>> samples;
    std::vector<uint8_t> buffer(BUFFER_SIZE);
    for (int i = 0; i < 50; ++i)
    {
        VStreamerParams in;
        randomParams(in, false);
        VStreamerParamsMask mask;
        randomMask(mask);
        int size{0};
        in.serialize(buffer.data(), BUFFER_SIZE, size, &mask);
        samples.emplace_back(buffer.begin(), buffer.begin() + size);
    }

    // Damage the samples: random bytes, random size. The result must be
    // deterministic, and a rejected call must not change the object.
    const uint32_t seed = g_randomState;
    uint32_t results[2]{0, 0};
    for (uint32_t& result : results)
    {
        g_randomState = seed;
        for (int i = 0; i < DAMAGED_SAMPLES; ++i)
        {
            std::vector<uint8_t> data = samples[static_cast<size_t>(
                    randomInt(static_cast<int>(samples.size())))];
            const int changes = 1 + randomInt(4);
            for (int k = 0; k < changes; ++k)
            {
                data[static_cast<size_t>(randomInt(
                        static_cast<int>(data.size())))] =
                        static_cast<uint8_t>(randomInt(256));
            }
            data.resize(static_cast<size_t>(
                    randomInt(static_cast<int>(data.size()) + 8)));
            VStreamerParams out;
            const VStreamerParams before = out;
            const bool accepted = out.deserialize(
                    data.data(), static_cast<int>(data.size()));
            if (!accepted && !sameParams(before, out))
            {
                return fail("Rejected damaged data changed the object");
            }
            result = result * 31U + (accepted ? 1U : 0U);
        }
    }
    if (results[0] != results[1])
    {
        return fail("Damaged data results are not deterministic");
    }
    std::cout << DAMAGED_SAMPLES << " damaged samples checked" << std::endl;
    return true;
}



bool commandsTest()
{
    uint8_t data[512];
    int size{0};
    VStreamerParam paramId{VStreamerParam::MODE};
    VStreamerCommand commandId{VStreamerCommand::RESTART};
    float value{0.0f};
    std::string strValue;

    // Every action command.
    for (int id = 1; id <= MAX_COMMAND_ID; ++id)
    {
        VStreamer::encodeCommand(data, size, static_cast<VStreamerCommand>(id));
        if (size != 7 ||
            VStreamer::decodeCommand(data, size, paramId, commandId, value,
                                     strValue) != 0 ||
            commandId != static_cast<VStreamerCommand>(id))
        {
            return fail("Command " + std::to_string(id));
        }
    }

    // Every param with a float and a string value.
    for (int id = 1; id <= MAX_PARAM_ID; ++id)
    {
        const auto param = static_cast<VStreamerParam>(id);
        float outValue{0.0f};
        randomValue(outValue, false);
        VStreamer::encodeSetParamCommand(data, size, param, outValue);
        if (size != 11 ||
            VStreamer::decodeCommand(data, size, paramId, commandId, value,
                                     strValue) != 1 ||
            paramId != param || !sameValue(value, outValue))
        {
            return fail("Float param " + std::to_string(id));
        }

        std::string outString;
        randomValue(outString, false);
        if (outString.size() > 400)
        {
            outString.resize(400);
        }
        VStreamer::encodeSetParamCommand(data, size, param, outString);
        if (size != 8 + static_cast<int>(outString.size()) ||
            VStreamer::decodeCommand(data, size, paramId, commandId, value,
                                     strValue) != 2 ||
            paramId != param || strValue != outString)
        {
            return fail("String param " + std::to_string(id));
        }
    }

    // nullptr buffers.
    size = 99;
    VStreamer::encodeCommand(nullptr, size, VStreamerCommand::RESTART);
    if (size != 0)
    {
        return fail("encodeCommand(nullptr)");
    }
    size = 99;
    VStreamer::encodeSetParamCommand(nullptr, size, VStreamerParam::FPS, 1.0f);
    if (size != 0)
    {
        return fail("encodeSetParamCommand(nullptr, float)");
    }
    size = 99;
    VStreamer::encodeSetParamCommand(nullptr, size, VStreamerParam::CODEC,
                                     std::string("H264"));
    if (size != 0)
    {
        return fail("encodeSetParamCommand(nullptr, string)");
    }

    // Invalid commands: the output arguments are not changed.
    uint8_t command[16];
    int commandSize{0};
    VStreamer::encodeCommand(command, commandSize, VStreamerCommand::OFF);
    uint8_t setParam[16];
    int setParamSize{0};
    VStreamer::encodeSetParamCommand(setParam, setParamSize,
                                     VStreamerParam::GOP, 25.0f);
    uint8_t setString[16];
    int setStringSize{0};
    VStreamer::encodeSetParamCommand(setString, setStringSize,
                                     VStreamerParam::CODEC,
                                     std::string("HEVC"));
    std::vector<std::vector<uint8_t>> invalid;
    // Wrong sizes.
    for (int n = 0; n < 16; ++n)
    {
        if (n != commandSize)
        {
            invalid.emplace_back(command, command + n);
        }
        if (n != setParamSize)
        {
            invalid.emplace_back(setParam, setParam + n);
        }
    }
    // String: no terminator, bytes after the terminator.
    invalid.emplace_back(setString, setString + setStringSize - 1);
    {
        std::vector<uint8_t> longer(setString, setString + setStringSize);
        longer.push_back('X');
        invalid.push_back(longer);
    }
    // Wrong version and data type.
    for (const auto* source : {command, setParam, setString})
    {
        const int sourceSize = source == command ? commandSize
                             : source == setParam ? setParamSize
                             : setStringSize;
        for (size_t pos = 0; pos < 3; ++pos)
        {
            for (int v = 0; v < 256; ++v)
            {
                std::vector<uint8_t> d(source, source + sourceSize);
                if (d[pos] == v || (pos == 0 && v <= 3 && v != 2))
                {
                    continue;
                }
                d[pos] = static_cast<uint8_t>(v);
                invalid.push_back(d);
            }
        }
    }
    // Unknown IDs.
    for (const int id : {0, -1, MAX_PARAM_ID + 1, 1000, INT32_MIN, INT32_MAX})
    {
        for (const auto* source : {command, setParam, setString})
        {
            const int sourceSize = source == command ? commandSize
                                 : source == setParam ? setParamSize
                                 : setStringSize;
            std::vector<uint8_t> d(source, source + sourceSize);
            std::memcpy(&d[3], &id, sizeof(id));
            invalid.push_back(d);
        }
    }
    {
        const int id{MAX_COMMAND_ID + 1};
        std::vector<uint8_t> d(command, command + commandSize);
        std::memcpy(&d[3], &id, sizeof(id));
        invalid.push_back(d);
    }
    // Serialized params are not a command.
    {
        VStreamerParams params;
        std::vector<uint8_t> d(BUFFER_SIZE);
        int n{0};
        params.serialize(d.data(), BUFFER_SIZE, n);
        d.resize(static_cast<size_t>(n));
        invalid.push_back(d);
    }
    for (std::vector<uint8_t>& d : invalid)
    {
        paramId = VStreamerParam::HEIGHT;
        commandId = VStreamerCommand::ON;
        value = 7.5f;
        strValue = "unchanged";
        if (VStreamer::decodeCommand(d.empty() ? nullptr : d.data(),
                                     static_cast<int>(d.size()), paramId,
                                     commandId, value, strValue) != -1)
        {
            return fail("Invalid command accepted");
        }
        if (paramId != VStreamerParam::HEIGHT ||
            commandId != VStreamerCommand::ON || !sameValue(value, 7.5f) ||
            strValue != "unchanged")
        {
            return fail("Invalid command changed the output arguments");
        }
    }
    if (VStreamer::decodeCommand(nullptr, 11, paramId, commandId, value,
                                 strValue) != -1)
    {
        return fail("decodeCommand(nullptr)");
    }
    std::cout << invalid.size() << " invalid commands checked" << std::endl;

    // decodeAndExecuteCommand(...) calls the right method.
    RecordingStreamer streamer;
    if (!streamer.decodeAndExecuteCommand(command, commandSize) ||
        streamer.call != 1 || streamer.commandId != VStreamerCommand::OFF)
    {
        return fail("decodeAndExecuteCommand: command");
    }
    if (!streamer.decodeAndExecuteCommand(setParam, setParamSize) ||
        streamer.call != 2 || streamer.paramId != VStreamerParam::GOP ||
        !sameValue(streamer.value, 25.0f))
    {
        return fail("decodeAndExecuteCommand: float param");
    }
    if (!streamer.decodeAndExecuteCommand(setString, setStringSize) ||
        streamer.call != 3 || streamer.paramId != VStreamerParam::CODEC ||
        streamer.strValue != "HEVC")
    {
        return fail("decodeAndExecuteCommand: string param");
    }
    streamer.call = 0;
    if (streamer.decodeAndExecuteCommand(invalid[0].data(),
                                         static_cast<int>(invalid[0].size())) ||
        streamer.decodeAndExecuteCommand(nullptr, 7) || streamer.call != 0)
    {
        return fail("decodeAndExecuteCommand: invalid command executed");
    }
    return true;
}



bool versionTest()
{
    const std::string expected = std::to_string(VSTREAMER_MAJOR_VERSION) +
                                 "." +
                                 std::to_string(VSTREAMER_MINOR_VERSION) +
                                 "." +
                                 std::to_string(VSTREAMER_PATCH_VERSION);
    std::cout << "VStreamer class version: " << VStreamer::getVersion()
              << std::endl;
    if (VStreamer::getVersion() != expected ||
        expected != VSTREAMER_VERSION)
    {
        return fail("Wrong version string");
    }
    return true;
}



bool jsonTest()
{
    const FileRemover remover(JSON_FILE_NAME);
    for (int i = 0; i < 100; ++i)
    {
        VStreamerParams in;
        randomParams(in, true);

        // File round trip.
        cr::utils::ConfigReader inConfig;
        if (!inConfig.set(in, "vStreamerParams") ||
            !inConfig.writeToFile(JSON_FILE_NAME))
        {
            return fail("Can't write params to file");
        }
        cr::utils::ConfigReader outConfig;
        VStreamerParams out;
        if (!outConfig.readFromFile(JSON_FILE_NAME) ||
            !outConfig.get(out, "vStreamerParams"))
        {
            return fail("Can't read params from file");
        }
        if (!sameParams(in, out))
        {
            return fail("Wrong params from file");
        }

        // String round trip.
        std::string json;
        VStreamerParams fromString;
        cr::utils::ConfigReader stringConfig;
        if (!inConfig.writeToString(json) ||
            !stringConfig.readFromString(json) ||
            !stringConfig.get(fromString, "vStreamerParams") ||
            !sameParams(in, fromString))
        {
            return fail("Wrong params from string");
        }
    }

    // Invalid documents: rejected, the object is not changed.
    VStreamerParams in;
    cr::utils::ConfigReader config;
    std::string json;
    config.set(in, "vStreamerParams");
    config.writeToString(json);
    const size_t widthPos = json.find("\"width\"");
    const size_t widthEnd = json.find(',', widthPos);
    std::string missingKey = json;
    missingKey.erase(widthPos, widthEnd - widthPos + 1);
    std::string wrongType = json;
    wrongType.replace(widthPos, widthEnd - widthPos, "\"width\":\"wide\"");
    std::string outOfRange = json;
    outOfRange.replace(widthPos, widthEnd - widthPos, "\"width\":1e20");
    const std::string documents[]{missingKey, wrongType, outOfRange,
                                  json.substr(0, json.size() / 2),
                                  "{\"vStreamerParams\":[]}",
                                  std::string(100000, '['), ""};
    for (const std::string& document : documents)
    {
        VStreamerParams out;
        randomParams(out, true);
        const VStreamerParams before = out;
        cr::utils::ConfigReader reader;
        if (reader.readFromString(document) &&
            reader.get(out, "vStreamerParams"))
        {
            return fail("Invalid JSON accepted");
        }
        if (!sameParams(before, out))
        {
            return fail("Invalid JSON changed the object");
        }
    }
    return true;
}
}



int main()
{
    std::cout << "#####################################" << std::endl;
    std::cout << "#                                   #" << std::endl;
    std::cout << "# VStreamerParams test              #" << std::endl;
    std::cout << "#                                   #" << std::endl;
    std::cout << "#####################################" << std::endl;
    std::cout << std::endl;

    int failed{0};
    failed += runTest("Copy test", copyTest) ? 0 : 1;
    failed += runTest("Serialize/Deserialize round trip test",
                      roundTripTest) ? 0 : 1;
    failed += runTest("Empty mask test", emptyMaskTest) ? 0 : 1;
    failed += runTest("Buffer boundaries test", bufferBoundariesTest) ? 0 : 1;
    failed += runTest("String with NUL character test",
                      stringWithNulTest) ? 0 : 1;
    failed += runTest("Invalid data test", invalidDataTest) ? 0 : 1;
    failed += runTest("Damaged data test", damagedDataTest) ? 0 : 1;
    failed += runTest("Encode/Decode commands test", commandsTest) ? 0 : 1;
    failed += runTest("Version test", versionTest) ? 0 : 1;
    failed += runTest("JSON read/write test", jsonTest) ? 0 : 1;

    std::cout << (failed == 0 ? "All tests passed" :
                  std::to_string(failed) + " test(s) failed") << std::endl;
    return failed == 0 ? 0 : 1;
}
