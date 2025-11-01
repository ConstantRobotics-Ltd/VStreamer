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
    bool ip{true};
    bool rtspPort{true};
    bool rtpPort{true};
    bool webRtcPort{true};
    bool hlsPort{true};
    bool srtPort{true};
    bool rtmpPort{true};
    bool metadataPort{true};
    bool rtspEnable{true};
    bool rtpEnable{true};
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
    /// Streamer IP, string.
    std::string ip{"0.0.0.0"};
    /// RTSP port, integer [0:65535].
    int rtspPort{8554};
    /// RTP port, integer [0:65535].
    int rtpPort{5004};
    /// WebRTC port, integer [0:65535].
    int webRtcPort{7000};
    /// HLS port, integer [0:65535].
    int hlsPort{8080};
    /// SRT port, integer [0:65535].
    int srtPort{6000};
    /// RTMP port, integer [0:65535].
    int rtmpPort{1935};
    /// Metadata port, integer [0:65535].
    int metadataPort{9000};
    /// RTSP protocol enable / disable, boolean: false - disable, true - enable.
    bool rtspEnable{true};
    /// RTP protocol enable / disable, boolean: false - disable, true - enable.
    bool rtpEnable{true};
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
    /// Streamer user (for RTSP streaming), string: "" - no user.
    std::string user{""};
    /// Streamer password (for RTSP streaming), string: "" - no password.
    std::string password{""};
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

    JSON_READABLE(VStreamerParams, enable, width, height, ip, rtspPort, rtpPort,
                  webRtcPort, hlsPort, srtPort, rtmpPort, metadataPort,
                  rtspEnable, rtpEnable, webRtcEnable, hlsEnable, srtEnable,
                  rtmpEnable, metadataEnable, rtspMulticastIp, rtspMulticastPort,
                  user, password, suffix, metadataSuffix, minBitrateKbps,
                  maxBitrateKbps, bitrateKbps, bitrateMode, fps, gop, h264Profile,
                  jpegQuality, codec, fitMode, overlayEnable, type, custom1,
                  custom2, custom3)

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
    /// Streamer IP, string.
    IP,
    /// RTSP port, integer [0:65535].
    RTSP_PORT,
    /// RTP port, integer [0:65535].
    RTP_PORT,
    /// WebRTC port, integer [0:65535].
    WEBRTC_PORT,
    /// HLS port, integer [0:65535].
    HLS_PORT,
    /// SRT port, integer [0:65535].
    SRT_PORT,
    /// RTMP port, integer [0:65535].
    RTMP_PORT,
    /// Metadata port, integer [0:65535].
    METADATA_PORT,
    /// RTSP protocol enable / disable, integer: 0 - disable, 1 - enable.
    RTSP_MODE,
    /// RTP protocol enable / disable, integer: 0 - disable, 1 - enable.
    RTP_MODE,
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
    CUSTOM3
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