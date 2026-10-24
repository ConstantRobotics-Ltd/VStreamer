#pragma once
#include <cstdint>
#include <string>
#include "ConfigReader.h"
#include "Frame.h"
#include "VCodec.h"
#include "VOverlay.h"



namespace rapidpixel
{
/**
 * @brief VStreamer params mask structure.
 *
 * Each flag selects serialization of the VStreamerParams field with the same
 * name (see VStreamerParams::serialize(...)): true - the field is serialized,
 * false - the field is skipped.
 */
struct VStreamerParamsMask
{
    /// Serialize enable field.
    bool enable{true};
    /// Serialize width field.
    bool width{true};
    /// Serialize height field.
    bool height{true};
    /// Serialize directStreamIp field.
    bool directStreamIp{true};
    /// Serialize rtspPort field.
    bool rtspPort{true};
    /// Serialize rtspsPort field.
    bool rtspsPort{true};
    /// Serialize directStreamPort field.
    bool directStreamPort{true};
    /// Serialize webRtcPort field.
    bool webRtcPort{true};
    /// Serialize hlsPort field.
    bool hlsPort{true};
    /// Serialize srtPort field.
    bool srtPort{true};
    /// Serialize rtmpPort field.
    bool rtmpPort{true};
    /// Serialize rtmpsPort field.
    bool rtmpsPort{true};
    /// Serialize metadataPort field.
    bool metadataPort{true};
    /// Serialize rtspEnable field.
    bool rtspEnable{true};
    /// Serialize directStreamEnable field.
    bool directStreamEnable{true};
    /// Serialize webRtcEnable field.
    bool webRtcEnable{true};
    /// Serialize hlsEnable field.
    bool hlsEnable{true};
    /// Serialize srtEnable field.
    bool srtEnable{true};
    /// Serialize rtmpEnable field.
    bool rtmpEnable{true};
    /// Serialize metadataEnable field.
    bool metadataEnable{true};
    /// Serialize rtspMulticastIp field.
    bool rtspMulticastIp{true};
    /// Serialize rtspMulticastPort field.
    bool rtspMulticastPort{true};
    /// Serialize user field.
    bool user{true};
    /// Serialize password field.
    bool password{true};
    /// Serialize suffix field.
    bool suffix{true};
    /// Serialize metadataSuffix field.
    bool metadataSuffix{true};
    /// Serialize minBitrateKbps field.
    bool minBitrateKbps{true};
    /// Serialize maxBitrateKbps field.
    bool maxBitrateKbps{true};
    /// Serialize bitrateKbps field.
    bool bitrateKbps{true};
    /// Serialize bitrateMode field.
    bool bitrateMode{true};
    /// Serialize fps field.
    bool fps{true};
    /// Serialize gop field.
    bool gop{true};
    /// Serialize h264Profile field.
    bool h264Profile{true};
    /// Serialize jpegQuality field.
    bool jpegQuality{true};
    /// Serialize codec field.
    bool codec{true};
    /// Serialize fitMode field.
    bool fitMode{true};
    /// Serialize cycleTimeUs field.
    bool cycleTimeUs{true};
    /// Serialize overlayEnable field.
    bool overlayEnable{true};
    /// Serialize type field.
    bool type{true};
    /// Serialize custom1 field.
    bool custom1{true};
    /// Serialize custom2 field.
    bool custom2{true};
    /// Serialize custom3 field.
    bool custom3{true};
    /// Serialize rtspKey field.
    bool rtspKey{true};
    /// Serialize rtspCert field.
    bool rtspCert{true};
    /// Serialize webRtcKey field.
    bool webRtcKey{true};
    /// Serialize webRtcCert field.
    bool webRtcCert{true};
    /// Serialize hlsKey field.
    bool hlsKey{true};
    /// Serialize hlsCert field.
    bool hlsCert{true};
    /// Serialize rtmpKey field.
    bool rtmpKey{true};
    /// Serialize rtmpCert field.
    bool rtmpCert{true};
    /// Serialize rtspEncryption field.
    bool rtspEncryption{true};
    /// Serialize webRtcEncryption field.
    bool webRtcEncryption{true};
    /// Serialize rtmpEncryption field.
    bool rtmpEncryption{true};
    /// Serialize hlsEncryption field.
    bool hlsEncryption{true};
    /// Serialize logLevel field.
    bool logLevel{true};
    /// Serialize directStreamType field.
    bool directStreamType{true};
    /// Serialize directStreamBitrateKbps field.
    bool directStreamBitrateKbps{true};
    /// Serialize directStreamMaxPayloadSize field.
    bool directStreamMaxPayloadSize{true};
    /// Serialize directStreamPacingMode field.
    bool directStreamPacingMode{true};
    /// Serialize serverStreamType field.
    bool serverStreamType{true};
    /// Serialize multicastTtl field.
    bool multicastTtl{true};
    /// Serialize securityProfile field.
    bool securityProfile{true};
    /// Serialize publicAddress field.
    bool publicAddress{true};
    /// Serialize bindAddress field.
    bool bindAddress{true};
    /// Serialize rtpPortMin field.
    bool rtpPortMin{true};
    /// Serialize rtpPortMax field.
    bool rtpPortMax{true};
    /// Serialize webRtcMediaPort field.
    bool webRtcMediaPort{true};
    /// Serialize corsAllowedOrigin field.
    bool corsAllowedOrigin{true};
    /// Serialize serverStreamMaxPayloadSize field.
    bool serverStreamMaxPayloadSize{true};
};



/**
 * @brief VStreamer params class.
 *
 * The ranges in the comments of the fields are the ranges which a video
 * streamer accepts. The class itself doesn't check the values of the fields:
 * serialize(...), deserialize(...) and the JSON functions transport the
 * values as they are, and the video streamer implementation must validate
 * them before use.
 *
 * @note The class is not thread-safe: an object must not be accessed from
 * several threads at the same time without external synchronization.
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
    /// RTSP protocol enable / disable, boolean: false - disable,
    /// true - enable.
    bool rtspEnable{true};
    /// Direct stream (point-to-point, bypasses MediaMTX) enable / disable,
    /// boolean: false - disable, true - enable. Uses directStreamIp /
    /// directStreamPort and the directStream* parameters.
    bool directStreamEnable{true};
    /// WebRTC protocol enable / disable, boolean: false - disable,
    /// true - enable.
    bool webRtcEnable{true};
    /// HLS protocol enable / disable, boolean: false - disable, true - enable.
    bool hlsEnable{true};
    /// SRT protocol enable / disable, boolean: false - disable, true - enable.
    bool srtEnable{true};
    /// RTMP protocol enable / disable, boolean: false - disable,
    /// true - enable.
    bool rtmpEnable{true};
    /// Metadata protocol enable / disable, boolean: false - disable,
    /// true - enable.
    bool metadataEnable{false};
    /// RTSP multicast IP, string.
    std::string rtspMulticastIp{"224.1.0.1/16"};
    /// RTSP multicast port, integer [0:65535].
    int rtspMulticastPort{18000};
    /// Streamer user (for RTSP streaming), string: "" or "no" - no user.
    std::string user{"no"};
    /// Streamer password (for RTSP streaming), string: "" or "no" - no
    /// password.
    std::string password{"no"};
    /// Streamer suffix for RTSP streaming (stream name), string: "" - no
    /// suffix.
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
    /// Cycle time, integer microseconds. Calculated by video streamer.
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
    /// Path to openssl certificate for RTSP, string: "" or "no" - no
    /// certificate.
    std::string rtspCert{"no"};
    /// Path to openssl key for WebRTC, string: "" or "no" - no key.
    std::string webRtcKey{"no"};
    /// Path to openssl certificate for WebRTC, string: "" or "no" - no
    /// certificate.
    std::string webRtcCert{"no"};
    /// Path to openssl key for HLS, string: "" or "no" - no key.
    std::string hlsKey{"no"};
    /// Path to openssl certificate for HLS, string: "" or "no" - no
    /// certificate.
    std::string hlsCert{"no"};
    /// Path to openssl key for RTMP, string: "" or "no" - no key.
    std::string rtmpKey{"no"};
    /// Path to openssl certificate for RTMP, string: "" or "no" - no
    /// certificate.
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
    /// Transport / type of the direct (point-to-point) stream. String whose
    /// accepted values are implementation-defined: each concrete VStreamer
    /// decides the set and what each value means, including whether KLV
    /// metadata is carried (no separate flag). Examples: "rtp", "mpegts".
    std::string directStreamType{"rtp"};
    /// Target sending bitrate for the direct stream, integer kbps.
    int directStreamBitrateKbps{5000};
    /// Maximum UDP/RTP payload size for the direct stream, integer bytes.
    int directStreamMaxPayloadSize{1472};
    /// Pacing mode of the direct stream, integer: 0 - target bitrate,
    /// 1 - push.
    int directStreamPacingMode{0};
    /// Transport / type of the server-delivered stream (fed to the media
    /// server, which fans it out to clients). String whose accepted values
    /// are implementation-defined: each concrete VStreamer decides the set
    /// and what each value means, including whether KLV metadata is carried
    /// (no separate flag). Examples: "rtp", "mpegts". Distinct from
    /// rtspEnable (protocol on / off).
    std::string serverStreamType{"rtp"};
    /// Multicast TTL (scope) for every multicast leg, integer [0:255]:
    /// 0 - implementation default. An implementation may cap the value and
    /// must document the cap. Applies to every leg that sends to a multicast
    /// group, not only the RTSP one.
    int multicastTtl{0};
    /// Security / compliance profile. String whose accepted values are
    /// implementation-defined, in the style of directStreamType: "" or "no" -
    /// the implementation's own default. An unrecognised value must be
    /// rejected by initVStreamer(...) / setParam(...), never mapped to a
    /// default: a silent downgrade of the security posture is the failure
    /// this field exists to prevent.
    std::string securityProfile{"no"};
    /// Public (routed) address advertised to clients in SDP and ICE candidate
    /// lines instead of the locally detected one, string: "" or "no" - detect
    /// automatically. An address literal, not a hostname: it is written onto
    /// the wire verbatim. Needed behind 1:1 NAT, in containers, and on
    /// multi-homed hosts, where the detected address is unroutable for the
    /// viewer.
    std::string publicAddress{"no"};
    /// Local address every listener binds to, string: "" or "0.0.0.0" - every
    /// interface. A multi-homed host has no other way to keep a stream off an
    /// interface it must not appear on.
    std::string bindAddress{"0.0.0.0"};
    /// Lowest port of the RTP/RTCP range, integer [0:65534]: 0 - any
    /// ephemeral port. Should be even, because RTCP conventionally takes
    /// port + 1.
    int rtpPortMin{0};
    /// Highest port of the RTP/RTCP range, integer [0:65535]: 0 - any
    /// ephemeral port. A firewall is configured for a range; without one an
    /// implementation picks ephemeral ports nothing has been opened for.
    int rtpPortMax{0};
    /// WebRTC media (UDP) port, integer [0:65535]: 0 - the implementation
    /// chooses. Distinct from webRtcPort, which carries signalling only.
    int webRtcMediaPort{0};
    /// Single origin permitted to reach the HTTP-based signalling endpoints,
    /// string "scheme://host[:port]": "" or "no" - the implementation's
    /// default policy. Deliberately one origin and not a wildcard list.
    std::string corsAllowedOrigin{"no"};
    /// Maximum RTP payload size of the server-delivered stream, integer
    /// bytes. The counterpart of directStreamMaxPayloadSize for the server
    /// leg. An implementation may clamp it lower: a transform applied after
    /// packetization (SRTP appends an authentication tag) can otherwise push
    /// the datagram past the path MTU.
    int serverStreamMaxPayloadSize{1472};

    /// JSON serialization: ConfigReader::get(...) fails if a field is absent
    /// or has a wrong type and doesn't change the object in this case.
    JSON_READABLE(VStreamerParams,
                  enable,
                  width,
                  height,
                  directStreamIp,
                  rtspPort,
                  rtspsPort,
                  directStreamPort,
                  webRtcPort,
                  hlsPort,
                  srtPort,
                  rtmpPort,
                  rtmpsPort,
                  metadataPort,
                  rtspEnable,
                  directStreamEnable,
                  webRtcEnable,
                  hlsEnable,
                  srtEnable,
                  rtmpEnable,
                  metadataEnable,
                  rtspMulticastIp,
                  rtspMulticastPort,
                  user,
                  password,
                  suffix,
                  metadataSuffix,
                  minBitrateKbps,
                  maxBitrateKbps,
                  bitrateKbps,
                  bitrateMode,
                  fps,
                  gop,
                  h264Profile,
                  jpegQuality,
                  codec,
                  fitMode,
                  cycleTimeUs,
                  overlayEnable,
                  type,
                  custom1,
                  custom2,
                  custom3,
                  rtspKey,
                  rtspCert,
                  webRtcKey,
                  webRtcCert,
                  hlsKey,
                  hlsCert,
                  rtmpKey,
                  rtmpCert,
                  rtspEncryption,
                  webRtcEncryption,
                  rtmpEncryption,
                  hlsEncryption,
                  logLevel,
                  directStreamType,
                  directStreamBitrateKbps,
                  directStreamMaxPayloadSize,
                  directStreamPacingMode,
                  serverStreamType,
                  multicastTtl,
                  securityProfile,
                  publicAddress,
                  bindAddress,
                  rtpPortMin,
                  rtpPortMax,
                  webRtcMediaPort,
                  corsAllowedOrigin,
                  serverStreamMaxPayloadSize)

    /**
     * @brief Serialize params.
     *
     * The data starts with a 13 bytes header: data type 0x02, major and minor
     * version of the library and a 10 bytes mask with one bit per field. The
     * selected fields follow in the order of the mask bits: a bool field as
     * 1 byte (0 or 1), an int or float field as 4 bytes in the byte order of
     * the host, a string as its characters and a terminating NUL byte. A
     * selected field which doesn't fit into the rest of the buffer, or a
     * string which contains a NUL character, is not serialized: its mask bit
     * is not set and the next fields are serialized if they fit.
     *
     * @param data Pointer to the data buffer. Must not be nullptr. The buffer
     * must be valid for bufferSize bytes.
     * @param bufferSize Size of the data buffer, bytes. Must be >= 14 (header
     * and the smallest field).
     * @param size Size of the serialized data, bytes. 0 if the method returns
     * FALSE.
     * @param mask Pointer to the params mask. If nullptr all fields are
     * selected.
     * @return TRUE if params are serialized or FALSE if data is nullptr or
     * bufferSize < 14. If FALSE is returned the buffer is not changed.
     */
    bool serialize(uint8_t* data, int bufferSize, int& size,
                   VStreamerParamsMask* mask = nullptr);

