#pragma once
#include "ConfigReader.h"
#include "VOverlay.h"
#include "VCodec.h"
#include <string>
#include <cstdint>



namespace cr
{
namespace video
{
/**
 * @brief VStreamer params mask structure.
 */
struct VStreamerParamsMask
{
    bool enable{true};
    bool width{true};
    bool height{true};
    bool directStreamIp{true};
    bool rtspPort{true};
    bool rtspsPort{true};
    bool directStreamPort{true};
    bool webRtcPort{true};
    bool hlsPort{true};
    bool srtPort{true};
    bool rtmpPort{true};
    bool rtmpsPort{true};
    bool metadataPort{true};
    bool rtspEnable{true};
    bool directStreamEnable{true};
    bool webRtcEnable{true};
    bool hlsEnable{true};
    bool srtEnable{true};
    bool rtmpEnable{true};
    bool metadataEnable{true};
    bool rtspMulticastIp{true};
    bool rtspMulticastPort{true};
    bool user{true};
    bool password{true};
    bool suffix{true};
    bool metadataSuffix{true};
    bool minBitrateKbps{true};
    bool maxBitrateKbps{true};
    bool bitrateKbps{true};
    bool bitrateMode{true};
    bool fps{true};
    bool gop{true};
    bool h264Profile{true};
    bool jpegQuality{true};
    bool codec{true};
    bool fitMode{true};
    bool cycleTimeUs{true};
    bool overlayEnable{true};
    bool type{true};
    bool custom1{true};
    bool custom2{true};
    bool custom3{true};
    bool rtspKey{true};
    bool rtspCert{true};
    bool webRtcKey{true};
    bool webRtcCert{true};
    bool hlsKey{true};
    bool hlsCert{true};
    bool rtmpKey{true};
    bool rtmpCert{true};
    bool rtspEncryption{true};
    bool webRtcEncryption{true};
    bool rtmpEncryption{true};
    bool hlsEncryption{true};
    bool logLevel{true};
    bool directStreamType{true};
    bool directStreamBitrateKbps{true};
    bool directStreamMaxPayloadSize{true};
    bool directStreamPacingMode{true};
    bool serverStreamType{true};
    bool multicastTtl{true};
    bool securityProfile{true};
    bool publicAddress{true};
    bool bindAddress{true};
    bool rtpPortMin{true};
    bool rtpPortMax{true};
    bool webRtcMediaPort{true};
    bool corsAllowedOrigin{true};
    bool serverStreamMaxPayloadSize{true};
};

/**
 * @brief VStreamer params class.
 */
class VStreamerParams
{
public:
    /// Mode, boolean: false - disabled, true - enabled.
    bool enable{true};
    /// Video stream width, integer [0:8192].
    int width{1280};
    /// Video stream height, integer [0:8192].
    int height{720};
    /// Destination IP of the direct stream (point-to-point, bypasses
    /// MediaMTX), string. Transport is set by directStreamType.
    std::string directStreamIp{"127.0.0.1"};
    /// RTSP port, integer [0:65535].
    int rtspPort{8554};
    /// RTSPS port, integer [0:65535].
    int rtspsPort{8555};
    /// Destination port of the direct stream, integer [0:65535].
    int directStreamPort{5004};
    /// WebRTC port, integer [0:65535].
    int webRtcPort{7000};
    /// HLS port, integer [0:65535].
    int hlsPort{8080};
    /// SRT port, integer [0:65535].
    int srtPort{6000};
    /// RTMP port, integer [0:65535].
    int rtmpPort{1935};
    /// RTMPS port, integer [0:65535].
    int rtmpsPort{1936};
    /// Metadata port, integer [0:65535].
    int metadataPort{9000};
    /// RTSP protocol enable / disable, boolean: false - disable, true - enable.
    bool rtspEnable{true};
    /// Direct stream (point-to-point, bypasses MediaMTX) enable / disable,
    /// boolean: false - disable, true - enable. Uses directStreamIp /
    /// directStreamPort and the directStream* parameters.
    bool directStreamEnable{true};
    /// WebRTC protocol enable / disable, boolean: false - disable, true - enable.
    bool webRtcEnable{true};
    /// HLS protocol enable / disable, boolean: false - disable, true - enable.
    bool hlsEnable{true};
    /// SRT protocol enable / disable, boolean: false - disable, true - enable.
    bool srtEnable{true};
    /// RTMP protocol enable / disable, boolean: false - disable, true - enable.
    bool rtmpEnable{true};
    /// Metadata protocol enable / disable, boolean: false - disable, true - enable.
    bool metadataEnable{false};
    /// RTSP multicast IP, string.
    std::string rtspMulticastIp{"224.1.0.1/16"};
    /// RTSP multicast port, integer [0:65535].
    int rtspMulticastPort{18000};
    /// Streamer user (for RTSP streaming), string: "" or "no" - no user.
    std::string user{"no"};
    /// Streamer password (for RTSP streaming), string: "" or "no" - no password.
    std::string password{"no"};
    /// Streamer suffix for RTSP streaming (stream name), string: "" - no suffix.
    std::string suffix{"live"};
    /// Metadata suffix (stream name), string: "" - no suffix.
    std::string metadataSuffix{"metadata"};
    /// Minimum bitrate for variable bitrate mode, integer kbps.
    int minBitrateKbps{1000};
    /// Maximum bitrate for variable bitrate mode, integer kbps.
    int maxBitrateKbps{5000};
    /// Current bitrate, integer kbps.
    int bitrateKbps{3000};
    /// Bitrate mode, integer: 0 - constant bitrate, 1 - variable bitrate.
    int bitrateMode{0};
    /// FPS, float.
    float fps{30.0f};
    /// GOP size for H264 and H265 codecs, integer [1:65535].
    int gop{30};
    /// H264 profile, integer: 0 - baseline, 1 - main, 2 - high.
    int h264Profile{0};
    /// JPEG quality, integer: [1:100]% for JPEG codec.
    int jpegQuality{80};
    /// Codec type, string: "H264", "HEVC" or "JPEG".
    std::string codec{"H264"};
    /// Scaling mode, integer: 0 - fit, 1 - fill.
    int fitMode{0};
    /// Cycle time, integer μsec (microseconds). Calculated by video streamer.
    int cycleTimeUs{0};
    /// Overlay mode, boolean: false - off, true - on.
    bool overlayEnable{true};
    /// Type of the streamer, integer. Depends on implementation.
    int type{0};
    /// Custom parameter 1, float.
    float custom1{0.0f};
    /// Custom parameter 2, float.
    float custom2{0.0f};
    /// Custom parameter 3, float.
    float custom3{0.0f};
    /// Path to openssl key for RTSP, string: "" or "no" - no key.
    std::string rtspKey{"no"};
    /// Path to openssl certificate for RTSP, string: "" or "no" - no certificate.
    std::string rtspCert{"no"};
    /// Path to openssl key for WebRTC, string: "" or "no" - no key.
    std::string webRtcKey{"no"};
    /// Path to openssl certificate for WebRTC, string: "" or "no" - no certificate.
    std::string webRtcCert{"no"};
    /// Path to openssl key for HLS, string: "" or "no" - no key.
    std::string hlsKey{"no"};
    /// Path to openssl certificate for HLS, string: "" or "no" - no certificate.
    std::string hlsCert{"no"};
    /// Path to openssl key for RTMP, string: "" or "no" - no key.
    std::string rtmpKey{"no"};
    /// Path to openssl certificate for RTMP, string: "" or "no" - no certificate.
    std::string rtmpCert{"no"};
    /// RTSP encryption type, string: "" or "no", "strict", "optional".
    std::string rtspEncryption{"no"};
    /// WebRTC encryption type, string: "" or "no", "yes".
    std::string webRtcEncryption{"no"};
    /// RTMP encryption type, string: "" or "no", "strict", "optional".
    std::string rtmpEncryption{"no"};
    /// HLS encryption type, string: "" or "no", "yes".
    std::string hlsEncryption{"no"};
    /// Logging mode. Values: 0 - Disable, 1 - Only file,
    /// 2 - Only terminal, 3 - File and terminal.
    int logLevel{0};
    /// Transport/type of the direct (point-to-point) stream. String whose
    /// accepted values are IMPLEMENTATION-DEFINED — each concrete VStreamer
    /// decides the set and what each value means, including whether KLV
    /// metadata is carried (no separate flag). Examples: "rtp", "mpegts".
    std::string directStreamType{"rtp"};
    /// Target sending bitrate for the direct stream, integer kbps.
    int directStreamBitrateKbps{5000};
    /// Maximum UDP/RTP payload size for the direct stream, integer bytes.
    int directStreamMaxPayloadSize{1472};
    /// Pacing mode of the direct stream, integer: 0 - target bitrate, 1 - push.
    int directStreamPacingMode{0};
    /// Transport/type of the server-delivered stream (fed to the media server,
    /// which fans it out to clients). String whose accepted values are
    /// IMPLEMENTATION-DEFINED — each concrete VStreamer decides the set and what
    /// each value means, including whether KLV metadata is carried (no separate
    /// flag). Examples: "rtp", "mpegts". Distinct from rtspEnable (protocol on/off).
    std::string serverStreamType{"rtp"};
    /// Multicast TTL (scope) for every multicast leg, integer [0:255]:
    /// 0 - implementation default. An implementation may cap the value and
    /// must document the cap. Applies to every leg that sends to a multicast
    /// group, not only the RTSP one.
    int multicastTtl{0};
    /// Security/compliance profile. String whose accepted values are
    /// IMPLEMENTATION-DEFINED, in the style of directStreamType: "" or "no" -
    /// the implementation's own default. An unrecognised value must be
    /// REJECTED by initVStreamer()/setParam(), never mapped to a default --
    /// silently downgrading a security posture is the failure this field
    /// exists to prevent.
    std::string securityProfile{"no"};
    /// Public (routed) address advertised to clients in SDP and ICE candidate
    /// lines instead of the locally detected one, string: "" or "no" - detect
    /// automatically. An address literal, NOT a hostname: it is written onto
    /// the wire verbatim. Needed behind 1:1 NAT, in containers, and on
    /// multi-homed hosts, where the detected address is unroutable for the
    /// viewer.
    std::string publicAddress{"no"};
    /// Local address every listener binds to, string: "" or "0.0.0.0" - every
    /// interface. A multi-homed host has no other way to keep a stream off an
    /// interface it must not appear on.
    std::string bindAddress{"0.0.0.0"};
    /// Lowest port of the RTP/RTCP range, integer [0:65534]: 0 - any ephemeral
    /// port. Should be even, because RTCP conventionally takes port+1.
    int rtpPortMin{0};
    /// Highest port of the RTP/RTCP range, integer [0:65535]: 0 - any
    /// ephemeral port. A firewall is configured for a range; without one an
    /// implementation picks ephemeral ports nothing has been opened for.
    int rtpPortMax{0};
    /// WebRTC media (UDP) port, integer [0:65535]: 0 - the implementation
    /// chooses. Distinct from webRtcPort, which carries signalling only.
    int webRtcMediaPort{0};
    /// Single origin permitted to reach the HTTP-based signalling endpoints,
    /// string "scheme://host[:port]": "" or "no" - the implementation's default
    /// policy. Deliberately one origin and not a wildcard list.
    std::string corsAllowedOrigin{"no"};
    /// Maximum RTP payload size of the server-delivered stream, integer bytes.
    /// The counterpart of directStreamMaxPayloadSize for the server leg. An
    /// implementation may clamp it lower: a transform applied after
    /// packetization (SRTP appends an authentication tag) can otherwise push
    /// the datagram past the path MTU.
    int serverStreamMaxPayloadSize{1472};

