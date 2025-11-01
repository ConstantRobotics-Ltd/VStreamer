#pragma once
#include "VStreamer.h"



namespace cr
{
namespace video
{
/// Custom video streamer class.
class CustomVStreamer: public VStreamer
{
public:

    /**
     * @brief Class destructor.
     */
    ~CustomVStreamer();

    /**
     * @brief Get string of current library version.
     * @return String of current library version.
     */
    static std::string getVersion();

    /**
     * @brief Initialize video streamer. All parameters will be set according to structure.
     * @param params Video streamer parameters structure.
     * @param codec Pointer to codec object (in case of raw frame streaming).
     * @param overlay Pointer to overlay object (in case of raw frame streaming).
     * @return TRUE if the video streamer is initialized or FALSE if not.
     */
    bool initVStreamer(VStreamerParams &params,
                       VCodec *codec = nullptr,
                       VOverlay *overlay = nullptr) override;

    /**
     * @brief Get initialization status.
     * @return TRUE if video streamer is initialized or FALSE if not.
     */
    bool isVStreamerInit() override;

    /**
     * @brief Close video streamer.
     */
    void closeVStreamer() override;

    /**
     * @brief Send frame to video streamer.
     * @param frame Reference to frame object.
     * @param userData Pointer to optional user data.
     * @param userDataSize Size of user data.
     * @return TRUE if frame was sent successfully or FALSE if not.
     */
    bool sendFrame(Frame& frame, uint8_t* userData = nullptr, int userDataSize = 0) override;

    /**
     * @brief Set video streamer parameter.
     * @param id Parameter ID.
     * @param value Parameter value to set.
     * @return TRUE if parameter was set or FALSE if not.
     */
    bool setParam(VStreamerParam id, float value) override;

    /**
     * @brief Set video streamer parameter.
     * @param id Parameter ID.
     * @param value Parameter value to set.
     * @return TRUE if parameter was set or FALSE if not.
     */
    bool setParam(VStreamerParam id, std::string value) override;

    /**
     * @brief Get video streamer parameters structure.
     * @param params Video streamer parameters class object.
     */
    void getParams(VStreamerParams& params) override;

    /**
     * @brief Execute command.
     * @param id Command ID.
     * @return TRUE if the command is accepted or FALSE if not.
     */
    bool executeCommand(VStreamerCommand id) override;

private:

    /// Video source parameters.
    VStreamerParams m_params;

};
}
}