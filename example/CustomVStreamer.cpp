#include "CustomVStreamer.h"
#include "CustomVStreamerVersion.h"
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <limits>
#include <mutex>
#include <new>
#include <string>
#include <utility>



namespace
{
using Param = rapidpixel::VStreamerParam;
using Params = rapidpixel::VStreamerParams;

/// Limit of float values which can be converted to int. 2^31 is exactly
/// representable as float, so (-LIMIT <= value < LIMIT) is the exact range
/// of int.
constexpr float INT_RANGE_LIMIT{2147483648.0f};
/// Maximum video stream width and height, pixels.
constexpr int MAX_FRAME_SIDE{8192};
/// Maximum port number.
constexpr int MAX_PORT{65535};
/// Maximum first port of the RTP/RTCP range: RTCP takes the next port.
constexpr int MAX_RTP_PORT_MIN{65534};
/// Maximum bitrate accepted by the example, kbps (100 Mbit/s).
constexpr int MAX_BITRATE_KBPS{100000};
/// Maximum GOP size.
constexpr int MAX_GOP{65535};
/// Maximum H264 profile: 2 - high.
constexpr int MAX_H264_PROFILE{2};
/// Minimum JPEG quality, percent.
constexpr int MIN_JPEG_QUALITY{1};
/// Maximum JPEG quality, percent.
constexpr int MAX_JPEG_QUALITY{100};
/// Maximum log level: 3 - file and terminal.
constexpr int MAX_LOG_LEVEL{3};
/// Maximum multicast TTL.
constexpr int MAX_MULTICAST_TTL{255};
/// Maximum UDP payload over IPv4, bytes: 65535 - 20 (IP header) - 8 (UDP
/// header).
constexpr int MAX_PAYLOAD_SIZE{65507};
/// Maximum type of the streamer: the example has one type only.
constexpr int MAX_STREAMER_TYPE{0};
/// Maximum FPS accepted by the example.
constexpr float MAX_FPS{1000.0f};
/// Maximum length of a text param (path, address, name), characters.
constexpr size_t MAX_TEXT_LENGTH{4096};
/// First character code which is not a control character.
constexpr unsigned char FIRST_PRINTABLE_CODE{0x20};
/// Code of DEL control character.
constexpr unsigned char DEL_CODE{0x7F};

/// Codec types.
constexpr const char* CODECS[]{"H264", "HEVC", "JPEG"};
/// RTSP and RTMP encryption types.
constexpr const char* ENCRYPTION_TYPES[]{"", "no", "strict", "optional"};
/// WebRTC and HLS encryption types.
constexpr const char* ENCRYPTION_MODES[]{"", "no", "yes"};
/// Types of the direct and server-delivered streams supported by the example.
constexpr const char* STREAM_TYPES[]{"rtp", "mpegts"};
/// Security profiles supported by the example: the default one only. Any
/// other value is rejected (never mapped to the default).
constexpr const char* SECURITY_PROFILES[]{"", "no"};



/// Boolean param: field. The param accepts 0 and 1.
struct FlagParam
{
    /// Param ID.
    Param id{Param::MODE};
    /// Field of VStreamerParams.
    bool Params::* field{nullptr};
};



/// Integer param: field and valid range.
struct IntParam
{
    /// Param ID.
    Param id{Param::WIDTH};
    /// Field of VStreamerParams.
    int Params::* field{nullptr};
    /// Minimum valid value.
    int minValue{0};
    /// Maximum valid value.
    int maxValue{0};
};



/// Float param: field and valid range.
struct FloatParam
{
    /// Param ID.
    Param id{Param::FPS};
    /// Field of VStreamerParams.
    float Params::* field{nullptr};
    /// Minimum valid value.
    float minValue{0.0f};
    /// Maximum valid value.
    float maxValue{0.0f};
};



/// Text param: field and valid values.
struct TextParam
{
    /// Param ID.
    Param id{Param::CODEC};
    /// Field of VStreamerParams.
    std::string Params::* field{nullptr};
    /// Valid values or nullptr if the param accepts any valid text.
    const char* const* values{nullptr};
    /// Number of valid values.
    size_t valuesNumber{0};
};



/// Boolean params.
constexpr FlagParam FLAG_PARAMS[]{
    {Param::MODE, &Params::enable},
    {Param::RTSP_MODE, &Params::rtspEnable},
    {Param::DIRECT_STREAM_ENABLE, &Params::directStreamEnable},
    {Param::WEBRTC_MODE, &Params::webRtcEnable},
    {Param::HLS_MODE, &Params::hlsEnable},
    {Param::SRT_MODE, &Params::srtEnable},
    {Param::RTMP_MODE, &Params::rtmpEnable},
    {Param::METADATA_MODE, &Params::metadataEnable},
    {Param::OVERLAY_MODE, &Params::overlayEnable}};

/// Integer params. CYCLE_TIME_USEC is not here: it is calculated by the video
/// streamer and can't be set.
constexpr IntParam INT_PARAMS[]{
    {Param::WIDTH, &Params::width, 0, MAX_FRAME_SIDE},
    {Param::HEIGHT, &Params::height, 0, MAX_FRAME_SIDE},
    {Param::RTSP_PORT, &Params::rtspPort, 0, MAX_PORT},
    {Param::RTSPS_PORT, &Params::rtspsPort, 0, MAX_PORT},
    {Param::DIRECT_STREAM_PORT, &Params::directStreamPort, 0, MAX_PORT},
    {Param::WEBRTC_PORT, &Params::webRtcPort, 0, MAX_PORT},
    {Param::HLS_PORT, &Params::hlsPort, 0, MAX_PORT},
    {Param::SRT_PORT, &Params::srtPort, 0, MAX_PORT},
    {Param::RTMP_PORT, &Params::rtmpPort, 0, MAX_PORT},
    {Param::RTMPS_PORT, &Params::rtmpsPort, 0, MAX_PORT},
    {Param::METADATA_PORT, &Params::metadataPort, 0, MAX_PORT},
    {Param::RTSP_MULTICAST_PORT, &Params::rtspMulticastPort, 0, MAX_PORT},
    {Param::MIN_BITRATE_KBPS, &Params::minBitrateKbps, 0, MAX_BITRATE_KBPS},
    {Param::MAX_BITRATE_KBPS, &Params::maxBitrateKbps, 0, MAX_BITRATE_KBPS},
    {Param::BITRATE_KBPS, &Params::bitrateKbps, 0, MAX_BITRATE_KBPS},
    {Param::BITRATE_MODE, &Params::bitrateMode, 0, 1},
    {Param::GOP, &Params::gop, 1, MAX_GOP},
    {Param::H264_PROFILE, &Params::h264Profile, 0, MAX_H264_PROFILE},
    {Param::JPEG_QUALITY, &Params::jpegQuality,
     MIN_JPEG_QUALITY, MAX_JPEG_QUALITY},
    {Param::FIT_MODE, &Params::fitMode, 0, 1},
    {Param::TYPE, &Params::type, 0, MAX_STREAMER_TYPE},
    {Param::LOG_LEVEL, &Params::logLevel, 0, MAX_LOG_LEVEL},
    {Param::DIRECT_STREAM_BITRATE_KBPS, &Params::directStreamBitrateKbps,
     0, MAX_BITRATE_KBPS},
    {Param::DIRECT_STREAM_MAX_PAYLOAD, &Params::directStreamMaxPayloadSize,
     1, MAX_PAYLOAD_SIZE},
    {Param::DIRECT_STREAM_PACING_MODE, &Params::directStreamPacingMode, 0, 1},
    {Param::MULTICAST_TTL, &Params::multicastTtl, 0, MAX_MULTICAST_TTL},
    {Param::RTP_PORT_MIN, &Params::rtpPortMin, 0, MAX_RTP_PORT_MIN},
    {Param::RTP_PORT_MAX, &Params::rtpPortMax, 0, MAX_PORT},
    {Param::WEBRTC_MEDIA_PORT, &Params::webRtcMediaPort, 0, MAX_PORT},
    {Param::SERVER_STREAM_MAX_PAYLOAD, &Params::serverStreamMaxPayloadSize,
     1, MAX_PAYLOAD_SIZE}};

/// Float params. Custom params accept any finite value.
constexpr FloatParam FLOAT_PARAMS[]{
    {Param::FPS, &Params::fps, 0.0f, MAX_FPS},
    {Param::CUSTOM1, &Params::custom1, std::numeric_limits<float>::lowest(),
     std::numeric_limits<float>::max()},
    {Param::CUSTOM2, &Params::custom2, std::numeric_limits<float>::lowest(),
     std::numeric_limits<float>::max()},
    {Param::CUSTOM3, &Params::custom3, std::numeric_limits<float>::lowest(),
     std::numeric_limits<float>::max()}};

/// Text params.
constexpr TextParam TEXT_PARAMS[]{
    {Param::DIRECT_STREAM_IP, &Params::directStreamIp, nullptr, 0},
    {Param::RTSP_MULTICAST_IP, &Params::rtspMulticastIp, nullptr, 0},
    {Param::USER, &Params::user, nullptr, 0},
    {Param::PASSWORD, &Params::password, nullptr, 0},
    {Param::SUFFIX, &Params::suffix, nullptr, 0},
    {Param::METADATA_SUFFIX, &Params::metadataSuffix, nullptr, 0},
    {Param::CODEC, &Params::codec, CODECS, std::size(CODECS)},
    {Param::RTSP_KEY, &Params::rtspKey, nullptr, 0},
    {Param::RTSP_CERT, &Params::rtspCert, nullptr, 0},
    {Param::WEBRTC_KEY, &Params::webRtcKey, nullptr, 0},
    {Param::WEBRTC_CERT, &Params::webRtcCert, nullptr, 0},
    {Param::HLS_KEY, &Params::hlsKey, nullptr, 0},
    {Param::HLS_CERT, &Params::hlsCert, nullptr, 0},
    {Param::RTMP_KEY, &Params::rtmpKey, nullptr, 0},
    {Param::RTMP_CERT, &Params::rtmpCert, nullptr, 0},
    {Param::RTSP_ENCRYPTION, &Params::rtspEncryption,
     ENCRYPTION_TYPES, std::size(ENCRYPTION_TYPES)},
    {Param::WEBRTC_ENCRYPTION, &Params::webRtcEncryption,
     ENCRYPTION_MODES, std::size(ENCRYPTION_MODES)},
    {Param::RTMP_ENCRYPTION, &Params::rtmpEncryption,
     ENCRYPTION_TYPES, std::size(ENCRYPTION_TYPES)},
    {Param::HLS_ENCRYPTION, &Params::hlsEncryption,
     ENCRYPTION_MODES, std::size(ENCRYPTION_MODES)},
    {Param::DIRECT_STREAM_TYPE, &Params::directStreamType,
     STREAM_TYPES, std::size(STREAM_TYPES)},
    {Param::SERVER_STREAM_TYPE, &Params::serverStreamType,
     STREAM_TYPES, std::size(STREAM_TYPES)},
    {Param::SECURITY_PROFILE, &Params::securityProfile,
     SECURITY_PROFILES, std::size(SECURITY_PROFILES)},
    {Param::PUBLIC_ADDRESS, &Params::publicAddress, nullptr, 0},
    {Param::BIND_ADDRESS, &Params::bindAddress, nullptr, 0},
    {Param::CORS_ALLOWED_ORIGIN, &Params::corsAllowedOrigin, nullptr, 0}};



/// Find the description of a param in a table. Return nullptr if the table
/// doesn't have the param.
template <class T, size_t N>
const T* findParam(const T (&table)[N], Param id)
{
    for (const T& param : table)
    {
        if (param.id == id)
        {
            return &param;
        }
    }
    return nullptr;
}



/// Convert float param value to int. A conversion of NaN or of a value outside
/// of the int range is undefined behavior, so such values are rejected. The
/// fractional part is dropped.
bool toInt(float value, int& result)
{
    // The comparison is false for NaN: NaN is rejected.
    if (!(value >= -INT_RANGE_LIMIT && value < INT_RANGE_LIMIT))
    {
        return false;
    }
    result = static_cast<int>(value);
    return true;
}



/// Check a float value: inside [minValue, maxValue]. NaN and infinity are
/// rejected (the comparisons are false for NaN).
bool isInRange(float value, float minValue, float maxValue)
{
    return value >= minValue && value <= maxValue;
}



/// Check a text value: the length is limited and control characters are not
/// accepted (the value can be written to a configuration file, a URL or the
/// command line of a media server).
bool isValidText(const std::string& value)
{
    if (value.size() > MAX_TEXT_LENGTH)
    {
        return false;
    }
    for (const char c : value)
    {
        const auto code = static_cast<unsigned char>(c);
        if (code < FIRST_PRINTABLE_CODE || code == DEL_CODE)
        {
            return false;
        }
    }
    return true;
}



/// Check a value of a text param: one of the valid values if the param has
/// a fixed set, any valid text if not.
bool isValidValue(const TextParam& param, const std::string& value)
{
    if (param.values == nullptr)
    {
        return isValidText(value);
    }
    for (size_t i = 0; i < param.valuesNumber; ++i)
    {
        if (value == param.values[i])
        {
            return true;
        }
    }
    return false;
}



/// Check all values of a params structure.
bool isValidParams(const Params& params)
{
    for (const IntParam& param : INT_PARAMS)
    {
        const int value = params.*param.field;
        if (value < param.minValue || value > param.maxValue)
        {
            return false;
        }
    }
    for (const FloatParam& param : FLOAT_PARAMS)
    {
        if (!isInRange(params.*param.field, param.minValue, param.maxValue))
        {
            return false;
        }
    }
    for (const TextParam& param : TEXT_PARAMS)
    {
        if (!isValidValue(param, params.*param.field))
        {
            return false;
        }
    }
    return true;
}



/// Set a boolean, integer or float param. The params are changed only if the
/// value is valid.
bool setNumber(Params& params, Param id, float value)
{
    int number{0};
    if (const FlagParam* param = findParam(FLAG_PARAMS, id))
    {
        if (!toInt(value, number) || number < 0 || number > 1)
        {
            return false;
        }
        params.*param->field = number == 1;
        return true;
    }
    if (const IntParam* param = findParam(INT_PARAMS, id))
    {
        if (!toInt(value, number) ||
            number < param->minValue || number > param->maxValue)
        {
            return false;
        }
        params.*param->field = number;
        return true;
    }
    if (const FloatParam* param = findParam(FLOAT_PARAMS, id))
    {
        if (!isInRange(value, param->minValue, param->maxValue))
        {
            return false;
        }
        params.*param->field = value;
        return true;
    }
    return false;
}



/// Set a text param. The params are changed only if the value is valid.
bool setText(Params& params, Param id, std::string&& value)
{
    const TextParam* param = findParam(TEXT_PARAMS, id);
    if (param == nullptr || !isValidValue(*param, value))
    {
        return false;
    }
    // The move assignment doesn't throw.
    params.*param->field = std::move(value);
    return true;
}
}



