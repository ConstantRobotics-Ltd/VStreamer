![vstreamer_web_logo](./static/vstreamer_web_logo.png)



# **VStreamer interface C++ library**

**v3.3.2**



# Table of contents

- [Overview](#overview)
- [Versions](#versions)
- [Library files](#library-files)
- [Video streamer interface class description](#video-streamer-interface-class-description)
  - [VStreamer class declaration](#vstreamer-class-declaration)
  - [getVersion method](#getversion-method)
  - [initVStreamer method](#initvstreamer-method)
  - [isVStreamerInit method](#isvstreamerinit-method)
  - [sendFrame method](#sendframe-method)
  - [closeVStreamer method](#closevstreamer-method)
  - [setParam method](#setparam-method)
  - [getParams method](#getparams-method)
  - [executeCommand method](#executecommand-method)
  - [decodeAndExecuteCommand method](#decodeandexecutecommand-method)
  - [encodeSetParamCommand method](#encodesetparamcommand-method)
  - [encodeCommand method](#encodecommand-method)
  - [decodeCommand method](#decodecommand-method)
- [Data structures](#data-structures)
  - [VStreamerCommand enum](#vstreamercommand-enum)
  - [VStreamerParam enum](#vstreamerparam-enum)
- [VStreamerParams class description](#vstreamerparams-class-description)
  - [VStreamerParams class declaration](#vstreamerparams-class-declaration)
  - [Serialize video streamer parameters](#serialize-video-streamer-parameters)
  - [Deserialize video streamer parameters](#deserialize-video-streamer-parameters)
  - [Read parameters from JSON file and write to JSON file](#read-parameters-from-json-file-and-write-to-json-file)
- [Build and connect to your project](#build-and-connect-to-your-project)
  - [Build stand alone](#build-stand-alone)
  - [CMake options](#cmake-options)
  - [Connect to your project](#connect-to-your-project)
- [Portability](#portability)
- [How to make custom implementation](#how-to-make-custom-implementation)



# Overview

The **VStreamer** C++ library provides a standard interface and defines data structures and rules for different video stream classes. The **VStreamer** interface class does not perform any operations by itself; it only provides an interface and methods to encode/decode commands and serialize/deserialize parameters. The **VStreamer** class also provides data structures for video stream parameters. Different video stream classes inherit the interface from the **VStreamer** C++ class. The **VStreamer.h** file contains a list of data structures ([VStreamerCommand](#vstreamercommand-enum) enum, [VStreamerParam](#vstreamerparam-enum) enum and [VStreamerParams](#vstreamerparams-class-description) class). The [VStreamerParams](#vstreamerparams-class-description) class contains all streamer parameters and includes methods to serialize and deserialize parameters. The [VStreamerCommand](#vstreamercommand-enum) enum contains IDs of commands supported by the **VStreamer** class. The [VStreamerParam](#vstreamerparam-enum) enum contains IDs of parameters supported by the **VStreamer** class. All video streamers should include parameters and commands listed in the **VStreamer.h** file. The **VStreamer** interface class depends on: [ConfigReader](https://rapidpixel.constantrobotics.com/docs/Service/ConfigReader.html) library (provides methods to read/write JSON config files), [VCodec](https://rapidpixel.constantrobotics.com/docs/VideoCoding/VCodec.html) library (provides interface for video codecs), [VOverlay](https://rapidpixel.constantrobotics.com/docs/Service/VOverlay.html) library (provides interface for overlay engines) and **Frame** library (describes video frame, used by **VCodec**, **VOverlay** and the **sendFrame(...)** method). The repository doesn't contain the source code of these libraries (see [Build and connect to your project](#build-and-connect-to-your-project)).



# Versions

**Table 1** - Library versions.

| Version | Release date | What's new                    |
| ------- | ------------ | ----------------------------- |
| 1.0.0   | 15.02.2024   | First version of the library. |
| 1.1.0   | 26.02.2024   | - New parameters added for multicast streaming. |
| 1.1.1   | 20.03.2024   | - VCodec class updated.<br />- VOverlay class updated.<br />- Frame sub-repository excluded.<br />- Documentation updated. |
| 1.1.2   | 21.05.2024   | - Submodules updated.<br />- Documentation updated. |
| 1.1.3   | 10.07.2024   | - Submodules updated.<br />- CMake updated. |
| 1.1.4   | 31.10.2024   | - Updated VCodec interface.    |
| 2.0.0   | 01.11.2025   | - Updated VStreamer interface to support new video servers. |
| 2.1.0   | 15.06.2026   | - New **directStreamType** parameter to select the direct stream transport/type. |
| 2.2.0   | 16.06.2026   | - **Breaking serialize/deserialize change** (8th parameter-mask byte added, strict major.minor version gate): producers and consumers must be rebuilt in lockstep.<br/>- New direct-stream parameters: **directStreamBitrateKbps**, **directStreamMaxPayloadSize**, **directStreamPacingMode**.<br/>- New **serverStreamType** (server-delivered stream type). |
| 3.0.0   | 17.06.2026   | - **Breaking parameter rename** for a clear two-leg model: `ip`→**directStreamIp**, `rtpPort`→**directStreamPort**, `rtpEnable`→**directStreamEnable**; `rtspStreamMode`→**serverStreamType**. Direct-stream params keep the `directStream*` prefix.<br/>- **directStreamType** and **serverStreamType** are **string** values whose accepted set is implementation-defined (each concrete video streamer defines the values and their meaning, including whether KLV metadata is carried; for example `"rtp"`, `"mpegts"`).<br/>- The direct stream is transport-agnostic (its own IP/port, not RTP-specific). |
| 3.1.0   | 18.06.2026   | - Removed **KlvMode** parameter. |
| 3.2.0   | 17.08.2026   | - Added new parameters. |
| 3.3.0   | 17.08.2026   | - ConfigReader submodule updated. |
| 3.3.1   | 09.10.2026   | Deep code review.<br />- Behavior change: **deserialize(...)** applies a message as a whole or not at all: a truncated field or a string without its terminator leaves the object as it was (before, the fields read up to the error were already overwritten).<br />- Behavior change: **encodeSetParamCommand(...)** with a string longer than INT_MAX - 8 bytes sets **size** to 0 and writes nothing (before, the size overflowed).<br />- Size arithmetic of **serialize(...)** and **deserialize(...)** cannot overflow for any buffer size or string length. |
| 3.3.2   | 17.10.2026   | - Sub-repositories excluded: **Frame**, **ConfigReader**, **VOverlay** and **VCodec** must be placed next to the library repository.<br />- Method **decodeCommand(...)** rejects unknown command and parameter IDs and doesn't change output arguments if it returns -1.<br />- Method **deserialize(...)** accepts data with empty mask (13 bytes) and rejects data with mask bits of unknown fields.<br />- Method **serialize(...)** skips a string which contains a NUL character, method **encodeSetParamCommand(...)** doesn't encode such a string.<br />- Methods **serialize(...)** and **deserialize(...)** use one table of fields (the format of the data is the same).<br />- Fixed description of the JSON functions and of the JSON file example.<br />- Compiler warning options and security options added to CMake files.<br />- Example of custom video streamer is thread-safe and checks values.<br />- Test application extended. |



# Library files

The library is supplied as source code only. The user receives the files as a CMake project (repository). The repository structure is shown below:

```xml
CMakeLists.txt ------------------- Main CMake file of the library.
example -------------------------- Folder with simple example of VStreamer implementation.
    CMakeLists.txt --------------- CMake file for example custom video streamer class.
    CustomVStreamer.cpp ---------- C++ implementation file.
    CustomVStreamer.h ------------ Header with CustomVStreamer class declaration.
    CustomVStreamerVersion.h ----- Header file which includes CustomVStreamer version.
    CustomVStreamerVersion.h.in -- CMake service file to generate version file.
test ----------------------------- Folder with VStreamer test application.
    CMakeLists.txt --------------- CMake file for VStreamer test application.
    main.cpp --------------------- Source code file of VStreamer class test application.
src ------------------------------ Folder with source code of the library.
    CMakeLists.txt --------------- CMake file of the library.
    VStreamer.cpp ---------------- Source code file of the library.
    VStreamer.h ------------------ Main library header file.
    VStreamerVersion.h ----------- Header file which includes version of the library.
    VStreamerVersion.h.in -------- CMake service file to generate version file.
```



# Video streamer interface class description



## VStreamer class declaration

The **VStreamer** interface class is declared in the **VStreamer.h** file. Class declaration:

```cpp
namespace rapidpixel
{
class VStreamer
{
public:

    /// Class destructor.
    virtual ~VStreamer();

    /// Get string of current library version.
    static std::string getVersion();

    /// Initialize video streamer.
    virtual bool initVStreamer(VStreamerParams& params,
                               VCodec* codec = nullptr,
                               VOverlay* overlay = nullptr) = 0;

    /// Get initialization status.
    virtual bool isVStreamerInit() = 0;

    /// Close video streamer.
    virtual void closeVStreamer() = 0;

    /// Send frame to video streamer.
    virtual bool sendFrame(Frame& frame, uint8_t* userData = nullptr,
                           int userDataSize = 0) = 0;

    /// Set video streamer parameter with a numeric value.
    virtual bool setParam(VStreamerParam id, float value) = 0;

    /// Set video streamer parameter with a string value.
    virtual bool setParam(VStreamerParam id, std::string value) = 0;

    /// Get video streamer params structure.
    virtual void getParams(VStreamerParams& params) = 0;

    /// Execute command.
    virtual bool executeCommand(VStreamerCommand id) = 0;

    /// Decode and execute command.
    virtual bool decodeAndExecuteCommand(uint8_t* data, int size);

    /// Encode set parameter command with a numeric value.
    static void encodeSetParamCommand(uint8_t* data, int& size,
                                      VStreamerParam id, float value);

    /// Encode set parameter command with a string value.
    static void encodeSetParamCommand(uint8_t* data, int& size,
                                      VStreamerParam id, std::string value);

    /// Encode action command.
    static void encodeCommand(uint8_t* data, int& size, VStreamerCommand id);

    /// Decode command.
    static int decodeCommand(uint8_t* data,
                             int size,
                             VStreamerParam& paramId,
                             VStreamerCommand& commandId,
                             float& value,
                             std::string& strValue);

protected:

    /// Default constructor. The class can be used as a base only.
    VStreamer() = default;

    /// Copy constructor.
    VStreamer(const VStreamer& src) = default;

    /// Move constructor.
    VStreamer(VStreamer&& src) = default;

    /// Copy assignment operator.
    VStreamer& operator=(const VStreamer& src) = default;

    /// Move assignment operator.
    VStreamer& operator=(VStreamer&& src) = default;
};
}
```



## getVersion method

The **getVersion()** method returns a string of the current version of the **VStreamer** class. A particular video streamer class can have its own **getVersion()** method. Method declaration:

```cpp
static std::string getVersion();
```

The method can be used without a **VStreamer** class instance:

```cpp
std::cout << "VStreamer class version: " << rapidpixel::VStreamer::getVersion()
          << std::endl;
```

Console output:

```bash
VStreamer class version: 3.3.2
```



## initVStreamer method

The **initVStreamer(...)** method initializes the video streamer with a structure of parameters. Method declaration:

```cpp
virtual bool initVStreamer(VStreamerParams& params,
                           VCodec* codec = nullptr,
                           VOverlay* overlay = nullptr) = 0;
```

| Parameter | Value                                                        |
| --------- | ------------------------------------------------------------ |
| params    | [VStreamerParams](#vstreamerparams-class-description) class object. The video streamer should set parameters according to the parameters class. A particular video streamer might not support all parameters listed in the [VStreamerParams](#vstreamerparams-class-description) class. The implementation must check the values and return FALSE for values it doesn't support (for example, an unknown **securityProfile**). |
| codec      | Pointer to [VCodec](https://rapidpixel.constantrobotics.com/docs/VideoCoding/VCodec.html) object. Used for encoding video in case of RAW input frame data. If the user sets the pointer to **nullptr**, the video streamer can process only compressed input video frames (H264, HEVC or JPEG). |
| overlay    | Pointer to [VOverlay](https://rapidpixel.constantrobotics.com/docs/Service/VOverlay.html) object. Used to overlay information on video in case the user provides RAW input frame data to the streamer. If the user sets the pointer to **nullptr**, the video streamer will not be able to overlay any information on the video. |

**Returns:** TRUE if the video streamer is initialized or FALSE if not.



## isVStreamerInit method

The **isVStreamerInit()** method returns the video streamer initialization status. Method declaration:

```cpp
virtual bool isVStreamerInit() = 0;
```

**Returns:** TRUE if the video streamer is initialized or FALSE if not.



## sendFrame method

The **sendFrame(...)** method is intended to send frames to clients. To provide a video stream, the user must call this method for every video frame coming from the video source. In case of processing RAW video frames, the streamer must resize the video (if necessary) and overlay information (if the pointer to the video overlay class is set in the [initVStreamer(...)](#initvstreamer-method) method). Method declaration:

```cpp
virtual bool sendFrame(Frame& frame, uint8_t* userData = nullptr,
                       int userDataSize = 0) = 0;
```

| Parameter | Value                                                        |
| --------- | ------------------------------------------------------------ |
| frame     | [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class object. Particular streamers can support RAW video frames or(and) compressed video frames. |
| userData  | Pointer to user data (telemetry). Some streamers may support telemetry streaming (for example, [KLV](https://en.wikipedia.org/wiki/KLV) metadata) synchronized with video streams (for example, by timestamp). If the parameter is **nullptr**, the streamer will not send any telemetry data. The buffer must be valid for **userDataSize** bytes. |
| userDataSize  | Size of user data (telemetry), in bytes. If the parameter is **0**, the streamer will not send any telemetry data. |

**Returns:** TRUE if the frame was sent (accepted by streamer) or FALSE if not.



## closeVStreamer method

The **closeVStreamer()** method closes the video streamer. The method stops all threads and releases memory. Method declaration:

```cpp
virtual void closeVStreamer() = 0;
```



## setParam method

The **setParam(...)** method sets a new value for a video stream parameter. Each implementation of the video streamer must provide a thread-safe **setParam(...)** method call. This means that the **setParam(...)** method can be safely called from any thread. Also, the method has two overloaded versions depending on the type of value. Method declaration:

```cpp
virtual bool setParam(VStreamerParam id, float value) = 0;
virtual bool setParam(VStreamerParam id, std::string value) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Video stream parameter ID according to [VStreamerParam](#vstreamerparam-enum) enum. |
| value     | Value of parameter. It can be either string or float type. It depends on parameter. The value can come from a decoded command: the implementation must check it (for example, NaN, infinity or a value out of the range of the parameter) before use. |

**Returns:** TRUE if the parameter is set or FALSE if not.



## getParams method

The **getParams(...)** method is designed to obtain the video streamer parameters class ([VStreamerParams](#vstreamerparams-class-description)). Each implementation of the video streamer must provide a thread-safe **getParams(...)** method call. This means that the **getParams(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual void getParams(VStreamerParams& params) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| params    | [VStreamerParams](#vstreamerparams-class-description) class object. |



## executeCommand method

The **executeCommand(...)** method executes a video stream command. A particular implementation of the video stream must provide a thread-safe **executeCommand(...)** method call. This means that the **executeCommand(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual bool executeCommand(VStreamerCommand id) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Video stream command ID according to [VStreamerCommand](#vstreamercommand-enum) enum. |

**Returns:** TRUE if the command was executed or FALSE if not.



## decodeAndExecuteCommand method

The **decodeAndExecuteCommand(...)** method decodes and executes command encoded by [encodeSetParamCommand(...)](#encodesetparamcommand-method) and [encodeCommand(...)](#encodecommand-method) methods on video streamer side. It is a virtual method which means if implementation does not define it, default definition from **VStreamer** class will be used. Each implementation of the video streamer must provide thread-safe **setParam(...)** and **executeCommand(...)** method calls to make default definition of **decodeAndExecuteCommand(...)** thread-safe. This means that the **decodeAndExecuteCommand(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual bool decodeAndExecuteCommand(uint8_t* data, int size);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to input command. The buffer must be valid for **size** bytes. |
| size      | Size of command.                                             |

**Returns:** TRUE if command decoded (SET_PARAM or COMMAND) by the [decodeCommand(...)](#decodecommand-method) method and executed (action command or set param command), or FALSE if the command is not decoded or not executed.



## encodeSetParamCommand method

The **encodeSetParamCommand(...)** static method encodes a command to change any parameter in a remote video streamer. To control a video streamer remotely, the developer has to design their own protocol and according to it encode the command and deliver it over the communication channel. To simplify this, the **VStreamer** class contains static methods for encoding the control command. The **VStreamer** class provides two types of commands: a parameter change command (SET_PARAM) and an action command (COMMAND). **encodeSetParamCommand(...)** is designed to encode the SET_PARAM command. The method has two overloads: one for numeric parameters and one for string parameters. Method declaration:

```cpp
static void encodeSetParamCommand(uint8_t* data, int& size,
                                  VStreamerParam id, float value);

static void encodeSetParamCommand(uint8_t* data, int& size,
                                  VStreamerParam id, std::string value);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to data buffer for encoded command. For the float overload must have size >= 11. For the string overload must have size >= 8 + value.size() (3-byte header + 4-byte parameter ID + the string content + null terminator). |
| size      | Size of encoded data. 11 bytes for the float overload; 8 + value.size() bytes for the string overload (minimum 8 bytes for an empty string). 0, and nothing is written, if **data** is null, the string contains a NUL character or the string is longer than INT_MAX - 8 bytes. |
| id        | Parameter ID according to [VStreamerParam](#vstreamerparam-enum) enum. |
| value     | Numeric video streamer parameter value. Only for non-string parameters. For string parameters (see [VStreamerParam](#vstreamerparam-enum) enum) this parameter may have any value. |
| value     | String parameter value (see [VStreamerParam](#vstreamerparam-enum) enum). |

**encodeSetParamCommand(...)** is a static method and is used without a **VStreamer** class instance. This method is used on the client side (control system). Example of command encoding:

```cpp
// Buffer for encoded data.
uint8_t data[11];
// Size of encoded data.
int size = 0;
// Parameter value.
const float outValue = 10.0f;
// Encode command.
rapidpixel::VStreamer::encodeSetParamCommand(
        data, size, rapidpixel::VStreamerParam::CUSTOM1, outValue);
if (size == 0)
{
    std::cout << "Command not encoded" << std::endl;
}
```



## encodeCommand method

The **encodeCommand(...)** static method encodes a command for a remote video streamer. To control a video streamer remotely, the developer has to design their own protocol and according to it encode the command and deliver it over the communication channel. To simplify this, the **VStreamer** class contains static methods for encoding the control command. The **VStreamer** class provides two types of commands: a parameter change command (SET_PARAM) and an action command (COMMAND). **encodeCommand(...)** is designed to encode the COMMAND (action command). Method declaration:

```cpp
static void encodeCommand(uint8_t* data, int& size, VStreamerCommand id);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to data buffer for output command. Must have size >= 7 bytes. |
| size      | Size of encoded data. Will be 7 bytes, or 0 (nothing is written) if **data** is null. |
| id        | Command ID according to [VStreamerCommand](#vstreamercommand-enum) enum. |

**encodeCommand(...)** is a static method and is used without a **VStreamer** class instance. This method is used on the client side (control system). Example of command encoding:

```cpp
// Buffer for encoded data.
uint8_t data[7];
// Size of encoded data.
int size = 0;
// Encode command.
rapidpixel::VStreamer::encodeCommand(
        data, size, rapidpixel::VStreamerCommand::RESTART);
if (size == 0)
{
    std::cout << "Command not encoded" << std::endl;
}
```



## decodeCommand method

The **decodeCommand(...)** static method decodes a command on the video streamer side (edge device). Method declaration:

```cpp
static int decodeCommand(uint8_t* data,
                         int size,
                         VStreamerParam& paramId,
                         VStreamerCommand& commandId,
                         float& value,
                         std::string& strValue);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to input command. The buffer must be valid for **size** bytes. |
| size      | Size of command. Must be exactly 11 bytes for a float SET_PARAM command, exactly 8 + `strlen(strValue)` bytes (including the null terminator) for a string SET_PARAM command, and exactly 7 bytes for COMMAND. A longer or unterminated buffer is an error. |
| paramId   | Parameter ID according to [VStreamerParam](#vstreamerparam-enum) enum. After decoding a SET_PARAM command the method will return the parameter ID. Not changed if the method returns **0** or **-1**. |
| commandId | Command ID according to [VStreamerCommand](#vstreamercommand-enum) enum. After decoding a COMMAND the method will return the command ID. Not changed if the method returns **1**, **2** or **-1**. |
| value    | Numeric video streamer parameter value of a SET_PARAM command with float value. Set to **0** if the method returns **0** or **2**, not changed if the method returns **-1**. |
| strValue    | String parameter value of a SET_PARAM command with string value (see [VStreamerParam](#vstreamerparam-enum) enum). Cleared if the method returns **0** or **1**, not changed if the method returns **-1**. |

**Returns:** **0** - in case of decoding COMMAND, **1** - in case of decoding SET_PARAM command with float value, **2** - in case of decoding SET_PARAM command with string value, or **-1** in case of errors.

The header byte selects the family: **0x00** COMMAND, **0x01** float SET_PARAM, **0x03** string SET_PARAM. **0x02** is the header a serialized **VStreamerParams** snapshot carries (see [Serialize video streamer parameters](#serialize-video-streamer-parameters)); a **0x02** datagram is therefore **not** a command and **decodeCommand** returns **-1** for it, rather than misreading the parameter mask as a command payload. A **null** `data` pointer, a command of another major or minor version, a COMMAND or float SET_PARAM whose `size` is not exact, a string SET_PARAM that is missing its null terminator or that has bytes after it, and a command or parameter ID which is not a value of the [VStreamerCommand](#vstreamercommand-enum) or [VStreamerParam](#vstreamerparam-enum) enum, also return **-1**. The method doesn't check the parameter value: the video streamer implementation must check it in the **setParam(...)** method.



# Data structures

The **VStreamer.h** file defines IDs for parameters (**VStreamerParam** enum) and IDs for commands (**VStreamerCommand** enum).



## VStreamerCommand enum

Enum declaration:

```cpp
enum class VStreamerCommand
{
    /// Restart.
    RESTART = 1,
    /// Enable. Equal to MODE param.
    ON,
    /// Disable. Equal to MODE param.
    OFF,
    /// Generate key frame command. The last value of the enum: it is used to
    /// check IDs.
    GENERATE_KEYFRAME
};
```

**Table 2** - Video stream action commands description. Some commands may be unsupported by a particular video stream class.

| Command    | Description                                                  |
| ------------ | ---------------------------------------------------------- |
| RESTART      | Restarts the streamer with the last [VStreamerParams](#vstreamerparams-class-declaration). |
| ON           | Enables the streamer if it is disabled.                        |
| OFF          | Disables the streamer if it is enabled.                        |
| GENERATE_KEYFRAME | Action command to generate a key frame by the video codec in case of **H264/HEVC** video encoding. This function is required in some cases. |



## VStreamerParam enum

Enum declaration:

```cpp
enum class VStreamerParam
{
    /// Streamer enable / disable, integer: 0 - disabled, 1 - enabled.
    MODE = 1,
    /// Video stream width, integer [0:8192].
    WIDTH,
    /// Video stream height, integer [0:8192].
    HEIGHT,
    /// Destination IP of the direct stream, string.
    DIRECT_STREAM_IP,
    /// RTSP port, integer [0:65535].
    RTSP_PORT,
    /// RTSPS port, integer [0:65535].
    RTSPS_PORT,
    /// Destination port of the direct stream, integer [0:65535].
    DIRECT_STREAM_PORT,
    /// WebRTC port, integer [0:65535].
    WEBRTC_PORT,
    /// HLS port, integer [0:65535].
    HLS_PORT,
    /// SRT port, integer [0:65535].
    SRT_PORT,
    /// RTMP port, integer [0:65535].
    RTMP_PORT,
    /// RTMPS port, integer [0:65535].
    RTMPS_PORT,
    /// Metadata port, integer [0:65535].
    METADATA_PORT,
    /// RTSP protocol enable / disable, integer: 0 - disable, 1 - enable.
    RTSP_MODE,
    /// Direct stream enable / disable, integer: 0 - disable, 1 - enable.
    DIRECT_STREAM_ENABLE,
    /// WebRTC protocol enable / disable, integer: 0 - disable, 1 - enable.
    WEBRTC_MODE,
    /// HLS protocol enable / disable, integer: 0 - disable, 1 - enable.
    HLS_MODE,
    /// SRT protocol enable / disable, integer: 0 - disable, 1 - enable.
    SRT_MODE,
    /// RTMP protocol enable / disable, integer: 0 - disable, 1 - enable.
    RTMP_MODE,
    /// Metadata protocol enable / disable, integer: 0 - disable, 1 - enable.
    METADATA_MODE,
    /// RTSP multicast IP, string.
    RTSP_MULTICAST_IP,
    /// RTSP multicast port, integer [0:65535].
    RTSP_MULTICAST_PORT,
    /// Streamer user (for RTSP streaming), string: "" - no user.
    USER,
    /// Streamer password (for RTSP streaming), string: "" - no password.
    PASSWORD,
    /// Streamer suffix for RTSP streaming (stream name), string: "" - no
    /// suffix.
    SUFFIX,
    /// Metadata suffix (stream name), string: "" - no suffix.
    METADATA_SUFFIX,
    /// Minimum bitrate for variable bitrate mode, integer kbps.
    MIN_BITRATE_KBPS,
    /// Maximum bitrate for variable bitrate mode, integer kbps.
    MAX_BITRATE_KBPS,
    /// Current bitrate, integer kbps.
    BITRATE_KBPS,
    /// Bitrate mode, integer: 0 - constant bitrate, 1 - variable bitrate.
    BITRATE_MODE,
    /// FPS, float.
    FPS,
    /// GOP size for H264 and H265 codecs, integer [1:65535].
    GOP,
    /// H264 profile, integer: 0 - baseline, 1 - main, 2 - high.
    H264_PROFILE,
    /// JPEG quality, integer: [1:100]% for JPEG codec.
    JPEG_QUALITY,
    /// Codec type, string: "H264", "HEVC" or "JPEG".
    CODEC,
    /// Scaling mode, integer: 0 - fit, 1 - fill.
    FIT_MODE,
    /// Cycle time, integer microseconds. Calculated by video streamer.
    CYCLE_TIME_USEC,
    /// Overlay mode, integer: 0 - disable, 1 - enable.
    OVERLAY_MODE,
    /// Type of the streamer, integer. Depends on implementation.
    TYPE,
    /// Custom parameter 1, float.
    CUSTOM1,
    /// Custom parameter 2, float.
    CUSTOM2,
    /// Custom parameter 3, float.
    CUSTOM3,
    /// Path to openssl key for RTSP, string.
    RTSP_KEY,
    /// Path to openssl certificate for RTSP, string.
    RTSP_CERT,
    /// Path to openssl key for WebRTC, string.
    WEBRTC_KEY,
    /// Path to openssl certificate for WebRTC, string.
    WEBRTC_CERT,
    /// Path to openssl key for HLS, string.
    HLS_KEY,
    /// Path to openssl certificate for HLS, string.
    HLS_CERT,
    /// Path to openssl key for RTMP, string.
    RTMP_KEY,
    /// Path to openssl certificate for RTMP, string.
    RTMP_CERT,
    /// RTSP encryption type, string: "no", "strict", "optional".
    RTSP_ENCRYPTION,
    /// WebRTC encryption type, string: "no", "yes".
    WEBRTC_ENCRYPTION,
    /// RTMP encryption type, string: "no", "strict", "optional".
    RTMP_ENCRYPTION,
    /// HLS encryption type, string: "no", "yes".
    HLS_ENCRYPTION,
    /// Logging mode. Values: 0 - Disable, 1 - Only file,
    /// 2 - Only terminal, 3 - File and terminal.
    LOG_LEVEL,
    /// Direct stream transport / type, string. Accepted values are
    /// implementation-defined (e.g. "rtp", "mpegts"); the value also decides
    /// whether KLV metadata is carried.
    DIRECT_STREAM_TYPE,
    /// Direct stream target bitrate, integer kbps.
    DIRECT_STREAM_BITRATE_KBPS,
    /// Direct stream max UDP/RTP payload size, integer bytes.
    DIRECT_STREAM_MAX_PAYLOAD,
    /// Direct stream pacing mode, integer: 0 - target bitrate, 1 - push.
    DIRECT_STREAM_PACING_MODE,
    /// Server-delivered stream type, string. Accepted values are
    /// implementation-defined (e.g. "rtp", "mpegts"); the value also decides
    /// whether KLV metadata is carried. Distinct from RTSP_MODE (protocol
    /// on / off).
    SERVER_STREAM_TYPE,
    /// Multicast TTL (scope) for every multicast leg, integer [0:255]:
    /// 0 - implementation default. An implementation may cap the value and
    /// must document the cap.
    MULTICAST_TTL,
    /// Security / compliance profile, string. Accepted values are
    /// implementation-defined; "" or "no" - the implementation's default. An
    /// unrecognised value must be rejected, never silently defaulted.
    SECURITY_PROFILE,
    /// Public (routed) address to advertise to clients in SDP/ICE instead of
    /// the locally detected one, string: "" or "no" - detect automatically.
    PUBLIC_ADDRESS,
    /// Local address to bind every listener to, string: "" or "0.0.0.0" -
    /// every interface.
    BIND_ADDRESS,
    /// Lowest port of the RTP/RTCP range, integer: 0 - any ephemeral port.
    RTP_PORT_MIN,
    /// Highest port of the RTP/RTCP range, integer: 0 - any ephemeral port.
    RTP_PORT_MAX,
    /// WebRTC media (UDP) port, integer: 0 - the implementation chooses.
    WEBRTC_MEDIA_PORT,
    /// Single origin permitted to reach the HTTP-based signalling endpoints,
    /// string: "" or "no" - the implementation's default policy.
    CORS_ALLOWED_ORIGIN,
    /// Maximum RTP payload size of the server-delivered stream, integer
    /// bytes. The last value of the enum: it is used to check IDs.
    SERVER_STREAM_MAX_PAYLOAD
};
```

**Table 3** - Video streamer parameters description. Some parameters may be unsupported by a particular video streamer class.

| Parameter        | Description         |
| ---------------- | ------------------- |
| MODE             | Enable/disable streamer, integer: **0** - disable, **1** - enabled. If the video streamer is disabled it should not stream video to clients by any protocol. |
| WIDTH            | Video stream width, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| HEIGHT           | Video stream height, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| DIRECT_STREAM_IP | Destination IP of the direct stream (point-to-point, bypasses MediaMTX), string. Transport is set by directStreamType. Default **127.0.0.1**. |
| RTSP_PORT        | Streamer's RTSP port, integer [0:65535]. |
| RTSPS_PORT       | Streamer's RTSPS port, integer [0:65535]. |
| DIRECT_STREAM_PORT         | Destination port of the direct stream (point-to-point, bypasses MediaMTX), integer [0:65535]. |
| WEBRTC_PORT      | Streamer's WebRTC port, integer [0:65535]. |
| HLS_PORT         | Streamer's HLS port, integer [0:65535]. |
| SRT_PORT         | Streamer's SRT port, integer [0:65535]. |
| RTMP_PORT        | Streamer's RTMP port, integer [0:65535]. |
| RTMPS_PORT       | Streamer's RTMPS port, integer [0:65535]. |
| METADATA_PORT    | Streamer's metadata port, integer [0:65535] (for example, for [KLV](https://en.wikipedia.org/wiki/KLV) metadata streaming.). |
| RTSP_MODE        | RTSP protocol enable / disable, integer: **0** - disable, **1** - enable. |
| DIRECT_STREAM_ENABLE         | Direct stream (point-to-point, bypasses MediaMTX) enable / disable, integer: **0** - disable, **1** - enable. |
| WEBRTC_MODE      | WebRTC protocol enable / disable, integer: **0** - disable, **1** - enable. |
| HLS_MODE         | HLS protocol enable / disable, integer: **0** - disable, **1** - enable. |
| SRT_MODE         | SRT protocol enable / disable, integer: **0** - disable, **1** - enable. |
| RTMP_MODE        | RTMP protocol enable / disable, integer: **0** - disable, **1** - enable. |
| METADATA_MODE    | Metadata protocol enable / disable, integer: **0** - disable, **1** - enable. |
| RTSP_MULTICAST_IP | RTSP multicast IP, string. Usually video server accepts range of IPs (default value **224.1.0.1/16**). Some video streamer may support only single IP (example **224.1.0.1/32**). This parameters is used only with IP mask. |
| RTSP_MULTICAST_PORT | RTSP multicast port, integer [0:65535]. |
| USER             | Streamer user (for RTSP streaming), string: "" - no user. |
| PASSWORD         | Streamer password (for RTSP streaming), string: "" - no password. |
| SUFFIX           | Streamer suffix for RTSP streaming (stream name), string: "" - no suffix. |
| METADATA_SUFFIX  | Metadata suffix (stream name), string: "" - no suffix. This parameter is used if the metadata is the separate stream in RTSP. |
| MIN_BITRATE_KBPS | Minimum bitrate for variable bitrate mode, integer kbps. |
| MAX_BITRATE_KBPS | Maximum bitrate for variable bitrate mode, integer kbps. |
| BITRATE_KBPS     | Current bitrate, integer kbps. This parameter is used for constant bitrate mode or as an initial value. |
| BITRATE_MODE     | Bitrate mode, integer: 0 - constant bitrate, 1 - variable bitrate. |
| FPS              | FPS, float. The input frame FPS can be different from the FPS in the video stream. The video streamer must provide video stream FPS for clients according to this parameter's value independent from input frame FPS ([sendFrame()](#sendframe-method)). If the FPS value is **0**, the streamer must provide FPS equal to the input video frame rate. |
| GOP              | Codec GOP size (key frame interval) in case of RAW input video frames. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| H264_PROFILE     | H264 profile, integer: 0 - baseline, 1 - main, 2 - high. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| JPEG_QUALITY     | JPEG quality, integer: [1:100]% for JPEG codec. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| CODEC            | Codec type, string: "H264", "HEVC" or "JPEG". If the user provides already encoded frames in the [sendFrame()](#sendframe-method) method. |
| FIT_MODE         | Scaling mode, integer: 0 - fit, 1 - fill. |
| CYCLE_TIME_USEC  | Cycle time, integer μsec (microseconds). Calculated by video streamer. |
| OVERLAY_MODE     | Overlay enable / disable, integer: **0** - disable, **1** - enable. This parameter enables or disables video overlay if the video overlay module is provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| TYPE             | Type of the streamer, integer. Depends on implementation. |
| CUSTOM1          | Custom parameter 1, float. |
| CUSTOM2          | Custom parameter 2, float. |
| CUSTOM3          | Custom parameter 3, float. |
| RTSP_KEY         | Path to openssl key for RTSP, string: **""** or **"no"** - no key. |
| RTSP_CERT        | Path to openssl certificate for RTSP, string: **""** or **"no"** - no certificate. |
| WEBRTC_KEY       | Path to openssl key for WebRTC, string: **""** or **"no"** - no key. |
| WEBRTC_CERT      | Path to openssl certificate for WebRTC, string: **""** or **"no"** - no certificate. |
| HLS_KEY          | Path to openssl key for HLS, string: **""** or **"no"** - no key. |
| HLS_CERT         | Path to openssl certificate for HLS, string: **""** or **"no"** - no certificate. |
| RTMP_KEY         | Path to openssl key for RTMP, string: **""** or **"no"** - no key. |
| RTMP_CERT        | Path to openssl certificate for RTMP, string: **""** or **"no"** - no certificate. |
| RTSP_ENCRYPTION  | RTSP encryption type, string: **""** or **"no"**, **"strict"**, **"optional"**. |
| WEBRTC_ENCRYPTION | WebRTC encryption type, string: **""** or **"no"**, **"yes"**. |
| RTMP_ENCRYPTION  | RTMP encryption type, string: **""** or **"no"**, **"strict"**, **"optional"**. |
| HLS_ENCRYPTION   | HLS encryption type, string: **""** or **"no"**, **"yes"**. |
| LOG_LEVEL        | Logging mode. Values: **0** - Disable, **1** - Only file, **2** - Only terminal, **3** - File and terminal. |
| DIRECT_STREAM_TYPE | Transport/type of the direct (point-to-point) stream, string. The accepted values are **implementation-defined**: the abstract **VStreamer** interface does not fix them — each concrete video-streamer implementation defines the value set and the meaning of each value, **including whether KLV metadata is carried** (there is no separate KLV flag). Example values: **"rtp"**, **"mpegts"** (and others, depending on implementation). Default **"rtp"**. |
| DIRECT_STREAM_BITRATE_KBPS | Target sending bitrate for the direct stream, integer kbps. Used as the pacer target when **DIRECT_STREAM_PACING_MODE** is **0**. |
| DIRECT_STREAM_MAX_PAYLOAD | Maximum UDP/RTP payload size for the direct stream, integer bytes. |
| DIRECT_STREAM_PACING_MODE | Pacing mode of the direct stream, integer: **0** - target bitrate, **1** - push. |
| SERVER_STREAM_TYPE | Transport/type of the **server-delivered** stream — fed to the media server, which fans it out to clients. String whose accepted values are **implementation-defined**: the abstract **VStreamer** interface does not fix them — each concrete video-streamer implementation defines the value set and the meaning of each value, **including whether KLV metadata is carried** (there is no separate KLV flag). Example values: **"rtp"**, **"mpegts"** (and others, depending on implementation). Distinct from **RTSP_MODE** (protocol enable/disable). Default **"rtp"**. |
| MULTICAST_TTL | Multicast TTL (scope) for **every** multicast leg, integer **[0:255]**: **0** - implementation default. An implementation may cap the value and must document the cap. Not RTSP-specific: it applies wherever the implementation sends to a group. Default **0**. |
| SECURITY_PROFILE | Security/compliance profile. String whose accepted values are **implementation-defined**, in the style of **DIRECT_STREAM_TYPE**: **""** or **"no"** - the implementation's own default. An unrecognised value **must be rejected**, never mapped to a default — silently downgrading a security posture is the failure this parameter exists to prevent. Default **"no"**. |
| PUBLIC_ADDRESS | Public (routed) address advertised to clients in SDP and ICE candidate lines instead of the locally detected one, string: **""** or **"no"** - detect automatically. An address **literal**, not a hostname: it goes onto the wire verbatim. Needed behind 1:1 NAT, in containers and on multi-homed hosts. Default **"no"**. |
| BIND_ADDRESS | Local address every listener binds to, string: **""** or **"0.0.0.0"** - every interface. A multi-homed host has no other way to keep a stream off an interface it must not appear on. Default **"0.0.0.0"**. |
| RTP_PORT_MIN | Lowest port of the RTP/RTCP range, integer **[0:65534]**: **0** - any ephemeral port. Should be even, because RTCP conventionally takes port+1. Default **0**. |
| RTP_PORT_MAX | Highest port of the RTP/RTCP range, integer **[0:65535]**: **0** - any ephemeral port. A firewall is configured for a range; without one an implementation picks ephemeral ports nothing has been opened for. Default **0**. |
| WEBRTC_MEDIA_PORT | WebRTC media (UDP) port, integer **[0:65535]**: **0** - the implementation chooses. Distinct from **WEBRTC_PORT**, which carries signalling only. Default **0**. |
| CORS_ALLOWED_ORIGIN | Single origin permitted to reach the HTTP-based signalling endpoints, string **"scheme://host[:port]"**: **""** or **"no"** - the implementation's default policy. Deliberately one origin, not a wildcard list. Default **"no"**. |
| SERVER_STREAM_MAX_PAYLOAD | Maximum RTP payload size of the **server-delivered** stream, integer bytes — the counterpart of **DIRECT_STREAM_MAX_PAYLOAD**. An implementation may clamp it lower: a transform applied after packetization (SRTP appends an authentication tag) can otherwise push the datagram past the path MTU. Default **1472**. |



# VStreamerParams class description



## VStreamerParams class declaration

The **VStreamerParams** class is used for video stream initialization (the [initVStreamer(...)](#initvstreamer-method) method) or to get all actual parameters (the [getParams(...)](#getparams-method) method). Also, **VStreamerParams** provides a structure to write/read parameters from JSON files, compatible with [ConfigReader](https://rapidpixel.constantrobotics.com/docs/Service/ConfigReader.html), and provides methods to serialize and deserialize parameters. The JSON functions of all 69 fields are generated by the **JSON_READABLE** macro of the **ConfigReader** library. The class doesn't check the values of the fields: the video streamer implementation must check them. The class is not thread-safe. Class declaration:

```cpp
class VStreamerParams
{
public:
    /// Mode, boolean: false - disabled, true - enabled.
    bool enable{true};
    /// Video stream width, integer [0:8192].
    int width{1280};
    /// Video stream height, integer [0:8192].
    int height{720};
    /// Destination IP of the direct stream (point-to-point, bypasses
    /// MediaMTX), string. Transport is set by directStreamType.
    std::string directStreamIp{"127.0.0.1"};
    /// RTSP port, integer [0:65535].
    int rtspPort{8554};
    /// RTSPS port, integer [0:65535].
    int rtspsPort{8555};
    /// Destination port of the direct stream, integer [0:65535].
    int directStreamPort{5004};
    /// WebRTC port, integer [0:65535].
    int webRtcPort{7000};
    /// HLS port, integer [0:65535].
    int hlsPort{8080};
    /// SRT port, integer [0:65535].
    int srtPort{6000};
    /// RTMP port, integer [0:65535].
    int rtmpPort{1935};
    /// RTMPS port, integer [0:65535].
    int rtmpsPort{1936};
    /// Metadata port, integer [0:65535].
    int metadataPort{9000};
    /// RTSP protocol enable / disable, boolean: false - disable,
    /// true - enable.
    bool rtspEnable{true};
    /// Direct stream (point-to-point, bypasses MediaMTX) enable / disable,
    /// boolean: false - disable, true - enable. Uses directStreamIp /
    /// directStreamPort and the directStream* parameters.
    bool directStreamEnable{true};
    /// WebRTC protocol enable / disable, boolean: false - disable,
    /// true - enable.
    bool webRtcEnable{true};
    /// HLS protocol enable / disable, boolean: false - disable, true - enable.
    bool hlsEnable{true};
    /// SRT protocol enable / disable, boolean: false - disable, true - enable.
    bool srtEnable{true};
    /// RTMP protocol enable / disable, boolean: false - disable,
    /// true - enable.
    bool rtmpEnable{true};
    /// Metadata protocol enable / disable, boolean: false - disable,
    /// true - enable.
    bool metadataEnable{false};
    /// RTSP multicast IP, string.
    std::string rtspMulticastIp{"224.1.0.1/16"};
    /// RTSP multicast port, integer [0:65535].
    int rtspMulticastPort{18000};
    /// Streamer user (for RTSP streaming), string: "" or "no" - no user.
    std::string user{"no"};
    /// Streamer password (for RTSP streaming), string: "" or "no" - no
    /// password.
    std::string password{"no"};
    /// Streamer suffix for RTSP streaming (stream name), string: "" - no
    /// suffix.
    std::string suffix{"live"};
    /// Metadata suffix (stream name), string: "" - no suffix.
    std::string metadataSuffix{"metadata"};
    /// Minimum bitrate for variable bitrate mode, integer kbps.
    int minBitrateKbps{1000};
    /// Maximum bitrate for variable bitrate mode, integer kbps.
    int maxBitrateKbps{5000};
    /// Current bitrate, integer kbps.
    int bitrateKbps{3000};
    /// Bitrate mode, integer: 0 - constant bitrate, 1 - variable bitrate.
    int bitrateMode{0};
    /// FPS, float.
    float fps{30.0f};
    /// GOP size for H264 and H265 codecs, integer [1:65535].
    int gop{30};
    /// H264 profile, integer: 0 - baseline, 1 - main, 2 - high.
    int h264Profile{0};
    /// JPEG quality, integer: [1:100]% for JPEG codec.
    int jpegQuality{80};
    /// Codec type, string: "H264", "HEVC" or "JPEG".
    std::string codec{"H264"};
    /// Scaling mode, integer: 0 - fit, 1 - fill.
    int fitMode{0};
    /// Cycle time, integer microseconds. Calculated by video streamer.
    int cycleTimeUs{0};
    /// Overlay mode, boolean: false - off, true - on.
    bool overlayEnable{true};
    /// Type of the streamer, integer. Depends on implementation.
    int type{0};
    /// Custom parameter 1, float.
    float custom1{0.0f};
    /// Custom parameter 2, float.
    float custom2{0.0f};
    /// Custom parameter 3, float.
    float custom3{0.0f};
    /// Path to openssl key for RTSP, string: "" or "no" - no key.
    std::string rtspKey{"no"};
    /// Path to openssl certificate for RTSP, string: "" or "no" - no
    /// certificate.
    std::string rtspCert{"no"};
    /// Path to openssl key for WebRTC, string: "" or "no" - no key.
    std::string webRtcKey{"no"};
    /// Path to openssl certificate for WebRTC, string: "" or "no" - no
    /// certificate.
    std::string webRtcCert{"no"};
    /// Path to openssl key for HLS, string: "" or "no" - no key.
    std::string hlsKey{"no"};
    /// Path to openssl certificate for HLS, string: "" or "no" - no
    /// certificate.
    std::string hlsCert{"no"};
    /// Path to openssl key for RTMP, string: "" or "no" - no key.
    std::string rtmpKey{"no"};
    /// Path to openssl certificate for RTMP, string: "" or "no" - no
    /// certificate.
    std::string rtmpCert{"no"};
    /// RTSP encryption type, string: "" or "no", "strict", "optional".
    std::string rtspEncryption{"no"};
    /// WebRTC encryption type, string: "" or "no", "yes".
    std::string webRtcEncryption{"no"};
    /// RTMP encryption type, string: "" or "no", "strict", "optional".
    std::string rtmpEncryption{"no"};
    /// HLS encryption type, string: "" or "no", "yes".
    std::string hlsEncryption{"no"};
    /// Logging mode. Values: 0 - Disable, 1 - Only file,
    /// 2 - Only terminal, 3 - File and terminal.
    int logLevel{0};
    /// Transport / type of the direct (point-to-point) stream. String whose
    /// accepted values are implementation-defined: each concrete VStreamer
    /// decides the set and what each value means, including whether KLV
    /// metadata is carried (no separate flag). Examples: "rtp", "mpegts".
    std::string directStreamType{"rtp"};
    /// Target sending bitrate for the direct stream, integer kbps.
    int directStreamBitrateKbps{5000};
    /// Maximum UDP/RTP payload size for the direct stream, integer bytes.
    int directStreamMaxPayloadSize{1472};
    /// Pacing mode of the direct stream, integer: 0 - target bitrate,
    /// 1 - push.
    int directStreamPacingMode{0};
    /// Transport / type of the server-delivered stream (fed to the media
    /// server, which fans it out to clients). String whose accepted values
    /// are implementation-defined: each concrete VStreamer decides the set
    /// and what each value means, including whether KLV metadata is carried
    /// (no separate flag). Examples: "rtp", "mpegts". Distinct from
    /// rtspEnable (protocol on / off).
    std::string serverStreamType{"rtp"};
    /// Multicast TTL (scope) for every multicast leg, integer [0:255]:
    /// 0 - implementation default. An implementation may cap the value and
    /// must document the cap. Applies to every leg that sends to a multicast
    /// group, not only the RTSP one.
    int multicastTtl{0};
    /// Security / compliance profile. String whose accepted values are
    /// implementation-defined, in the style of directStreamType: "" or "no" -
    /// the implementation's own default. An unrecognised value must be
    /// rejected by initVStreamer(...) / setParam(...), never mapped to a
    /// default: a silent downgrade of the security posture is the failure
    /// this field exists to prevent.
    std::string securityProfile{"no"};
    /// Public (routed) address advertised to clients in SDP and ICE candidate
    /// lines instead of the locally detected one, string: "" or "no" - detect
    /// automatically. An address literal, not a hostname: it is written onto
    /// the wire verbatim. Needed behind 1:1 NAT, in containers, and on
    /// multi-homed hosts, where the detected address is unroutable for the
    /// viewer.
    std::string publicAddress{"no"};
    /// Local address every listener binds to, string: "" or "0.0.0.0" - every
    /// interface. A multi-homed host has no other way to keep a stream off an
    /// interface it must not appear on.
    std::string bindAddress{"0.0.0.0"};
    /// Lowest port of the RTP/RTCP range, integer [0:65534]: 0 - any
    /// ephemeral port. Should be even, because RTCP conventionally takes
    /// port + 1.
    int rtpPortMin{0};
    /// Highest port of the RTP/RTCP range, integer [0:65535]: 0 - any
    /// ephemeral port. A firewall is configured for a range; without one an
    /// implementation picks ephemeral ports nothing has been opened for.
    int rtpPortMax{0};
    /// WebRTC media (UDP) port, integer [0:65535]: 0 - the implementation
    /// chooses. Distinct from webRtcPort, which carries signalling only.
    int webRtcMediaPort{0};
    /// Single origin permitted to reach the HTTP-based signalling endpoints,
    /// string "scheme://host[:port]": "" or "no" - the implementation's
    /// default policy. Deliberately one origin and not a wildcard list.
    std::string corsAllowedOrigin{"no"};
    /// Maximum RTP payload size of the server-delivered stream, integer
    /// bytes. The counterpart of directStreamMaxPayloadSize for the server
    /// leg. An implementation may clamp it lower: a transform applied after
    /// packetization (SRTP appends an authentication tag) can otherwise push
    /// the datagram past the path MTU.
    int serverStreamMaxPayloadSize{1472};

    /// JSON serialization.
    JSON_READABLE(VStreamerParams, ...)

    /// Serialize parameters.
    bool serialize(uint8_t* data, int bufferSize, int& size,
                   VStreamerParamsMask* mask = nullptr);

    /// Deserialize parameters.
    bool deserialize(uint8_t* data, int dataSize);
};
```

**Parameter groups.** The parameters describe **two output legs** plus shared ones (a concrete streamer may support a subset):

- **Direct stream** (point-to-point to a single destination): `directStreamEnable`, `directStreamIp`, `directStreamPort`, `directStreamType`, `directStreamBitrateKbps`, `directStreamMaxPayloadSize`, `directStreamPacingMode`.
- **Server stream** (delivered via a media server that fans it out to clients): `serverStreamType`; plus the protocol endpoints `rtspEnable`/`rtspPort`/`rtspsPort`, `srtEnable`/`srtPort`, `hlsEnable`/`hlsPort`, `rtmpEnable`/`rtmpPort`/`rtmpsPort`, `webRtcEnable`/`webRtcPort`, `rtspMulticastIp`/`rtspMulticastPort`, `user`/`password`/`suffix`.
- **Metadata / KLV**: `metadataEnable`, `metadataPort`, `metadataSuffix`.
- **Common / encoding**: `enable`, `width`, `height`, `codec`, `fps`, `gop`, `bitrateKbps`, `minBitrateKbps`, `maxBitrateKbps`, `bitrateMode`, `h264Profile`, `jpegQuality`, `fitMode`, `overlayEnable`, `type`, `logLevel`, `custom1..3`, SSL keys/certificates & encryption.

**Table 4** - Video streamer parameters description. Some parameters may be unsupported by a particular video streamer class. The parameters correspond to the [VStreamerParam](#vstreamerparam-enum) enum.

| Parameter        | Description         |
| ---------------- | ------------------- |
| enable             | Enable/disable streamer, boolean: **false** - disable, **true** - enabled. If the video streamer disabled it should not stream video to client by any protocol. |
| width            | Video stream width, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| height           | Video stream height, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| directStreamIp | Destination IP of the direct stream (point-to-point, bypasses MediaMTX), string. Transport is set by directStreamType. Default **127.0.0.1**. |
| rtspPort        | Streamer's RTSP port, integer [0:65535]. |
| rtspsPort       | Streamer's RTSPS port, integer [0:65535]. |
| directStreamPort         | Destination port of the direct stream (point-to-point, bypasses MediaMTX), integer [0:65535]. |
| webRtcPort      | Streamer's WebRTC port, integer [0:65535]. |
| hlsPort         | Streamer's HLS port, integer [0:65535]. |
| srtPort         | Streamer's SRT port, integer [0:65535]. |
| rtmpPort        | Streamer's RTMP port, integer [0:65535]. |
| rtmpsPort       | Streamer's RTMPS port, integer [0:65535]. |
| metadataPort    | Streamer's metadata port, integer [0:65535] (for example, for [KLV](https://en.wikipedia.org/wiki/KLV) metadata streaming.). |
| rtspEnable      | RTSP protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| directStreamEnable       | Direct stream (point-to-point, bypasses MediaMTX) enable / disable, boolean: **false** - disable, **true** - enable. |
| webRtcEnable    | WebRTC protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| hlsEnable       | HLS protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| srtEnable       | SRT protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| rtmpEnable      | RTMP protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| metadataEnable  | Metadata protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| rtspMulticastIp | RTSP multicast IP, string. Usually video server accepts range of IPs (default value **224.1.0.1/16**). Some video streamer may support only single IP (example **224.1.0.1/32**). This parameters is used only with IP mask. |
| rtspMulticastPort | RTSP multicast port, integer [0:65535]. |
| user            | Streamer user (for RTSP streaming), string: **""** or **"no"** - no user. |
| password        | Streamer password (for RTSP streaming), string: **""** or **"no"** - no password. |
| suffix          | Streamer suffix for RTSP streaming (stream name), string: **""** - no suffix. |
| metadataSuffix  | Metadata suffix (stream name), string: **""** - no suffix. This parameter is used if the metadata is the separate stream in RTSP. |
| minBitrateKbps  | Minimum bitrate for variable bitrate mode, integer kbps. |
| maxBitrateKbps  | Maximum bitrate for variable bitrate mode, integer kbps. |
| bitrateKbps     | Current bitrate, integer kbps. This parameters is used for constant bitrate mode or as initial value. |
| bitrateMode     | Bitrate mode, integer: 0 - constant bitrate, 1 - variable bitrate. |
| fps             | FPS, float. The input frame FPS can be different from the FPS in the video stream. The video streamer must provide video stream FPS for clients according to this parameter's value independent from input frame FPS ([sendFrame()](#sendframe-method)). If the FPS value is **0**, the streamer must provide FPS equal to the input video frame rate. |
| gop             | Codec GOP size (key frame interval) in case of RAW input video frames. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| h264Profile     | H264 profile, integer: **0** - baseline, **1** - main, **2** - high. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| jpegQuality     | JPEG quality, integer: [1:100]% for JPEG codec. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| codec           | Codec type, string: **"H264"**, **"HEVC"** or **"JPEG"**. If the user provides already encoded frames in [sendFrame()](#sendframe-method) method. |
| fitMode         | Scaling mode, integer: 0 - fit, 1 - fill. |
| cycleTimeUs     | Cycle time, integer μsec (microseconds). Calculated by video streamer. |
| overlayEnable   | Overlay enable / disable, boolean: **false** - disable, **true** - enable. This parameter enables or disables video overlay if the video overlay module is provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| type            | Type of the streamer, integer. Depends on implementation. |
| custom1         | Custom parameter 1, float. |
| custom2         | Custom parameter 2, float. |
| custom3         | Custom parameter 3, float. |
| rtspKey         | Path to openssl key for RTSP, string: **""** or **"no"** - no key. |
| rtspCert        | Path to openssl certificate for RTSP, string: **""** or **"no"** - no certificate. |
| webRtcKey       | Path to openssl key for WebRTC, string: **""** or **"no"** - no key. |
| webRtcCert      | Path to openssl certificate for WebRTC, string: **""** or **"no"** - no certificate. |
| hlsKey          | Path to openssl key for HLS, string: **""** or **"no"** - no key. |
| hlsCert         | Path to openssl certificate for HLS, string: **""** or **"no"** - no certificate. |
| rtmpKey         | Path to openssl key for RTMP, string: **""** or **"no"** - no key. |
| rtmpCert        | Path to openssl certificate for RTMP, string: **""** or **"no"** - no certificate. |
| rtspEncryption  | RTSP encryption type, string: **""** or **"no"**, **"strict"**, **"optional"**. |
| webRtcEncryption | WebRTC encryption type, string: **""** or **"no"**, **"yes"**. |
| rtmpEncryption  | RTMP encryption type, string: **""** or **"no"**, **"strict"**, **"optional"**. |
| hlsEncryption   | HLS encryption type, string: **""** or **"no"**, **"yes"**. |
| logLevel        | Logging mode. Values: **0** - Disable, **1** - Only file, **2** - Only terminal, **3** - File and terminal. |
| directStreamType | Transport/type of the direct (point-to-point) stream, string. The accepted values are **implementation-defined**: the abstract **VStreamer** interface does not fix them — each concrete video-streamer implementation defines the value set and the meaning of each value, **including whether KLV metadata is carried** (there is no separate KLV flag). Example values: **"rtp"**, **"mpegts"** (and others, depending on implementation). Default **"rtp"**. |
| directStreamBitrateKbps | Target sending bitrate for the direct stream, integer kbps. Used as the pacer target when **directStreamPacingMode** is **0**. Default **5000**. |
| directStreamMaxPayloadSize | Maximum UDP/RTP payload size for the direct stream, integer bytes. Default **1472**. |
| directStreamPacingMode | Pacing mode of the direct stream, integer: **0** - target bitrate, **1** - push. |
| serverStreamType | Transport/type of the **server-delivered** stream — fed to the media server, which fans it out to clients. String whose accepted values are **implementation-defined**: the abstract **VStreamer** interface does not fix them — each concrete video-streamer implementation defines the value set and the meaning of each value, **including whether KLV metadata is carried** (there is no separate KLV flag). Example values: **"rtp"**, **"mpegts"** (and others, depending on implementation). Distinct from **rtspEnable** (protocol enable/disable). Default **"rtp"**. |
| multicastTtl | Multicast TTL (scope) for **every** multicast leg, integer **[0:255]**: **0** - implementation default. An implementation may cap the value and must document the cap. Default **0**. |
| securityProfile | Security/compliance profile. String whose accepted values are **implementation-defined**: **""** or **"no"** - the implementation's own default. An unrecognised value **must be rejected**, never mapped to a default. Default **"no"**. |
| publicAddress | Public (routed) address advertised to clients in SDP and ICE candidate lines instead of the locally detected one, string: **""** or **"no"** - detect automatically. An address **literal**, not a hostname. Default **"no"**. |
| bindAddress | Local address every listener binds to, string: **""** or **"0.0.0.0"** - every interface. Default **"0.0.0.0"**. |
| rtpPortMin | Lowest port of the RTP/RTCP range, integer **[0:65534]**: **0** - any ephemeral port. Should be even, because RTCP conventionally takes port+1. Default **0**. |
| rtpPortMax | Highest port of the RTP/RTCP range, integer **[0:65535]**: **0** - any ephemeral port. Default **0**. |
| webRtcMediaPort | WebRTC media (UDP) port, integer **[0:65535]**: **0** - the implementation chooses. Distinct from **webRtcPort**, which carries signalling only. Default **0**. |
| corsAllowedOrigin | Single origin permitted to reach the HTTP-based signalling endpoints, string **"scheme://host[:port]"**: **""** or **"no"** - the implementation's default policy. Default **"no"**. |
| serverStreamMaxPayloadSize | Maximum RTP payload size of the **server-delivered** stream, integer bytes — the counterpart of **directStreamMaxPayloadSize**. An implementation may clamp it lower. Default **1472**. |



## Serialize video streamer parameters

The **VStreamerParams** class provides a method **serialize(...)** to serialize video streamer parameters (fields of the [VStreamerParams](#vstreamerparams-class-description) class). Serialization of video streamer parameters is necessary when you need to send video streamer parameters via communication channels. The method provides options to exclude particular parameters from serialization. To do this, the method inserts a binary mask (10 bytes) where each bit represents a particular parameter and the **deserialize(...)** method recognizes it. The mask follows a 3-byte header (data type **0x02** plus major and minor version of the library), so the parameter payload starts at offset 13. The parameters follow in the order of the mask bits: bool as 1 byte (**0** or **1**), integers and floats as 4 bytes, strings as their characters and a terminating NUL byte. Integers and floats are stored in the **byte order of the host** that serializes them: the data is meant for hosts of the same byte order, and a consumer of the other order reads wrong values. A string which contains a NUL character is not serialized (its mask bit is not set): **deserialize(...)** would end the string at that character and read the rest of it as the next parameters. **deserialize(...)** accepts only data of its own major and minor version. Method declaration:

```cpp
bool serialize(uint8_t* data, int bufferSize, int& size,
               VStreamerParamsMask* mask = nullptr);
```

| Parameter  | Value                                                        |
| ---------- | ------------------------------------------------------------ |
| data       | Pointer to data buffer. Must not be null. The buffer must be valid for **bufferSize** bytes. |
| bufferSize | Data buffer size, **minimum 14 bytes** (13-byte header plus one field). Below that the method returns FALSE, sets **size** to 0 and doesn't change the buffer. Above it, a buffer too small for every selected parameter is filled with as many as fit, and the ones that did not fit are simply absent from the mask. |
| size       | Size of serialized data. 0 if the method returns FALSE.      |
| mask       | Parameters mask - pointer to **VStreamerParamsMask** structure. **VStreamerParamsMask** (declared in VStreamer.h file) determines flags for each field (parameter) declared in **VStreamerParams** class. If the mask is **nullptr** all parameters are serialized. To exclude a particular parameter from serialization, set the corresponding flag of the mask to **false**. |

**Returns:** TRUE if parameters are serialized or FALSE if **data** is null or **bufferSize** is less than 14 bytes.

**VStreamerParamsMask** structure declaration:

```cpp
struct VStreamerParamsMask
{
    /// Serialize enable field.
    bool enable{true};
    /// Serialize width field.
    bool width{true};
    /// Serialize height field.
    bool height{true};
    /// Serialize directStreamIp field.
    bool directStreamIp{true};
    /// Serialize rtspPort field.
    bool rtspPort{true};
    /// Serialize rtspsPort field.
    bool rtspsPort{true};
    /// Serialize directStreamPort field.
    bool directStreamPort{true};
    /// Serialize webRtcPort field.
    bool webRtcPort{true};
    /// Serialize hlsPort field.
    bool hlsPort{true};
    /// Serialize srtPort field.
    bool srtPort{true};
    /// Serialize rtmpPort field.
    bool rtmpPort{true};
    /// Serialize rtmpsPort field.
    bool rtmpsPort{true};
    /// Serialize metadataPort field.
    bool metadataPort{true};
    /// Serialize rtspEnable field.
    bool rtspEnable{true};
    /// Serialize directStreamEnable field.
    bool directStreamEnable{true};
    /// Serialize webRtcEnable field.
    bool webRtcEnable{true};
    /// Serialize hlsEnable field.
    bool hlsEnable{true};
    /// Serialize srtEnable field.
    bool srtEnable{true};
    /// Serialize rtmpEnable field.
    bool rtmpEnable{true};
    /// Serialize metadataEnable field.
    bool metadataEnable{true};
    /// Serialize rtspMulticastIp field.
    bool rtspMulticastIp{true};
    /// Serialize rtspMulticastPort field.
    bool rtspMulticastPort{true};
    /// Serialize user field.
    bool user{true};
    /// Serialize password field.
    bool password{true};
    /// Serialize suffix field.
    bool suffix{true};
    /// Serialize metadataSuffix field.
    bool metadataSuffix{true};
    /// Serialize minBitrateKbps field.
    bool minBitrateKbps{true};
    /// Serialize maxBitrateKbps field.
    bool maxBitrateKbps{true};
    /// Serialize bitrateKbps field.
    bool bitrateKbps{true};
    /// Serialize bitrateMode field.
    bool bitrateMode{true};
    /// Serialize fps field.
    bool fps{true};
    /// Serialize gop field.
    bool gop{true};
    /// Serialize h264Profile field.
    bool h264Profile{true};
    /// Serialize jpegQuality field.
    bool jpegQuality{true};
    /// Serialize codec field.
    bool codec{true};
    /// Serialize fitMode field.
    bool fitMode{true};
    /// Serialize cycleTimeUs field.
    bool cycleTimeUs{true};
    /// Serialize overlayEnable field.
    bool overlayEnable{true};
    /// Serialize type field.
    bool type{true};
    /// Serialize custom1 field.
    bool custom1{true};
    /// Serialize custom2 field.
    bool custom2{true};
    /// Serialize custom3 field.
    bool custom3{true};
    /// Serialize rtspKey field.
    bool rtspKey{true};
    /// Serialize rtspCert field.
    bool rtspCert{true};
    /// Serialize webRtcKey field.
    bool webRtcKey{true};
    /// Serialize webRtcCert field.
    bool webRtcCert{true};
    /// Serialize hlsKey field.
    bool hlsKey{true};
    /// Serialize hlsCert field.
    bool hlsCert{true};
    /// Serialize rtmpKey field.
    bool rtmpKey{true};
    /// Serialize rtmpCert field.
    bool rtmpCert{true};
    /// Serialize rtspEncryption field.
    bool rtspEncryption{true};
    /// Serialize webRtcEncryption field.
    bool webRtcEncryption{true};
    /// Serialize rtmpEncryption field.
    bool rtmpEncryption{true};
    /// Serialize hlsEncryption field.
    bool hlsEncryption{true};
    /// Serialize logLevel field.
    bool logLevel{true};
    /// Serialize directStreamType field.
    bool directStreamType{true};
    /// Serialize directStreamBitrateKbps field.
    bool directStreamBitrateKbps{true};
    /// Serialize directStreamMaxPayloadSize field.
    bool directStreamMaxPayloadSize{true};
    /// Serialize directStreamPacingMode field.
    bool directStreamPacingMode{true};
    /// Serialize serverStreamType field.
    bool serverStreamType{true};
    /// Serialize multicastTtl field.
    bool multicastTtl{true};
    /// Serialize securityProfile field.
    bool securityProfile{true};
    /// Serialize publicAddress field.
    bool publicAddress{true};
    /// Serialize bindAddress field.
    bool bindAddress{true};
    /// Serialize rtpPortMin field.
    bool rtpPortMin{true};
    /// Serialize rtpPortMax field.
    bool rtpPortMax{true};
    /// Serialize webRtcMediaPort field.
    bool webRtcMediaPort{true};
    /// Serialize corsAllowedOrigin field.
    bool corsAllowedOrigin{true};
    /// Serialize serverStreamMaxPayloadSize field.
    bool serverStreamMaxPayloadSize{true};
};
```

Example without parameters mask:

```cpp
// Prepare params.
rapidpixel::VStreamerParams in;
in.directStreamIp = "alsfghljb";
in.directStreamPort = 0;

// Serialize parameters.
uint8_t data[1024];
int size = 0;
if (!in.serialize(data, sizeof(data), size))
{
    std::cout << "Parameters not serialized" << std::endl;
}
std::cout << "Serialized data size: " << size << " bytes" << std::endl;
```

Example with parameters mask:

```cpp
// Prepare parameters.
rapidpixel::VStreamerParams in;
in.directStreamIp = "alsfghljb";
in.directStreamPort = 0;

// Prepare parameters mask.
rapidpixel::VStreamerParamsMask mask;
mask.directStreamPort = false; // Exclude directStreamPort. Others by default.

// Serialize parameters.
uint8_t data[1024];
int size = 0;
if (!in.serialize(data, sizeof(data), size, &mask))
{
    std::cout << "Parameters not serialized" << std::endl;
}
std::cout << "Serialized data size: " << size << " bytes" << std::endl;
```



## Deserialize video streamer parameters

The **VStreamerParams** class provides a method **deserialize(...)** to deserialize video streamer parameters (fields of the [VStreamerParams](#vstreamerparams-class-description) class). Deserialization of video streamer parameters is necessary when you need to receive video streamer parameters via communication channels. The method automatically recognizes which parameters were serialized by the **serialize(...)** method. Method declaration:

```cpp
bool deserialize(uint8_t* data, int dataSize);
```

| Parameter | Value         |
| --------- | ------------- |
| data      | Pointer to serialized data buffer. Must not be null. The buffer must be valid for **dataSize** bytes. |
| dataSize  | Size of data, minimum 13 bytes (header). |

**deserialize(...)** replaces the WHOLE object: every parameter whose mask bit
is clear is reset to a zero value (**0**, **false** or an empty string) in the
destination, not left at whatever it held before. It is not a partial update,
so deserialize into a fresh **VStreamerParams** unless you intend the excluded
fields to be cleared. The method also refuses a buffer shorter than 13 bytes, a
foreign header byte, any message whose major **or minor** version differs
from the library's own, and a mask with bits of unknown parameters. Bytes after
the last parameter are ignored. A message is applied as a whole or not at all:
when the method returns FALSE (a truncated field, a string without its
terminator) the object is exactly as it was before the call. The values of
the parameters are not checked: the video streamer implementation must check
them before use.

**Returns:** TRUE if data is deserialized or FALSE if not.

Example:

```cpp
// Serialize parameters.
rapidpixel::VStreamerParams in;
uint8_t data[1024];
int size = 0;
if (!in.serialize(data, sizeof(data), size))
{
    std::cout << "Parameters not serialized" << std::endl;
}
std::cout << "Serialized data size: " << size << " bytes" << std::endl;

// Deserialize parameters.
rapidpixel::VStreamerParams out;
if (!out.deserialize(data, size))
{
    std::cout << "Can't deserialize data" << std::endl;
}
```



## Read parameters from JSON file and write to JSON file

The **VStreamer** library depends on the **ConfigReader** library which provides methods to read parameters from JSON files and to write parameters to JSON files. The **get(...)** method of **ConfigReader** returns FALSE if a parameter is absent in the JSON or has a wrong type (for example, a string instead of a number, or a number out of the range of the parameter type), and doesn't change the **VStreamerParams** object in this case. A number with a fractional part is truncated for an integer parameter. The values are not checked against the ranges of the parameters. Example of writing and reading parameters to JSON file:

```cpp
// Write params to file.
rapidpixel::VStreamerParams in;
rapidpixel::ConfigReader inConfig;
if (!inConfig.set(in, "vStreamerParams") ||
    !inConfig.writeToFile("TestVStreamerParams.json"))
{
    std::cout << "Can't write config file" << std::endl;
}

// Read params from file.
rapidpixel::ConfigReader outConfig;
rapidpixel::VStreamerParams out;
if (!outConfig.readFromFile("TestVStreamerParams.json") ||
    !outConfig.get(out, "vStreamerParams"))
{
    std::cout << "Can't read params from config file" << std::endl;
}
```

**TestVStreamerParams.json** will look like (default values):

```json
{
    "vStreamerParams": {
        "enable": true,
        "width": 1280,
        "height": 720,
        "directStreamIp": "127.0.0.1",
        "rtspPort": 8554,
        "rtspsPort": 8555,
        "directStreamPort": 5004,
        "webRtcPort": 7000,
        "hlsPort": 8080,
        "srtPort": 6000,
        "rtmpPort": 1935,
        "rtmpsPort": 1936,
        "metadataPort": 9000,
        "rtspEnable": true,
        "directStreamEnable": true,
        "webRtcEnable": true,
        "hlsEnable": true,
        "srtEnable": true,
        "rtmpEnable": true,
        "metadataEnable": false,
        "rtspMulticastIp": "224.1.0.1/16",
        "rtspMulticastPort": 18000,
        "user": "no",
        "password": "no",
        "suffix": "live",
        "metadataSuffix": "metadata",
        "minBitrateKbps": 1000,
        "maxBitrateKbps": 5000,
        "bitrateKbps": 3000,
        "bitrateMode": 0,
        "fps": 30.0,
        "gop": 30,
        "h264Profile": 0,
        "jpegQuality": 80,
        "codec": "H264",
        "fitMode": 0,
        "cycleTimeUs": 0,
        "overlayEnable": true,
        "type": 0,
        "custom1": 0.0,
        "custom2": 0.0,
        "custom3": 0.0,
        "rtspKey": "no",
        "rtspCert": "no",
        "webRtcKey": "no",
        "webRtcCert": "no",
        "hlsKey": "no",
        "hlsCert": "no",
        "rtmpKey": "no",
        "rtmpCert": "no",
        "rtspEncryption": "no",
        "webRtcEncryption": "no",
        "rtmpEncryption": "no",
        "hlsEncryption": "no",
        "logLevel": 0,
        "directStreamType": "rtp",
        "directStreamBitrateKbps": 5000,
        "directStreamMaxPayloadSize": 1472,
        "directStreamPacingMode": 0,
        "serverStreamType": "rtp",
        "multicastTtl": 0,
        "securityProfile": "no",
        "publicAddress": "no",
        "bindAddress": "0.0.0.0",
        "rtpPortMin": 0,
        "rtpPortMax": 0,
        "webRtcMediaPort": 0,
        "corsAllowedOrigin": "no",
        "serverStreamMaxPayloadSize": 1472
    }
}
```



# Build and connect to your project



## Build stand alone

The repository doesn't contain sub-repositories. The libraries **VStreamer** depends on (**Frame**, **ConfigReader**, **VOverlay** and **VCodec**) must be cloned into the same folder as **VStreamer**. The folder structure must be:

```bash
<work folder>
    VStreamer
    Frame
    ConfigReader
    VOverlay
    VCodec
```

Typical commands to build the library, the test application and the example (use the URLs of the repositories provided to you):

```bash
git clone <VStreamer repository URL>
git clone <Frame repository URL>
git clone <ConfigReader repository URL>
git clone <VOverlay repository URL>
git clone <VCodec repository URL>
cd VStreamer
mkdir build
cd build
cmake ..
make
```

On Windows use `cmake --build . --config Release` instead of `make`. If **VStreamer** is the top-level CMake project, the main CMakeLists.txt file adds the folders ../Frame, ../ConfigReader, ../VOverlay and ../VCodec (in this order) before the library itself. If a folder doesn't exist CMake stops with an error.



## CMake options

**Table 5** - CMake options of the repository. In the options below ${PARENT} is the prefix defined by the top-level project (empty if **VStreamer** is the top-level project).

| Option                              | Default                                           | Description                                                  |
| ----------------------------------- | ------------------------------------------------- | ------------------------------------------------------------ |
| ${PARENT}_VSTREAMER                 | ON                                                | Build the library.                                           |
| ${PARENT}_VSTREAMER_TEST            | ON (stand alone), OFF (included in other project) | Build the test application.                                  |
| ${PARENT}_VSTREAMER_EXAMPLE         | ON (stand alone), OFF (included in other project) | Build the example of custom video streamer.                  |
| ${PARENT}_SUBMODULE_CACHE_OVERWRITE | ON                                                | Forced rewriting of the options above in the CMake cache. The top-level project sets it to OFF when it includes **VStreamer** as a sub-repository. |
| CMAKE_BUILD_TYPE                    | Release (if not specified)                        | Build type.                                                  |



## Connect to your project

If you want to connect **VStreamer** library to your CMake project as source code you can make follow. For example, if your repository has structure:

```bash
CMakeLists.txt
src
    CMakeLists.txt
    yourLib.h
    yourLib.cpp
```

Create folder **3rdparty** in your repository and clone (or copy) the repositories of **Frame**, **ConfigReader**, **VOverlay**, **VCodec** and **VStreamer** there. Structure of your repository with the libraries:

```bash
CMakeLists.txt
src
    CMakeLists.txt
    yourLib.h
    yourLib.cpp
3rdparty
    Frame
    ConfigReader
    VOverlay
    VCodec
    VStreamer
```

When **VStreamer** is included in another project it doesn't add the libraries it depends on: your project must add **Frame**, **ConfigReader**, **VOverlay** and **VCodec** by itself. If they are not added the compiler stops with the error `ConfigReader.h: No such file or directory`. Create CMakeLists.txt file in **3rdparty** folder. CMakeLists.txt should contain:

```cmake
cmake_minimum_required(VERSION 3.13)

################################################################################
## 3RD-PARTY
## dependencies for the project
################################################################################
project(3rdparty LANGUAGES CXX)

################################################################################
## SETTINGS
## basic 3rd-party settings before use
################################################################################
# To inherit the top-level architecture when the project is used as a submodule.
SET(PARENT ${PARENT}_YOUR_PROJECT_3RDPARTY)
# Disable self-overwriting of parameters inside included subdirectories.
SET(${PARENT}_SUBMODULE_CACHE_OVERWRITE OFF CACHE BOOL "" FORCE)

################################################################################
## CONFIGURATION
## 3rd-party submodules configuration
################################################################################
SET(${PARENT}_SUBMODULE_FRAME                           ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_FRAME)
    SET(${PARENT}_FRAME                                 ON  CACHE BOOL "" FORCE)
    SET(${PARENT}_FRAME_TEST                            OFF CACHE BOOL "" FORCE)
endif()

SET(${PARENT}_SUBMODULE_CONFIG_READER                   ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_CONFIG_READER)
    SET(${PARENT}_CONFIG_READER                         ON  CACHE BOOL "" FORCE)
    SET(${PARENT}_CONFIG_READER_EXAMPLES                OFF CACHE BOOL "" FORCE)
    SET(${PARENT}_CONFIG_READER_TESTS                   OFF CACHE BOOL "" FORCE)
endif()

SET(${PARENT}_SUBMODULE_VOVERLAY                        ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_VOVERLAY)
    SET(${PARENT}_VOVERLAY                              ON  CACHE BOOL "" FORCE)
endif()

SET(${PARENT}_SUBMODULE_VCODEC                          ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_VCODEC)
    SET(${PARENT}_VCODEC                                ON  CACHE BOOL "" FORCE)
endif()

SET(${PARENT}_SUBMODULE_VSTREAMER                       ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_VSTREAMER)
    SET(${PARENT}_VSTREAMER                             ON  CACHE BOOL "" FORCE)
    SET(${PARENT}_VSTREAMER_TEST                        OFF CACHE BOOL "" FORCE)
    SET(${PARENT}_VSTREAMER_EXAMPLE                     OFF CACHE BOOL "" FORCE)
endif()

################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
################################################################################
if (${PARENT}_SUBMODULE_FRAME)
    add_subdirectory(Frame)
endif()

if (${PARENT}_SUBMODULE_CONFIG_READER)
    add_subdirectory(ConfigReader)
endif()

if (${PARENT}_SUBMODULE_VOVERLAY)
    add_subdirectory(VOverlay)
endif()

if (${PARENT}_SUBMODULE_VCODEC)
    add_subdirectory(VCodec)
endif()

if (${PARENT}_SUBMODULE_VSTREAMER)
    add_subdirectory(VStreamer)
endif()
```

File **3rdparty/CMakeLists.txt** adds folders **Frame**, **ConfigReader**, **VOverlay**, **VCodec** and **VStreamer** (in this order: **VStreamer** is added after the libraries it depends on) to your project and excludes test applications and examples from compiling (by default test application and example excluded from compiling if **VStreamer** included as sub-repository). Structure of your repository will be:

```bash
CMakeLists.txt
src
    CMakeLists.txt
    yourLib.h
    yourLib.cpp
3rdparty
    CMakeLists.txt
    Frame
    ConfigReader
    VOverlay
    VCodec
    VStreamer
```

Next you need include folder 3rdparty in main **CMakeLists.txt** file of your repository. Add string at the end of your main **CMakeLists.txt**:

```cmake
add_subdirectory(3rdparty)
```

Next you have to include VStreamer library in your **src/CMakeLists.txt** file:

```cmake
target_link_libraries(${PROJECT_NAME} VStreamer)
```

Done!



# Portability

Serialized parameters (**VStreamerParams::serialize(...)** method) and encoded commands (**VStreamer::encodeCommand(...)** and **VStreamer::encodeSetParamCommand(...)** methods) store int and float values as raw 4 bytes in the byte order of the host and bool values as 1 byte. The library checks at compile time that int and float have 4 bytes and bool has 1 byte. Data must be exchanged between hosts with the same byte order. The library was built and tested only on little-endian CPUs (x86-64 and AArch64).

The library doesn't use SIMD instructions or CPU specific code. The library, the example and the test application were built without warnings with GCC 11 and GCC 12 (x86-64) and with the GCC 11 cross compiler for AArch64, and the test application was run on x86-64 and under emulation for AArch64.



# How to make custom implementation

The **VStreamer** class provides only an interface, data structures, and methods for encoding and decoding commands and params. To create your own implementation of the video streamer, you must include the VStreamer repository in your project (see [Build and connect to your project](#build-and-connect-to-your-project) section). The catalogue **example** (see [Library files](#library-files) section) includes an example of the design of the custom video streamer. You must implement all the methods of the VStreamer interface class. The methods **setParam(...)**, **getParams(...)** and **executeCommand(...)** must be thread-safe, and every value which comes from outside (**initVStreamer(...)**, **setParam(...)**, decoded commands) must be checked before it is used. The example keeps the parameters under a mutex, rejects a value which is not valid (NaN, infinity, a value out of the range of the parameter, an unknown string value, text with control characters) and doesn't change the parameter in this case. Custom video streamer class declaration:

```cpp
namespace rapidpixel
{
/// Custom video streamer class.
class CustomVStreamer : public VStreamer
{
public:

    /// Class constructor.
    CustomVStreamer();

    /// Class destructor.
    ~CustomVStreamer() override;

    /// Copy and move are deleted: the object owns a mutex.
    CustomVStreamer(const CustomVStreamer&) = delete;
    CustomVStreamer(CustomVStreamer&&) = delete;
    CustomVStreamer& operator=(const CustomVStreamer&) = delete;
    CustomVStreamer& operator=(CustomVStreamer&&) = delete;

    /// Get string of current library version.
    static std::string getVersion();

    /// Initialize video streamer. All parameters are checked first.
    bool initVStreamer(VStreamerParams& params,
                       VCodec* codec = nullptr,
                       VOverlay* overlay = nullptr) override;

    /// Get initialization status.
    bool isVStreamerInit() override;

    /// Close video streamer.
    void closeVStreamer() override;

    /// Send frame to video streamer.
    bool sendFrame(Frame& frame, uint8_t* userData = nullptr,
                   int userDataSize = 0) override;

    /// Set video streamer parameter with a numeric value.
    bool setParam(VStreamerParam id, float value) override;

    /// Set video streamer parameter with a string value.
    bool setParam(VStreamerParam id, std::string value) override;

    /// Get video streamer parameters structure.
    void getParams(VStreamerParams& params) override;

    /// Execute command.
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
```