    /// JSON serialisation.
    ///
    /// Hand-written rather than JSON_READABLE(): that macro forwards to
    /// nlohmann's NLOHMANN_DEFINE_TYPE_INTRUSIVE, whose expansion is capped at
    /// 63 fields, and 3.2 takes the structure past it. Patching the vendored
    /// amalgamated nlohmann header instead would be undone by its next update.
    ///
    /// One deliberate difference from the macro: a key MISSING from the JSON
    /// leaves the field at its default instead of throwing. The macro's `.at()`
    /// meant a configuration file that did not list every single parameter
    /// failed to load at all -- so a file written for 3.1 could not be read by
    /// 3.2, which is precisely when a deployment needs it to be.
    template<typename J, typename T>
    static void get(const J& j, const char* key, T& out)
    {
        const auto it = j.find(key);
        if (it != j.end() && !it->is_null())
            it->template get_to(out);
    }

    friend void to_json(nlohmann::json& j, const VStreamerParams& p)
    {
        j["enable"] = p.enable;
        j["width"] = p.width;
        j["height"] = p.height;
        j["directStreamIp"] = p.directStreamIp;
        j["rtspPort"] = p.rtspPort;
        j["rtspsPort"] = p.rtspsPort;
        j["directStreamPort"] = p.directStreamPort;
        j["webRtcPort"] = p.webRtcPort;
        j["hlsPort"] = p.hlsPort;
        j["srtPort"] = p.srtPort;
        j["rtmpPort"] = p.rtmpPort;
        j["rtmpsPort"] = p.rtmpsPort;
        j["metadataPort"] = p.metadataPort;
        j["rtspEnable"] = p.rtspEnable;
        j["directStreamEnable"] = p.directStreamEnable;
        j["webRtcEnable"] = p.webRtcEnable;
        j["hlsEnable"] = p.hlsEnable;
        j["srtEnable"] = p.srtEnable;
        j["rtmpEnable"] = p.rtmpEnable;
        j["metadataEnable"] = p.metadataEnable;
        j["rtspMulticastIp"] = p.rtspMulticastIp;
        j["rtspMulticastPort"] = p.rtspMulticastPort;
        j["user"] = p.user;
        j["password"] = p.password;
        j["suffix"] = p.suffix;
        j["metadataSuffix"] = p.metadataSuffix;
        j["minBitrateKbps"] = p.minBitrateKbps;
        j["maxBitrateKbps"] = p.maxBitrateKbps;
        j["bitrateKbps"] = p.bitrateKbps;
        j["bitrateMode"] = p.bitrateMode;
        j["fps"] = p.fps;
        j["gop"] = p.gop;
        j["h264Profile"] = p.h264Profile;
        j["jpegQuality"] = p.jpegQuality;
        j["codec"] = p.codec;
        j["fitMode"] = p.fitMode;
        j["overlayEnable"] = p.overlayEnable;
        j["type"] = p.type;
        j["custom1"] = p.custom1;
        j["custom2"] = p.custom2;
        j["custom3"] = p.custom3;
        j["rtspKey"] = p.rtspKey;
        j["rtspCert"] = p.rtspCert;
        j["webRtcKey"] = p.webRtcKey;
        j["webRtcCert"] = p.webRtcCert;
        j["hlsKey"] = p.hlsKey;
        j["hlsCert"] = p.hlsCert;
        j["rtmpKey"] = p.rtmpKey;
        j["rtmpCert"] = p.rtmpCert;
        j["rtspEncryption"] = p.rtspEncryption;
        j["webRtcEncryption"] = p.webRtcEncryption;
        j["rtmpEncryption"] = p.rtmpEncryption;
        j["hlsEncryption"] = p.hlsEncryption;
        j["logLevel"] = p.logLevel;
        j["directStreamType"] = p.directStreamType;
        j["directStreamBitrateKbps"] = p.directStreamBitrateKbps;
        j["directStreamMaxPayloadSize"] = p.directStreamMaxPayloadSize;
        j["directStreamPacingMode"] = p.directStreamPacingMode;
        j["serverStreamType"] = p.serverStreamType;
        j["multicastTtl"] = p.multicastTtl;
        j["securityProfile"] = p.securityProfile;
        j["publicAddress"] = p.publicAddress;
        j["bindAddress"] = p.bindAddress;
        j["rtpPortMin"] = p.rtpPortMin;
        j["rtpPortMax"] = p.rtpPortMax;
        j["webRtcMediaPort"] = p.webRtcMediaPort;
        j["corsAllowedOrigin"] = p.corsAllowedOrigin;
        j["serverStreamMaxPayloadSize"] = p.serverStreamMaxPayloadSize;
    }

