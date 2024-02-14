#pragma once
#include "Frame.h"
#include "ConfigReader.h"
#include "VOverlay.h"
#include "VCodec.h"



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
    bool port{true};
    bool user{true};
    bool password{true};
    bool suffix{true};
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
    bool cycleTimeMksec{true};
    bool overlayMode{true};
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
    /// Streamer mode: false - Off, true - On.
    bool enable{true};
    /// Video stream width from 8 to 8192.
    int width{1280};
    /// Video stream height from 8 to 8192.
    int height{720};
    /// Streamer IP.
    std::string ip{"127.0.0.1"};
    /// Streamer port.
    int port{8554};
    /// Streamer user (for rtsp streaming): "" - no user.
    std::string user{""};
    /// Streamer password (for rtsp streaming): "" - no password.
    std::string password{""};
    /// Streamer suffix (for rtsp streaming) (stream name).
    std::string suffix{"live"};
    /// Minimum bitrate for variable bitrate mode, kbps.
    int minBitrateKbps{1000};
    /// Maximum bitrate for variable bitrate mode, kbps.
    int maxBitrateKbps{5000};
    /// Current bitrate, kbps.
    int bitrateKbps{3000};
    /// Bitrate mode: 0 - constant bitrate, 1 - variable bitrate.
    int bitrateMode{0};
    /// FPS.
    float fps{30.0f};
    /// GOP size for H264 and H265 codecs.
    int gop{30};
    /// H264 profile: 0 - baseline, 1 - main, 2 - high.
    int h264Profile{0};
    /// JPEG quality from 1 to 100% for JPEG codec.
    int jpegQuality{80};
    /// Codec type: "H264", "HEVC" or "JPEG".
    std::string codec{"H264"};
    /// Scaling mode: 0 - fit, 1 - cut.
    int fitMode{0};
    /// Cycle time, mksec. Calculated by RTSP server.
    int cycleTimeMksec{0};
    /// Overlay mode: false - off, true - on.
    bool overlayMode{true};
    /// type of the streamer
    int type{0};
    /// Custom parameter 1.
    float custom1{0.0f};
    /// Custom parameter 2.
    float custom2{0.0f};
    /// Custom parameter 3.
    float custom3{0.0f};

    JSON_READABLE(VStreamerParams, enable, width, height, ip, port, user,
                  password, suffix, minBitrateKbps, maxBitrateKbps, bitrateKbps,
                  bitrateMode, fps, gop, h264Profile, jpegQuality, codec,
                  fitMode, overlayMode, type, custom1, custom2, custom3)

    /**
     * @brief operator =
     * @param src Source object.
     * @return VStreamerParams object.
     */
    VStreamerParams& operator= (const VStreamerParams& src);

    /**
     * @brief Encode params. Method doesn't encode initString.
     * @param data Pointer to data buffer. Must have at least 99 bytes size.
     * @param bufferSize Size of data buffer. Min value is 99.
     * @param size Size of data.
     * @param mask Pointer to parameters mask.
     * @return TRUE if params encoded or FALSE if not.
     */
    bool encode(uint8_t* data, int bufferSize, int& size,
                VStreamerParamsMask* mask = nullptr);

    /**
     * @brief Decode params. Method doesn't decode initString.
     * @param data Pointer to data.
     * @param dataSize Size of data.
     * @return TRUE is params decoded or FALSE if not.
     */
    bool decode(uint8_t* data, int dataSize);
};



/**
 * @brief Enum of VStreamer params.
 */
