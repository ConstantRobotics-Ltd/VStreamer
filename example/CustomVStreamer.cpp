#include "CustomVStreamer.h"
#include "CustomVStreamerVersion.h"



cr::video::CustomVStreamer::~CustomVStreamer()
{

}



std::string cr::video::CustomVStreamer::getVersion()
{
    return CUSTOM_VSTREAMER_VERSION;
}





bool cr::video::CustomVStreamer::initVStreamer(VStreamerParams& params, VOverlay* overlay, VCodec* codec)
{
    // Copy params.
    m_params = params;
    return true;
}



bool cr::video::CustomVStreamer::isVStreamerInit()
{
    return m_params.enable;
}



void cr::video::CustomVStreamer::closeVStreamer()
{
    // close here the video streamer.
}



bool cr::video::CustomVStreamer::sendFrame(Frame& frame)
{
    // Send frame here.
    return true;
}



bool cr::video::CustomVStreamer::setParam(VStreamerParam id, float value)
{
    return true;
}



float cr::video::CustomVStreamer::getParam(VStreamerParam id)
{
    return 0.0f;
}



void cr::video::CustomVStreamer::getParams(VStreamerParams& params)
{
    params = m_params;
}



bool cr::video::CustomVStreamer::executeCommand(VStreamerCommand id)
{
    // Check command ID.
    switch (id)
    {
    case cr::video::VStreamerCommand::RESTART:
    {
        return true;
    }
    default:
    {
        return false;
    }
    }

    return false;
}