    friend void from_json(const nlohmann::json& j, VStreamerParams& p)
    {
        get(j, "enable", p.enable);
        get(j, "width", p.width);
        get(j, "height", p.height);
        get(j, "directStreamIp", p.directStreamIp);
        get(j, "rtspPort", p.rtspPort);
        get(j, "rtspsPort", p.rtspsPort);
        get(j, "directStreamPort", p.directStreamPort);
        get(j, "webRtcPort", p.webRtcPort);
        get(j, "hlsPort", p.hlsPort);
        get(j, "srtPort", p.srtPort);
        get(j, "rtmpPort", p.rtmpPort);
        get(j, "rtmpsPort", p.rtmpsPort);
        get(j, "metadataPort", p.metadataPort);
        get(j, "rtspEnable", p.rtspEnable);
        get(j, "directStreamEnable", p.directStreamEnable);
        get(j, "webRtcEnable", p.webRtcEnable);
        get(j, "hlsEnable", p.hlsEnable);
        get(j, "srtEnable", p.srtEnable);
        get(j, "rtmpEnable", p.rtmpEnable);
        get(j, "metadataEnable", p.metadataEnable);
        get(j, "rtspMulticastIp", p.rtspMulticastIp);
        get(j, "rtspMulticastPort", p.rtspMulticastPort);
        get(j, "user", p.user);
        get(j, "password", p.password);
        get(j, "suffix", p.suffix);
        get(j, "metadataSuffix", p.metadataSuffix);
        get(j, "minBitrateKbps", p.minBitrateKbps);
        get(j, "maxBitrateKbps", p.maxBitrateKbps);
        get(j, "bitrateKbps", p.bitrateKbps);
        get(j, "bitrateMode", p.bitrateMode);
        get(j, "fps", p.fps);
        get(j, "gop", p.gop);
        get(j, "h264Profile", p.h264Profile);
        get(j, "jpegQuality", p.jpegQuality);
        get(j, "codec", p.codec);
        get(j, "fitMode", p.fitMode);
        get(j, "overlayEnable", p.overlayEnable);
        get(j, "type", p.type);
        get(j, "custom1", p.custom1);
        get(j, "custom2", p.custom2);
        get(j, "custom3", p.custom3);
        get(j, "rtspKey", p.rtspKey);
        get(j, "rtspCert", p.rtspCert);
        get(j, "webRtcKey", p.webRtcKey);
        get(j, "webRtcCert", p.webRtcCert);
        get(j, "hlsKey", p.hlsKey);
        get(j, "hlsCert", p.hlsCert);
        get(j, "rtmpKey", p.rtmpKey);
        get(j, "rtmpCert", p.rtmpCert);
        get(j, "rtspEncryption", p.rtspEncryption);
        get(j, "webRtcEncryption", p.webRtcEncryption);
        get(j, "rtmpEncryption", p.rtmpEncryption);
        get(j, "hlsEncryption", p.hlsEncryption);
        get(j, "logLevel", p.logLevel);
        get(j, "directStreamType", p.directStreamType);
        get(j, "directStreamBitrateKbps", p.directStreamBitrateKbps);
        get(j, "directStreamMaxPayloadSize", p.directStreamMaxPayloadSize);
        get(j, "directStreamPacingMode", p.directStreamPacingMode);
        get(j, "serverStreamType", p.serverStreamType);
        get(j, "multicastTtl", p.multicastTtl);
        get(j, "securityProfile", p.securityProfile);
        get(j, "publicAddress", p.publicAddress);
        get(j, "bindAddress", p.bindAddress);
        get(j, "rtpPortMin", p.rtpPortMin);
        get(j, "rtpPortMax", p.rtpPortMax);
        get(j, "webRtcMediaPort", p.webRtcMediaPort);
        get(j, "corsAllowedOrigin", p.corsAllowedOrigin);
        get(j, "serverStreamMaxPayloadSize", p.serverStreamMaxPayloadSize);
    }

