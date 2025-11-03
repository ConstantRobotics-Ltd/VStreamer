#include "VStreamer.h"
#include "VStreamerVersion.h"
#include <string>
#include <cstring>


// Macro to check bit in byte.
#define checkBit(byte, position) ((byte) & (1 << (position)))


// Link namespaces.
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



bool VStreamerParams::serialize(uint8_t *data, int bufferSize, int &size, VStreamerParamsMask *mask)
{
    // Check buffer size.
    if (bufferSize < 11) // Header + one bool parameter.
    {
        size = 0;
        return false;
    }

    // Fill header.
    data[0] = 0x02; // Header.
    data[1] = VSTREAMER_MAJOR_VERSION; // Major version.
    data[2] = VSTREAMER_MINOR_VERSION; // Minor version.
    data[3] = 0; // Parameter mask byte 1
    data[4] = 0; // Parameter mask byte 2
    data[5] = 0; // Parameter mask byte 3
    data[6] = 0; // Parameter mask byte 4
    data[7] = 0; // Parameter mask byte 5
    data[8] = 0; // Parameter mask byte 6
    data[9] = 0; // Parameter mask byte 7

    // If mask is not initialized then encode all parameters.
    VStreamerParamsMask defaultMask;
    if (mask == nullptr)
        mask = &defaultMask;
    
    // Fill data.
    int pos = 10;

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

    if (mask->rtspPort && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &rtspPort, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 3);
    }

    if (mask->rtpPort && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &rtpPort, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 2);
    }

    if (mask->webRtcPort && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &webRtcPort, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 1);
    }

    if (mask->hlsPort && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &hlsPort, sizeof(int));
        pos += sizeof(int);
        data[3] |= (1 << 0);
    }

    if (mask->srtPort && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &srtPort, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 7);
    }

    if (mask->rtmpPort && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &rtmpPort, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 6);
    }

    if (mask->metadataPort && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &metadataPort, sizeof(int));
        pos += sizeof(int);
        data[4] |= (1 << 5);
    }

    if (mask->rtspEnable && (bufferSize > pos + sizeof(bool)))
    {
        memcpy(&data[pos], &rtspEnable, sizeof(bool));
        pos += sizeof(bool);
        data[4] |= (1 << 4);
    }

    if (mask->rtpEnable && (bufferSize > pos + sizeof(bool)))
    {
        memcpy(&data[pos], &rtpEnable, sizeof(bool));
        pos += sizeof(bool);
        data[4] |= (1 << 3);
    }

    if (mask->webRtcEnable && (bufferSize > pos + sizeof(bool)))
    {
        memcpy(&data[pos], &webRtcEnable, sizeof(bool));
        pos += sizeof(bool);
        data[4] |= (1 << 2);
    }

    if (mask->hlsEnable && (bufferSize > pos + sizeof(bool)))
    {
        memcpy(&data[pos], &hlsEnable, sizeof(bool));
        pos += sizeof(bool);
        data[4] |= (1 << 1);
    }

    if (mask->srtEnable && (bufferSize > pos + sizeof(bool)))
    {
        memcpy(&data[pos], &srtEnable, sizeof(bool));
        pos += sizeof(bool);
        data[4] |= (1 << 0);
    }

    if (mask->rtmpEnable && (bufferSize > pos + sizeof(bool)))
    {
        memcpy(&data[pos], &rtmpEnable, sizeof(bool));
        pos += sizeof(bool);
        data[5] |= (1 << 7);
    }

    if (mask->metadataEnable && (bufferSize > pos + sizeof(bool)))
    {
        memcpy(&data[pos], &metadataEnable, sizeof(bool));
        pos += sizeof(bool);
        data[5] |= (1 << 6);
    }

    if (mask->rtspMulticastIp && (bufferSize > pos + rtspMulticastIp.size() + 1))
    {
        memcpy(&data[pos], rtspMulticastIp.c_str(), rtspMulticastIp.size() + 1);
        pos += rtspMulticastIp.size() + 1;
        data[5] |= (1 << 5);
    }

    if (mask->rtspMulticastPort && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &rtspMulticastPort, sizeof(int));
        pos += sizeof(int);
        data[5] |= (1 << 4);
    }

    if (mask->user && (bufferSize > pos + user.size() + 1))
    {
        memcpy(&data[pos], user.c_str(), user.size() + 1);
        pos += user.size() + 1;
        data[5] |= (1 << 3);
    }

    if (mask->password && (bufferSize > pos + password.size() + 1))
    {
        memcpy(&data[pos], password.c_str(), password.size() + 1);
        pos += password.size() + 1;
        data[5] |= (1 << 2);
    }

    if (mask->suffix && (bufferSize > pos + suffix.size() + 1))
    {
        memcpy(&data[pos], suffix.c_str(), suffix.size() + 1);
        pos += suffix.size() + 1;
        data[5] |= (1 << 1);
    }

    if (mask->metadataSuffix && (bufferSize > pos + metadataSuffix.size() + 1))
    {
        memcpy(&data[pos], metadataSuffix.c_str(), metadataSuffix.size() + 1);
        pos += metadataSuffix.size() + 1;
        data[5] |= (1 << 0);
    }

    if (mask->minBitrateKbps && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &minBitrateKbps, sizeof(int));
        pos += sizeof(int);
        data[6] |= (1 << 7);
    }

    if (mask->maxBitrateKbps && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &maxBitrateKbps, sizeof(int));
        pos += sizeof(int);
        data[6] |= (1 << 6);
    }

    if (mask->bitrateKbps && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &bitrateKbps, sizeof(int));
        pos += sizeof(int);
        data[6] |= (1 << 5);
    }

    if (mask->bitrateMode && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &bitrateMode, sizeof(int));
        pos += sizeof(int);
        data[6] |= (1 << 4);
    }

    if (mask->fps && (bufferSize > pos + sizeof(float)))
    {
        memcpy(&data[pos], &fps, sizeof(float));
        pos += sizeof(float);
        data[6] |= (1 << 3);
    }

    if (mask->gop && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &gop, sizeof(int));
        pos += sizeof(int);
        data[6] |= (1 << 2);
    }

    if (mask->h264Profile && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &h264Profile, sizeof(int));
        pos += sizeof(int);
        data[6] |= (1 << 1);
    }

    if (mask->jpegQuality && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &jpegQuality, sizeof(int));
        pos += sizeof(int);
        data[6] |= (1 << 0);
    }

    if (mask->codec && (bufferSize > pos + codec.size() + 1))
    {
        memcpy(&data[pos], codec.c_str(), codec.size() + 1);
        pos += codec.size() + 1;
        data[7] |= (1 << 7);
    }

    if (mask->fitMode && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &fitMode, sizeof(int));
        pos += sizeof(int);
        data[7] |= (1 << 6);
    }

    if (mask->cycleTimeUs && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &cycleTimeUs, sizeof(int));
        pos += sizeof(int);
        data[7] |= (1 << 5);
    }

    if (mask->overlayEnable && (bufferSize > pos + sizeof(bool)))
    {
        memcpy(&data[pos], &overlayEnable, sizeof(bool));
        pos += sizeof(bool);
        data[7] |= (1 << 4);
    }

    if (mask->type && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &type, sizeof(int));
        pos += sizeof(int);
        data[7] |= (1 << 3);
    }

    if (mask->custom1 && (bufferSize > pos + sizeof(float)))
    {
        memcpy(&data[pos], &custom1, sizeof(float));
        pos += sizeof(float);
        data[7] |= (1 << 2);
    }

    if (mask->custom2 && (bufferSize > pos + sizeof(float)))
    {
        memcpy(&data[pos], &custom2, sizeof(float));
        pos += sizeof(float);
        data[7] |= (1 << 1);
    }

    if (mask->custom3 && (bufferSize > pos + sizeof(float)))
    {
        memcpy(&data[pos], &custom3, sizeof(float));
        pos += sizeof(float);
        data[7] |= (1 << 0);
    }

    if (mask->rtspKey && (bufferSize > pos + rtspKey.size() + 1))
    {
        memcpy(&data[pos], rtspKey.c_str(), rtspKey.size() + 1);
        pos += rtspKey.size() + 1;
        data[8] |= (1 << 7);
    }

    if (mask->rtspCert && (bufferSize > pos + rtspCert.size() + 1))
    {
        memcpy(&data[pos], rtspCert.c_str(), rtspCert.size() + 1);
        pos += rtspCert.size() + 1;
        data[8] |= (1 << 6);
    }

    if (mask->webRtcKey && (bufferSize > pos + webRtcKey.size() + 1))
    {
        memcpy(&data[pos], webRtcKey.c_str(), webRtcKey.size() + 1);
        pos += webRtcKey.size() + 1;
        data[8] |= (1 << 5);
    }

    if (mask->webRtcCert && (bufferSize > pos + webRtcCert.size() + 1))
    {
        memcpy(&data[pos], webRtcCert.c_str(), webRtcCert.size() + 1);
        pos += webRtcCert.size() + 1;
        data[8] |= (1 << 4);
    }

    if (mask->hlsKey && (bufferSize > pos + hlsKey.size() + 1))
    {
        memcpy(&data[pos], hlsKey.c_str(), hlsKey.size() + 1);
        pos += hlsKey.size() + 1;
        data[8] |= (1 << 3);
    }

    if (mask->hlsCert && (bufferSize > pos + hlsCert.size() + 1))
    {
        memcpy(&data[pos], hlsCert.c_str(), hlsCert.size() + 1);
        pos += hlsCert.size() + 1;
        data[8] |= (1 << 2);
    }

    if (mask->rtmpKey && (bufferSize > pos + rtmpKey.size() + 1))
    {
        memcpy(&data[pos], rtmpKey.c_str(), rtmpKey.size() + 1);
        pos += rtmpKey.size() + 1;
        data[8] |= (1 << 1);
    }

    if (mask->rtmpCert && (bufferSize > pos + rtmpCert.size() + 1))
    {
        memcpy(&data[pos], rtmpCert.c_str(), rtmpCert.size() + 1);
        pos += rtmpCert.size() + 1;
        data[8] |= (1 << 0);
    }

    if (mask->rtspEncryption && (bufferSize > pos + rtspEncryption.size() + 1))
    {
        memcpy(&data[pos], rtspEncryption.c_str(), rtspEncryption.size() + 1);
        pos += rtspEncryption.size() + 1;
        data[9] |= (1 << 7);
    }

    if (mask->webRtcEncryption && (bufferSize > pos + webRtcEncryption.size() + 1))
    {
        memcpy(&data[pos], webRtcEncryption.c_str(), webRtcEncryption.size() + 1);
        pos += webRtcEncryption.size() + 1;
        data[9] |= (1 << 6);
    }

    if (mask->rtmpEncryption && (bufferSize > pos + rtmpEncryption.size() + 1))
    {
        memcpy(&data[pos], rtmpEncryption.c_str(), rtmpEncryption.size() + 1);
        pos += rtmpEncryption.size() + 1;
        data[9] |= (1 << 5);
    }

    if (mask->hlsEncryption && (bufferSize > pos + hlsEncryption.size() + 1))
    {
        memcpy(&data[pos], hlsEncryption.c_str(), hlsEncryption.size() + 1);
        pos += hlsEncryption.size() + 1;
        data[9] |= (1 << 4);
    }

    if (mask->logLevel && (bufferSize > pos + sizeof(int)))
    {
        memcpy(&data[pos], &logLevel, sizeof(int));
        pos += sizeof(int);
        data[9] |= (1 << 3);
    }

    size = pos;

    return true;
}



