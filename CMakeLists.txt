cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)
project(mupen64plus-rsp-cxd4 LANGUAGES CXX C)

include_directories(../mupen64plus-core/src/api)
add_definitions(-DM64P_PLUGIN_API)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)
check_ipo_supported(RESULT ENABLE_IPO)
if(ENABLE_IPO)
    message("Interprocedural optimizations enabled")
endif(ENABLE_IPO)

if(ENABLE_IPO AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Gui Widgets Core REQUIRED)

set(NAME_PLUGIN_M64P "${CMAKE_PROJECT_NAME}")
set(PATH_SRC "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DARCH_MIN_SSE2 -O3 -flto -Wall")

set(CXD4_SOURCES
"${PATH_SRC}/module.cpp"
"${PATH_SRC}/su.c"
"${PATH_SRC}/vu/add.c"
"${PATH_SRC}/vu/divide.c"
"${PATH_SRC}/vu/logical.c"
"${PATH_SRC}/vu/multiply.c"
"${PATH_SRC}/vu/select.c"
"${PATH_SRC}/vu/vu.c"
"${PATH_SRC}/UserInterface/MainDialog.cpp"
"${PATH_SRC}/UserInterface/MainDialog.ui"
)

if (MINGW)
  list(APPEND CXD4_SOURCES
    "${PATH_SRC}/osal_dynamiclib_win32.c"
  )
else()
  list(APPEND CXD4_SOURCES
    "${PATH_SRC}/osal_dynamiclib_unix.c"
  )
endif()

add_library(${NAME_PLUGIN_M64P} SHARED ${CXD4_SOURCES})

set_target_properties(${NAME_PLUGIN_M64P} PROPERTIES PREFIX "")
target_link_libraries(${NAME_PLUGIN_M64P} Qt5::Gui Qt5::Widgets)
