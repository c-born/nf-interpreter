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


# Graphics and Touch Core
#__________________
list(APPEND NF_UI_Graphics_SRC_FILE "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_core/lv_group.c")
list(APPEND NF_UI_Graphics_SRC_FILE "${PROJECT_SOURCE_DIR}/src/LittlevGL/lvgl/lv_themes/lv_theme_zen.c")


# Display Driver Source
#__________________
list(APPEND NF_UI_Graphics_SRC_FILE "${PROJECT_SOURCE_DIR}/src/LittlevGL/lv_drivers/display/fbdev.c")
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

# Display Driver Include
#__________________
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/UI/Core/Bmp")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/UI/Core/Font")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/UI/Core/Gif")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/UI/Core/Includes")

list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg")

list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/UI/DeviceInterfaces/UI.Graphics/Font")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/UI/DeviceDrivers/UI/Includes")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/UI/DeviceDrivers/UI/Displays/${UI_DISPLAY_DRIVER}")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${TARGET_BASE_LOCATION}/UI.Display/SPI")

# Touch drivers source
#__________________
list(APPEND NF_UI_Graphics_SRC_FILE "${PROJECT_SOURCE_DIR}/src/LittlevGL/nfCommunityDrivers/ili9341_xpt2046/ili9341.c")

# Touch drivers include
#__________________
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/LittlevGL/nfCommunityDrivers/ili9341_xpt2046")
list(APPEND NF_UI_Graphics_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}/src/LittlevGL/nfCommunityDrivers/misc")



# make var global
#__________________
set(NF_UI_Graphics_SRC_FILE ${NF_UI_Graphics_SRC_FILE} CACHE INTERNAL "make global")
set(NF_UI_Graphics_INCLUDE_DIRS ${NF_UI_Graphics_INCLUDE_DIRS} CACHE INTERNAL "make global")


