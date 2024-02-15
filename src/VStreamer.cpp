#include "VStreamer.h"
#include "VStreamerVersion.h"



#define checkBit(byte, position) ((byte) & (1 << (position)))



using namespace cr::video;
using namespace std;



VStreamer::~VStreamer()
{
    // Empty.
}



string VStreamer::getVersion()
{
    return VSTREAMER_VERSION;
}



VStreamerParams &VStreamerParams::operator=(const VStreamerParams &src)
{
    // Check yourself.
    if (this == &src)
        return *this;

    // Copy params.
    enable = src.enable;
    width = src.width;
    height = src.height;
    ip = src.ip;
    port = src.port;
    user = src.user;
    password = src.password;
    suffix = src.suffix;
    minBitrateKbps = src.minBitrateKbps;
    maxBitrateKbps = src.maxBitrateKbps;
    bitrateKbps = src.bitrateKbps;
    bitrateMode = src.bitrateMode;
    fps = src.fps;
    gop = src.gop;
    h264Profile = src.h264Profile;
    jpegQuality = src.jpegQuality;
    codec = src.codec;
    fitMode = src.fitMode;
    cycleTimeMksec = src.cycleTimeMksec;
    overlayMode = src.overlayMode;
    type = src.type;
    custom1 = src.custom1;
    custom2 = src.custom2;
    custom3 = src.custom3;

    return *this;
}



