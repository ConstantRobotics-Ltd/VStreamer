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
    bool klvMode{true};
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
    /// Transport/type of the direct stream (point-to-point to
    /// directStreamIp:directStreamPort, bypassing MediaMTX), integer index:
    /// 0 - rtp (codec RTP), 1 - mpegts (MPEG-TS over UDP, MISB ST 1402),
    /// 2 - mpegts-rtp (MPEG-TS over RTP, MISB ST 1403). 1/2 carry KLV per
    /// STANAG 4609. JPEG supports 0 (rtp) only.
    int directStreamType{0};
    /// Target sending bitrate for the direct stream, integer kbps (>= 0).
    /// Used as the pacer target when directStreamPacingMode == 0.
    int directStreamBitrateKbps{5000};
    /// Maximum UDP/RTP payload size for the direct stream, integer bytes
    /// [256:65535]. Keep ~1420 (MTU 1500) for normal use; large values
    /// are for localhost / trusted LAN only (RtpPusher grows its ring
    /// buffer proportionally). Applies to the rtp/mpegts-rtp transports.
    int directStreamMaxPayloadSize{1472};
    /// Pacing mode of the direct stream, integer: 0 - target bitrate
    /// (token-bucket, uses directStreamBitrateKbps), 1 - back-pressure
    /// (kernel send-buffer occupancy).
    int directStreamPacingMode{0};
    /// Transport/type of the server-delivered stream — the stream fed to
    /// the media server, which then fans it out to clients (RTSP / SRT /
    /// HLS / RTMP / WebRTC). Integer index: 0 - rtp (codec-RTP + SDP, KLV
    /// muxed as a metadata track), 1 - mpegts (STANAG 4609 MPEG-TS over UDP;
    /// the server demuxes the KLV PID and re-serves it as a native KLV
    /// track). Both preserve KLV. The concrete media server is an
    /// implementation detail (MediaMTX in VStreamerMediaMtx).
    /// NOTE: distinct from rtspEnable (RTSP protocol enable/disable).
    int serverStreamType{0};
    /// KLV signalling for the MPEG-TS paths (direct mpegts/mpegts-rtp and
    /// the loopback when serverStreamType == 1), integer: 0 - asynchronous
    /// (stream_type 0x06 + "KLVA" registration, raw KLV), 1 - synchronous
    /// (stream_type 0x15 + metadata_descriptor, KLV in a metadata_AU_cell).
    /// MISB ST 0604; ignored for the rtp transport. Default 0 (widest
    /// receiver compatibility).
    int klvMode{0};

    JSON_READABLE(VStreamerParams, enable, width, height, directStreamIp, rtspPort, rtspsPort, directStreamPort,
                  webRtcPort, hlsPort, srtPort, rtmpPort, rtmpsPort, metadataPort,
                  rtspEnable, directStreamEnable, webRtcEnable, hlsEnable, srtEnable,
                  rtmpEnable, metadataEnable, rtspMulticastIp, rtspMulticastPort,
                  user, password, suffix, metadataSuffix, minBitrateKbps,
                  maxBitrateKbps, bitrateKbps, bitrateMode, fps, gop, h264Profile,
                  jpegQuality, codec, fitMode, overlayEnable, type, custom1,
                  custom2, custom3, rtspKey, rtspCert, webRtcKey, webRtcCert,
                  hlsKey, hlsCert, rtmpKey, rtmpCert, rtspEncryption,
                  webRtcEncryption, rtmpEncryption, hlsEncryption, logLevel,
                  directStreamType, directStreamBitrateKbps, directStreamMaxPayloadSize,
                  directStreamPacingMode, serverStreamType, klvMode)

    /**
     * @brief Serialize parameters.
     * @param data Pointer to data buffer. Must have at least 128 bytes size.
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
    /// Direct stream transport/type, integer: 0 - rtp, 1 - mpegts, 2 - mpegts-rtp.
    DIRECT_STREAM_TYPE,
    /// Direct stream target bitrate, integer kbps (>= 0).
    DIRECT_STREAM_BITRATE_KBPS,
    /// Direct stream max UDP/RTP payload size, integer bytes [256:65535].
    DIRECT_STREAM_MAX_PAYLOAD,
    /// Direct stream pacing mode, integer: 0 - target bitrate, 1 - back-pressure.
    DIRECT_STREAM_PACING_MODE,
    /// Server-delivered stream type, integer: 0 - rtp (codec-RTP + SDP),
    /// 1 - mpegts (STANAG 4609 MPEG-TS; the media server re-serves KLV
    /// natively). Distinct from RTSP_MODE (RTSP protocol enable/disable).
    SERVER_STREAM_TYPE,
    /// KLV signalling for MPEG-TS paths, integer: 0 - asynchronous
    /// (stream_type 0x06 + "KLVA"), 1 - synchronous (stream_type 0x15 +
    /// metadata_descriptor + metadata_AU_cell). MISB ST 0604.
    KLV_MODE
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
     * @param data Pointer to data buffer. Must have size >= 11.
     * @param size Size of encoded data.
     * @param id Parameter ID.
     * @param value Parameter value.
     */
    static void encodeSetParamCommand(uint8_t* data, int& size, 
                                        VStreamerParam id, std::string value);

    /**
     * @brief Encode command.
     * @param data Pointer to data buffer. Must have size >= 11.
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