    /**
     * @brief Serialize parameters.
     * @param data Pointer to data buffer. Must be at least 12 bytes (header
     *             plus one bool field); if smaller than the size required for
     *             all selected parameters, fewer parameters are serialized.
     * @param bufferSize Size of data buffer.
     * @param size Size of data.
     * @param mask Pointer to parameters mask.
     * @return TRUE if parameters serialized or FALSE if not.
     */
    bool serialize(uint8_t* data, int bufferSize, int& size,
                   VStreamerParamsMask* mask = nullptr);

    /**
     * @brief Deserialize parameters.
     * @param data Pointer to data.
     * @param dataSize Size of data.
     * @return TRUE if parameters deserialized or FALSE if not.
     */
    bool deserialize(uint8_t* data, int dataSize);
};



/**
 * @brief Enum of VStreamer parameters.
 */
enum class VStreamerParam
{
    /// Streamer enable / disable, integer: 0 - disabled, 1 - enabled.
    MODE = 1,
    /// Video stream width, integer [0:8192].
    WIDTH,
    /// Video stream height, integer [0:8192].
    HEIGHT,
    /// Destination IP of the direct stream, string.
    DIRECT_STREAM_IP,
    /// RTSP port, integer [0:65535].
    RTSP_PORT,
    /// RTSPS port, integer [0:65535].
    RTSPS_PORT,
    /// Destination port of the direct stream, integer [0:65535].
    DIRECT_STREAM_PORT,
    /// WebRTC port, integer [0:65535].
    WEBRTC_PORT,
    /// HLS port, integer [0:65535].
    HLS_PORT,
    /// SRT port, integer [0:65535].
    SRT_PORT,
    /// RTMP port, integer [0:65535].
    RTMP_PORT,
    /// RTMPS port, integer [0:65535].
    RTMPS_PORT,
    /// Metadata port, integer [0:65535].
    METADATA_PORT,
    /// RTSP protocol enable / disable, integer: 0 - disable, 1 - enable.
    RTSP_MODE,
    /// Direct stream enable / disable, integer: 0 - disable, 1 - enable.
    DIRECT_STREAM_ENABLE,
    /// WebRTC protocol enable / disable, integer: 0 - disable, 1 - enable.
    WEBRTC_MODE,
    /// HLS protocol enable / disable, integer: 0 - disable, 1 - enable.
    HLS_MODE,
    /// SRT protocol enable / disable, integer: 0 - disable, 1 - enable.
    SRT_MODE,
    /// RTMP protocol enable / disable, integer: 0 - disable, 1 - enable.
    RTMP_MODE,
    /// Metadata protocol enable / disable, integer: 0 - disable, 1 - enable.
    METADATA_MODE,
    /// RTSP multicast IP, string.
    RTSP_MULTICAST_IP,
    /// RTSP multicast port, integer [0:65535].
    RTSP_MULTICAST_PORT,
    /// Streamer user (for RTSP streaming), string: "" - no user.
    USER,
    /// Streamer password (for RTSP streaming), string: "" - no password.
    PASSWORD,
    /// Streamer suffix for RTSP streaming (stream name), string: "" - no suffix.
    SUFFIX,
    /// Metadata suffix (stream name), string: "" - no suffix.
    METADATA_SUFFIX,
    /// Minimum bitrate for variable bitrate mode, integer kbps.
    MIN_BITRATE_KBPS,
    /// Maximum bitrate for variable bitrate mode, integer kbps.
    MAX_BITRATE_KBPS,
    /// Current bitrate, integer kbps.
    BITRATE_KBPS,
    /// Bitrate mode, integer: 0 - constant bitrate, 1 - variable bitrate.
    BITRATE_MODE,
    /// FPS, float.
    FPS,
    /// GOP size for H264 and H265 codecs, integer [1:65535].
    GOP,
    /// H264 profile, integer: 0 - baseline, 1 - main, 2 - high.
    H264_PROFILE,
    /// JPEG quality, integer: [1:100]% for JPEG codec.
    JPEG_QUALITY,
    /// Codec type, string: "H264", "HEVC" or "JPEG".
    CODEC,
    /// Scaling mode, integer: 0 - fit, 1 - fill.
    FIT_MODE,
    /// Cycle time, integer μsec (microseconds). Calculated by video streamer.
    CYCLE_TIME_USEC,
    /// Overlay mode, integer: 0 - disable, 1 - enable.
    OVERLAY_MODE,
    /// Type of the streamer, integer. Depends on implementation.
    TYPE,
    /// Custom parameter 1, float.
    CUSTOM1,
    /// Custom parameter 2, float.
    CUSTOM2,
    /// Custom parameter 3, float.
    CUSTOM3,
    /// Path to openssl key for RTSP, string.
    RTSP_KEY,
    /// Path to openssl certificate for RTSP, string.
    RTSP_CERT,
    /// Path to openssl key for WebRTC, string.
    WEBRTC_KEY,
    /// Path to openssl certificate for WebRTC, string.
    WEBRTC_CERT,
    /// Path to openssl key for HLS, string.
    HLS_KEY,
    /// Path to openssl certificate for HLS, string.
    HLS_CERT,
    /// Path to openssl key for RTMP, string.
    RTMP_KEY,
    /// Path to openssl certificate for RTMP, string.
    RTMP_CERT,
    /// RTSP encryption type, string: "no", "strict", "optional".
    RTSP_ENCRYPTION,
    /// WebRTC encryption type, string: "no", "yes".
    WEBRTC_ENCRYPTION,
    /// RTMP encryption type, string: "no", "strict", "optional".
    RTMP_ENCRYPTION,
    /// HLS encryption type, string: "no", "yes".
    HLS_ENCRYPTION,
    /// Logging mode. Values: 0 - Disable, 1 - Only file,
    /// 2 - Only terminal, 3 - File and terminal.
    LOG_LEVEL,
    /// Direct stream transport/type, string. Accepted values are
    /// implementation-defined (e.g. "rtp", "mpegts"); the value also decides
    /// whether KLV metadata is carried.
    DIRECT_STREAM_TYPE,
    /// Direct stream target bitrate, integer kbps.
    DIRECT_STREAM_BITRATE_KBPS,
    /// Direct stream max UDP/RTP payload size, integer bytes.
    DIRECT_STREAM_MAX_PAYLOAD,
    /// Direct stream pacing mode, integer: 0 - target bitrate, 1 - push.
    DIRECT_STREAM_PACING_MODE,
    /// Server-delivered stream type, string. Accepted values are
    /// implementation-defined (e.g. "rtp", "mpegts"); the value also decides
    /// whether KLV metadata is carried. Distinct from RTSP_MODE (protocol on/off).
    SERVER_STREAM_TYPE,
    /// Multicast TTL (scope) for every multicast leg, integer [0:255]:
    /// 0 - implementation default. An implementation may cap the value and
    /// must document the cap.
    MULTICAST_TTL,
    /// Security/compliance profile, string. Accepted values are
    /// IMPLEMENTATION-DEFINED; "" or "no" - the implementation's default. An
    /// unrecognised value must be REJECTED, never silently defaulted.
    SECURITY_PROFILE,
    /// Public (routed) address to advertise to clients in SDP/ICE instead of
    /// the locally detected one, string: "" or "no" - detect automatically.
    PUBLIC_ADDRESS,
    /// Local address to bind every listener to, string: "" or "0.0.0.0" -
    /// every interface.
    BIND_ADDRESS,
    /// Lowest port of the RTP/RTCP range, integer: 0 - any ephemeral port.
    RTP_PORT_MIN,
    /// Highest port of the RTP/RTCP range, integer: 0 - any ephemeral port.
    RTP_PORT_MAX,
    /// WebRTC media (UDP) port, integer: 0 - the implementation chooses.
    WEBRTC_MEDIA_PORT,
    /// Single origin permitted to reach the HTTP-based signalling endpoints,
    /// string: "" or "no" - the implementation's default policy.
    CORS_ALLOWED_ORIGIN,
    /// Maximum RTP payload size of the server-delivered stream, integer bytes.
    SERVER_STREAM_MAX_PAYLOAD
};



/**
 * @brief Enum of VStreamer action commands.
 */
enum class VStreamerCommand
{
    /// Restart.
    RESTART = 1,
    /// Enable. Equal to MODE param.
    ON,
    /// Disable. Equal to MODE param.
    OFF,
    /// Generate key frame command.
    GENERATE_KEYFRAME
};



/**
 * @brief VStreamer interface class.
 */
class VStreamer
{
public:

