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
     * @brief Init video streamer. All params will be set according to structure.
     * @param params Video streamer parameters structure.
     * @param overlay Pointer to overlay object (in case raw frame streaming).
     * @param codec Pointer to codec object (in case raw frame streaming).
     * @return TRUE if the video streamer init or FALSE if not.
     */
    bool initVStreamer(VStreamerParams &params,
                               VOverlay *overlay = nullptr,
                               VCodec *codec = nullptr);

    /**
     * @brief Get open status.
     * @return TRUE if video streamer init or FALSE if not.
     */
    bool isVStreamerInit();

    /**
     * @brief Close video streamer.
     */
    void closeVStreamer();

    /**
     * @brief Send frame to video streamer.
     * @param frame Pointer to frame object.
     */
    bool sendFrame(Frame& frame);

    /**
     * @brief Set video streamer param.
     * @param id Parameter ID.
     * @param value Parameter value to set.
     * @return TRUE if property was set of FALSE.
     */
    bool setParam(VStreamerParam id, float value);

    /**
     * @brief Set video streamer param.
     * @param id Parameter ID.
     * @param value Parameter value to set.
     * @return TRUE if property was set of FALSE.
     */
    bool setParam(VStreamerParam id, std::string value);

    /**
     * @brief Get video streamer params structure.
     * @param params Video streamer params class object.
     */
    void getParams(VStreamerParams& params);

    /**
     * @brief Execute command.
     * @param id Command ID.
     * @return TRUE if the command accepted or FALSE if not.
     */
    bool executeCommand(VStreamerCommand id);

private:

    /// Video source params.
    VStreamerParams m_params;

};
}
}