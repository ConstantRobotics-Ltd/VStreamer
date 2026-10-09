#include "VStreamer.h"
#include "VStreamerVersion.h"
#include <string>
#include <cstring>
#include <limits>
#include <utility>


// Macro to check bit in byte.
#define checkBit(byte, position) ((byte) & (1 << (position)))


// Link namespaces.
using namespace cr::video;
using namespace std;


// Wire sizes of the fixed-size fields. Positions and sizes are int in this
// API, so the sizes are kept as int too: the bounds checks then compare int
// with int and never mix in an unsigned type.
static constexpr int BOOL_SIZE = static_cast<int>(sizeof(bool));
static constexpr int INT_SIZE = static_cast<int>(sizeof(int));
static constexpr int FLOAT_SIZE = static_cast<int>(sizeof(float));



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
    // Check buffer size. Header is 13 bytes; one bool is the smallest field.
    if (data == nullptr || bufferSize < 14)
    {
        size = 0;
        return false;
    }

    // Fill header.
    //
    // The mask is 10 bytes, not 8: the 8-byte mask of 3.1 had 60 of its 64
    // bits taken and could not describe the parameters added in 3.2. Growing
    // it moves the start of the payload, so a 3.1 peer would misread a 3.2
    // message -- which it never sees, because deserialize() rejects on the
    // minor version before it reaches the mask. That version check is what
    // makes the wire format extensible at all.
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
    data[10] = 0; // Parameter mask byte 8
    data[11] = 0; // Parameter mask byte 9
    data[12] = 0; // Parameter mask byte 10

    // If mask is not initialized then encode all parameters.
    VStreamerParamsMask defaultMask;
    if (mask == nullptr)
    {
        mask = &defaultMask;
    }

    // Fill data.
    int pos = 13;

    // Inclusive (>=) on purpose: a buffer that is exactly the size of the
    // next field must still accept it. The previous `>` dropped the last
    // field whenever the caller sized the buffer to the exact payload.
    // Written as a subtraction: pos never passes bufferSize, so
    // bufferSize - pos cannot overflow, while pos + n could.
    auto fits = [&](int n)
    {
        return bufferSize - pos >= n;
    };

    // A string takes its characters plus the terminator. The length is
    // compared as size_t: a string longer than INT_MAX must not wrap into a
    // small or negative int that passes the check and overruns the buffer.
    auto fitsString = [&](const std::string& value)
    {
        return value.size() < static_cast<size_t>(bufferSize - pos);
    };

    if (mask->enable && fits(BOOL_SIZE))
    {
        memcpy(&data[pos], &enable, sizeof(bool));
        pos += BOOL_SIZE;
        data[3] |= (1 << 7);
    }

    if (mask->width && fits(INT_SIZE))
    {
        memcpy(&data[pos], &width, sizeof(int));
        pos += INT_SIZE;
        data[3] |= (1 << 6);
    }

    if (mask->height && fits(INT_SIZE))
    {
        memcpy(&data[pos], &height, sizeof(int));
        pos += INT_SIZE;
        data[3] |= (1 << 5);
    }

    if (mask->directStreamIp && fitsString(directStreamIp))
    {
        memcpy(&data[pos], directStreamIp.c_str(), directStreamIp.size() + 1);
        pos += static_cast<int>(directStreamIp.size()) + 1;
        data[3] |= (1 << 4);
    }

    if (mask->rtspPort && fits(INT_SIZE))
    {
        memcpy(&data[pos], &rtspPort, sizeof(int));
        pos += INT_SIZE;
        data[3] |= (1 << 3);
    }

    if (mask->directStreamPort && fits(INT_SIZE))
    {
        memcpy(&data[pos], &directStreamPort, sizeof(int));
        pos += INT_SIZE;
        data[3] |= (1 << 2);
    }

    if (mask->webRtcPort && fits(INT_SIZE))
    {
        memcpy(&data[pos], &webRtcPort, sizeof(int));
        pos += INT_SIZE;
        data[3] |= (1 << 1);
    }

    if (mask->hlsPort && fits(INT_SIZE))
    {
        memcpy(&data[pos], &hlsPort, sizeof(int));
        pos += INT_SIZE;
        data[3] |= (1 << 0);
    }

    if (mask->srtPort && fits(INT_SIZE))
    {
        memcpy(&data[pos], &srtPort, sizeof(int));
        pos += INT_SIZE;
        data[4] |= (1 << 7);
    }

    if (mask->rtmpPort && fits(INT_SIZE))
    {
        memcpy(&data[pos], &rtmpPort, sizeof(int));
        pos += INT_SIZE;
        data[4] |= (1 << 6);
    }

    if (mask->metadataPort && fits(INT_SIZE))
    {
        memcpy(&data[pos], &metadataPort, sizeof(int));
        pos += INT_SIZE;
        data[4] |= (1 << 5);
    }

    if (mask->rtspEnable && fits(BOOL_SIZE))
    {
        memcpy(&data[pos], &rtspEnable, sizeof(bool));
        pos += BOOL_SIZE;
        data[4] |= (1 << 4);
    }

    if (mask->directStreamEnable && fits(BOOL_SIZE))
    {
        memcpy(&data[pos], &directStreamEnable, sizeof(bool));
        pos += BOOL_SIZE;
        data[4] |= (1 << 3);
    }

    if (mask->webRtcEnable && fits(BOOL_SIZE))
    {
        memcpy(&data[pos], &webRtcEnable, sizeof(bool));
        pos += BOOL_SIZE;
        data[4] |= (1 << 2);
    }

    if (mask->hlsEnable && fits(BOOL_SIZE))
    {
        memcpy(&data[pos], &hlsEnable, sizeof(bool));
        pos += BOOL_SIZE;
        data[4] |= (1 << 1);
    }

    if (mask->srtEnable && fits(BOOL_SIZE))
    {
        memcpy(&data[pos], &srtEnable, sizeof(bool));
        pos += BOOL_SIZE;
        data[4] |= (1 << 0);
    }

    if (mask->rtmpEnable && fits(BOOL_SIZE))
    {
        memcpy(&data[pos], &rtmpEnable, sizeof(bool));
        pos += BOOL_SIZE;
        data[5] |= (1 << 7);
    }

    if (mask->metadataEnable && fits(BOOL_SIZE))
    {
        memcpy(&data[pos], &metadataEnable, sizeof(bool));
        pos += BOOL_SIZE;
        data[5] |= (1 << 6);
    }

    if (mask->rtspMulticastIp && fitsString(rtspMulticastIp))
    {
        memcpy(&data[pos], rtspMulticastIp.c_str(), rtspMulticastIp.size() + 1);
        pos += static_cast<int>(rtspMulticastIp.size()) + 1;
        data[5] |= (1 << 5);
    }

    if (mask->rtspMulticastPort && fits(INT_SIZE))
    {
        memcpy(&data[pos], &rtspMulticastPort, sizeof(int));
        pos += INT_SIZE;
        data[5] |= (1 << 4);
    }

    if (mask->user && fitsString(user))
    {
        memcpy(&data[pos], user.c_str(), user.size() + 1);
        pos += static_cast<int>(user.size()) + 1;
        data[5] |= (1 << 3);
    }

    if (mask->password && fitsString(password))
    {
        memcpy(&data[pos], password.c_str(), password.size() + 1);
        pos += static_cast<int>(password.size()) + 1;
        data[5] |= (1 << 2);
    }

    if (mask->suffix && fitsString(suffix))
    {
        memcpy(&data[pos], suffix.c_str(), suffix.size() + 1);
        pos += static_cast<int>(suffix.size()) + 1;
        data[5] |= (1 << 1);
    }

    if (mask->metadataSuffix && fitsString(metadataSuffix))
    {
        memcpy(&data[pos], metadataSuffix.c_str(), metadataSuffix.size() + 1);
        pos += static_cast<int>(metadataSuffix.size()) + 1;
        data[5] |= (1 << 0);
    }

    if (mask->minBitrateKbps && fits(INT_SIZE))
    {
        memcpy(&data[pos], &minBitrateKbps, sizeof(int));
        pos += INT_SIZE;
        data[6] |= (1 << 7);
    }

    if (mask->maxBitrateKbps && fits(INT_SIZE))
    {
        memcpy(&data[pos], &maxBitrateKbps, sizeof(int));
        pos += INT_SIZE;
        data[6] |= (1 << 6);
    }

    if (mask->bitrateKbps && fits(INT_SIZE))
    {
        memcpy(&data[pos], &bitrateKbps, sizeof(int));
        pos += INT_SIZE;
        data[6] |= (1 << 5);
    }

    if (mask->bitrateMode && fits(INT_SIZE))
    {
        memcpy(&data[pos], &bitrateMode, sizeof(int));
        pos += INT_SIZE;
        data[6] |= (1 << 4);
    }

    if (mask->fps && fits(FLOAT_SIZE))
    {
        memcpy(&data[pos], &fps, sizeof(float));
        pos += FLOAT_SIZE;
        data[6] |= (1 << 3);
    }

    if (mask->gop && fits(INT_SIZE))
    {
        memcpy(&data[pos], &gop, sizeof(int));
        pos += INT_SIZE;
        data[6] |= (1 << 2);
    }

    if (mask->h264Profile && fits(INT_SIZE))
    {
        memcpy(&data[pos], &h264Profile, sizeof(int));
        pos += INT_SIZE;
        data[6] |= (1 << 1);
    }

    if (mask->jpegQuality && fits(INT_SIZE))
    {
        memcpy(&data[pos], &jpegQuality, sizeof(int));
        pos += INT_SIZE;
        data[6] |= (1 << 0);
    }

    if (mask->codec && fitsString(codec))
    {
        memcpy(&data[pos], codec.c_str(), codec.size() + 1);
        pos += static_cast<int>(codec.size()) + 1;
        data[7] |= (1 << 7);
    }

    if (mask->fitMode && fits(INT_SIZE))
    {
        memcpy(&data[pos], &fitMode, sizeof(int));
        pos += INT_SIZE;
        data[7] |= (1 << 6);
    }

    if (mask->cycleTimeUs && fits(INT_SIZE))
    {
        memcpy(&data[pos], &cycleTimeUs, sizeof(int));
        pos += INT_SIZE;
        data[7] |= (1 << 5);
    }

    if (mask->overlayEnable && fits(BOOL_SIZE))
    {
        memcpy(&data[pos], &overlayEnable, sizeof(bool));
        pos += BOOL_SIZE;
        data[7] |= (1 << 4);
    }

    if (mask->type && fits(INT_SIZE))
    {
        memcpy(&data[pos], &type, sizeof(int));
        pos += INT_SIZE;
        data[7] |= (1 << 3);
    }

    if (mask->custom1 && fits(FLOAT_SIZE))
    {
        memcpy(&data[pos], &custom1, sizeof(float));
        pos += FLOAT_SIZE;
        data[7] |= (1 << 2);
    }

    if (mask->custom2 && fits(FLOAT_SIZE))
    {
        memcpy(&data[pos], &custom2, sizeof(float));
        pos += FLOAT_SIZE;
        data[7] |= (1 << 1);
    }

    if (mask->custom3 && fits(FLOAT_SIZE))
    {
        memcpy(&data[pos], &custom3, sizeof(float));
        pos += FLOAT_SIZE;
        data[7] |= (1 << 0);
    }

    if (mask->rtspKey && fitsString(rtspKey))
    {
        memcpy(&data[pos], rtspKey.c_str(), rtspKey.size() + 1);
        pos += static_cast<int>(rtspKey.size()) + 1;
        data[8] |= (1 << 7);
    }

    if (mask->rtspCert && fitsString(rtspCert))
    {
        memcpy(&data[pos], rtspCert.c_str(), rtspCert.size() + 1);
        pos += static_cast<int>(rtspCert.size()) + 1;
        data[8] |= (1 << 6);
    }

    if (mask->webRtcKey && fitsString(webRtcKey))
    {
        memcpy(&data[pos], webRtcKey.c_str(), webRtcKey.size() + 1);
        pos += static_cast<int>(webRtcKey.size()) + 1;
        data[8] |= (1 << 5);
    }

    if (mask->webRtcCert && fitsString(webRtcCert))
    {
        memcpy(&data[pos], webRtcCert.c_str(), webRtcCert.size() + 1);
        pos += static_cast<int>(webRtcCert.size()) + 1;
        data[8] |= (1 << 4);
    }

    if (mask->hlsKey && fitsString(hlsKey))
    {
        memcpy(&data[pos], hlsKey.c_str(), hlsKey.size() + 1);
        pos += static_cast<int>(hlsKey.size()) + 1;
        data[8] |= (1 << 3);
    }

    if (mask->hlsCert && fitsString(hlsCert))
    {
        memcpy(&data[pos], hlsCert.c_str(), hlsCert.size() + 1);
        pos += static_cast<int>(hlsCert.size()) + 1;
        data[8] |= (1 << 2);
    }

    if (mask->rtmpKey && fitsString(rtmpKey))
    {
        memcpy(&data[pos], rtmpKey.c_str(), rtmpKey.size() + 1);
        pos += static_cast<int>(rtmpKey.size()) + 1;
        data[8] |= (1 << 1);
    }

    if (mask->rtmpCert && fitsString(rtmpCert))
    {
        memcpy(&data[pos], rtmpCert.c_str(), rtmpCert.size() + 1);
        pos += static_cast<int>(rtmpCert.size()) + 1;
        data[8] |= (1 << 0);
    }

    if (mask->rtspEncryption && fitsString(rtspEncryption))
    {
        memcpy(&data[pos], rtspEncryption.c_str(), rtspEncryption.size() + 1);
        pos += static_cast<int>(rtspEncryption.size()) + 1;
        data[9] |= (1 << 7);
    }

    if (mask->webRtcEncryption && fitsString(webRtcEncryption))
    {
        memcpy(&data[pos], webRtcEncryption.c_str(), webRtcEncryption.size() + 1);
        pos += static_cast<int>(webRtcEncryption.size()) + 1;
        data[9] |= (1 << 6);
    }

    if (mask->rtmpEncryption && fitsString(rtmpEncryption))
    {
        memcpy(&data[pos], rtmpEncryption.c_str(), rtmpEncryption.size() + 1);
        pos += static_cast<int>(rtmpEncryption.size()) + 1;
        data[9] |= (1 << 5);
    }

    if (mask->hlsEncryption && fitsString(hlsEncryption))
    {
        memcpy(&data[pos], hlsEncryption.c_str(), hlsEncryption.size() + 1);
        pos += static_cast<int>(hlsEncryption.size()) + 1;
        data[9] |= (1 << 4);
    }

    if (mask->logLevel && fits(INT_SIZE))
    {
        memcpy(&data[pos], &logLevel, sizeof(int));
        pos += INT_SIZE;
        data[9] |= (1 << 3);
    }

    if (mask->rtspsPort && fits(INT_SIZE))
    {
        memcpy(&data[pos], &rtspsPort, sizeof(int));
        pos += INT_SIZE;
        data[9] |= (1 << 2);
    }

    if (mask->rtmpsPort && fits(INT_SIZE))
    {
        memcpy(&data[pos], &rtmpsPort, sizeof(int));
        pos += INT_SIZE;
        data[9] |= (1 << 1);
    }

    if (mask->directStreamType && fitsString(directStreamType))
    {
        memcpy(&data[pos], directStreamType.c_str(), directStreamType.size() + 1);
        pos += static_cast<int>(directStreamType.size()) + 1;
        data[9] |= (1 << 0);
    }

    if (mask->directStreamBitrateKbps && fits(INT_SIZE))
    {
        memcpy(&data[pos], &directStreamBitrateKbps, sizeof(int));
        pos += INT_SIZE;
        data[10] |= (1 << 7);
    }

    if (mask->directStreamMaxPayloadSize && fits(INT_SIZE))
    {
        memcpy(&data[pos], &directStreamMaxPayloadSize, sizeof(int));
        pos += INT_SIZE;
        data[10] |= (1 << 6);
    }

    if (mask->directStreamPacingMode && fits(INT_SIZE))
    {
        memcpy(&data[pos], &directStreamPacingMode, sizeof(int));
        pos += INT_SIZE;
        data[10] |= (1 << 5);
    }

    if (mask->serverStreamType && fitsString(serverStreamType))
    {
        memcpy(&data[pos], serverStreamType.c_str(), serverStreamType.size() + 1);
        pos += static_cast<int>(serverStreamType.size()) + 1;
        data[10] |= (1 << 4);
    }

    if (mask->multicastTtl && fits(INT_SIZE))
    {
        memcpy(&data[pos], &multicastTtl, sizeof(int));
        pos += INT_SIZE;
        data[10] |= (1 << 3);
    }

    if (mask->securityProfile && fitsString(securityProfile))
    {
        memcpy(&data[pos], securityProfile.c_str(), securityProfile.size() + 1);
        pos += static_cast<int>(securityProfile.size()) + 1;
        data[10] |= (1 << 2);
    }

    if (mask->publicAddress && fitsString(publicAddress))
    {
        memcpy(&data[pos], publicAddress.c_str(), publicAddress.size() + 1);
        pos += static_cast<int>(publicAddress.size()) + 1;
        data[10] |= (1 << 1);
    }

    if (mask->bindAddress && fitsString(bindAddress))
    {
        memcpy(&data[pos], bindAddress.c_str(), bindAddress.size() + 1);
        pos += static_cast<int>(bindAddress.size()) + 1;
        data[10] |= (1 << 0);
    }

    if (mask->rtpPortMin && fits(INT_SIZE))
    {
        memcpy(&data[pos], &rtpPortMin, sizeof(int));
        pos += INT_SIZE;
        data[11] |= (1 << 7);
    }

    if (mask->rtpPortMax && fits(INT_SIZE))
    {
        memcpy(&data[pos], &rtpPortMax, sizeof(int));
        pos += INT_SIZE;
        data[11] |= (1 << 6);
    }

    if (mask->webRtcMediaPort && fits(INT_SIZE))
    {
        memcpy(&data[pos], &webRtcMediaPort, sizeof(int));
        pos += INT_SIZE;
        data[11] |= (1 << 5);
    }

    if (mask->corsAllowedOrigin && fitsString(corsAllowedOrigin))
    {
        memcpy(&data[pos], corsAllowedOrigin.c_str(), corsAllowedOrigin.size() + 1);
        pos += static_cast<int>(corsAllowedOrigin.size()) + 1;
        data[11] |= (1 << 4);
    }

    if (mask->serverStreamMaxPayloadSize && fits(INT_SIZE))
    {
        memcpy(&data[pos], &serverStreamMaxPayloadSize, sizeof(int));
        pos += INT_SIZE;
        data[11] |= (1 << 3);
    }

    size = pos;

    return true;
}