bool VStreamerParams::deserialize(uint8_t *data, int dataSize)
{
    // Check data size.
    if (dataSize < 11)
        return false;

    // Check header.
    if (data[0] != 0x02)
        return false;

    // Decode version.
    if (data[1] != VSTREAMER_MAJOR_VERSION || data[2] != VSTREAMER_MINOR_VERSION)
        return false;

    // Array for string conversion.
    char strArray[512];

    // Start of actual data.
    int pos = 10;

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
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&width, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        width = 0;
    }

    if (checkBit(data[3], 5))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&height, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        height = 0;
    }

    if (checkBit(data[3], 4))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        ip = strArray;
    }
    else
    {
        ip = "";
    }

    if (checkBit(data[3], 3))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&rtspPort, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        rtspPort = 0;
    }

    if (checkBit(data[3], 2))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&rtpPort, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        rtpPort = 0;
    }

    if (checkBit(data[3], 1))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&webRtcPort, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        webRtcPort = 0;
    }

    if (checkBit(data[3], 0))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&hlsPort, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        hlsPort = 0;
    }

    if (checkBit(data[4], 7))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&srtPort, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        srtPort = 0;
    }

    if (checkBit(data[4], 6))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&rtmpPort, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        rtmpPort = 0;
    }

    if (checkBit(data[4], 5))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&metadataPort, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        metadataPort = 0;
    }

    if (checkBit(data[4], 4))
    {
        if (dataSize < pos + 1)
            return false;
        memcpy(&rtspEnable, &data[pos], sizeof(bool));
        pos += sizeof(bool);
    }
    else
    {
        rtspEnable = false;
    }

    if (checkBit(data[4], 3))
    {
        if (dataSize < pos + 1)
            return false;
        memcpy(&rtpEnable, &data[pos], sizeof(bool));
        pos += sizeof(bool);
    }
    else
    {
        rtpEnable = false;
    }

    if (checkBit(data[4], 2))
    {
        if (dataSize < pos + 1)
            return false;
        memcpy(&webRtcEnable, &data[pos], sizeof(bool));
        pos += sizeof(bool);
    }
    else
    {
        webRtcEnable = false;
    }

    if (checkBit(data[4], 1))
    {
        if (dataSize < pos + 1)
            return false;
        memcpy(&hlsEnable, &data[pos], sizeof(bool));
        pos += sizeof(bool);
    }
    else
    {
        hlsEnable = false;
    }

    if (checkBit(data[4], 0))
    {
        if (dataSize < pos + 1)
            return false;
        memcpy(&srtEnable, &data[pos], sizeof(bool));
        pos += sizeof(bool);
    }
    else
    {
        srtEnable = false;
    }

    if (checkBit(data[5], 7))
    {
        if (dataSize < pos + 1)
            return false;
        memcpy(&rtmpEnable, &data[pos], sizeof(bool));
        pos += sizeof(bool);
    }
    else
    {
        rtmpEnable = false;
    }

    if (checkBit(data[5], 6))
    {
        if (dataSize < pos + 1)
            return false;
        memcpy(&metadataEnable, &data[pos], sizeof(bool));
        pos += sizeof(bool);
    }
    else
    {
        metadataEnable = false;
    }

    if (checkBit(data[5], 5))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        rtspMulticastIp = strArray;
    }
    else
    {
        rtspMulticastIp = "";
    }

    if (checkBit(data[5], 4))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&rtspMulticastPort, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        rtspMulticastPort = 0;
    }

    if (checkBit(data[5], 3))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        user = strArray;
    }
    else
    {
        user = "";
    }

    if (checkBit(data[5], 2))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        password = strArray;
    }
    else
    {
        password = "";
    }

    if (checkBit(data[5], 1))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        suffix = strArray;
    }
    else
    {
        suffix = "";
    }

    if (checkBit(data[5], 0))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        metadataSuffix = strArray;
    }
    else
    {
        metadataSuffix = "";
    }

    if (checkBit(data[6], 7))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&minBitrateKbps, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        minBitrateKbps = 0;
    }

    if (checkBit(data[6], 6))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&maxBitrateKbps, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        maxBitrateKbps = 0;
    }

    if (checkBit(data[6], 5))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&bitrateKbps, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        bitrateKbps = 0;
    }

    if (checkBit(data[6], 4))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&bitrateMode, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        bitrateMode = 0;
    }

    if (checkBit(data[6], 3))
    {
        if (dataSize < pos + sizeof(float))
            return false;
        memcpy(&fps, &data[pos], sizeof(float));
        pos += sizeof(float);
    }
    else
    {
        fps = 0;
    }

    if (checkBit(data[6], 2))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&gop, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        gop = 0;
    }

    if (checkBit(data[6], 1))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&h264Profile, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        h264Profile = 0;
    }

    if (checkBit(data[6], 0))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&jpegQuality, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        jpegQuality = 0;
    }

    if (checkBit(data[7], 7))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        codec = strArray;
    }
    else
    {
        codec = "";
    }

    if (checkBit(data[7], 6))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&fitMode, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        fitMode = 0;
    }

    if (checkBit(data[7], 5))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&cycleTimeUs, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        cycleTimeUs = 0;
    }

    if (checkBit(data[7], 4))
    {
        if (dataSize < pos + 1)
            return false;
        memcpy(&overlayEnable, &data[pos], sizeof(bool));
        pos += sizeof(bool);
    }
    else
    {
        overlayEnable = false;
    }

    if (checkBit(data[7], 3))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&type, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        type = 0;
    }

    if (checkBit(data[7], 2))
    {
        if (dataSize < pos + sizeof(float))
            return false;
        memcpy(&custom1, &data[pos], sizeof(float));
        pos += sizeof(float);
    }
    else
    {
        custom1 = 0;
    }

    if (checkBit(data[7], 1))
    {
        if (dataSize < pos + sizeof(float))
            return false;
        memcpy(&custom2, &data[pos], sizeof(float));
        pos += sizeof(float);
    }
    else
    {
        custom2 = 0;
    }

    if (checkBit(data[7], 0))
    {
        if (dataSize < pos + sizeof(float))
            return false;
        memcpy(&custom3, &data[pos], sizeof(float));
        pos += sizeof(float);
    }
    else
    {
        custom3 = 0;
    }

    if (checkBit(data[8], 7))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        rtspKey = strArray;
    }
    else
    {
        rtspKey = "";
    }

    if (checkBit(data[8], 6))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        rtspCert = strArray;
    }
    else
    {
        rtspCert = "";
    }

    if (checkBit(data[8], 5))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        webRtcKey = strArray;
    }
    else
    {
        webRtcKey = "";
    }

    if (checkBit(data[8], 4))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        webRtcCert = strArray;
    }
    else
    {
        webRtcCert = "";
    }

    if (checkBit(data[8], 3))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        hlsKey = strArray;
    }
    else
    {
        hlsKey = "";
    }

    if (checkBit(data[8], 2))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        hlsCert = strArray;
    }
    else
    {
        hlsCert = "";
    }

    if (checkBit(data[8], 1))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        rtmpKey = strArray;
    }
    else
    {
        rtmpKey = "";
    }

    if (checkBit(data[8], 0))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        rtmpCert = strArray;
    }
    else
    {
        rtmpCert = "";
    }

    if (checkBit(data[9], 7))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        rtspEncryption = strArray;
    }
    else
    {
        rtspEncryption = "";
    }

    if (checkBit(data[9], 6))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        webRtcEncryption = strArray;
    }
    else
    {
        webRtcEncryption = "";
    }

    if (checkBit(data[9], 5))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        rtmpEncryption = strArray;
    }
    else
    {
        rtmpEncryption = "";
    }

    if (checkBit(data[9], 4))
    {
        memset(strArray, 0, 512);
        strcpy(strArray, (char *)&data[pos]);
        pos += strlen(strArray) + 1;
        hlsEncryption = strArray;
    }
    else
    {
        hlsEncryption = "";
    }

    if (checkBit(data[9], 3))
    {
        if (dataSize < pos + sizeof(int))
            return false;
        memcpy(&logLevel, &data[pos], sizeof(int));
        pos += sizeof(int);
    }
    else
    {
        logLevel = 0;
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



void cr::video::VStreamer::encodeSetParamCommand(
    uint8_t* data, int& size, VStreamerParam id, std::string value)
{
    // Fill header.
    data[0] = 0x02;
    data[1] = VSTREAMER_MAJOR_VERSION;
    data[2] = VSTREAMER_MINOR_VERSION;

    // Fill data.
    int paramId = (int)id;
    memcpy(&data[3], &paramId, 4);
    memcpy(&data[7], value.c_str(), value.size() + 1);
    size = 7 + value.size() + 1;
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
                                        float &value,
                                        string &strValue)
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
    strValue = "";

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
            return -1;

        paramId = (VStreamerParam)id;
        memcpy(&value, &data[7], 4);
        return 1;
    }
    else if(data[0] == 0x02)
    {
        // Check minimum size for string command.
        if (size < 8)
            return -1;

        paramId = (VStreamerParam)id;

        // Safe string copying with bounds checking
        int maxLen = size - 7;  // Remaining buffer size after header and parameter ID
        char tempBuffer[512];   // Temporary buffer for safety
        int copyLen = (maxLen < 511) ? maxLen : 511;
        memcpy(tempBuffer, &data[7], copyLen);
        tempBuffer[copyLen] = '\0';  // Ensure null termination
        strValue = std::string(tempBuffer);
        return 2;
    }

    return -1;
}



bool cr::video::VStreamer::decodeAndExecuteCommand(uint8_t* data, int size)
{
    // Decode command.
    VStreamerCommand commandId = VStreamerCommand::RESTART; // Default value.
    VStreamerParam paramId = VStreamerParam::FIT_MODE; // Default value.
    float value = 0.0f;
    std::string strValue = "";
    switch (VStreamer::decodeCommand(data, size, paramId, commandId, value, strValue))
    {
    // Command.
    case 0:
        return executeCommand(commandId);
    // Set parameter.
    case 1:
        return setParam(paramId, value);
    // Set parameter string.
    case 2:
        return setParam(paramId, strValue);
    default:
        return false;
    }

    return false;
}