bool VStreamerParams::encode(uint8_t *data, int bufferSize, int &size, VStreamerParamsMask *mask)
{
    // Check buffer size.
    if (bufferSize < 8)
    {
        size = 0;
        return false;
    }

    /*  Indices of datas in buffer.
        0 = header with value 0x02
        1 and 2 = versions
        3, 4 and 5 = Masks
        6 = int size from source system in terms bytes
        7 = start of actual data.
    */

    // Encode version.
    int pos = 0;
    data[0] = 0x02;
    data[1] = VSTREAMER_MAJOR_VERSION;
    data[2] = VSTREAMER_MINOR_VERSION;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = sizeof(int);

    size = 8;
    pos = 8;

    if (mask == nullptr)
    {

        // start of actual data.

        if (bufferSize < pos + sizeof(bool))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &enable, sizeof(bool));
        pos += sizeof(bool);
        data[3] |= (1 << 7);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &width, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 6);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &height, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 5);

        if (bufferSize < pos + ip.size() + 1)
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], ip.c_str(), ip.size() + 1);
        pos += ip.size() + 1;
        data[3] |= (1 << 4);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &port, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 3);

        if (bufferSize < pos + user.size() + 1)
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], user.c_str(), user.size() + 1);
        pos += user.size() + 1;
        data[3] |= (1 << 2);

        if (bufferSize < pos + suffix.size() + 1)
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], suffix.c_str(), suffix.size() + 1);
        pos += suffix.size() + 1;
        data[3] |= (1 << 1);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &minBitrateKbps, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 0);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &maxBitrateKbps, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 7);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &bitrateKbps, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 6);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &bitrateMode, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 5);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        int tempFps = fps;
        memcpy(&data[pos], &tempFps, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 4);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &gop, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 3);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &h264Profile, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 2);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &jpegQuality, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 1);

        if (bufferSize < pos + codec.size() + 1)
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], codec.c_str(), codec.size() + 1);
        pos += codec.size() + 1;
        data[5] |= (1 << 7);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &fitMode, sizeof(int));
        pos += sizeof(int);
        data[5] |= (1 << 6);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &cycleTimeMksec, sizeof(int));
        pos += sizeof(int);
        data[5] |= (1 << 5);

        if (bufferSize < pos + password.size() + 1)
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], password.c_str(), password.size() + 1);
        pos += password.size() + 1;
        data[5] |= (1 << 4);

        if (bufferSize < pos + sizeof(bool))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &overlayMode, sizeof(bool));
        pos += sizeof(bool);
        data[5] |= (1 << 3);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        memcpy(&data[pos], &type, sizeof(int));
        pos += sizeof(int);
        data[5] |= (1 << 2);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        int tempCustom1 = custom1;
        memcpy(&data[pos], &tempCustom1, sizeof(int));
        pos += sizeof(int);
        data[5] |= (1 << 1);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        int tempCustom2 = custom2;
        memcpy(&data[pos], &tempCustom2, sizeof(int));
        pos += sizeof(int);
        data[5] |= (1 << 0);

        if (bufferSize < pos + sizeof(int))
        {
            size = pos;
            return true;
        }
        int tempCustom3 = custom3;
        memcpy(&data[pos], &tempCustom3, sizeof(int));
        pos += sizeof(int);
        data[6] |= (1 << 7);

        size = pos;
        return true;
    }

    // start of actual data with masks.
    if (mask->enable && (bufferSize > pos + sizeof(bool)))
    {
        memcpy(&data[pos], &enable, sizeof(bool));
        pos += sizeof(bool);
        data[3] |= (1 << 7);
    }

    if (mask->width && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &width, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 6);
    }

    if (mask->height && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &height, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 5);
    }

    if (mask->ip && (bufferSize > pos + ip.size() + 1))
    {
        memcpy(&data[pos], ip.c_str(), ip.size() + 1);
        pos += ip.size() + 1;
        data[3] |= (1 << 4);
    }

    if (mask->port && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &port, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 3);
    }

    if (mask->user && (bufferSize > pos + user.size() + 1))
    {
        memcpy(&data[pos], user.c_str(), user.size() + 1);
        pos += user.size() + 1;
        data[3] |= (1 << 2);
    }

    if (mask->suffix && (bufferSize > pos + user.size() + 1))
    {
        memcpy(&data[pos], suffix.c_str(), suffix.size() + 1);
        pos += suffix.size() + 1;
        data[3] |= (1 << 1);
    }

    if (mask->minBitrateKbps && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &minBitrateKbps, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 0);
    }

    if (mask->maxBitrateKbps && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &maxBitrateKbps, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 7);
    }

    if (mask->bitrateKbps && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &bitrateKbps, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 6);
    }

    if (mask->bitrateMode && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &bitrateMode, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 5);
    }

    if (mask->fps && (bufferSize > pos + sizeof(int)))
    {
        int tempFps = fps;
        memcpy(&data[pos], &tempFps, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 4);
    }

    if (mask->gop && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &gop, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 3);
    }

    if (mask->h264Profile && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &h264Profile, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 2);
    }

    if (mask->jpegQuality && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &jpegQuality, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 1);
    }

    if (mask->codec && (bufferSize > pos + user.size() + 1))
    {
        memcpy(&data[pos], codec.c_str(), codec.size() + 1);
        pos += codec.size() + 1;
        data[5] |= (1 << 7);
    }

    if (mask->fitMode && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &fitMode, sizeof(int));
        pos += sizeof(int);
        data[5] |= (1 << 6);
    }

    if (mask->cycleTimeMksec && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &cycleTimeMksec, sizeof(int));
        pos += sizeof(int);
        data[5] |= (1 << 5);
    }

    if (mask->password && (bufferSize > pos + password.size() + 1))
    {
        memcpy(&data[pos], password.c_str(), password.size() + 1);
        pos += password.size() + 1;
        data[5] |= (1 << 4);
    }

    if (mask->overlayMode && (bufferSize > pos + sizeof(bool)))
    {
        memcpy(&data[pos], &overlayMode, sizeof(bool));
        pos += sizeof(bool);
        data[5] |= (1 << 3);
    }

    if (mask->type && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &type, sizeof(int));
        pos += sizeof(int);
        data[5] |= (1 << 2);
    }

    if (mask->custom1 && (bufferSize > pos + sizeof(int)))
    {
        int tempCustom1 = custom1;
        memcpy(&data[pos], &tempCustom1, sizeof(int));
        pos += sizeof(int);
        data[5] |= (1 << 1);
    }

    if (mask->custom2 && (bufferSize > pos + sizeof(int)))
    {
        int tempCustom2 = custom2;
        memcpy(&data[pos], &tempCustom2, sizeof(int));
        pos += sizeof(int);
        data[5] |= (1 << 0);
    }

    if (mask->custom3 && (bufferSize > pos + sizeof(int)))
    {
        int tempCustom3 = custom3;
        memcpy(&data[pos], &tempCustom3, sizeof(int));
        pos += sizeof(int);
        data[6] |= (1 << 7);
    }

    size = pos;

    return true;
}