    /**
     * @brief Deserialize params serialized by serialize(...) method.
     *
     * The method replaces the whole object: a field which is not selected by
     * the mask of the data is set to 0, false or an empty string. The method
     * rejects data of another data type, data of another major or minor
     * version, a mask with bits of unknown fields, a field which is not
     * complete and a string without a terminating NUL byte. Bytes after the
     * last selected field are ignored. The values of the fields are not
     * checked against any range.
     *
     * @param data Pointer to the serialized data. Must not be nullptr. The
     * buffer must be valid for dataSize bytes.
     * @param dataSize Size of the serialized data, bytes. Must be >= 13.
     * @return TRUE if params are deserialized or FALSE if not. If FALSE is
     * returned the object is not changed.
     */
    bool deserialize(uint8_t* data, int dataSize);
};



/**
 * @brief Enum of VStreamer parameters.
 *
 * The values are used in encoded commands. VStreamer::decodeCommand(...)
 * accepts the IDs from MODE to SERVER_STREAM_MAX_PAYLOAD (the last value of
 * the enum).
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
    /// Streamer suffix for RTSP streaming (stream name), string: "" - no
    /// suffix.
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
    /// Cycle time, integer microseconds. Calculated by video streamer.
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
    /// Direct stream transport / type, string. Accepted values are
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
    /// whether KLV metadata is carried. Distinct from RTSP_MODE (protocol
    /// on / off).
    SERVER_STREAM_TYPE,
    /// Multicast TTL (scope) for every multicast leg, integer [0:255]:
    /// 0 - implementation default. An implementation may cap the value and
    /// must document the cap.
    MULTICAST_TTL,
    /// Security / compliance profile, string. Accepted values are
    /// implementation-defined; "" or "no" - the implementation's default. An
    /// unrecognised value must be rejected, never silently defaulted.
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
    /// Maximum RTP payload size of the server-delivered stream, integer
    /// bytes. The last value of the enum: it is used to check IDs.
    SERVER_STREAM_MAX_PAYLOAD
};



/**
 * @brief Enum of VStreamer action commands.
 *
 * The values are used in encoded commands. VStreamer::decodeCommand(...)
 * accepts the IDs from RESTART to GENERATE_KEYFRAME (the last value of the
 * enum).
 */