    /**
     * @brief Class destructor.
     */
    virtual ~VStreamer();

    /**
     * @brief Get string of current library version.
     * @return String of current library version.
     */
    static std::string getVersion();

    /**
     * @brief Initialize video streamer. All params will be set according to structure.
     * @param params Video streamer parameters structure.
     * @param codec Pointer to codec object (in case of raw frame streaming).
     * @param overlay Pointer to overlay object (in case of raw frame streaming).
     * @return TRUE if the video streamer is initialized or FALSE if not.
     */
    virtual bool initVStreamer(VStreamerParams &params,
                               VCodec *codec = nullptr,
                               VOverlay *overlay = nullptr) = 0;

    /**
     * @brief Get initialization status.
     * @return TRUE if video streamer is initialized or FALSE if not.
     */
    virtual bool isVStreamerInit() = 0;

    /**
     * @brief Close video streamer.
     */
    virtual void closeVStreamer() = 0;

    /**
     * @brief Send frame to video streamer.
     * @param frame Reference to frame object.
     * @param userData Pointer to optional user data.
     * @param userDataSize Size of user data.
     * @return TRUE if frame was sent successfully or FALSE if not.
     */
    virtual bool sendFrame(Frame& frame, uint8_t* userData = nullptr, int userDataSize = 0) = 0;

