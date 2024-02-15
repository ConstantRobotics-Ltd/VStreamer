#include <iostream>
#include "VStreamer.h"



using namespace cr::video;
using namespace std;



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



bool copyTest()
{
    // Prepare random params.
    VStreamerParams in;
    in.enable = rand() % 2;
    in.width = rand() % 255;
    in.height = rand() % 255;
    in.ip = "afhjaskdm";
    in.port = rand() % 255;
    in.user = "afhidsjfnm";
    in.password = "adafsodjf";
    in.suffix = "asdasdasd";
    in.minBitrateKbps = rand() % 255;
    in.maxBitrateKbps = rand() % 255;
    in.bitrateKbps = rand() % 255;
    in.bitrateMode = rand() % 255;
    in.fps = rand() % 255;
    in.gop = true;
    in.h264Profile = rand() % 255;
    in.codec = "eydiucnksa";
    in.fitMode = rand() % 255;
    in.cycleTimeMksec = rand() % 255;
    in.overlayMode = rand() % 255;
    in.type = rand() % 255;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;

    // Copy params.
    VStreamerParams out = in;

    // Compare params.
    if (in.enable != out.enable)
    {
        cout << "in.enable" << endl;
        return false;
    }
    if (in.width != out.width)
    {
        cout << "in.width" << endl;
        return false;
    }
    if (in.height != out.height)
    {
        cout << "in.height" << endl;
        return false;
    }
    if (in.ip != out.ip)
    {
        cout << "in.ip" << endl;
        return false;
    }
    if (in.port != out.port)
    {
        cout << "in.port" << endl;
        return false;
    }
    if (in.user != out.user)
    {
        cout << "in.user" << endl;
        return false;
    }
    if (in.password != out.password)
    {
        cout << "in.password" << endl;
        return false;
    }
    if (in.suffix != out.suffix)
    {
        cout << "in.suffix" << endl;
        return false;
    }
    if (in.minBitrateKbps != out.minBitrateKbps)
    {
        cout << "in.minBitrateKbps" << endl;
        return false;
    }
    if (in.maxBitrateKbps != out.maxBitrateKbps)
    {
        cout << "in.maxBitrateKbps" << endl;
        return false;
    }
    if (in.bitrateKbps != out.bitrateKbps)
    {
        cout << "in.bitrateKbps" << endl;
        return false;
    }
    if (in.bitrateMode != out.bitrateMode)
    {
        cout << "in.bitrateMode" << endl;
        return false;
    }
    if (in.fps != out.fps)
    {
        cout << "in.fps" << endl;
        return false;
    }
    if (in.gop != out.gop)
    {
        cout << "in.gop" << endl;
        return false;
    }
    if (in.h264Profile != out.h264Profile)
    {
        cout << "in.h264Profile" << endl;
        return false;
    }
    if (in.jpegQuality != out.jpegQuality)
    {
        cout << "in.jpegQuality" << endl;
        return false;
    }
    if (in.codec != out.codec)
    {
        cout << "in.codec" << endl;
        return false;
    }
    if (in.fitMode != out.fitMode)
    {
        cout << "in.fitMode" << endl;
        return false;
    }
    if (in.cycleTimeMksec != out.cycleTimeMksec)
    {
        cout << "in.cycleTimeMksec" << endl;
        return false;
    }
    if (in.overlayMode != out.overlayMode)
    {
        cout << "in.overlayMode" << endl;
        return false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if (in.custom1 != out.custom1)
    {
        cout << "in.custom1" << std::endl;
        return false;
    }
    if (in.custom2 != out.custom2)
    {
        cout << "in.custom2" << std::endl;
        return false;
    }
    if (in.custom3 != out.custom3)
    {
        cout << "in.custom3" << std::endl;
        return false;
    }

    return true;
}



bool encodeDecodeTest()
{
    // Prepare random params.
    VStreamerParams in;
    in.enable = rand() % 2;
    in.width = rand() % 255;
    in.height = rand() % 255;
    in.ip = "afhjaskdm";
    in.port = rand() % 255;
    in.user = "afhidsjfnm";
    in.password = "adafsodjf";
    in.suffix = "asdasdasd";
    in.minBitrateKbps = rand() % 255;
    in.maxBitrateKbps = rand() % 255;
    in.bitrateKbps = rand() % 255;
    in.bitrateMode = rand() % 255;
    in.fps = rand() % 255;
    in.gop = true;
    in.h264Profile = rand() % 255;
    in.codec = "eydiucnksa";
    in.fitMode = rand() % 255;
    in.cycleTimeMksec = rand() % 255;
    in.overlayMode = rand() % 255;
    in.type = rand() % 255;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;

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
    if (in.enable != out.enable)
    {
        cout << "in.enable" << endl;
        return false;
    }
    if (in.width != out.width)
    {
        cout << "in.width" << endl;
        return false;
    }
    if (in.height != out.height)
    {
        cout << "in.height" << endl;
        return false;
    }
    if (in.ip != out.ip)
    {
        cout << "in.ip" << endl;
        return false;
    }
    if (in.port != out.port)
    {
        cout << "in.port" << endl;
        return false;
    }
    if (in.user != out.user)
    {
        cout << "in.user" << endl;
        return false;
    }
    if (in.password != out.password)
    {
        cout << "in.password" << endl;
        return false;
    }
    if (in.suffix != out.suffix)
    {
        cout << "in.suffix" << endl;
        return false;
    }
    if (in.minBitrateKbps != out.minBitrateKbps)
    {
        cout << "in.minBitrateKbps" << endl;
        return false;
    }
    if (in.maxBitrateKbps != out.maxBitrateKbps)
    {
        cout << "in.maxBitrateKbps" << endl;
        return false;
    }
    if (in.bitrateKbps != out.bitrateKbps)
    {
        cout << "in.bitrateKbps" << endl;
        return false;
    }
    if (in.bitrateMode != out.bitrateMode)
    {
        cout << "in.bitrateMode" << endl;
        return false;
    }
    if (in.fps != out.fps)
    {
        cout << "in.fps" << endl;
        return false;
    }
    if (in.gop != out.gop)
    {
        cout << "in.gop" << endl;
        return false;
    }
    if (in.h264Profile != out.h264Profile)
    {
        cout << "in.h264Profile" << endl;
        return false;
    }
    if (in.jpegQuality != out.jpegQuality)
    {
        cout << "in.jpegQuality" << endl;
        return false;
    }
    if (in.codec != out.codec)
    {
        cout << "in.codec" << endl;
        return false;
    }
    if (in.fitMode != out.fitMode)
    {
        cout << "in.fitMode" << endl;
        return false;
    }
    if (in.cycleTimeMksec != out.cycleTimeMksec)
    {
        cout << "in.cycleTimeMksec" << endl;
        return false;
    }
    if (in.overlayMode != out.overlayMode)
    {
        cout << "in.overlayMode" << endl;
        return false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if ((int)in.custom1 != (int)out.custom1)
    {
        cout << "in.custom1" << endl;
        return false;
    }
    if (in.custom2 != out.custom2)
    {
        cout << "in.custom2" << endl;
        return false;
    }
    if (in.custom3 != out.custom3)
    {
        cout << "in.custom3" << endl;
        return false;
    }

    return true;
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
    if (VStreamer::decodeCommand(data, size, paramId, commandId, value) != 0)
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
    if (VStreamer::decodeCommand(data, size, paramId, commandId, value) != 1)
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
    in.enable = rand() % 2;
    in.width = rand() % 255;
    in.height = rand() % 255;
    in.ip = "afhjaskdm";
    in.port = rand() % 255;
    in.user = "afhidsjfnm";
    in.password = "adafsodjf";
    in.suffix = "asdasdasd";
    in.minBitrateKbps = rand() % 255;
    in.maxBitrateKbps = rand() % 255;
    in.bitrateKbps = rand() % 255;
    in.bitrateMode = rand() % 255;
    in.fps = rand() % 255;
    in.gop = true;
    in.h264Profile = rand() % 255;
    in.codec = "eydiucnksa";
    in.fitMode = rand() % 255;
    in.overlayMode = rand() % 255;
    in.type = rand() % 255;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;

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
    if (in.enable != out.enable)
    {
        cout << "in.enable" << endl;
        return false;
    }
    if (in.width != out.width)
    {
        cout << "in.width" << endl;
        return false;
    }
    if (in.height != out.height)
    {
        cout << "in.height" << endl;
        return false;
    }
    if (in.ip != out.ip)
    {
        cout << "in.ip" << endl;
        return false;
    }
    if (in.port != out.port)
    {
        cout << "in.port" << endl;
        return false;
    }
    if (in.user != out.user)
    {
        cout << "in.user" << endl;
        return false;
    }
    if (in.password != out.password)
    {
        cout << "in.password" << endl;
        return false;
    }
    if (in.suffix != out.suffix)
    {
        cout << "in.suffix" << endl;
        return false;
    }
    if (in.minBitrateKbps != out.minBitrateKbps)
    {
        cout << "in.minBitrateKbps" << endl;
        return false;
    }
    if (in.maxBitrateKbps != out.maxBitrateKbps)
    {
        cout << "in.maxBitrateKbps" << endl;
        return false;
    }
    if (in.bitrateKbps != out.bitrateKbps)
    {
        cout << "in.bitrateKbps" << endl;
        return false;
    }
    if (in.bitrateMode != out.bitrateMode)
    {
        cout << "in.bitrateMode" << endl;
        return false;
    }
    if (in.fps != out.fps)
    {
        cout << "in.fps" << endl;
        return false;
    }
    if (in.gop != out.gop)
    {
        cout << "in.gop" << endl;
        return false;
    }
    if (in.h264Profile != out.h264Profile)
    {
        cout << "in.h264Profile" << endl;
        return false;
    }
    if (in.jpegQuality != out.jpegQuality)
    {
        cout << "in.jpegQuality" << endl;
        return false;
    }
    if (in.codec != out.codec)
    {
        cout << "in.codec" << endl;
        return false;
    }
    if (in.fitMode != out.fitMode)
    {
        cout << "in.fitMode" << endl;
        return false;
    }
    if (in.overlayMode != out.overlayMode)
    {
        cout << "in.overlayMode" << endl;
        return false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if (in.custom1 != out.custom1)
    {
        cout << "in.custom1" << endl;
        return false;
    }
    if (in.custom2 != out.custom2)
    {
        cout << "in.custom2" << endl;
        return false;
    }
    if (in.custom3 != out.custom3)
    {
        cout << "in.custom3" << endl;
        return false;
    }

    return true;
}



bool encodeDecodeWithMaskTest()
{
    // Prepare random params.
    VStreamerParams in;
    in.enable = rand() % 2;
    in.width = rand() % 255;
    in.height = rand() % 255;
    in.ip = "afhjaskdm";
    in.port = rand() % 255;
    in.user = "afhidsjfnm";
    in.password = "adafsodjf";
    in.suffix = "asdasdasd";
    in.minBitrateKbps = rand() % 255;
    in.maxBitrateKbps = rand() % 255;
    in.bitrateKbps = rand() % 255;
    in.bitrateMode = rand() % 255;
    in.fps = rand() % 255;
    in.gop = true;
    in.h264Profile = rand() % 255;
    in.codec = "eydiucnksa";
    in.fitMode = rand() % 255;
    in.cycleTimeMksec = rand() % 255;
    in.overlayMode = rand() % 255;
    in.type = rand() % 255;
    in.custom1 = rand() % 255;
    in.custom2 = rand() % 255;
    in.custom3 = rand() % 255;

    // Prepare params mask.
    VStreamerParamsMask mask;
    mask.enable = true;
    mask.width = false;
    mask.height = true;
    mask.ip = false;
    mask.port = true;
    mask.user = false;
    mask.password = true;
    mask.suffix = false;
    mask.minBitrateKbps = true;
    mask.maxBitrateKbps = false;
    mask.bitrateKbps = true;
    mask.bitrateMode = false;
    mask.fps = true;
    mask.gop = false;
    mask.h264Profile = true;
    mask.jpegQuality = false;
    mask.codec = true;
    mask.fitMode = false;
    mask.cycleTimeMksec = true;
    mask.overlayMode = false;
    mask.type = true;
    mask.custom1 = false;
    mask.custom2 = true;
    mask.custom3 = false;

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
    if (in.enable != out.enable)
    {
        cout << "in.enable" << endl;
        return false;
    }
    if (0 != out.width)
    {
        cout << "in.width" << endl;
        return false;
    }
    if (in.height != out.height)
    {
        cout << "in.height" << endl;
        return false;
    }
    if ("" != out.ip)
    {
        cout << "in.ip" << endl;
        return false;
    }
    if (in.port != out.port)
    {
        cout << "in.port" << endl;
        return false;
    }
    if ("" != out.user)
    {
        cout << "in.user" << endl;
        return false;
    }
    if (in.password != out.password)
    {
        cout << "in.password" << endl;
        return false;
    }
    if ("" != out.suffix)
    {
        cout << "in.suffix" << endl;
        return false;
    }
    if (in.minBitrateKbps != out.minBitrateKbps)
    {
        cout << "in.minBitrateKbps" << endl;
        return false;
    }
    if (0 != out.maxBitrateKbps)
    {
        cout << "in.maxBitrateKbps" << endl;
        return false;
    }
    if (in.bitrateKbps != out.bitrateKbps)
    {
        cout << "in.bitrateKbps" << endl;
        return false;
    }
    if (0 != out.bitrateMode)
    {
        cout << "in.bitrateMode" << endl;
        return false;
    }
    if (in.fps != out.fps)
    {
        cout << "in.fps" << endl;
        return false;
    }
    if (0 != out.gop)
    {
        cout << "in.gop" << endl;
        return false;
    }
    if (in.h264Profile != out.h264Profile)
    {
        cout << "in.h264Profile" << endl;
        return false;
    }
    if (0 != out.jpegQuality)
    {
        cout << "in.jpegQuality" << endl;
        return false;
    }
    if (in.codec != out.codec)
    {
        cout << "in.codec" << endl;
        return false;
    }
    if (-1 != out.fitMode)
    {
        cout << "in.fitMode" << endl;
        return false;
    }
    if (in.cycleTimeMksec != out.cycleTimeMksec)
    {
        cout << "in.cycleTimeMksec" << endl;
        return false;
    }
    if (false != out.overlayMode)
    {
        cout << "in.overlayMode" << endl;
        return false;
    }
    if (in.type != out.type)
    {
        cout << "in.type" << endl;
        return false;
    }
    if (-1 != out.custom1)
    {
        cout << "in.custom1" << endl;
        return false;
    }
    if (in.custom2 != out.custom2)
    {
        cout << "in.custom2" << endl;
        return false;
    }
    if (-1 != out.custom3)
    {
        cout << "in.custom3" << endl;
        return false;
    }
    return true;
}