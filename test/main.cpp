#include <iostream>
#include "VStreamer.h"



// Link namespaces.
using namespace cr::video;
using namespace std;



// Fill random data.
void fillRandomData(VStreamerParams &a)
{

}


// Compare params function.
bool compareParams(VStreamerParams &a, VStreamerParams &b, VStreamerParamsMask* mask = nullptr);

// Copy test.
bool copyTest();

// Encode/decode test.
bool encodeDecodeTest();

/// Encode/decode test with params mask.
bool encodeDecodeWithMaskTest();

/// Encode/decode commands test.
bool encodeDecodeCommandsTest();

/// JSON read/write test.
bool jsonReadWriteTest();



int main(void)
{
    cout << "#####################################" << endl;
    cout << "#                                   #" << endl;
    cout << "# VStreamerParams test              #" << endl;
    cout << "#                                   #" << endl;
    cout << "#####################################" << endl;
    cout << endl;

    cout << "Copy test:" << endl;
    if (copyTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    cout << "Encode/Decode test:" << endl;
    if (encodeDecodeTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    cout << "Encode/Decode test with params mask:" << endl;
    if (encodeDecodeWithMaskTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    cout << "Encode/Decode commands test:" << endl;
    if (encodeDecodeCommandsTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    cout << "JSON read/write test:" << endl;
    if (jsonReadWriteTest())
        cout << "OK" << endl;
    else
        cout << "ERROR" << endl;
    cout << endl;

    return 1;
}



bool compareParams(VStreamerParams &a, VStreamerParams &b, VStreamerParamsMask* mask)
{
    // If mask not initialized then compare all params.
    VStreamerParamsMask defaultMask;
    if (mask == nullptr)
        mask = &defaultMask;

    if (mask->enable && (a.enable != b.enable))
    {
        cout << "enable" << endl;
        return false;
    }
    if (mask->width && (a.width != b.width))
    {
        cout << "width" << endl;
        return false;
    }
    if (mask->height && (a.height != b.height))
    {
        cout << "height" << endl;
        return false;
    }
    if (mask->ip && (a.ip != b.ip))
    {
        cout << "ip" << endl;
        return false;
    }
    if (mask->rtspPort && (a.rtspPort != b.rtspPort))
    {
        cout << "rtspPort" << endl;
        return false;
    }
    if (mask->rtpPort && (a.rtpPort != b.rtpPort))
    {
        cout << "rtpPort" << endl;
        return false;
    }
    if (mask->webRtcPort && (a.webRtcPort != b.webRtcPort))
    {
        cout << "webRtcPort" << endl;
        return false;
    }
    if (mask->hlsPort && (a.hlsPort != b.hlsPort))
    {
        cout << "hlsPort" << endl;
        return false;
    }
    if (mask->srtPort && (a.srtPort != b.srtPort))
    {
        cout << "srtPort" << endl;
        return false;
    }
    if (mask->rtmpPort && (a.rtmpPort != b.rtmpPort))
    {
        cout << "rtmpPort" << endl;
        return false;
    }
    if (mask->metadataPort && (a.metadataPort != b.metadataPort))
    {
        cout << "metadataPort" << endl;
        return false;
    }
    if (mask->rtspEnable && (a.rtspEnable != b.rtspEnable))
    {
        cout << "rtspEnable" << endl;
        return false;
    }
    if (mask->rtpEnable && (a.rtpEnable != b.rtpEnable))
    {
        cout << "rtpEnable" << endl;
        return false;
    }
    if (mask->webRtcEnable && (a.webRtcEnable != b.webRtcEnable))
    {
        cout << "webRtcEnable" << endl;
        return false;
    }
    if (mask->hlsEnable && (a.hlsEnable != b.hlsEnable))
    {
        cout << "hlsEnable" << endl;
        return false;
    }
    if (mask->srtEnable && (a.srtEnable != b.srtEnable))
    {
        cout << "srtEnable" << endl;
        return false;
    }
    if (mask->rtmpEnable && (a.rtmpEnable != b.rtmpEnable))
    {
        cout << "rtmpEnable" << endl;
        return false;
    }
    if (mask->metadataEnable && (a.metadataEnable != b.metadataEnable))
    {
        cout << "metadataEnable" << endl;
        return false;
    }
    if (mask->rtspMulticastIp && (a.rtspMulticastIp != b.rtspMulticastIp))
    {
        cout << "rtspMulticastIp" << endl;
        return false;
    }
    if (mask->rtspMulticastPort && (a.rtspMulticastPort != b.rtspMulticastPort))
    {
        cout << "rtspMulticastPort" << endl;
        return false;
    }
    if (mask->user && (a.user != b.user))
    {
        cout << "user" << endl;
        return false;
    }
    if (mask->password && (a.password != b.password))
    {
        cout << "password" << endl;
        return false;
    }
    if (mask->suffix && (a.suffix != b.suffix))
    {
        cout << "suffix" << endl;
        return false;
    }
    if (mask->metadataSuffix && (a.metadataSuffix != b.metadataSuffix))
    {
        cout << "metadataSuffix" << endl;
        return false;
    }
    if (mask->minBitrateKbps && (a.minBitrateKbps != b.minBitrateKbps))
    {
        cout << "minBitrateKbps" << endl;
        return false;
    }
    if (mask->maxBitrateKbps && (a.maxBitrateKbps != b.maxBitrateKbps))
    {
        cout << "maxBitrateKbps" << endl;
        return false;
    }
    if (mask->bitrateKbps && (a.bitrateKbps != b.bitrateKbps))
    {
        cout << "bitrateKbps" << endl;
        return false;
    }
    if (mask->bitrateMode && (a.bitrateMode != b.bitrateMode))
    {
        cout << "bitrateMode" << endl;
        return false;
    }
    if (mask->fps && (a.fps != b.fps))
    {
        cout << "fps" << endl;
        return false;
    }
    if (mask->gop && (a.gop != b.gop))
    {
        cout << "gop" << endl;
        return false;
    }
    if (mask->h264Profile && (a.h264Profile != b.h264Profile))
    {
        cout << "h264Profile" << endl;
        return false;
    }
    if (mask->jpegQuality && (a.jpegQuality != b.jpegQuality))
    {
        cout << "jpegQuality" << endl;
        return false;
    }
    if (mask->codec && (a.codec != b.codec))
    {
        cout << "codec" << endl;
        return false;
    }
    if (mask->fitMode && (a.fitMode != b.fitMode))
    {
        cout << "fitMode" << endl;
        return false;
    }
    if (mask->cycleTimeMksec && (a.cycleTimeMksec != b.cycleTimeMksec))
    {
        cout << "cycleTimeMksec" << endl;
    }
    if (mask->overlayEnable && (a.overlayEnable != b.overlayEnable))    
    {
        cout << "overlayEnable" << endl;
        return false;
    }
    if (mask->type && (a.type != b.type))
    {
        cout << "type" << endl;
        return false;
    }
    if (mask->custom1 && (a.custom1 != b.custom1))
    {
        cout << "custom1" << endl;
        return false;
    }
    if (mask->custom2 && (a.custom2 != b.custom2))
    {
        cout << "custom2" << endl;
        return false;
    }
    if (mask->custom3 && (a.custom3 != b.custom3))
    {
        cout << "custom3" << endl;
        return false;
    }

    return true;
}



bool copyTest()
{
    // Prepare random params.
    VStreamerParams in;
    fillRandomData(in);

    // Copy params.
    VStreamerParams out = in;

    // Compare params.
    return compareParams(in, out);
}



bool encodeDecodeTest()
{
    // Prepare random params.
    VStreamerParams in;
    fillRandomData(in);

    // Encode data.
    uint8_t data[1024];
    int size = 0;
    in.encode(data, 1024, size);

    cout << "Encoded data size: " << size << " bytes" << endl;

    // Decode data.
    VStreamerParams out;
    if (!out.decode(data, size))
    {
        cout << "Can't decode data" << endl;
        return false;
    }

    // Compare params.
    return compareParams(in, out);
}



bool encodeDecodeCommandsTest()
{
    // Encode command.
    uint8_t data[1024];
    int size = 0;
    float outValue = (float)(rand() % 20);
    VStreamer::encodeCommand(data, size, VStreamerCommand::RESTART);

    // Decode command.
    VStreamerCommand commandId;
    VStreamerParam paramId;
    float value = 0.0f;
    std::string strValue = "";
    if (VStreamer::decodeCommand(data, size, paramId, commandId, value, strValue) == -1)
    {
        cout << "Command not decoded" << endl;
        return false;
    }

    // Checkk ID and value.
    if (commandId != VStreamerCommand::RESTART)
    {
        cout << "not a VStreamerCommand::RESTART" << endl;
        return false;
    }

    // Encode param.
    outValue = (float)(rand() % 20);
    VStreamer::encodeSetParamCommand(data, size, VStreamerParam::WIDTH, outValue);

    // Decode command.
    value = 0.0f;
    strValue = "";
    if (VStreamer::decodeCommand(data, size, paramId, commandId, value, strValue) != 1)
    {
        cout << "Set param command not decoded" << endl;
        return false;
    }

    // Checkk ID and value.
    if (paramId != VStreamerParam::WIDTH)
    {
        cout << "not a VStreamerParam::WIDTH" << endl;
        return false;
    }
    if (value != outValue)
    {
        cout << "not equal value" << endl;
        return false;
    }

    return true;
}



bool jsonReadWriteTest()
{
    // Prepare random params.
    VStreamerParams in;
    fillRandomData(in);

    // Write params to file.
    cr::utils::ConfigReader inConfig;
    inConfig.set(in, "vStreamerParams");
    inConfig.writeToFile("TestVStreamerParams.json");

    // Read params from file.
    cr::utils::ConfigReader outConfig;
    if (!outConfig.readFromFile("TestVStreamerParams.json"))
    {
        cout << "Can't open config file" << endl;
        return false;
    }

    VStreamerParams out;
    if (!outConfig.get(out, "vStreamerParams"))
    {
        cout << "Can't read params from file" << endl;
        return false;
    }

    // Compare params.
    return compareParams(in, out);
}



bool encodeDecodeWithMaskTest()
{
    // Prepare random params.
    VStreamerParams in;
    fillRandomData(in);

    // Prepare random params mask.
    VStreamerParamsMask mask;
    mask.enable = true;
    mask.width = true;
    mask.height = false;
    mask.ip = true;
    mask.rtspPort = true;
    mask.rtpPort = false;
    mask.webRtcPort = true;
    mask.hlsPort = false;
    mask.srtPort = false;
    mask.rtmpPort = false;
    mask.metadataPort = true;
    mask.rtspEnable = true;
    mask.rtpEnable = true;
    mask.webRtcEnable = false;
    mask.hlsEnable = false;
    mask.srtEnable = true;
    mask.rtmpEnable = true;
    mask.metadataEnable = false;
    mask.rtspMulticastIp = true;
    mask.rtspMulticastPort = false;
    mask.user = false;
    mask.password = false;
    mask.suffix = false;
    mask.metadataSuffix = true;
    mask.minBitrateKbps = true;
    mask.maxBitrateKbps = false;
    mask.bitrateKbps = true;
    mask.bitrateMode = false;
    mask.fps = true;
    mask.gop = true;
    mask.h264Profile = true;
    mask.jpegQuality = false;
    mask.codec = false;
    mask.fitMode = false;
    mask.cycleTimeMksec = false;
    mask.overlayEnable = true;
    mask.type = true;
    mask.custom1 = true;
    mask.custom2 = false;
    mask.custom3 = true;

    // Encode data.
    uint8_t data[1024];
    int size = 0;
    in.encode(data, 1024, size, &mask);

    cout << "Encoded data size: " << size << " bytes" << endl;

    // Decode data.
    VStreamerParams out;
    if (!out.decode(data, size))
    {
        cout << "Can't decode data" << endl;
        return false;
    }

    // Compare params.
    return compareParams(in, out, &mask);
}