enum class VStreamerCommand
{
    /// Restart.
    RESTART = 1,
    /// Enable. Equal to MODE param.
    ON,
    /// Disable. Equal to MODE param.
    OFF,
    /// Generate key frame command. The last value of the enum: it is used to
    /// check IDs.
    GENERATE_KEYFRAME
};



/**
 * @brief VStreamer interface class.
 *
 * The class defines the interface of video streamers and provides static
 * methods to encode and decode control commands.
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
     * @return String of current library version "Major.Minor.Patch".
     */
    static std::string getVersion();

    /**
     * @brief Initialize video streamer. All params will be set according to
     * the structure.
     * @param params Video streamer parameters structure. The implementation
     * must validate the values and reject unsupported ones.
     * @param codec Pointer to codec object (in case of raw frame streaming).
     * nullptr - only compressed frames can be streamed.
     * @param overlay Pointer to overlay object (in case of raw frame
     * streaming). nullptr - no overlay.
     * @return TRUE if the video streamer is initialized or FALSE if not.
     */
    virtual bool initVStreamer(VStreamerParams& params,
                               VCodec* codec = nullptr,
                               VOverlay* overlay = nullptr) = 0;

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
     * @param userData Pointer to optional user data (telemetry). nullptr - no
     * user data. The buffer must be valid for userDataSize bytes.
     * @param userDataSize Size of user data, bytes. 0 - no user data.
     * @return TRUE if frame was sent successfully or FALSE if not.
     */
    virtual bool sendFrame(Frame& frame, uint8_t* userData = nullptr,
                           int userDataSize = 0) = 0;

    /**
     * @brief Set video streamer parameter with a numeric value.
     * @note The implementation must be thread-safe.
     * @param id Parameter ID.
     * @param value Parameter value to set. The implementation must check the
     * value: it can come from a decoded command (NaN, infinity, a value out
     * of the int range).
     * @return TRUE if parameter was set or FALSE if not.
     */
    virtual bool setParam(VStreamerParam id, float value) = 0;

    /**
     * @brief Set video streamer parameter with a string value.
     * @note The implementation must be thread-safe.
     * @param id Parameter ID.
     * @param value Parameter value to set. The implementation must check the
     * value: it can come from a decoded command.
     * @return TRUE if parameter was set or FALSE if not.
     */
    virtual bool setParam(VStreamerParam id, std::string value) = 0;

    /**
     * @brief Get video streamer params structure.
     * @note The implementation must be thread-safe.
     * @param params Video streamer params class object.
     */
    virtual void getParams(VStreamerParams& params) = 0;

    /**
     * @brief Execute command.
     * @note The implementation must be thread-safe.
     * @param id Command ID.
     * @return TRUE if the command is accepted or FALSE if not.
     */
    virtual bool executeCommand(VStreamerCommand id) = 0;

    /**
     * @brief Decode and execute command encoded by encodeCommand(...) or
     * encodeSetParamCommand(...) methods.
     *
     * The method decodes the command with decodeCommand(...) and calls
     * executeCommand(...) or setParam(...). The method is thread-safe if
     * these methods of the implementation are thread-safe.
     *
     * @param data Pointer to command data. The buffer must be valid for size
     * bytes.
     * @param size Size of data, bytes.
     * @return TRUE if the command was decoded and executed successfully or
     * FALSE if not.
     */
    virtual bool decodeAndExecuteCommand(uint8_t* data, int size);

    /**
     * @brief Encode set parameter command with a numeric value.
     *
     * The command is 11 bytes: data type 0x01, major and minor version of the
     * library, parameter ID (4 bytes) and value (4 bytes) in the byte order
     * of the host.
     *
     * @param data Pointer to data buffer. Must not be nullptr. The buffer
     * must be valid for 11 bytes.
     * @param size Size of encoded data: 11, or 0 if data is nullptr (nothing
     * is written).
     * @param id Parameter ID.
     * @param value Parameter value.
     */
    static void encodeSetParamCommand(uint8_t* data, int& size,
                                      VStreamerParam id, float value);

    /**
     * @brief Encode set parameter command with a string value.
     *
     * The command is 8 + value.size() bytes: data type 0x03, major and minor
     * version of the library, parameter ID (4 bytes, in the byte order of the
     * host), the characters of the value and a terminating NUL byte.
     *
     * @param data Pointer to data buffer. Must not be nullptr. The buffer
     * must be valid for 8 + value.size() bytes.
     * @param size Size of encoded data: 8 + value.size(), or 0 (nothing is
     * written) if data is nullptr, the value contains a NUL character or the
     * value is longer than INT_MAX - 8 bytes.
     * @param id Parameter ID.
     * @param value Parameter value.
     */
    static void encodeSetParamCommand(uint8_t* data, int& size,
                                      VStreamerParam id, std::string value);

    /**
     * @brief Encode action command.
     *
     * The command is 7 bytes: data type 0x00, major and minor version of the
     * library and command ID (4 bytes, in the byte order of the host).
     *
     * @param data Pointer to data buffer. Must not be nullptr. The buffer
     * must be valid for 7 bytes.
     * @param size Size of encoded data: 7, or 0 if data is nullptr (nothing is
     * written).
     * @param id Command ID.
     */
    static void encodeCommand(uint8_t* data, int& size, VStreamerCommand id);

    /**
     * @brief Decode command encoded by encodeCommand(...) or
     * encodeSetParamCommand(...) methods.
     *
     * The method checks the data type, the version, the exact size of the
     * command and the range of the command or parameter ID. The output
     * arguments are changed only if the command is decoded: for an action
     * command commandId is set, value is set to 0 and strValue is cleared;
     * for a set parameter command paramId and value or strValue are set and
     * the other value is set to 0 or cleared.
     *
     * @param data Pointer to command data. The buffer must be valid for size
     * bytes.
     * @param size Size of data, bytes: 7 for an action command, 11 for a set
     * parameter command with a numeric value, 8 + length of the string for a
     * set parameter command with a string value.
     * @param paramId Output parameter ID.
     * @param commandId Output command ID.
     * @param value Output numeric parameter value.
     * @param strValue Output string parameter value.
     * @return 0 - action command decoded, 1 - set parameter command with a
     * numeric value decoded, 2 - set parameter command with a string value
     * decoded, -1 - error: data is nullptr, wrong size, data type or version,
     * unknown command or parameter ID, a string without a terminating NUL
     * byte or with bytes after it.
     */
    static int decodeCommand(uint8_t* data,
                             int size,
                             VStreamerParam& paramId,
                             VStreamerCommand& commandId,
                             float& value,
                             std::string& strValue);

protected:

    /**
     * @brief Default constructor. The class can be used as a base only.
     */
    VStreamer() = default;

    /**
     * @brief Copy constructor.
     * @param src Source object.
     */
    VStreamer(const VStreamer& src) = default;

    /**
     * @brief Move constructor.
     * @param src Source object.
     */
    VStreamer(VStreamer&& src) = default;

    /**
     * @brief Copy assignment operator.
     * @param src Source object.
     * @return Reference to this object.
     */
    VStreamer& operator=(const VStreamer& src) = default;

    /**
     * @brief Move assignment operator.
     * @param src Source object.
     * @return Reference to this object.
     */
    VStreamer& operator=(VStreamer&& src) = default;
};
}



// Compatibility: the names of namespace rapidpixel are also available in
// namespace cr::video.
namespace cr
{
namespace video
{
using namespace ::rapidpixel;
}
}
