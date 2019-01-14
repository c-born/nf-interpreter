#
# Copyright (c) 2019 The nanoFramework project contributors
# See LICENSE file in the project root for full license information.
#

# check for graphics driver in target directory so we can display a meaningfull message
if(NOT EXISTS "${TARGET_BASE_LOCATION}/UI.Display/SPI/CPU_To_Graphics_Display.cpp")
    message(FATAL_ERROR, "\nCPU to Graphics display not found in target directory.\n")
endif()

# check for display driver so we can display a meaningfull message
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/src/DeviceDrivers/UI/Displays/${UI_DISPLAY_DRIVER}/Display_driver.cpp")
    message(FATAL_ERROR, "\nDisplay driver not found in device drivers directory.\n")
endif()

# set include directories
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics/Bmp")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics/Gif")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics/Jpeg")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics/Includes")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics/Font")

list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics/Font")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/DeviceDrivers/UI/Includes")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/DeviceDrivers/UI/Displays/${UI_DISPLAY_DRIVER}")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${TARGET_BASE_LOCATION}/UI.Display/SPI")

# source files
set(NF_UI_Graphics_SRCS

    Graphics.cpp
    Graphics_Driver.cpp
    Simple_Heap.cpp

    Bitmap.cpp
    BmpHelper.cpp

    Font.cpp
    Font8x15.cpp
    Font8x8.cpp

    Gif.cpp
    GifDecoder.cpp
    lzwread.cpp

    Jpeg.cpp
    jbytearraydatasrc.c
    jcapimin.c
    jcapistd.c
    jccoefct.c
    jccolor.c
    jcdctmgr.c
    jchuff.c
    jchuff.h
    jcinit.c
    jcmainct.c
    jcmarker.c
    jcmaster.c
    jcomapi.c
    jconfig.h
    jcparam.c
    jcphuff.c
    jcprepct.c
    jcsample.c
    jctrans.c
    jdapimin.c
    jdapistd.c
    jdcoefct.c
    jdcolor.c
    jdct.h
    jddctmgr.c
    jdhuff.c
    jdhuff.h
    jdinput.c
    jdmainct.c
    jdmarker.c
    jdmaster.c
    jdmerge.c
    jdphuff.c
    jdpostct.c
    jdsample.c
    jdtrans.c
    jerror.c
    jerror.h
    jfdctflt.c
    jfdctfst.c
    jfdctint.c
    jidctflt.c
    jidctfst.c
    jidctint.c
    jidctred.c
    jinclude.h
    jmemmgr.c
    jmemsys.h
    jmemtinyclr.cpp
    jmorecfg.h
    Jpeg.cpp
    jpegint.h
    jpeglib.h
    jquant1.c
    jquant2.c
    jutils.c
    jversion.h
    mcbcr.c
    mcbcr.h
    mfint.c
    miint.c
    pfint.c
    piint.c
    transupp.c

    Display_driver.cpp

    CPU_To_Graphics_Display.cpp

    Graphics_native.cpp
    Graphics_native_Bitmap.cpp
    Graphics_native_Font.cpp
)

foreach(SRC_FILE ${NF_UI_Graphics_SRCS})
    set(NF_UI_Graphics_SRC_FILE SRC_FILE-NOTFOUND)
    find_file(NF_UI_Graphics_SRC_FILE ${SRC_FILE}
        PATHS

            "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics"
            "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics/Bmp"
            "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics/Gif"
            "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics/Jpeg"
            "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics/Font"

            "${PROJECT_SOURCE_DIR}/src/DeviceInterfaces/UI.Graphics/Native"

            "${PROJECT_SOURCE_DIR}/src/DeviceDrivers/UI/Displays/${UI_DISPLAY_DRIVER}"

            "${TARGET_BASE_LOCATION}/UI.Display/SPI"
 
        CMAKE_FIND_ROOT_PATH_BOTH
    )
    # message("${SRC_FILE} >> ${NF_UI_Graphics_SRC_FILE}") # debug helper
    list(APPEND NF_UI_Graphics_SOURCES ${NF_UI_Graphics_SRC_FILE})
endforeach()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(NF_UI_Graphics DEFAULT_MSG NF_UI_Graphics_INCLUDE_DIRS NF_UI_Graphics_SOURCES)