// Read a null-terminated string from the buffer with bounds checking.
// Advances pos past the terminator. Returns false if no terminator is found
// within [pos, dataSize) (protects against out-of-bounds reads and overflow).
static bool readString(const uint8_t* data, int dataSize, int& pos, std::string& out)
{
    if (pos < 0 || pos >= dataSize)
    {
        return false;
    }
    // Positive here, so the conversion to size_t keeps the value.
    const size_t remaining = static_cast<size_t>(dataSize - pos);
    const void* nullPos = memchr(&data[pos], 0, remaining);
    if (nullPos == nullptr)
    {
        return false; // No null terminator within the buffer bounds.
    }
    // The terminator lies inside [pos, dataSize): length < remaining, so
    // pos + length + 1 <= dataSize and the int arithmetic below is exact.
    const size_t length = static_cast<size_t>(
        static_cast<const uint8_t*>(nullPos) - &data[pos]);
    out.assign(reinterpret_cast<const char*>(&data[pos]), length);
    pos += static_cast<int>(length) + 1;
    return true;
}



namespace
{

// Restores the parameters unless commit() was called: deserialize() replaces
// the object as a whole or leaves it as it was.
class ParamsRollback
{
public:
    explicit ParamsRollback(VStreamerParams& target) : m_target(target), m_saved(target)
    {
    }