    /**
     * @brief Set video streamer parameter.
     * @param id Parameter ID.
     * @param value Parameter value to set.
     * @return TRUE if parameter was set or FALSE if not.
     */
    virtual bool setParam(VStreamerParam id, float value) = 0;

    /**
     * @brief Set video streamer parameter.
     * @param id Parameter ID.
     * @param value Parameter value to set.
     * @return TRUE if parameter was set or FALSE if not.
     */
    virtual bool setParam(VStreamerParam id, std::string value) = 0;

    /**
     * @brief Get video streamer params structure.
     * @param params Video streamer params class object.
     */
    virtual void getParams(VStreamerParams& params) = 0;

    /**
     * @brief Execute command.
     * @param id Command ID.
     * @return TRUE if the command is accepted or FALSE if not.
     */
    virtual bool executeCommand(VStreamerCommand id) = 0;

    /**
     * @brief Decode and execute command.
     * @param data Pointer to command data.
     * @param size Size of data.
     * @return TRUE if command was decoded and executed successfully or FALSE if not.
     */
    virtual bool decodeAndExecuteCommand(uint8_t* data, int size);

    /**
     * @brief Encode set parameter command.
     * @param data Pointer to data buffer. Must have size >= 11.
     * @param size Size of encoded data.
     * @param id Parameter ID.
     * @param value Parameter value.
     */
    static void encodeSetParamCommand(uint8_t *data, int &size, 
                                        VStreamerParam id, float value);