rapidpixel::CustomVStreamer::CustomVStreamer() = default;



rapidpixel::CustomVStreamer::~CustomVStreamer() = default;



std::string rapidpixel::CustomVStreamer::getVersion()
{
    return CUSTOM_VSTREAMER_VERSION;
}



bool rapidpixel::CustomVStreamer::initVStreamer(VStreamerParams& params,
                                                VCodec*,
                                                VOverlay*)
{
    // Check all values before anything is changed.
    if (!isValidParams(params))
    {
        return false;
    }

    // Copy params outside of the lock. An allocation failure is reported as
    // an initialization failure.
    VStreamerParams newParams;
    try
    {
        newParams = params;
    }
    catch (const std::bad_alloc&)
    {
        return false;
    }
    // Cycle time is calculated by the video streamer.
    newParams.cycleTimeUs = 0;

    const std::lock_guard<std::mutex> lock(m_mutex);
    m_params = std::move(newParams);
    m_isInit = true;
    return true;
}



bool rapidpixel::CustomVStreamer::isVStreamerInit()
{
    const std::lock_guard<std::mutex> lock(m_mutex);
    return m_isInit;
}



void rapidpixel::CustomVStreamer::closeVStreamer()
{
    const std::lock_guard<std::mutex> lock(m_mutex);
    m_isInit = false;
}