enum class VStreamerParam
{
    /// Mode: 0 - disabled, 1 - enabled.
    MODE = 1,
    /// Video stream width from 8 to 8192.
    WIDTH,
    /// Video stream height from 8 to 8192.
    HEIGHT,
    /// Streamer IP.
    IP,
    /// Streamer port.
    PORT,
    /// Streamer user (for rtsp streaming): "" - no user.
    USER,
    /// Streamer password (for rtsp streaming): "" - no password.
    PASSWORD,
    /// Streamer suffix(for rtsp streaming, stream name).
    SUFFIX,
    /// Minimum bitrate for variable bitrate mode, kbps.
    MIN_BITRATE_KBPS,
    /// Maximum bitrate for variable bitrate mode, kbps.
    MAX_BITRATE_KBPS,
    /// Current bitrate, kbps.
    BITRATE_KBPS,
    /// Bitrate mode: 0 - constant bitrate, 1 - variable bitrate.
    BITRATE_MODE,
    /// FPS.
    FPS,
    /// GOP size for H264 and H265 codecs.
    GOP,
    /// H264 profile: 0 - baseline, 1 - main, 2 - high.
    H264_PROFILE,
    /// JPEG quality from 1 to 100% for JPEG codec.
    JPEG_QUALITY,
    /// Codec type: "H264", "HEVC" or "JPEG".
    CODEC,
    /// Scaling mode: 0 - fit, 1 - cut.
    FIT_MODE,
    /// Overlay mode: false - off, true - on.
    OVERLAY_MODE,
    /// TYPE of the streamer
    TYPE,
    /// Custom parameter 1.
    CUSTOM1,
    /// Custom parameter 2.
    CUSTOM2,
    /// Custom parameter 3. 
    CUSTOM3
};



/**
 * @brief Enum of VSteamer commands.
 */
enum class VStreamerCommand
{
    /// Restart.
    RESTART = 1,
    /// Enable. Equal to MODE param.
    ON,
    /// Disable. Equal to MODE params.
    OFF
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
     * @brief Init video streamer. All params will be set according to structure.
     * @param params Video streamer parameters structure.
     * @param overlay Pointer to overlay object (in case raw frame streaming).
     * @param codec Pointer to codec object (in case raw frame streaming).
     * @return TRUE if the video streamer init or FALSE if not.
     */
    virtual bool initVStreamer(VStreamerParams &params,
                               VOverlay *overlay = nullptr,
                               VCodec *codec = nullptr) = 0;

    /**
     * @brief Get open status.
     * @return TRUE if video streamer init or FALSE if not.
     */
    virtual bool isVStreamerInit() = 0;

    /**
     * @brief Close video streamer.
     */
    virtual void closeVStreamer() = 0;

    /**
     * @brief Set video streamer param.
     * @param id Parameter ID.
     * @param value Parameter value to set.
     * @return TRUE if property was set of FALSE.
     */
    virtual bool setParam(VStreamerParam id, float value) = 0;

    /**
     * @brief Set video streamer param.
     * @param id Parameter ID.
     * @param value Parameter value to set.
     * @return TRUE if property was set of FALSE.
     */
    virtual bool setParam(VStreamerParam id, std::string value) = 0;

    /**
     * @brief Get video streamer param value.
     * @param id Parameter ID.
     * @return Parameter value or -1.
     */
    virtual float getParam(VStreamerParam id) = 0;

    /**
     * @brief Get video streamer params structure.
     * @param params Video streamer params class object.
     */
    virtual void getParams(VStreamerParams& params) = 0;

    /**
     * @brief Execute command.
     * @param id Command ID.
     * @return TRUE if the command accepted or FALSE if not.
     */
    virtual bool executeCommand(VStreamerCommand id) = 0;

    /**
     * @brief Encode set param command.
     * @param data Pointer to data buffer. Must have size >= 11.
     * @param size Size of encoded data.
     * @param id Parameter id.
     * @param value Parameter value.
     */
    static void encodeSetParamCommand(
            uint8_t* data, int& size, VStreamerParam id, float value);

    /**
     * @brief Encode command.
     * @param data Pointer to data buffer. Must have size >= 11.
     * @param size Size of encoded data.
     * @param id Command ID.
     */
    static void encodeCommand(
            uint8_t* data, int& size, VStreamerCommand id);

    /**
     * @brief Decode command.
     * @param data Pointer to command data.
     * @param size Size of data.
     * @param paramId Output command ID.
     * @param commandId Output command ID.
     * @param value Param or command value.
     * @return 0 - command decoded, 1 - set param command decoded, -1 - error.
     */
    static int decodeCommand(uint8_t* data,
                             int size,
                             VStreamerParam& paramId,
                             VStreamerCommand& commandId,
                             float& value);

    /**
     * @brief Decode and execute command.
     * @param data Pointer to command data.
     * @param size Size of data.
     * @return 0 - command decoded, 1 - set param command decoded, -1 - error.
     */
    virtual bool decodeAndExecuteCommand(uint8_t* data, int size) = 0;
};

}
}