    ParamsRollback(const ParamsRollback&) = delete;
    ParamsRollback& operator=(const ParamsRollback&) = delete;

    ~ParamsRollback()
    {
        if (!m_committed)
        {
            m_target = std::move(m_saved);
        }
    }

    void commit()
    {
        m_committed = true;
    }

private:
    VStreamerParams& m_target;
    VStreamerParams m_saved;
    bool m_committed{false};
};

} // namespace



bool VStreamerParams::deserialize(uint8_t *data, int dataSize)
{
    // Check data size.
    if (data == nullptr || dataSize < 14)
    {
        return false;
    }

    // Check header.
    if (data[0] != 0x02)
    {
        return false;
    }

    // Decode version.
    //
    // Both halves are checked, and the minor half matters as much as the
    // major: the parameter mask grew from 8 bytes to 10 in 3.2, so a 3.1
    // message read with 3.2 offsets would decode garbage into every field.
    // Rejecting it here is what keeps the format extensible.
    if (data[1] != VSTREAMER_MAJOR_VERSION || data[2] != VSTREAMER_MINOR_VERSION)
    {
        return false;
    }

    // All or nothing: a message that fails halfway (a truncated field, a
    // string without its terminator) must not leave a mixture of old and new
    // values in the object.
    ParamsRollback rollback(*this);

    // Start of actual data.
    int pos = 13;

    if (checkBit(data[3], 7))
    {
        if (dataSize - pos < BOOL_SIZE)
        {
            return false;
        }
        // Normalised, not memcpy'd: a bool holding any byte other than 0
        // or 1 is undefined behaviour, and the wire is attacker-supplied.
        enable = (data[pos] != 0);
        pos += BOOL_SIZE;
    }
    else
    {
        enable = false;
    }

    if (checkBit(data[3], 6))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&width, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        width = 0;
    }

    if (checkBit(data[3], 5))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&height, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        height = 0;
    }

    if (checkBit(data[3], 4))
    {
        if (!readString(data, dataSize, pos, directStreamIp))
        {
            return false;
        }
    }
    else
    {
        directStreamIp = "";
    }

    if (checkBit(data[3], 3))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&rtspPort, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        rtspPort = 0;
    }

    if (checkBit(data[3], 2))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&directStreamPort, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        directStreamPort = 0;
    }

    if (checkBit(data[3], 1))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&webRtcPort, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        webRtcPort = 0;
    }

    if (checkBit(data[3], 0))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&hlsPort, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        hlsPort = 0;
    }

    if (checkBit(data[4], 7))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&srtPort, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        srtPort = 0;
    }

    if (checkBit(data[4], 6))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&rtmpPort, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        rtmpPort = 0;
    }

    if (checkBit(data[4], 5))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&metadataPort, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        metadataPort = 0;
    }

    if (checkBit(data[4], 4))
    {
        if (dataSize - pos < BOOL_SIZE)
        {
            return false;
        }
        // Normalised, not memcpy'd: a bool holding any byte other than 0
        // or 1 is undefined behaviour, and the wire is attacker-supplied.
        rtspEnable = (data[pos] != 0);
        pos += BOOL_SIZE;
    }
    else
    {
        rtspEnable = false;
    }

    if (checkBit(data[4], 3))
    {
        if (dataSize - pos < BOOL_SIZE)
        {
            return false;
        }
        // Normalised, not memcpy'd: a bool holding any byte other than 0
        // or 1 is undefined behaviour, and the wire is attacker-supplied.
        directStreamEnable = (data[pos] != 0);
        pos += BOOL_SIZE;
    }
    else
    {
        directStreamEnable = false;
    }

    if (checkBit(data[4], 2))
    {
        if (dataSize - pos < BOOL_SIZE)
        {
            return false;
        }
        // Normalised, not memcpy'd: a bool holding any byte other than 0
        // or 1 is undefined behaviour, and the wire is attacker-supplied.
        webRtcEnable = (data[pos] != 0);
        pos += BOOL_SIZE;
    }
    else
    {
        webRtcEnable = false;
    }

    if (checkBit(data[4], 1))
    {
        if (dataSize - pos < BOOL_SIZE)
        {
            return false;
        }
        // Normalised, not memcpy'd: a bool holding any byte other than 0
        // or 1 is undefined behaviour, and the wire is attacker-supplied.
        hlsEnable = (data[pos] != 0);
        pos += BOOL_SIZE;
    }
    else
    {
        hlsEnable = false;
    }

    if (checkBit(data[4], 0))
    {
        if (dataSize - pos < BOOL_SIZE)
        {
            return false;
        }
        // Normalised, not memcpy'd: a bool holding any byte other than 0
        // or 1 is undefined behaviour, and the wire is attacker-supplied.
        srtEnable = (data[pos] != 0);
        pos += BOOL_SIZE;
    }
    else
    {
        srtEnable = false;
    }

    if (checkBit(data[5], 7))
    {
        if (dataSize - pos < BOOL_SIZE)
        {
            return false;
        }
        // Normalised, not memcpy'd: a bool holding any byte other than 0
        // or 1 is undefined behaviour, and the wire is attacker-supplied.
        rtmpEnable = (data[pos] != 0);
        pos += BOOL_SIZE;
    }
    else
    {
        rtmpEnable = false;
    }

    if (checkBit(data[5], 6))
    {
        if (dataSize - pos < BOOL_SIZE)
        {
            return false;
        }
        // Normalised, not memcpy'd: a bool holding any byte other than 0
        // or 1 is undefined behaviour, and the wire is attacker-supplied.
        metadataEnable = (data[pos] != 0);
        pos += BOOL_SIZE;
    }
    else
    {
        metadataEnable = false;
    }

    if (checkBit(data[5], 5))
    {
        if (!readString(data, dataSize, pos, rtspMulticastIp))
        {
            return false;
        }
    }
    else
    {
        rtspMulticastIp = "";
    }

    if (checkBit(data[5], 4))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&rtspMulticastPort, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        rtspMulticastPort = 0;
    }

    if (checkBit(data[5], 3))
    {
        if (!readString(data, dataSize, pos, user))
        {
            return false;
        }
    }
    else
    {
        user = "";
    }

    if (checkBit(data[5], 2))
    {
        if (!readString(data, dataSize, pos, password))
        {
            return false;
        }
    }
    else
    {
        password = "";
    }

    if (checkBit(data[5], 1))
    {
        if (!readString(data, dataSize, pos, suffix))
        {
            return false;
        }
    }
    else
    {
        suffix = "";
    }

    if (checkBit(data[5], 0))
    {
        if (!readString(data, dataSize, pos, metadataSuffix))
        {
            return false;
        }
    }
    else
    {
        metadataSuffix = "";
    }

    if (checkBit(data[6], 7))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&minBitrateKbps, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        minBitrateKbps = 0;
    }

    if (checkBit(data[6], 6))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&maxBitrateKbps, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        maxBitrateKbps = 0;
    }

    if (checkBit(data[6], 5))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&bitrateKbps, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        bitrateKbps = 0;
    }

    if (checkBit(data[6], 4))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&bitrateMode, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        bitrateMode = 0;
    }

    if (checkBit(data[6], 3))
    {
        if (dataSize - pos < FLOAT_SIZE)
        {
            return false;
        }
        memcpy(&fps, &data[pos], sizeof(float));
        pos += FLOAT_SIZE;
    }
    else
    {
        fps = 0;
    }

    if (checkBit(data[6], 2))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&gop, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        gop = 0;
    }

    if (checkBit(data[6], 1))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&h264Profile, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        h264Profile = 0;
    }

    if (checkBit(data[6], 0))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&jpegQuality, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        jpegQuality = 0;
    }

    if (checkBit(data[7], 7))
    {
        if (!readString(data, dataSize, pos, codec))
        {
            return false;
        }
    }
    else
    {
        codec = "";
    }

    if (checkBit(data[7], 6))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&fitMode, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        fitMode = 0;
    }

    if (checkBit(data[7], 5))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&cycleTimeUs, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        cycleTimeUs = 0;
    }

    if (checkBit(data[7], 4))
    {
        if (dataSize - pos < BOOL_SIZE)
        {
            return false;
        }
        // Normalised, not memcpy'd: a bool holding any byte other than 0
        // or 1 is undefined behaviour, and the wire is attacker-supplied.
        overlayEnable = (data[pos] != 0);
        pos += BOOL_SIZE;
    }
    else
    {
        overlayEnable = false;
    }

    if (checkBit(data[7], 3))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&type, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        type = 0;
    }

    if (checkBit(data[7], 2))
    {
        if (dataSize - pos < FLOAT_SIZE)
        {
            return false;
        }
        memcpy(&custom1, &data[pos], sizeof(float));
        pos += FLOAT_SIZE;
    }
    else
    {
        custom1 = 0;
    }

    if (checkBit(data[7], 1))
    {
        if (dataSize - pos < FLOAT_SIZE)
        {
            return false;
        }
        memcpy(&custom2, &data[pos], sizeof(float));
        pos += FLOAT_SIZE;
    }
    else
    {
        custom2 = 0;
    }

    if (checkBit(data[7], 0))
    {
        if (dataSize - pos < FLOAT_SIZE)
        {
            return false;
        }
        memcpy(&custom3, &data[pos], sizeof(float));
        pos += FLOAT_SIZE;
    }
    else
    {
        custom3 = 0;
    }

    if (checkBit(data[8], 7))
    {
        if (!readString(data, dataSize, pos, rtspKey))
        {
            return false;
        }
    }
    else
    {
        rtspKey = "";
    }

    if (checkBit(data[8], 6))
    {
        if (!readString(data, dataSize, pos, rtspCert))
        {
            return false;
        }
    }
    else
    {
        rtspCert = "";
    }

    if (checkBit(data[8], 5))
    {
        if (!readString(data, dataSize, pos, webRtcKey))
        {
            return false;
        }
    }
    else
    {
        webRtcKey = "";
    }

    if (checkBit(data[8], 4))
    {
        if (!readString(data, dataSize, pos, webRtcCert))
        {
            return false;
        }
    }
    else
    {
        webRtcCert = "";
    }

    if (checkBit(data[8], 3))
    {
        if (!readString(data, dataSize, pos, hlsKey))
        {
            return false;
        }
    }
    else
    {
        hlsKey = "";
    }

    if (checkBit(data[8], 2))
    {
        if (!readString(data, dataSize, pos, hlsCert))
        {
            return false;
        }
    }
    else
    {
        hlsCert = "";
    }

    if (checkBit(data[8], 1))
    {
        if (!readString(data, dataSize, pos, rtmpKey))
        {
            return false;
        }
    }
    else
    {
        rtmpKey = "";
    }

    if (checkBit(data[8], 0))
    {
        if (!readString(data, dataSize, pos, rtmpCert))
        {
            return false;
        }
    }
    else
    {
        rtmpCert = "";
    }

    if (checkBit(data[9], 7))
    {
        if (!readString(data, dataSize, pos, rtspEncryption))
        {
            return false;
        }
    }
    else
    {
        rtspEncryption = "";
    }

    if (checkBit(data[9], 6))
    {
        if (!readString(data, dataSize, pos, webRtcEncryption))
        {
            return false;
        }
    }
    else
    {
        webRtcEncryption = "";
    }

    if (checkBit(data[9], 5))
    {
        if (!readString(data, dataSize, pos, rtmpEncryption))
        {
            return false;
        }
    }
    else
    {
        rtmpEncryption = "";
    }

    if (checkBit(data[9], 4))
    {
        if (!readString(data, dataSize, pos, hlsEncryption))
        {
            return false;
        }
    }
    else
    {
        hlsEncryption = "";
    }

    if (checkBit(data[9], 3))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&logLevel, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        logLevel = 0;
    }

    if (checkBit(data[9], 2))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&rtspsPort, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        rtspsPort = 0;
    }

    if (checkBit(data[9], 1))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&rtmpsPort, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        rtmpsPort = 0;
    }

    if (checkBit(data[9], 0))
    {
        if (!readString(data, dataSize, pos, directStreamType))
        {
            return false;
        }
    }
    else
    {
        directStreamType = "";
    }

    if (checkBit(data[10], 7))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&directStreamBitrateKbps, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        directStreamBitrateKbps = 0;
    }

    if (checkBit(data[10], 6))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&directStreamMaxPayloadSize, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        directStreamMaxPayloadSize = 0;
    }

    if (checkBit(data[10], 5))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&directStreamPacingMode, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        directStreamPacingMode = 0;
    }

    if (checkBit(data[10], 4))
    {
        if (!readString(data, dataSize, pos, serverStreamType))
        {
            return false;
        }
    }
    else
    {
        serverStreamType = "";
    }

    if (checkBit(data[10], 3))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&multicastTtl, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        multicastTtl = 0;
    }

    if (checkBit(data[10], 2))
    {
        if (!readString(data, dataSize, pos, securityProfile))
        {
            return false;
        }
    }
    else
    {
        securityProfile = "";
    }

    if (checkBit(data[10], 1))
    {
        if (!readString(data, dataSize, pos, publicAddress))
        {
            return false;
        }
    }
    else
    {
        publicAddress = "";
    }

    if (checkBit(data[10], 0))
    {
        if (!readString(data, dataSize, pos, bindAddress))
        {
            return false;
        }
    }
    else
    {
        bindAddress = "";
    }

    if (checkBit(data[11], 7))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&rtpPortMin, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        rtpPortMin = 0;
    }

    if (checkBit(data[11], 6))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&rtpPortMax, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        rtpPortMax = 0;
    }

    if (checkBit(data[11], 5))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&webRtcMediaPort, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        webRtcMediaPort = 0;
    }

    if (checkBit(data[11], 4))
    {
        if (!readString(data, dataSize, pos, corsAllowedOrigin))
        {
            return false;
        }
    }
    else
    {
        corsAllowedOrigin = "";
    }

    if (checkBit(data[11], 3))
    {
        if (dataSize - pos < INT_SIZE)
        {
            return false;
        }
        memcpy(&serverStreamMaxPayloadSize, &data[pos], sizeof(int));
        pos += INT_SIZE;
    }
    else
    {
        serverStreamMaxPayloadSize = 0;
    }

    rollback.commit();

    return true;
}