bool rapidpixel::CustomVStreamer::sendFrame(Frame& frame,
                                            uint8_t* userData,
                                            int userDataSize)
{
    // Check the frame and the user data: a size without data or a negative
    // size is an error.
    if (frame.data == nullptr || frame.size <= 0 || userDataSize < 0 ||
        (userData == nullptr && userDataSize != 0))
    {
        return false;
    }

    // The example doesn't send frames: a frame is accepted if the video
    // streamer is initialized and enabled.
    const std::lock_guard<std::mutex> lock(m_mutex);
    return m_isInit && m_params.enable;
}



bool rapidpixel::CustomVStreamer::setParam(VStreamerParam id, float value)
{
    const std::lock_guard<std::mutex> lock(m_mutex);
    return setNumber(m_params, id, value);
}



bool rapidpixel::CustomVStreamer::setParam(VStreamerParam id,
                                           std::string value)
{
    const std::lock_guard<std::mutex> lock(m_mutex);
    return setText(m_params, id, std::move(value));
}



void rapidpixel::CustomVStreamer::getParams(VStreamerParams& params)
{
    const std::lock_guard<std::mutex> lock(m_mutex);
    params = m_params;
}



bool rapidpixel::CustomVStreamer::executeCommand(VStreamerCommand id)
{
    const std::lock_guard<std::mutex> lock(m_mutex);
    switch (id)
    {
    case VStreamerCommand::RESTART:
        return m_isInit;
    case VStreamerCommand::ON:
        m_params.enable = true;
        return true;
    case VStreamerCommand::OFF:
        m_params.enable = false;
        return true;
    case VStreamerCommand::GENERATE_KEYFRAME:
        return m_isInit;
    default:
        return false;
    }
}
