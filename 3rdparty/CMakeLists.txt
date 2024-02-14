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
SET(PARENT ${PARENT}_VSTREAMER_3RDPARTY)
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
endif()


SET(${PARENT}_SUBMODULE_VOVERLAY                        ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_VOVERLAY)
    SET(${PARENT}_VOVERLAY                              ON  CACHE BOOL "" FORCE)
endif()


SET(${PARENT}_SUBMODULE_VCODEC                           ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_VCODEC)
    SET(${PARENT}_VCODEC                                 ON  CACHE BOOL "" FORCE)
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