void VStreamer::encodeSetParamCommand(
    uint8_t *data, int &size, VStreamerParam id, float value)
{
    if (data == nullptr)
    {
        size = 0;
        return;
    }

    // Fill header.
    data[0] = 0x01;
    data[1] = VSTREAMER_MAJOR_VERSION;
    data[2] = VSTREAMER_MINOR_VERSION;

    // Fill data.
    int paramId = static_cast<int>(id);
    memcpy(&data[3], &paramId, 4);
    memcpy(&data[7], &value, 4);
    size = 11;
}



void cr::video::VStreamer::encodeSetParamCommand(
    uint8_t* data, int& size, VStreamerParam id, std::string value)
{
    // The encoded size (8 + value.size()) is reported in an int: a value too
    // long for it is refused before anything is written, instead of wrapping
    // into a wrong size.
    if (data == nullptr ||
        value.size() > static_cast<size_t>(numeric_limits<int>::max() - 8))
    {
        size = 0;
        return;
    }

    // Fill header. 0x03, NOT 0x02: 0x02 is the params-serialize header, and a
    // string set-param command sharing it meant decodeCommand would misread a
    // serialized VStreamerParams snapshot as a garbage string set-param. The
    // two message families now have disjoint header bytes
    // (0x00 command, 0x01 numeric param, 0x03 string param, 0x02 params).
    data[0] = 0x03;
    data[1] = VSTREAMER_MAJOR_VERSION;
    data[2] = VSTREAMER_MINOR_VERSION;

    // Fill data.
    int paramId = static_cast<int>(id);
    memcpy(&data[3], &paramId, 4);
    memcpy(&data[7], value.c_str(), value.size() + 1);
    size = 7 + static_cast<int>(value.size()) + 1;
}



