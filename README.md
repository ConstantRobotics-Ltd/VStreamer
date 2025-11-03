![vstreamer_web_logo](./static/vstreamer_web_logo.png)



# **VStreamer interface C++ library**

**v2.0.0**



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
- [How to make custom implementation](#how-to-make-custom-implementation)



# Overview

The **VStreamer** C++ library provides a standard interface and defines data structures and rules for different video stream classes. The **VStreamer** interface class does not perform any operations by itself; it only provides an interface and methods to encode/decode commands and serialize/deserialize parameters. The **VStreamer** class also provides data structures for video stream parameters. Different video stream classes inherit the interface from the **VStreamer** C++ class. The **VStreamer.h** file contains a list of data structures ([VStreamerCommand](#vstreamercommand-enum) enum, [VStreamerParam](#vstreamerparam-enum) enum and [VStreamerParams](#vstreamerparams-class-description) class). The [VStreamerParams](#vstreamerparams-class-description) class contains all streamer parameters and includes methods to serialize and deserialize parameters. The [VStreamerCommand](#vstreamercommand-enum) enum contains IDs of commands supported by the **VStreamer** class. The [VStreamerParam](#vstreamerparam-enum) enum contains IDs of parameters supported by the **VStreamer** class. All video streamers should include parameters and commands listed in the **VStreamer.h** file. The **VStreamer** interface class depends on: [ConfigReader](https://rapidpixel.constantrobotics.com/docs/Service/ConfigReader.html) library (provides methods to read/write JSON config files, source code included, Apache 2.0 license), [VCodec](https://rapidpixel.constantrobotics.com/docs/VideoCoding/VCodec.html) library (provides interface for video codecs, source code included, Apache 2.0 license), [VOverlay](https://rapidpixel.constantrobotics.com/docs/Service/VOverlay.html) library (provides interface for overlay engines, source code included, Apache 2.0 license). The library is licensed under the **Apache 2.0** license.



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



# Library files

The library is supplied as source code only. The user receives the files as a CMake project (repository). The repository structure is shown below:

```xml
CMakeLists.txt ------------------- Main CMake file of the library.
3rdparty ------------------------- Folder with third-party libraries.
    CMakeLists.txt --------------- CMake file to include third-party libraries.
    ConfigReader ----------------- Folder with ConfigReader library source code.
    VCodec ----------------------- Folder with VCodec library source code.
    VOverlay --------------------- Folder with VOverlay library source code.
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
namespace cr
{
namespace video
{
class VStreamer
{
public:

    /// Class destructor.
    virtual ~VStreamer();

    /// Get string of current library version.
    static std::string getVersion();

    /// Initialize video streamer.
    virtual bool initVStreamer(VStreamerParams &params,
                               VCodec *codec = nullptr,
                               VOverlay *overlay = nullptr) = 0;

    /// Get initialization status.
    virtual bool isVStreamerInit() = 0;

    /// Close video streamer.
    virtual void closeVStreamer() = 0;

    /// Send frame to video streamer.
    virtual bool sendFrame(Frame& frame, uint8_t* userData = nullptr, int userDataSize = 0) = 0;

    /// Set video streamer parameter.
    virtual bool setParam(VStreamerParam id, float value) = 0;

    /// Set video streamer parameter.
    virtual bool setParam(VStreamerParam id, std::string value) = 0;

    /// Get video streamer params structure.
    virtual void getParams(VStreamerParams& params) = 0;

    /// Execute command.
    virtual bool executeCommand(VStreamerCommand id) = 0;

    /// Decode and execute command.
    virtual bool decodeAndExecuteCommand(uint8_t* data, int size);

    /// Encode set parameter command.
    static void encodeSetParamCommand(uint8_t *data, int &size, 
                                        VStreamerParam id, float value);

    /// Encode set parameter command.
    static void encodeSetParamCommand(uint8_t* data, int& size, 
                                        VStreamerParam id, std::string value);

    /// Encode command.
    static void encodeCommand(uint8_t* data, int& size, VStreamerCommand id);

    /// Decode command.
    static int decodeCommand(uint8_t* data,
                             int size,
                             VStreamerParam& paramId,
                             VStreamerCommand& commandId,
                             float& value,
                             std::string& strValue);

};
}
}
```



## getVersion method

The **getVersion()** method returns a string of the current version of the **VStreamer** class. A particular video streamer class can have its own **getVersion()** method. Method declaration:

```cpp
static std::string getVersion();
```

The method can be used without a **VStreamer** class instance:

```cpp
std::cout << "VStreamer class version: " << VStreamer::getVersion();
```

Console output:

```bash
VStreamer class version: 2.0.0
```



## initVStreamer method

The **initVStreamer(...)** method initializes the video streamer with a structure of parameters. Method declaration:

```cpp
virtual bool initVStreamer(VStreamerParams &params,
                           VCodec *codec = nullptr,
                           VOverlay *overlay = nullptr) = 0;
```

| Parameter | Value                                                        |
| --------- | ------------------------------------------------------------ |
| params    | [VStreamerParams](#vstreamerparams-class-description) class object. The video streamer should set parameters according to the parameters class. A particular video streamer might not support all parameters listed in the [VStreamerParams](#vstreamerparams-class-description) class. |
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
virtual bool sendFrame(Frame& frame, uint8_t* userData = nullptr, int userDataSize = 0) = 0;
```

| Parameter | Value                                                        |
| --------- | ------------------------------------------------------------ |
| frame     | [Frame](https://rapidpixel.constantrobotics.com/docs/Service/Frame.html) class object. Particular streamers can support RAW video frames or(and) compressed video frames. |
| userData  | Pointer to user data (telemetry). Some streamers may support telemetry streaming (for example, [KLV](https://en.wikipedia.org/wiki/KLV) metadata) synchronized with video streams (for example, by timestamp). If the parameter is **nullptr**, the streamer will not send any telemetry data. |
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
| value     | Value of parameter. It can be either string or float type. It depends on parameter. |

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
| data      | Pointer to input command.                                    |
| size      | Size of command.                                             |

**Returns:** TRUE if command decoded (SET_PARAM or COMMAND) and executed (action command or set param command).



## encodeSetParamCommand method

The **encodeSetParamCommand(...)** static method encodes a command to change any parameter in a remote video streamer. To control a video streamer remotely, the developer has to design their own protocol and according to it encode the command and deliver it over the communication channel. To simplify this, the **VStreamer** class contains static methods for encoding the control command. The **VStreamer** class provides two types of commands: a parameter change command (SET_PARAM) and an action command (COMMAND). **encodeSetParamCommand(...)** is designed to encode the SET_PARAM command. The method has two overloads: one for numeric parameters and one for string parameters. Method declaration:

```cpp
static void encodeSetParamCommand(uint8_t *data, int &size,  VStreamerParam id, float value);

static void encodeSetParamCommand(uint8_t* data, int& size, VStreamerParam id, std::string value);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to data buffer for encoded command. Must have size >= 11 or in case of string parameters it must be enough to keep string + 12 bytes. |
| size      | Size of encoded data. Will be minimum 11 bytes.              |
| id        | Parameter ID according to [VStreamerParam](#vstreamerparam-enum) enum. |
| value     | Numeric video streamer parameter value. Only for non-string parameters. For string parameters (see [VStreamerParam](#vstreamerparam-enum) enum) this parameter may have any value. |
| value     | String parameter value (see [VStreamerParam](#vstreamerparam-enum) enum). |

**encodeSetParamCommand(...)** is a static method and is used without a **VStreamer** class instance. This method is used on the client side (control system). Example of command encoding:

```cpp
// Buffer for encoded data.
uint8_t data[11];
// Size of encoded data.
int size = 0;
// Random parameter value.
float outValue = (float)(rand() % 20);
// Encode command.
VStreamer::encodeSetParamCommand(data, size, VStreamerParam::CUSTOM1, outValue);
```



## encodeCommand method

The **encodeCommand(...)** static method encodes a command for a remote video streamer. To control a video streamer remotely, the developer has to design their own protocol and according to it encode the command and deliver it over the communication channel. To simplify this, the **VStreamer** class contains static methods for encoding the control command. The **VStreamer** class provides two types of commands: a parameter change command (SET_PARAM) and an action command (COMMAND). **encodeCommand(...)** is designed to encode the COMMAND (action command). Method declaration:

```cpp
static void encodeCommand(uint8_t* data, int& size, VStreamerCommand id);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to data buffer for output command. Must have size >= 7 bytes. |
| size      | Size of encoded data. Will be 7 bytes.                       |
| id        | Command ID according to [VStreamerCommand](#vstreamercommand-enum) enum. |

**encodeCommand(...)** is a static method and is used without a **VStreamer** class instance. This method is used on the client side (control system). Example of command encoding:

```cpp
// Buffer for encoded data.
uint8_t data[11];
// Size of encoded data.
int size = 0;
// Encode command.
VStreamer::encodeCommand(data, size, VStreamerCommand::RESTART);
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
| data      | Pointer to input command.                                    |
| size      | Size of command. Should be minimum 11 bytes for SET_PARAM and 7 bytes for COMMAND. |
| paramId   | Parameter ID according to [VStreamerParam](#vstreamerparam-enum) enum. After decoding a SET_PARAM command the method will return the parameter ID. |
| commandId | Command ID according to [VStreamerCommand](#vstreamercommand-enum) enum. After decoding a COMMAND the method will return the command ID. |
| value    | Numeric video streamer parameter value. Only for non-string parameters. For string parameters (see [VStreamerParam](#vstreamerparam-enum) enum) this parameter may have any value. |
| strValue    | String parameter value (see [VStreamerParam](#vstreamerparam-enum) enum). |

**Returns:** **0** - in case of decoding COMMAND, **1** - in case of decoding SET_PARAM command or **-1** in case of errors.



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
    /// Generate key frame command.
    GENERATE_KEYFRAME
};
```

**Table 4** - Video stream action commands description. Some commands may be unsupported by a particular video stream class.

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
    /// Streamer IP, string.
    IP,
    /// RTSP port, integer [0:65535].
    RTSP_PORT,
    /// RTSPS port, integer [0:65535].
    RTSPS_PORT,
    /// RTP port, integer [0:65535].
    RTP_PORT,
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
    /// RTP protocol enable / disable, integer: 0 - disable, 1 - enable.
    RTP_MODE,
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
    /// Streamer suffix for RTSP streaming (stream name), string: "" - no suffix.
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
    /// Cycle time, integer μsec (microseconds). Calculated by video streamer.
    CYCLE_TIME_USEC,
    /// Overlay enable / disable, integer: 0 - disable, 1 - enable.
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
    LOG_LEVEL
};
```

**Table 5** - Video streamer parameters description. Some parameters may be unsupported by a particular video streamer class.

| Parameter        | Description         |
| ---------------- | ------------------- |
| MODE             | Enable/disable streamer, integer: **0** - disable, **1** - enabled. If the video streamer is disabled it should not stream video to clients by any protocol. |
| WIDTH            | Video stream width, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| HEIGHT           | Video stream height, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| IP               | Streamer IP, string. It can be, for example, RTSP server IP or destination IP. Default value is **0.0.0.0** which is a universal IP to receive client connections from any IP.  |
| RTSP_PORT        | Streamer's RTSP port, integer [0:65535]. |
| RTSPS_PORT       | Streamer's RTSPS port, integer [0:65535]. |
| RTP_PORT         | Streamer's RTP port, integer [0:65535]. Usually is used for RTP stream only or to determine port to stream video from streamer to video proxy. |
| WEBRTC_PORT      | Streamer's WebRTC port, integer [0:65535]. |
| HLS_PORT         | Streamer's HLS port, integer [0:65535]. |
| SRT_PORT         | Streamer's SRT port, integer [0:65535]. |
| RTMP_PORT        | Streamer's RTMP port, integer [0:65535]. |
| RTMPS_PORT       | Streamer's RTMPS port, integer [0:65535]. |
| METADATA_PORT    | Streamer's metadata port, integer [0:65535] (for example, for [KLV](https://en.wikipedia.org/wiki/KLV) metadata streaming.). |
| RTSP_MODE        | RTSP protocol enable / disable, integer: **0** - disable, **1** - enable. |
| RTP_MODE         | RTP protocol enable / disable, integer: **0** - disable, **1** - enable. |
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



# VStreamerParams class description



## VStreamerParams class declaration

The **VStreamerParams** class is used for video stream initialization (the [initVStreamer(...)](#initvstreamer-method) method) or to get all actual parameters (the [getParams(...)](#getparams-method) method). Also, **VStreamerParams** provides a structure to write/read parameters from JSON files (**JSON_READABLE** macro, see [ConfigReader](https://rapidpixel.constantrobotics.com/docs/Service/ConfigReader.html) class description) and provides methods to serialize and deserialize parameters. Class declaration:

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
    /// Streamer IP, string.
    std::string ip{"0.0.0.0"};
    /// RTSP port, integer [0:65535].
    int rtspPort{8554};
    /// RTSPS port, integer [0:65535].
    int rtspsPort{8555};
    /// RTP port, integer [0:65535].
    int rtpPort{5004};
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
    /// RTSP protocol enable / disable, boolean: false - disable, true - enable.
    bool rtspEnable{true};
    /// RTP protocol enable / disable, boolean: false - disable, true - enable.
    bool rtpEnable{true};
    /// WebRTC protocol enable / disable, boolean: false - disable, true - enable.
    bool webRtcEnable{true};
    /// HLS protocol enable / disable, boolean: false - disable, true - enable.
    bool hlsEnable{true};
    /// SRT protocol enable / disable, boolean: false - disable, true - enable.
    bool srtEnable{true};
    /// RTMP protocol enable / disable, boolean: false - disable, true - enable.
    bool rtmpEnable{true};
    /// Metadata protocol enable / disable, boolean: false - disable, true - enable.
    bool metadataEnable{false};
    /// RTSP multicast IP, string.
    std::string rtspMulticastIp{"224.1.0.1/16"};
    /// RTSP multicast port, integer [0:65535].
    int rtspMulticastPort{18000};
    /// Streamer user (for RTSP streaming), string: "" - no user.
    std::string user{""};
    /// Streamer password (for RTSP streaming), string: "" - no password.
    std::string password{""};
    /// Streamer suffix for RTSP streaming (stream name), string: "" - no suffix.
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
    /// Cycle time, integer μsec (microseconds). Calculated by video streamer.
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
    /// Path to openssl certificate for RTSP, string: "" or "no" - no certificate.
    std::string rtspCert{"no"};
    /// Path to openssl key for WebRTC, string: "" or "no" - no key.
    std::string webRtcKey{"no"};
    /// Path to openssl certificate for WebRTC, string: "" or "no" - no certificate.
    std::string webRtcCert{"no"};
    /// Path to openssl key for HLS, string: "" or "no" - no key.
    std::string hlsKey{"no"};
    /// Path to openssl certificate for HLS, string: "" or "no" - no certificate.
    std::string hlsCert{"no"};
    /// Path to openssl key for RTMP, string: "" or "no" - no key.
    std::string rtmpKey{"no"};
    /// Path to openssl certificate for RTMP, string: "" or "no" - no certificate.
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

    JSON_READABLE(VStreamerParams, enable, width, height, ip, rtspPort, rtspsPort, rtpPort,
                  webRtcPort, hlsPort, srtPort, rtmpPort, rtmpsPort, metadataPort,
                  rtspEnable, rtpEnable, webRtcEnable, hlsEnable, srtEnable,
                  rtmpEnable, metadataEnable, rtspMulticastIp, rtspMulticastPort,
                  user, password, suffix, metadataSuffix, minBitrateKbps,
                  maxBitrateKbps, bitrateKbps, bitrateMode, fps, gop, h264Profile,
                  jpegQuality, codec, fitMode, overlayEnable, type, custom1,
                  custom2, custom3, rtspKey, rtspCert, webRtcKey, webRtcCert,
                  hlsKey, hlsCert, rtmpKey, rtmpCert, rtspEncryption,
                  webRtcEncryption, rtmpEncryption, hlsEncryption, logLevel)

    /// Serialize parameters.
    bool serialize(uint8_t* data, int bufferSize, int& size,
                   VStreamerParamsMask* mask = nullptr);

    /// Deserialize parameters.
    bool deserialize(uint8_t* data, int dataSize);
};
```

**Table 6** - Video streamer parameters description. Some parameters may be unsupported by a particular video streamer class. The parameters correspond to the [VStreamerParam](#vstreamerparam-enum) enum.

| Parameter        | Description         |
| ---------------- | ------------------- |
| enable             | Enable/disable streamer, boolean: **false** - disable, **true** - enabled. If the video streamer disabled it should not stream video to client by any protocol. |
| width            | Video stream width, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| height           | Video stream height, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| ip               |Streamer IP, string. It can be, for example, RTSP server IP or destination IP. Default value is **0.0.0.0** which is a universal IP to receive client connections from any IP.  |
| rtspPort        | Streamer's RTSP port, integer [0:65535]. |
| rtspsPort       | Streamer's RTSPS port, integer [0:65535]. |
| rtpPort         | Streamer's RTP port, integer [0:65535]. Usually is used for RTP stream only or to determine port to stream video from streamer to video proxy. |
| webRtcPort      | Streamer's WebRTC port, integer [0:65535]. |
| hlsPort         | Streamer's HLS port, integer [0:65535]. |
| srtPort         | Streamer's SRC port, integer [0:65535]. |
| rtmpPort        | Streamer's RTMP port, integer [0:65535]. |
| rtmpsPort       | Streamer's RTMPS port, integer [0:65535]. |
| metadataPort    | Streamer's metadata port, integer [0:65535] (for example, for [KLV](https://en.wikipedia.org/wiki/KLV) metadata streaming.). |
| rtspEnable      | RTSP protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| rtpEnable       | RTP protocol enable / disable, boolean:**false** - disable, **true** - enable. |
| webRtcEnable    | WebRTC protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| hlsEnable       | HLS protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| srtEnable       | SRT protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| rtmpEnable      | RTMP protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| metadataEnable  | Metadata protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| rtspMulticastIp | RTSP multicast IP, string. Usually video server accepts range of IPs (default value **224.1.0.1/16**). Some video streamer may support only single IP (example **224.1.0.1/32**). This parameters is used only with IP mask. |
| rtspMulticastPort | RTSP multicast port, integer [0:65535]. |
| user            | Streamer user (for rtsp streaming), string: **""** - no user. |
| password        | Streamer password (for RTSP streaming), string: **""** - no password. |
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



## Serialize video streamer parameters

The **VStreamerParams** class provides a method **serialize(...)** to serialize video streamer parameters (fields of the [VStreamerParams](#vstreamerparams-class-description) class). Serialization of video streamer parameters is necessary when you need to send video streamer parameters via communication channels. The method provides options to exclude particular parameters from serialization. To do this, the method inserts a binary mask (5 bytes) where each bit represents a particular parameter and the **deserialize(...)** method recognizes it. Method declaration:

```cpp
bool serialize(uint8_t* data, int bufferSize, int& size, VStreamerParamsMask* mask = nullptr);
```

| Parameter  | Value                                                        |
| ---------- | ------------------------------------------------------------ |
| data       | Pointer to data buffer.                                      |
| bufferSize | Data buffer size. If buffer size smaller than required, buffer will be filled with fewer parameters. |
| size       | Size of serialized data.                                     |
| mask       | Parameters mask - pointer to **VStreamerParamsMask** structure. **VStreamerParamsMask** (declared in VStreamer.h file) determines flags for each field (parameter) declared in **VStreamerParams** class. If the user wants to exclude any parameters from serialization, he can put a pointer to the mask. If the user wants to exclude a particular parameter from serialization, he should set the corresponding flag in the VStreamerParams structure. |

**VStreamerParamsMask** structure declaration:

```cpp
struct VStreamerParamsMask
{
    bool enable{true};
    bool width{true};
    bool height{true};
    bool ip{true};
    bool rtspPort{true};
    bool rtspsPort{true};
    bool rtpPort{true};
    bool webRtcPort{true};
    bool hlsPort{true};
    bool srtPort{true};
    bool rtmpPort{true};
    bool rtmpsPort{true};
    bool metadataPort{true};
    bool rtspEnable{true};
    bool rtpEnable{true};
    bool webRtcEnable{true};
    bool hlsEnable{true};
    bool srtEnable{true};
    bool rtmpEnable{true};
    bool metadataEnable{true};
    bool rtspMulticastIp{true};
    bool rtspMulticastPort{true};
    bool user{true};
    bool password{true};
    bool suffix{true};
    bool metadataSuffix{true};
    bool minBitrateKbps{true};
    bool maxBitrateKbps{true};
    bool bitrateKbps{true};
    bool bitrateMode{true};
    bool fps{true};
    bool gop{true};
    bool h264Profile{true};
    bool jpegQuality{true};
    bool codec{true};
    bool fitMode{true};
    bool cycleTimeUs{true};
    bool overlayEnable{true};
    bool type{true};
    bool custom1{true};
    bool custom2{true};
    bool custom3{true};
    bool rtspKey{true};
    bool rtspCert{true};
    bool webRtcKey{true};
    bool webRtcCert{true};
    bool hlsKey{true};
    bool hlsCert{true};
    bool rtmpKey{true};
    bool rtmpCert{true};
    bool rtspEncryption{true};
    bool webRtcEncryption{true};
    bool rtmpEncryption{true};
    bool hlsEncryption{true};
    bool logLevel{true};
};
```

Example without parameters mask:

```cpp
// Prepare random params.
VStreamerParams in;
in.ip = "alsfghljb";
in.port = 0;

// Serislize parameters.
uint8_t data[1024];
int size = 0;
in.serialize(data, 1024, size);
cout << "Serialized data size: " << size << " bytes" << endl;
```

Example with parameters mask:

```cpp
// Prepare random parameters.
VStreamerParams in;
in.ip = "alsfghljb";
in.port = 0;

// Prepare parameters mask.
VStreamerParamsMask mask;
mask.port = false; // Exclude port. Others by default.

// Encode parameters.
uint8_t data[1024];
int size = 0;
in.serialize(data, 1024, size, &mask);
cout << "Serialized data size: " << size << " bytes" << endl;
```



## Deserialize video streamer parameters

The **VStreamerParams** class provides a method **deserialize(...)** to deserialize video streamer parameters (fields of the [VStreamerParams](#vstreamerparams-class-description) class). Deserialization of video streamer parameters is necessary when you need to receive video streamer parameters via communication channels. The method automatically recognizes which parameters were serialized by the **serialize(...)** method. Method declaration:

```cpp
bool deserialize(uint8_t* data, int dataSize);
```

| Parameter | Value         |
| --------- | ------------- |
| data      | Pointer to serialized data buffer. |
| dataSize  | Size of data. |

**Returns:** TRUE if data is deserialized or FALSE if not.

Example:

```cpp
// Serialize parameters.
VStreamerParams in;
uint8_t data[1024];
int size = 0;
in.serialize(data, 1024, size);

cout << "Serialized data size: " << size << " bytes" << endl;

// Seserialize parameters.
VStreamerParams out;
if (!out.deserialize(data, size))
    cout << "Can't decode data" << endl;
```



## Read parameters from JSON file and write to JSON file

The **VStreamer** library depends on the **ConfigReader** library which provides methods to read parameters from JSON files and to write parameters to JSON files. Example of writing and reading parameters to JSON file:

```cpp
// Write params to file.
VStreamerParams in;
cr::utils::ConfigReader inConfig;
inConfig.set(in, "vStreamerParams");
inConfig.writeToFile("TestVStreamerParams.json");

// Read params from file.
cr::utils::ConfigReader outConfig;
if(!outConfig.readFromFile("TestVStreamerParams.json"))
{
    cout << "Can't open config file" << endl;
    return false;
}
```

**TestVStreamerParams.json** will look like (random values):

```json
{
    "vStreamerParams": 
    {
        "bitrateKbps": 45157,
        "bitrateMode": 53395,
        "codec": "dkgvmkrnjv",
        "custom1": 16353.0,
        "custom2": 30513.0,
        "custom3": 16213.0,
        "enable": false,
        "fitMode": 14594,
        "fps": 12255.0,
        "gop": 32446,
        "h264Profile": 17051,
        "height": 44304,
        "hlsCert": "24kjcnnv",
        "hlsEnable": false,
        "hlsEncryption": "wieufjpowkf",
        "hlsKey": "wqlovf;qb",
        "hlsPort": 9365,
        "ip": "sfspfo9jbjnbjhklvllks",
        "jpegQuality": 22605,
        "logLevel": 0,
        "maxBitrateKbps": 11267,
        "metadataEnable": false,
        "metadataPort": 35074,
        "metadataSuffix": "z.,nfpowe",
        "minBitrateKbps": 6818,
        "overlayEnable": true,
        "password": "sddgoihw,",
        "rtmpCert": "wfpomv",
        "rtmpEnable": true,
        "rtmpEncryption": "skldfjdf",
        "rtmpKey": "dkkkkjfkjdkjfkj2134",
        "rtmpPort": 55981,
        "rtmpsPort": 1936,
        "rtpEnable": true,
        "rtpPort": 31062,
        "rtspCert": "lkjrkjg",
        "rtspEnable": true,
        "rtspEncryption": "quyen",
        "rtspKey": "dh;skcsf",
        "rtspMulticastIp": "wpofuihifo",
        "rtspMulticastPort": 47135,
        "rtspPort": 42745,
        "rtspsPort": 56847,
        "srtEnable": true,
        "srtPort": 1963,
        "suffix": "pisfhcowmfv",
        "type": 5617,
        "user": "slfljkv",
        "webRtcCert": "erghshiAJ",
        "webRtcEnable": false,
        "webRtcEncryption": "l;uoykh",
        "webRtcKey": "WERUHUHFE",
        "webRtcPort": 50955,
        "width": 48849
    }
}
```



# Build and connect to your project

Typical commands to build **VStreamer** library:

```bash
cd VStreamer
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
```

If you want connect **VStreamer** library to your CMake project as source code you can make follow. For example, if your repository has structure:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
```

Create folder **3rdparty** and copy **VStreamer** repository folder there. New structure of your repository:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    VStreamer
```

Create CMakeLists.txt file in **3rdparty** folder. CMakeLists.txt should contain:

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
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
################################################################################
add_subdirectory(VStreamer)
```

File **3rdparty/CMakeLists.txt** adds folder **VStreamer** to your project and excludes test application and example (VStreamer class test applications and example of custom video streamer class implementation) from compiling (by default test application and example excluded from compiling if **VStreamer** included as sub-repository). Your repository new structure will be:

```bash
CMakeLists.txt
src
    CMakeList.txt
    yourLib.h
    yourLib.cpp
3rdparty
    CMakeLists.txt
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



# How to make custom implementation

The **VStreamer** class provides only an interface, data structures, and methods for encoding and decoding commands and params. To create your own implementation of the video streamer, you must include the VStreamer repository in your project (see [Build and connect to your project](#build-and-connect-to-your-project) section). The catalogue **example** (see [Library files](#library-files) section) includes an example of the design of the custom video streamer. You must implement all the methods of the VStreamer interface class. Custom video streamer class declaration:

```cpp
namespace cr
{
namespace video
{
/// Custom video streamer class.
class CustomVStreamer: public VStreamer
{
public:

    /// Class destructor.
    ~CustomVStreamer();

    /// Get string of current library version.
    static std::string getVersion();

    /// Init video streamer. All params will be set according to structure.
    bool initVStreamer(VStreamerParams &params,
                       VCodec *codec = nullptr,
                       VOverlay *overlay = nullptr) override;

    /// Get open status.
    bool isVStreamerInit() override;

    /// Close video streamer.
    void closeVStreamer() override;

    /// Send frame to video streamer.
    bool sendFrame(Frame& frame, uint8_t* userData = nullptr, int userDataSize = 0) override;

    /// Set video streamer param.
    bool setParam(VStreamerParam id, float value) override;

    /// Set video streamer param.
    bool setParam(VStreamerParam id, std::string value) override;

    /// Get video streamer params structure.
    void getParams(VStreamerParams& params) override;

    /// Execute command.
    bool executeCommand(VStreamerCommand id) override;
};
}
}
```