bool VStreamerParams::decode(uint8_t *data, int dataSize)
{

    /*
        0 = header with value 0x02
        1 and 2 = versions
        3, 4 and 5 = Masks
        6 = int size from source system in terms bytes
        7 = start of actual data.
    */

    // Check data size.
    if (dataSize < 8)
        return false;

    // Check header.
    if (data[0] != 0x02)
        return false;

    // Decode version.
    if (data[1] != VSTREAMER_MAJOR_VERSION)
        return false;
    if (data[2] != VSTREAMER_MINOR_VERSION)
        return false;

    // get int size from source system.
    int sizeInt = data[7];

    // start of actual data.
    int pos = 8;

    if (checkBit(data[3], 7))
    {
        if (dataSize < pos + 1)
            return false;
        memcpy(&enable, &data[pos], sizeof(bool));
        pos += sizeof(bool);
    }
    else
    {
        enable = false;
    }

    if (checkBit(data[3], 6))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&width, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        width = 0;
    }

    if (checkBit(data[3], 5))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&height, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        height = 0;
    }

    if (checkBit(data[3], 4))
    {
        char *tempVal = new char[50]; // 50 is enough big for any array.
        strcpy(tempVal, (char *)&data[pos]);
        pos += strlen(tempVal) + 1;
        ip = tempVal;
        delete[] tempVal;
    }
    else
    {
        ip = "";
    }

    if (checkBit(data[3], 3))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&port, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        port = 0;
    }

    if (checkBit(data[3], 2))
    {
        char *tempVal = new char[50]; // 50 is enough big for any array.
        strcpy(tempVal, (char *)&data[pos]);
        pos += strlen(tempVal) + 1;
        user = tempVal;
        delete[] tempVal;
    }
    else
    {
        user = "";
    }

    if (checkBit(data[3], 1))
    {
        char *tempVal = new char[50]; // 50 is enough big for any array.
        strcpy(tempVal, (char *)&data[pos]);
        pos += strlen(tempVal) + 1;
        suffix = tempVal;
        delete[] tempVal;
    }
    else
    {
        suffix = "";
    }

    if (checkBit(data[3], 0))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&minBitrateKbps, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        minBitrateKbps = 0;
    }

    if (checkBit(data[4], 7))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&maxBitrateKbps, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        maxBitrateKbps = 0;
    }

    if (checkBit(data[4], 6))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&bitrateKbps, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        bitrateKbps = 0;
    }

    if (checkBit(data[4], 5))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&bitrateMode, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        bitrateMode = 0.0f;
    }

    if (checkBit(data[4], 4))
    {
        if (dataSize < pos + sizeInt)
            return false;
        int tempFps;
        memcpy(&tempFps, &data[pos], sizeInt);
        pos += sizeInt;
        fps = tempFps;
    }
    else
    {
        fps = 0;
    }

    if (checkBit(data[4], 3))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&gop, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        gop = 0;
    }

    if (checkBit(data[4], 2))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&h264Profile, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        h264Profile = -1;
    }

    if (checkBit(data[4], 1))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&jpegQuality, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        jpegQuality = 0;
    }

    if (checkBit(data[5], 7))
    {
        char *tempVal = new char[50]; // 50 is enough big for any array.
        strcpy(tempVal, (char *)&data[pos]);
        pos += strlen(tempVal) + 1;
        codec = tempVal;
        delete[] tempVal;
    }
    else
    {
        codec = "";
    }

    if (checkBit(data[5], 6))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&fitMode, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        fitMode = -1;
    }

    if (checkBit(data[5], 5))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&cycleTimeMksec, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        cycleTimeMksec = -1;
    }

    if (checkBit(data[5], 4))
    {
        char *tempVal = new char[50]; // 50 is enough big for any array.
        strcpy(tempVal, (char *)&data[pos]);
        pos += strlen(tempVal) + 1;
        password = tempVal;
        delete[] tempVal;
    }
    else
    {
        password = "";
    }

    if (checkBit(data[5], 3))
    {
        if (dataSize < pos + 1)
            return false;
        memcpy(&overlayMode, &data[pos], sizeof(bool));
        pos += sizeof(bool);
    }
    else
    {
        overlayMode = false;
    }

    if (checkBit(data[5], 2))
    {
        if (dataSize < pos + sizeInt)
            return false;
        memcpy(&type, &data[pos], sizeInt);
        pos += sizeInt;
    }
    else
    {
        type = -1;
    }

    if (checkBit(data[5], 1))
    {
        if (dataSize < pos + sizeInt)
            return false;
        int tempCustom1;
        memcpy(&tempCustom1, &data[pos], sizeInt);
        pos += sizeInt;
        custom1 = tempCustom1;
    }
    else
    {
        custom1 = -1;
    }

    if (checkBit(data[5], 0))
    {
        if (dataSize < pos + sizeInt)
            return false;
        int tempCustom2;
        memcpy(&tempCustom2, &data[pos], sizeInt);
        pos += sizeInt;
        custom2 = tempCustom2;
    }
    else
    {
        custom2 = -1;
    }

    if (checkBit(data[6], 7))
    {
        if (dataSize < pos + sizeInt)
            return false;
        int tempCustom3;
        memcpy(&tempCustom3, &data[pos], sizeInt);
        pos += sizeInt;
        custom3 = tempCustom3;
    }
    else
    {
        custom3 = -1;
    }

    return true;
}