    /**
     * @brief Encode set parameter command.
     * @param data Pointer to data buffer. Must have size >= 8 + value.size()
     *             (3-byte header + 4-byte param ID + the string and its null
     *             terminator).
     * @param size Size of encoded data.
     * @param id Parameter ID.
     * @param value Parameter value.
     */
    static void encodeSetParamCommand(uint8_t* data, int& size,
                                        VStreamerParam id, std::string value);

    /**
     * @brief Encode command.
     * @param data Pointer to data buffer. Must have size >= 7.
     * @param size Size of encoded data.
     * @param id Command ID.
     */
    static void encodeCommand(uint8_t* data, int& size, VStreamerCommand id);

    /**
     * @brief Decode command.
     * @param data Pointer to command data.
     * @param size Size of data.
     * @param paramId Output parameter ID.
     * @param commandId Output command ID.
     * @param value Parameter or command value.
     * @param strValue Parameter or command string value.
     * @return -1 - Error 
     *          0 - Action command decoded.
     *          1 - Set parameter command with float value.
     *          2 - Set parameter command with string value.
     */
    static int decodeCommand(uint8_t* data,
                             int size,
                             VStreamerParam& paramId,
                             VStreamerCommand& commandId,
                             float& value,
                             std::string& strValue);

};
}
}