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

The **VStreamer** C++ library provides a standard interface and defines data structures and rules for different video stream classes. The **VStreamer** interface class does nothing by itself, just provides an interface and methods to encode/decode commands and serialize/deserialize parameters. The **VStreamer** class also provides data structures for video stream parameters. Different video stream classes inherit the interface from the **VStreamer** C++ class. The **VStreamer.h** file contains a list of data structures ([VStreamerCommand](#vstreamercommand-enum) enum, [VStreamerParam](#vstreamerparam-enum) enum and [VStreamerParams](#vstreamerparams-class-description) class). The [VStreamerParams](#vstreamerparams-class-description) class contains all streamer parameters and includes methods to serialize and deserialize parameters. The [VStreamerCommand](#vstreamercommand-enum) enum contains IDs of commands supported by the **VStreamer** class. The [VStreamerParam](#vstreamerparam-enum) enum contains IDs of parameters supported by the **VStreamer** class. All video streamers should include parameters and commands listed in the **VStreamer.h** file. The **VStreamer** interface class depends on: [ConfigReader](https://rapidpixel.constantrobotics.com/docs/Service/ConfigReader.html) library (provides methods to read/write JSON config files, source code included, Apache 2.0 license), [VCodec](https://rapidpixel.constantrobotics.com/docs/VideoCoding/VCodec.html) library (provides interface for video codecs, source code included, Apache 2.0 license), [VOverlay](https://rapidpixel.constantrobotics.com/docs/Service/VOverlay.html) library (provides interface for overlay engines, source code included, Apache 2.0 license). The library is licensed under the **Apache 2.0** license.



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

The library is supplied as source code only. The user will be given a set of files in the form of a CMake project (repository). The repository structure is shown below:

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
| params    | [VStreamerParams](#vstreamerparams-class-description) class object. The video streamer should set parameters according to parameters class. Particular video streamer might not support all parameters listed in [VStreamerParams](#vstreamerparams-class-description) class. |
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

The **setParam(...)** method sets new value of video stream parameter. Each implementation of the video streamer must provide thread-safe **setParam(...)** method call. This means that the **setParam(...)** method can be safely called from any thread. Also, method has two overloaded version that depends on type of value. Method declaration:

```cpp
virtual bool setParam(VStreamerParam id, float value) = 0;
virtual bool setParam(VStreamerParam id, std::string value) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Video stream parameter ID according to [VStreamerParam](#vstreamerparam-enum) enum. |
| value     | Value of parameter. It can be either string or float type. It depends on parameter. |

**Returns:** TRUE is the parameter is set or FALSE if not.



## getParams method

The **getParams(...)** method designed to obtain video streamer params class ([VStreamerParams](#vstreamerparams-class-description)). Each implementation of the video streamer must provide thread-safe **getParams(...)** method call. This means that the **getParams(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual void getParams(VStreamerParams& params) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| params    | [VStreamerParams](#vstreamerparams-class-description) class object. |



## executeCommand method

The **executeCommand(...)** method to execute video stream command. The particular implementation of the video stream must provide thread-safe **executeCommand(...)** method call. This means that the **executeCommand(...)** method can be safely called from any thread. Method declaration:

```cpp
virtual bool executeCommand(VStreamerCommand id) = 0;
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| id        | Video stream command ID according to [VStreamerCommand](#vstreamercommand-enum) enum. |

**Returns:** TRUE is the command was executed or FALSE if not.



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

The **encodeSetParamCommand(...)** static method to encode command to change any parameter in remote video streamer. To control video streamer remotely, the developer has to design his own protocol and according to it encode the command and deliver it over the communication channel. To simplify this, the **VStreamer** class contains static methods for encoding the control command. The **VStreamer** class provides two types of commands: a parameter change command (SET_PARAM) and an action command (COMMAND). **encodeSetParamCommand(...)** designed to encode SET_PARAM command. Method has two overlays: one for numeric parameters and one for string parameters. Method declaration:

```cpp
static void encodeSetParamCommand(uint8_t *data, int &size,  VStreamerParam id, float value);

static void encodeSetParamCommand(uint8_t* data, int& size, VStreamerParam id, std::string value);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to data buffer for encoded command. Must have size >= 11 or in case string parameters it must be enough to keep string + 12 bytes. |
| size      | Size of encoded data. Will be minimum 11 bytes.              |
| id        | Parameter ID according to [VStreamerParam](#vstreamerparam-enum) enum. |
| value     | Numeral video streamer parameter value. Only for non string parameters. For string parameters (see [VStreamerParam](#vstreamerparam-enum) enum) this parameters may have any values. |
| value     | String parameter value (see [VStreamerParam](#vstreamerparam-enum) enum). |

**encodeSetParamCommand(...)** is static method and used without **VStreamer** class instance. This method used on client side (control system). Command encoding example:

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

The **encodeCommand(...)** static method to encode command for remote video streamer. To control a video streamer remotely, the developer has to design his own protocol and according to it encode the command and deliver it over the communication channel. To simplify this, the **VStreamer** class contains static methods for encoding the control command. The **VStreamer** class provides two types of commands: a parameter change command (SET_PARAM) and an action command (COMMAND). **encodeCommand(...)** designed to encode COMMAND (action command). Method declaration:

```cpp
static void encodeCommand(uint8_t* data, int& size, VStreamerCommand id);
```

| Parameter | Description                                                  |
| --------- | ------------------------------------------------------------ |
| data      | Pointer to data buffer for output command. Must have size >= 7 bytes. |
| size      | Size of encoded data. Will be 7 bytes.                       |
| id        | Command ID according to [VStreamerCommand](#vstreamercommand-enum) enum. |

**encodeCommand(...)** is static method and used without **VStreamer** class instance. This method used on client side (control system). Command encoding example:

```cpp
// Buffer for encoded data.
uint8_t data[11];
// Size of encoded data.
int size = 0;
// Encode command.
VStreamer::encodeCommand(data, size, VStreamerCommand::RESTART);
```



## decodeCommand method

The **decodeCommand(...)** static method to decode command on video streamer side (edge device). Method declaration:

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
| paramId   | Parameter ID according to [VStreamerParam](#vstreamerparam-enum) enum. After decoding SET_PARAM command the method will return parameter ID. |
| commandId | Command ID according to [VStreamerCommand](#vstreamercommand-enum) enum. After decoding COMMAND the method will return command ID. |
| value    | Numeral video streamer parameter value. Only for non string parameters. For string parameters (see [VStreamerParam](#vstreamerparam-enum) enum) this parameters may have any values. |
| strValue    | String parameter value (see [VStreamerParam](#vstreamerparam-enum) enum). |

**Returns:** **0** - in case decoding COMMAND, **1** - in case decoding SET_PARAM command or **-1** in case errors.



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

**Table 4** - Video stream action commands description. Some commands maybe unsupported by particular video stream class.

| Command    | Description                                                  |
| ------------ | ---------------------------------------------------------- |
| RESTART      | Restarts streamer with last [VStreamerParams](#vstreamerparams-class-declaration). |
| ON           | Enables streamer if it is disabled.                        |
| OFF          | Disables streamer if it is enabled.                        |
| GENERATE_KEYFRAME | Action command to generate key frame by video codec in case **H264/HEVC** video encoding. This function is obligatory in some case. |



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
    CUSTOM3
};
```

**Table 5** - Video streamer params description. Some params maybe unsupported by particular video streamer class.

| Parameter        | Description         |
| ---------------- | ------------------- |
| MODE             | Enable/disable streamer, integer: **0** - disable, **1** - enabled. If the video streamer disabled it should not stream video to client by any protocol. |
| WIDTH            | Video stream width, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| HEIGHT           | Video stream height, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| IP               |Streamer IP, string. It can be, for example, RTSP server IP or destination IP. Default value is **0.0.0.0** which is a universal IP to receive client connections from any IP.  |
| RTSP_PORT        | Streamer's RTSP port, integer [0:65535]. |
| RTP_PORT         | Streamer's RTP port, integer [0:65535]. Usually is used for RTP stream only or to determine port to stream video from streamer to video proxy. |
| WEBRTC_PORT      | Streamer's WebRTC port, integer [0:65535]. |
| HLS_PORT         | Streamer's HLS port, integer [0:65535]. |
| SRT_PORT         | Streamer's SRC port, integer [0:65535]. |
| RTMP_PORT        | Streamer's RTMP port, integer [0:65535]. |
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
| USER             | Streamer user (for rtsp streaming), string: "" - no user. |
| PASSWORD         | Streamer password (for RTSP streaming), string: "" - no password. |
| SUFFIX           | Streamer suffix for RTSP streaming (stream name), string: "" - no suffix. |
| METADATA_SUFFIX  | Metadata suffix (stream name), string: "" - no suffix. This parameter is used if the metadata is the separate stream in RTSP. |
| MIN_BITRATE_KBPS | Minimum bitrate for variable bitrate mode, integer kbps. |
| MAX_BITRATE_KBPS | Maximum bitrate for variable bitrate mode, integer kbps. |
| BITRATE_KBPS     | Current bitrate, integer kbps. This parameter is used for constant bitrate mode or as initial value. |
| BITRATE_MODE     | Bitrate mode, integer: 0 - constant bitrate, 1 - variable bitrate. |
| FPS              | FPS, float. The input frame FPS can be different from the FPS in the video stream. The video streamer must provide video stream FPS for clients according to this parameter's value independent from input frame FPS ([sendFrame()](#sendframe-method)). If the FPS value is **0**, the streamer must provide FPS equal to the input video frame rate. |
| GOP              | Codec GOP size (key frame interval) in case of RAW input video frames. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| H264_PROFILE     | H264 profile, integer: 0 - baseline, 1 - main, 2 - high. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| JPEG_QUALITY     | JPEG quality, integer: [1:100]% for JPEG codec. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| CODEC            | Codec type, string: "H264", "HEVC" or "JPEG". If the user provides already encoded frames in [sendFrame()](#sendframe-method) method. |
| FIT_MODE         | Scaling mode, integer: 0 - fit, 1 - fill. |
| CYCLE_TIME_USEC  | Cycle time, integer μsec (microseconds). Calculated by video streamer. |
| OVERLAY_MODE     | Overlay enable / disable, integer: **0** - disable, **1** - enable. This parameter enables or disables video overlay if the video overlay module is provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| TYPE             | Type of the streamer, integer. Depends on implementation. |
| CUSTOM1          | Custom parameter 1, float. |
| CUSTOM2          | Custom parameter 2, float. |
| CUSTOM3          | Custom parameter 3, float. |



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

    JSON_READABLE(VStreamerParams, enable, width, height, ip, rtspPort, rtpPort,
                  webRtcPort, hlsPort, srtPort, rtmpPort, metadataPort,
                  rtspEnable, rtpEnable, webRtcEnable, hlsEnable, srtEnable,
                  rtmpEnable, metadataEnable, rtspMulticastIp, rtspMulticastPort,
                  user, password, suffix, metadataSuffix, minBitrateKbps,
                  maxBitrateKbps, bitrateKbps, bitrateMode, fps, gop, h264Profile,
                  jpegQuality, codec, fitMode, overlayEnable, type, custom1,
                  custom2, custom3)

    /// Serialize parameters.
    bool serialize(uint8_t* data, int bufferSize, int& size,
                   VStreamerParamsMask* mask = nullptr);

    /// Deserialize parameters.
    bool deserialize(uint8_t* data, int dataSize);
};
```

**Table 6** - Video streamer params description. Some params maybe unsupported by particular video streamer class. The parameters reflect [VStreamerParam](#vstreamerparam-enum) enum.

| Parameter        | Description         |
| ---------------- | ------------------- |
| enable             | Enable/disable streamer, boolean: **false** - disable, **true** - enabled. If the video streamer disabled it should not stream video to client by any protocol. |
| width            | Video stream width, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| height           | Video stream height, integer [0:8192]. Regardless of the resolution of the input video, if RAW data is processed, the streamer should scale the images according to this parameter. |
| ip               |Streamer IP, string. It can be, for example, RTSP server IP or destination IP. Default value is **0.0.0.0** which is a universal IP to receive client connections from any IP.  |
| rtspPort        | Streamer's RTSP port, integer [0:65535]. |
| rtpPort         | Streamer's RTP port, integer [0:65535]. Usually is used for RTP stream only or to determine port to stream video from streamer to video proxy. |
| webRtcPort      | Streamer's WebRTC port, integer [0:65535]. |
| hlsPort         | Streamer's HLS port, integer [0:65535]. |
| srtPort         | Streamer's SRC port, integer [0:65535]. |
| rtmpPort        | Streamer's RTMP port, integer [0:65535]. |
| metadataPort    | Streamer's metadata port, integer [0:65535] (for example, for [KLV](https://en.wikipedia.org/wiki/KLV) metadata streaming.). |
| rtspEnable        | RTSP protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| rtpEnable         | RTP protocol enable / disable, boolean:**false** - disable, **true** - enable. |
| webRtcEnable | WebRTC protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| hlsEnable | HLS protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| srtEnable | SRT protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| rtmpEnable | RTMP protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| metadataEnable | Metadata protocol enable / disable, boolean: **false** - disable, **true** - enable. |
| rtspMulticastIp | RTSP multicast IP, string. Usually video server accepts range of IPs (default value **224.1.0.1/16**). Some video streamer may support only single IP (example **224.1.0.1/32**). This parameters is used only with IP mask. |
| rtspMulticastPort | RTSP multicast port, integer [0:65535]. |
| user | Streamer user (for rtsp streaming), string: "" - no user. |
| password | Streamer password (for RTSP streaming), string: "" - no password. |
| suffix | Streamer suffix for RTSP streaming (stream name), string: "" - no suffix. |
| metadataSuffix | Metadata suffix (stream name), string: "" - no suffix. This parameter is used if the metadata is the separate stream in RTSP. |
| minBitrateKbps | Minimum bitrate for variable bitrate mode, integer kbps. |
| maxBitrateKbps | Maximum bitrate for variable bitrate mode, integer kbps. |
| bitrateKbps | Current bitrate, integer kbps. This parameters is used for constant bitrate mode or as initial value. |
| bitrateMode | Bitrate mode, integer: 0 - constant bitrate, 1 - variable bitrate. |
| fps | FPS, float. The input frame FPS can be different from the FPS in the video stream. The video streamer must provide video stream FPS for clients according to this parameter's value independent from input frame FPS ([sendFrame()](#sendframe-method)). If the FPS value is **0**, the streamer must provide FPS equal to the input video frame rate. |
| gop | Codec GOP size (key frame interval) in case of RAW input video frames. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| h264Profile | H264 profile, integer: 0 - baseline, 1 - main, 2 - high. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| jpegQuality | JPEG quality, integer: [1:100]% for JPEG codec. This parameter will be set to the codec provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| codec | Codec type, string: "H264", "HEVC" or "JPEG". If the user provides already encoded frames in [sendFrame()](#sendframe-method) method. |
| fitMode | Scaling mode, integer: 0 - fit, 1 - fill. |
| cycleTimeUs | Cycle time, integer μsec (microseconds). Calculated by video streamer. |
| overlayEnable | Overlay enable / disable, boolean: **false** - disable, **true** - enable. This parameter enables or disables video overlay if the video overlay module is provided by the user in the [initVStreamer()](#initvstreamer-method) method. |
| type | Type of the streamer, integer. Depends on implementation. |
| custom1 | Custom parameter 1, float. |
| custom2 | Custom parameter 2, float. |
| custom3 | Custom parameter 3, float. |



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
    bool rtpPort{true};
    bool webRtcPort{true};
    bool hlsPort{true};
    bool srtPort{true};
    bool rtmpPort{true};
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

**TestVStreamerParams.json** will look like:

```json
{
    "vStreamerParams": {
        "bitrateKbps": 3000,
        "bitrateMode": 0,
        "codec": "H264",
        "custom1": 0.0,
        "custom2": 0.0,
        "custom3": 0.0,
        "enable": true,
        "fitMode": 0,
        "fps": 30.0,
        "gop": 30,
        "h264Profile": 0,
        "height": 720,
        "hlsEnable": true,
        "hlsPort": 8080,
        "ip": "0.0.0.0",
        "jpegQuality": 80,
        "maxBitrateKbps": 5000,
        "metadataEnable": false,
        "metadataPort": 9000,
        "metadataSuffix": "metadata",
        "minBitrateKbps": 1000,
        "overlayEnable": true,
        "password": "",
        "rtmpEnable": true,
        "rtmpPort": 1935,
        "rtpEnable": true,
        "rtpPort": 5004,
        "rtspEnable": true,
        "rtspMulticastIp": "224.1.0.1/16",
        "rtspMulticastPort": 18000,
        "rtspPort": 8554,
        "srtEnable": true,
        "srtPort": 6000,
        "suffix": "live",
        "type": 0,
        "user": "",
        "webRtcEnable": true,
        "webRtcPort": 7000,
        "width": 1280
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