void VStreamer::encodeSetParamCommand(
    uint8_t *data, int &size, VStreamerParam id, float value)
{
    // Fill header.
    data[0] = 0x01;
    data[1] = VSTREAMER_MAJOR_VERSION;
    data[2] = VSTREAMER_MINOR_VERSION;

    // Fill data.
    int paramId = (int)id;
    memcpy(&data[3], &paramId, 4);
    memcpy(&data[7], &value, 4);
    size = 11;
}



void cr::video::VStreamer::encodeCommand(uint8_t *data,
                                         int &size,
                                         cr::video::VStreamerCommand id)
{
    // Fill header.
    data[0] = 0x00;
    data[1] = VSTREAMER_MAJOR_VERSION;
    data[2] = VSTREAMER_MINOR_VERSION;

    // Fill data.
    int commandId = (int)id;
    memcpy(&data[3], &commandId, 4);
    size = 7;
}



int cr::video::VStreamer::decodeCommand(uint8_t *data,
                                        int size,
                                        cr::video::VStreamerParam &paramId,
                                        cr::video::VStreamerCommand &commandId,
                                        float &value)
{
    // Check size.
    if (size < 7)
        return -1;

    // Check version.
    if (data[1] != VSTREAMER_MAJOR_VERSION || data[2] != VSTREAMER_MINOR_VERSION)
        return -1;

    // Extract data.
    int id = 0;
    memcpy(&id, &data[3], 4);
    value = 0.0f;

    // Check command type.
    if (data[0] == 0x00)
    {
        commandId = (VStreamerCommand)id;
        return 0;
    }
    else if (data[0] == 0x01)
    {
        // Check size.
        if (size != 11)
            return false;

        paramId = (VStreamerParam)id;
        memcpy(&value, &data[7], 4);
        return 1;
    }

    return -1;
}