void cr::video::VStreamer::encodeCommand(uint8_t *data,
                                         int &size,
                                         cr::video::VStreamerCommand id)
{
    if (data == nullptr)
    {
        size = 0;
        return;
    }

    // Fill header.
    data[0] = 0x00;
    data[1] = VSTREAMER_MAJOR_VERSION;
    data[2] = VSTREAMER_MINOR_VERSION;

    // Fill data.
    int commandId = static_cast<int>(id);
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
    value = 0.0f;
    strValue = "";

    // Check size.
    if (data == nullptr || size < 7)
    {
        return -1;
    }

    // Check version.
    if (data[1] != VSTREAMER_MAJOR_VERSION || data[2] != VSTREAMER_MINOR_VERSION)
    {
        return -1;
    }

    // Extract data.
    int id = 0;
    memcpy(&id, &data[3], 4);

    // Check command type.
    if (data[0] == 0x00)
    {
        // Action command is a fixed 7-byte datagram. A longer buffer is a
        // different message (or a truncated concat), not a COMMAND.
        if (size != 7)
        {
            return -1;
        }
        commandId = static_cast<VStreamerCommand>(id);
        return 0;
    }
    else if (data[0] == 0x01)
    {
        // Check size.
        if (size != 11)
        {
            return -1;
        }

        paramId = static_cast<VStreamerParam>(id);
        memcpy(&value, &data[7], 4);
        return 1;
    }
    else if (data[0] == 0x03)
    {
        // String set-param. A 0x02 datagram is a params-serialize snapshot, not
        // a command, and now falls through to the -1 below rather than being
        // mangled into a string set-param.
        // Header (3) + param id (4) + at least the null terminator.
        if (size < 8)
        {
            return -1;
        }

        paramId = static_cast<VStreamerParam>(id);

        // Require an in-range terminator. Silently truncating at 511 bytes
        // used to accept a payload that was never encoded that way, and a
        // missing terminator used to swallow whatever followed in the buffer.
        // size >= 8 here, so remaining is positive and so is the size_t.
        const int remaining = size - 7;
        const void* nullPos = memchr(&data[7], 0,
                                     static_cast<size_t>(remaining));
        if (nullPos == nullptr)
        {
            return -1;
        }
        // length < remaining: it fits in an int.
        const size_t length = static_cast<size_t>(
            static_cast<const uint8_t*>(nullPos) - &data[7]);
        if (7 + static_cast<int>(length) + 1 != size)
        {
            return -1;
        }
        strValue.assign(reinterpret_cast<const char*>(&data[7]), length);
        return 2;
    }

    return -1;
}



bool cr::video::VStreamer::decodeAndExecuteCommand(uint8_t* data, int size)
{
    // Decode command. Defaults are unused: decodeCommand fills the id that
    // matches the header, and a decode failure returns before execute/setParam.
    VStreamerCommand commandId = VStreamerCommand::RESTART;
    VStreamerParam paramId = VStreamerParam::FIT_MODE;
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