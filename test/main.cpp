#include <iostream>
#include "VStreamer.h"



// Link namespaces.
using namespace cr::video;
using namespace std;



// Fill random data.
void fillRandomData(VStreamerParams &a)
{
    a.enable = false;
    a.width = rand() % 65535 + 1;
    a.height = rand() % 65535 + 1;
    a.directStreamIp = "sfspfo9jbjnbjhklvllks";
    a.rtspPort = rand() % 65535 + 1;
    a.rtspsPort = rand() % 65535 + 1;
    a.directStreamPort = rand() % 65535 + 1;
    a.webRtcPort = rand() % 65535 + 1;
    a.hlsPort = rand() % 65535 + 1;
    a.srtPort = rand() % 65535 + 1;
    a.rtmpPort = rand() % 65535 + 1;
    a.rtmpsPort = rand() % 65535 + 1;
    a.metadataPort = rand() % 65535 + 1;
    a.rtspEnable = true;
    a.directStreamEnable = true;
    a.webRtcEnable = false;
    a.hlsEnable = false;
    a.srtEnable = true;
    a.rtmpEnable = true;
    a.metadataEnable = false;
    a.rtspMulticastIp = "wpofuihifo";
    a.rtspMulticastPort = rand() % 65535 + 1;
    a.user = "slfljkv";
    a.password = "sddgoihw,";
    a.suffix = "pisfhcowmfv";
    a.metadataSuffix = "z.,nfpowe";
    a.minBitrateKbps = rand() % 65535 + 1;
    a.maxBitrateKbps = rand() % 65535 + 1;
    a.bitrateKbps = rand() % 65535 + 1;
    a.bitrateMode = rand() % 65535 + 1;
    a.fps = rand() % 65535 + 1;
    a.gop = rand() % 65535 + 1;
    a.h264Profile = rand() % 65535 + 1;
    a.jpegQuality = rand() % 65535 + 1;
    a.codec = "dkgvmkrnjv";
    a.fitMode = rand() % 65535 + 1;
    a.cycleTimeUs = rand() % 65535 + 1;
    a.overlayEnable = true;
    a.type = rand() % 65535 + 1;
    a.custom1 = rand() % 65535 + 1;
    a.custom2 = rand() % 65535 + 1;
    a.custom3 = rand() % 65535 + 1;
    a.rtspKey = "dh;skcsf";
    a.rtspCert = "lkjrkjg";
    a.webRtcKey = "WERUHUHFE";
    a.webRtcCert = "erghshiAJ";
    a.hlsKey = "wqlovf;qb";
    a.hlsCert = "24kjcnnv";
    a.rtmpKey = "dkkkkjfkjdkjfkj2134";
    a.rtmpCert = "wfpomv";
    a.rtspEncryption = "quyen";
    a.webRtcEncryption = "l;uoykh";
    a.rtmpEncryption = "skldfjdf";
    a.hlsEncryption = "wieufjpowkf";
    a.logLevel = rand() % 4;
    const std::string directStreamTypes[] = {"rtp", "mpegts", "mpegts-rtp"};
    a.directStreamType = directStreamTypes[rand() % 3];
    a.directStreamBitrateKbps = rand() % 65535 + 1;
    a.directStreamMaxPayloadSize = rand() % 65535 + 1;
    a.directStreamPacingMode = rand() % 2;
    const std::string serverStreamTypes[] = {"rtp", "rtp-klv", "mpegts-rtp-klv"};
    a.serverStreamType = serverStreamTypes[rand() % 3];
    a.multicastTtl = rand() % 256;
    const std::string profiles[] = {"no", "ONVIF", "STRICT_FIPS", "CRA_STRICT"};
    a.securityProfile = profiles[rand() % 4];
    a.publicAddress = "203.0.113." + std::to_string(rand() % 256);
    a.bindAddress = "192.0.2." + std::to_string(rand() % 256);
    a.rtpPortMin = rand() % 65535;
    a.rtpPortMax = rand() % 65535;
    a.webRtcMediaPort = rand() % 65535;
    a.corsAllowedOrigin = "https://app" + std::to_string(rand() % 100) + ".example";
    a.serverStreamMaxPayloadSize = rand() % 65535 + 1;
}


// Compare params function.
bool compareParams(VStreamerParams &a, VStreamerParams &b, VStreamerParamsMask* mask = nullptr);

// Copy test.
bool copyTest();

// Serialize/deserialize test.
bool serializeDeserializeTest();

