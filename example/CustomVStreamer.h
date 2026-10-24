#pragma once
#include <cstdint>
#include <mutex>
#include <string>
#include "VStreamer.h"



namespace rapidpixel
{
/**
 * @brief Custom video streamer class: example of the VStreamer interface
 * implementation.
 *
 * The class doesn't stream video: it shows how an implementation keeps and
 * validates params. Every value which comes from outside (initVStreamer(...),
 * setParam(...), decoded commands) is checked before it is accepted.
 *
 * @note All methods are thread-safe.
 */
class CustomVStreamer : public VStreamer
{
public:

    /**
     * @brief Class constructor.
     */
    CustomVStreamer();

    /**
     * @brief Class destructor.
     */
    ~CustomVStreamer() override;

    /**
     * @brief Copy constructor is deleted: the object owns a mutex.
     */
    CustomVStreamer(const CustomVStreamer&) = delete;

    /**
     * @brief Move constructor is deleted: the object owns a mutex.
     */
    CustomVStreamer(CustomVStreamer&&) = delete;

    /**
     * @brief Copy assignment is deleted: the object owns a mutex.
     * @return Reference to this object.
     */
    CustomVStreamer& operator=(const CustomVStreamer&) = delete;

    /**
     * @brief Move assignment is deleted: the object owns a mutex.
     * @return Reference to this object.
     */
    CustomVStreamer& operator=(CustomVStreamer&&) = delete;

    /**
     * @brief Get string of current library version.
     * @return String of current library version "Major.Minor.Patch".
     */
    static std::string getVersion();

    /**
     * @brief Initialize video streamer. All parameters will be set according
     * to the structure.
     * @param params Video streamer parameters structure. Every value is
     * checked: if a value is not valid the method returns FALSE and the
     * video streamer is not changed. cycleTimeUs is ignored (calculated by
     * the video streamer).
     * @param codec Pointer to codec object. Not used by the example.
     * @param overlay Pointer to overlay object. Not used by the example.
     * @return TRUE if the video streamer is initialized or FALSE if not.
     */
    bool initVStreamer(VStreamerParams& params,
                       VCodec* codec = nullptr,
                       VOverlay* overlay = nullptr) override;

    /**
     * @brief Get initialization status.
     * @return TRUE if video streamer is initialized or FALSE if not.
     */
    bool isVStreamerInit() override;

    /**
     * @brief Close video streamer. The params are kept.
     */
    void closeVStreamer() override;

    /**
     * @brief Send frame to video streamer. The example doesn't send frames.
     * @param frame Reference to frame object. Must have data.
     * @param userData Pointer to optional user data. nullptr - no user data.
     * @param userDataSize Size of user data, bytes. Must be 0 if userData is
     * nullptr and must not be negative.
     * @return TRUE if the video streamer is initialized and enabled, and the
     * frame and the user data are valid, or FALSE if not.
     */
    bool sendFrame(Frame& frame, uint8_t* userData = nullptr,
                   int userDataSize = 0) override;

    /**
     * @brief Set video streamer parameter with a numeric value.
     * @param id Parameter ID. CYCLE_TIME_USEC can't be set and string
     * parameters can't be set by a numeric value.
     * @param value Parameter value to set. Boolean parameters accept 0 and 1,
     * integer parameters accept values inside their range (see the
     * VStreamerParam enum), the fractional part of a value of a boolean or
     * integer parameter is dropped. FPS accepts [0:1000], CUSTOM1..CUSTOM3
     * accept any finite value.
     * @return TRUE if parameter was set or FALSE if not (the parameter is not
     * changed).
     */
    bool setParam(VStreamerParam id, float value) override;

    /**
     * @brief Set video streamer parameter with a string value.
     * @param id Parameter ID. Numeric parameters can't be set by a string.
     * @param value Parameter value to set. Parameters with a fixed set of
     * values (codec, encryption types, stream types, security profile) accept
     * only these values; the other parameters accept text up to 4096
     * characters without control characters.
     * @return TRUE if parameter was set or FALSE if not (the parameter is not
     * changed).
     */
    bool setParam(VStreamerParam id, std::string value) override;

    /**
     * @brief Get video streamer parameters structure.
     * @param params Video streamer parameters class object.
     */
    void getParams(VStreamerParams& params) override;

    /**
     * @brief Execute command.
     * @param id Command ID. RESTART and GENERATE_KEYFRAME need an initialized
     * video streamer; ON and OFF set the MODE parameter.
     * @return TRUE if the command is accepted or FALSE if not.
     */
    bool executeCommand(VStreamerCommand id) override;

private:

    /// Video streamer parameters. Protected by m_mutex.
    VStreamerParams m_params;
    /// Initialization status. Protected by m_mutex.
    bool m_isInit{false};
    /// Mutex to protect m_params and m_isInit.
    std::mutex m_mutex;
};
}