/// Serialize/deserialize test with params mask.
bool serializeDeserializeWithMaskTest();

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

    int failed = 0;

    cout << "Copy test:" << endl;
    if (copyTest())
        cout << "OK" << endl;
    else
    {
        cout << "ERROR" << endl;
        ++failed;
    }
    cout << endl;

    cout << "Serialize/Deserialize test:" << endl;
    if (serializeDeserializeTest())
        cout << "OK" << endl;
    else
    {
        cout << "ERROR" << endl;
        ++failed;
    }
    cout << endl;

    cout << "Serialize/Deserialize test with params mask:" << endl;
    if (serializeDeserializeWithMaskTest())
        cout << "OK" << endl;
    else
    {
        cout << "ERROR" << endl;
        ++failed;
    }
    cout << endl;

    cout << "Encode/Decode commands test:" << endl;
    if (encodeDecodeCommandsTest())
        cout << "OK" << endl;
    else
    {
        cout << "ERROR" << endl;
        ++failed;
    }
    cout << endl;

    cout << "JSON read/write test:" << endl;
    if (jsonReadWriteTest())
        cout << "OK" << endl;
    else
    {
        cout << "ERROR" << endl;
        ++failed;
    }
    cout << endl;

    return failed ? 1 : 0;
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
    if (mask->directStreamIp && (a.directStreamIp != b.directStreamIp))
    {
        cout << "directStreamIp" << endl;
        return false;
    }
    if (mask->rtspPort && (a.rtspPort != b.rtspPort))
    {
        cout << "rtspPort" << endl;
        return false;
    }
    if (mask->directStreamPort && (a.directStreamPort != b.directStreamPort))
    {
        cout << "directStreamPort" << endl;
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
    if (mask->directStreamEnable && (a.directStreamEnable != b.directStreamEnable))
    {
        cout << "directStreamEnable" << endl;
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
    if (mask->cycleTimeUs && (a.cycleTimeUs != b.cycleTimeUs))
    {
        cout << "cycleTimeUs" << endl;
        return false;
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
    if (mask->rtspKey && (a.rtspKey != b.rtspKey))
    {
        cout << "rtspKey" << endl;
        return false;
    }
    if (mask->rtspCert && (a.rtspCert != b.rtspCert))
    {
        cout << "rtspCert" << endl;
        return false;
    }
    if (mask->webRtcKey && (a.webRtcKey != b.webRtcKey))
    {
        cout << "webRtcKey" << endl;
        return false;
    }
    if (mask->webRtcCert && (a.webRtcCert != b.webRtcCert))
    {
        cout << "webRtcCert" << endl;
        return false;
    }
    if (mask->hlsKey && (a.hlsKey != b.hlsKey))
    {
        cout << "hlsKey" << endl;
        return false;
    }
    if (mask->hlsCert && (a.hlsCert != b.hlsCert))
    {
        cout << "hlsCert" << endl;
        return false;
    }
    if (mask->rtmpKey && (a.rtmpKey != b.rtmpKey))
    {
        cout << "rtmpKey" << endl;
        return false;
    }
    if (mask->rtmpCert && (a.rtmpCert != b.rtmpCert))
    {
        cout << "rtmpCert" << endl;
        return false;
    }
    if (mask->rtspEncryption && (a.rtspEncryption != b.rtspEncryption))
    {
        cout << "rtspEncryption" << endl;
        return false;
    }
    if (mask->webRtcEncryption && (a.webRtcEncryption != b.webRtcEncryption))
    {
        cout << "webRtcEncryption" << endl;
        return false;
    }
    if (mask->rtmpEncryption && (a.rtmpEncryption != b.rtmpEncryption))
    {
        cout << "rtmpEncryption" << endl;
        return false;
    }
    if (mask->hlsEncryption && (a.hlsEncryption != b.hlsEncryption))
    {
        cout << "hlsEncryption" << endl;
        return false;
    }
    if (mask->logLevel && (a.logLevel != b.logLevel))
    {
        cout << "logLevel" << endl;
        return false;
    }
    if (mask->rtspsPort && (a.rtspsPort != b.rtspsPort))
    {
        cout << "rtspsPort" << endl;
        return false;
    }
    if (mask->rtmpsPort && (a.rtmpsPort != b.rtmpsPort))
    {
        cout << "rtmpsPort" << endl;
        return false;
    }
    if (mask->directStreamType && (a.directStreamType != b.directStreamType))
    {
        cout << "directStreamType" << endl;
        return false;
    }
    if (mask->directStreamBitrateKbps && (a.directStreamBitrateKbps != b.directStreamBitrateKbps))
    {
        cout << "directStreamBitrateKbps" << endl;
        return false;
    }
    if (mask->directStreamMaxPayloadSize && (a.directStreamMaxPayloadSize != b.directStreamMaxPayloadSize))
    {
        cout << "directStreamMaxPayloadSize" << endl;
        return false;
    }
    if (mask->directStreamPacingMode && (a.directStreamPacingMode != b.directStreamPacingMode))
    {
        cout << "directStreamPacingMode" << endl;
        return false;
    }
    if (mask->serverStreamType && (a.serverStreamType != b.serverStreamType))
    {
        cout << "serverStreamType" << endl;
        return false;
    }
    if (mask->multicastTtl && (a.multicastTtl != b.multicastTtl))
    {
        cout << "multicastTtl" << endl;
        return false;
    }
    if (mask->securityProfile && (a.securityProfile != b.securityProfile))
    {
        cout << "securityProfile" << endl;
        return false;
    }
    if (mask->publicAddress && (a.publicAddress != b.publicAddress))
    {
        cout << "publicAddress" << endl;
        return false;
    }
    if (mask->bindAddress && (a.bindAddress != b.bindAddress))
    {
        cout << "bindAddress" << endl;
        return false;
    }
    if (mask->rtpPortMin && (a.rtpPortMin != b.rtpPortMin))
    {
        cout << "rtpPortMin" << endl;
        return false;
    }
    if (mask->rtpPortMax && (a.rtpPortMax != b.rtpPortMax))
    {
        cout << "rtpPortMax" << endl;
        return false;
    }
    if (mask->webRtcMediaPort && (a.webRtcMediaPort != b.webRtcMediaPort))
    {
        cout << "webRtcMediaPort" << endl;
        return false;
    }
    if (mask->corsAllowedOrigin && (a.corsAllowedOrigin != b.corsAllowedOrigin))
    {
        cout << "corsAllowedOrigin" << endl;
        return false;
    }
    if (mask->serverStreamMaxPayloadSize &&
        (a.serverStreamMaxPayloadSize != b.serverStreamMaxPayloadSize))
    {
        cout << "serverStreamMaxPayloadSize" << endl;
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



bool serializeDeserializeTest()
{
    // Prepare random params.
    VStreamerParams in;
    fillRandomData(in);

    // Serialize data.
    uint8_t data[1024];
    int size = 0;
    in.serialize(data, 1024, size);

    cout << "Serialized data size: " << size << " bytes" << endl;

    // Deserialize data.
    VStreamerParams out;
    if (!out.deserialize(data, size))
    {
        cout << "Can't deserialize data" << endl;
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

    // Check ID and value.
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

    // Check ID and value.
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

    // Every numeric parameter added in 3.2 must survive the round trip. The
    // test used to cover exactly one id, so a new enum entry could be
    // unencodable and nothing would say so.
    const VStreamerParam numericIds[] = {
        VStreamerParam::MULTICAST_TTL,
        VStreamerParam::RTP_PORT_MIN,
        VStreamerParam::RTP_PORT_MAX,
        VStreamerParam::WEBRTC_MEDIA_PORT,
        VStreamerParam::SERVER_STREAM_MAX_PAYLOAD};
    for (VStreamerParam id : numericIds)
    {
        outValue = (float)(rand() % 30000);
        VStreamer::encodeSetParamCommand(data, size, id, outValue);
        value = 0.0f;
        strValue = "";
        if (VStreamer::decodeCommand(data, size, paramId, commandId,
                                     value, strValue) != 1)
        {
            cout << "3.2 numeric param not decoded" << endl;
            return false;
        }
        if (paramId != id || value != outValue)
        {
            cout << "3.2 numeric param round trip mismatch" << endl;
            return false;
        }
    }

    // The string parameters, through the string overload.
    const VStreamerParam stringIds[] = {
        VStreamerParam::SECURITY_PROFILE,
        VStreamerParam::PUBLIC_ADDRESS,
        VStreamerParam::BIND_ADDRESS,
        VStreamerParam::CORS_ALLOWED_ORIGIN};
    const std::string stringValues[] = {
        "CRA_STRICT", "203.0.113.7", "192.0.2.1", "https://app.example"};
    for (int i = 0; i < 4; ++i)
    {
        VStreamer::encodeSetParamCommand(data, size, stringIds[i],
                                         stringValues[i]);
        value = 0.0f;
        strValue = "";
        // A string set-param decodes as 2, not 1: the return value is the
        // command KIND (0 command, 1 numeric param, 2 string param), which is
        // how a caller knows which of value/strValue was filled.
        if (VStreamer::decodeCommand(data, size, paramId, commandId,
                                     value, strValue) != 2)
        {
            cout << "3.2 string param not decoded" << endl;
            return false;
        }
        if (paramId != stringIds[i] || strValue != stringValues[i])
        {
            cout << "3.2 string param round trip mismatch: got '"
                 << strValue << "'" << endl;
            return false;
        }
    }

    // A params message from a different MINOR version must be refused. This is
    // the guarantee the wire format rests on: the parameter mask grew from 8
    // bytes to 10 in 3.2, so a 3.1 message read with 3.2 offsets would decode
    // garbage into every field rather than fail.
    {
        VStreamerParams p;
        fillRandomData(p);
        uint8_t buf[4096];
        int n = 0;
        if (!p.serialize(buf, sizeof(buf), n))
        {
            cout << "params did not serialize" << endl;
            return false;
        }
        VStreamerParams round;
        if (!round.deserialize(buf, n))
        {
            cout << "params did not deserialize" << endl;
            return false;
        }

        buf[2] = (uint8_t)(buf[2] + 1);         // a different minor version
        VStreamerParams other;
        if (other.deserialize(buf, n))
        {
            cout << "a foreign minor version was accepted" << endl;
            return false;
        }
        buf[2] = (uint8_t)(buf[2] - 1);
        buf[1] = (uint8_t)(buf[1] + 1);         // a different major version
        if (other.deserialize(buf, n))
        {
            cout << "a foreign major version was accepted" << endl;
            return false;
        }
        buf[1] = (uint8_t)(buf[1] - 1);
        buf[0] = 0x03;                          // not a params message at all
        if (other.deserialize(buf, n))
        {
            cout << "a foreign header byte was accepted" << endl;
            return false;
        }

        // And every truncation of a valid message must be refused rather than
        // read past its end.
        buf[0] = 0x02;
        for (int cut = 0; cut < n; ++cut)
        {
            VStreamerParams t;
            if (t.deserialize(buf, cut))
            {
                cout << "a truncated params message was accepted at "
                     << cut << " of " << n << endl;
                return false;
            }
        }

        // A params-serialize snapshot (header 0x02) must NOT be decoded as a
        // command: string set-param now uses 0x03, so the two families no
        // longer collide and decodeCommand rejects a params blob.
        VStreamerParam pid;
        VStreamerCommand cid;
        float v = 0.0f;
        std::string sv;
        if (VStreamer::decodeCommand(buf, n, pid, cid, v, sv) != -1)
        {
            cout << "a params snapshot was misdecoded as a command" << endl;
            return false;
        }
    }

    // encode/decode must refuse a null buffer rather than write through it.
    {
        int n = 99;
        VStreamer::encodeCommand(nullptr, n, VStreamerCommand::RESTART);
        if (n != 0)
        {
            cout << "encodeCommand(nullptr) did not report size 0" << endl;
            return false;
        }
        n = 99;
        VStreamer::encodeSetParamCommand(nullptr, n, VStreamerParam::WIDTH, 1.0f);
        if (n != 0)
        {
            cout << "encodeSetParamCommand(nullptr, float) did not report size 0"
                 << endl;
            return false;
        }
        n = 99;
        VStreamer::encodeSetParamCommand(nullptr, n, VStreamerParam::CODEC,
                                         std::string("H264"));
        if (n != 0)
        {
            cout << "encodeSetParamCommand(nullptr, string) did not report size 0"
                 << endl;
            return false;
        }
        if (VStreamer::decodeCommand(nullptr, 11, paramId, commandId,
                                     value, strValue) != -1)
        {
            cout << "decodeCommand(nullptr) was accepted" << endl;
            return false;
        }
    }

    // A string SET_PARAM without a terminator, or with trailing garbage after
    // the terminator, must be refused. The old decoder stuffed a '\0' at a
    // 511-byte cap and accepted both.
    {
        uint8_t raw[16] = {0x03, 3, 2};
        int id = (int)VStreamerParam::CODEC;
        memcpy(&raw[3], &id, 4);
        raw[7] = 'A'; raw[8] = 'B'; raw[9] = 'C';   // no terminator
        if (VStreamer::decodeCommand(raw, 10, paramId, commandId,
                                     value, strValue) != -1)
        {
            cout << "unterminated string SET_PARAM was accepted" << endl;
            return false;
        }
        raw[7] = 'A'; raw[8] = 0; raw[9] = 'X';     // terminator, then junk
        if (VStreamer::decodeCommand(raw, 10, paramId, commandId,
                                     value, strValue) != -1)
        {
            cout << "string SET_PARAM with trailing bytes was accepted" << endl;
            return false;
        }
        uint8_t cmd[8] = {0x00, 3, 2};
        int cid = (int)VStreamerCommand::RESTART;
        memcpy(&cmd[3], &cid, 4);
        cmd[7] = 0xFF;                              // COMMAND is exactly 7 bytes
        if (VStreamer::decodeCommand(cmd, 8, paramId, commandId,
                                     value, strValue) != -1)
        {
            cout << "over-long COMMAND was accepted" << endl;
            return false;
        }
    }

    // serialize() used `bufferSize > pos + n`, so a buffer sized exactly to
    // the payload dropped the last field. A 14-byte buffer must still hold
    // the header plus one bool.
    {
        VStreamerParams p;
        p.enable = true;
        VStreamerParamsMask mask{};   // all false
        mask.enable = true;
        uint8_t tiny[14];
        int n = 0;
        if (!p.serialize(tiny, 14, n, &mask) || n != 14)
        {
            cout << "exact-size serialize of one bool failed, n=" << n << endl;
            return false;
        }
        VStreamerParams out;
        if (!out.deserialize(tiny, n) || out.enable != true)
        {
            cout << "exact-size serialize/deserialize of enable failed" << endl;
            return false;
        }
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

    // cycleTimeUs is in the JSON as of 3.2 (it used to be binary-only).
    VStreamerParamsMask mask;

    // Compare params.
    return compareParams(in, out, &mask);
}



bool serializeDeserializeWithMaskTest()
{
    // Prepare random params.
    VStreamerParams in;
    fillRandomData(in);

    // Prepare random params mask.
    VStreamerParamsMask mask;
    mask.enable = true;
    mask.width = true;
    mask.height = false;
    mask.directStreamIp = true;
    mask.rtspPort = true;
    mask.directStreamPort = false;
    mask.webRtcPort = true;
    mask.hlsPort = false;
    mask.srtPort = false;
    mask.rtmpPort = false;
    mask.metadataPort = true;
    mask.rtspEnable = true;
    mask.directStreamEnable = true;
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
    mask.cycleTimeUs = false;
    mask.overlayEnable = true;
    mask.type = true;
    mask.custom1 = true;
    mask.custom2 = false;
    mask.custom3 = true;
    mask.rtspKey = true;
    mask.rtspCert = false;
    mask.webRtcKey = true;
    mask.webRtcCert = false;
    mask.hlsKey = true;
    mask.hlsCert = true;
    mask.rtmpKey = false;
    mask.rtmpCert = false;
    mask.rtspEncryption = false;
    mask.webRtcEncryption = true;
    mask.rtmpEncryption = false;
    mask.hlsEncryption = true;
    mask.logLevel = true;
    mask.rtspsPort = true;
    mask.rtmpsPort = true;
    mask.directStreamType = true;
    mask.directStreamBitrateKbps = false;
    mask.directStreamMaxPayloadSize = true;
    mask.directStreamPacingMode = false;
    mask.serverStreamType = true;
    // The 3.2 parameters, deliberately mixed: a mask test proves nothing if
    // every new bit is set the same way.
    mask.multicastTtl = true;
    mask.securityProfile = false;
    mask.publicAddress = true;
    mask.bindAddress = false;
    mask.rtpPortMin = true;
    mask.rtpPortMax = true;
    mask.webRtcMediaPort = false;
    mask.corsAllowedOrigin = true;
    mask.serverStreamMaxPayloadSize = false;

    // Encode data.
    uint8_t data[1024];
    int size = 0;
    in.serialize(data, 1024, size, &mask);

    cout << "Serialized data size: " << size << " bytes" << endl;

    // Decode data.
    VStreamerParams out;
    if (!out.deserialize(data, size))
    {
        cout << "Can't deserialize data" << endl;
        return false;
    }

    // Compare params.
    return compareParams(in, out, &mask);
}