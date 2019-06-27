#
# Copyright (c) 2019 The nanoFramework project contributors
# See LICENSE file in the project root for full license information.
#

# UI/Core/Bmp
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Bmp/Bitmap.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Bmp/Graphics_Bmp.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Core/Bmp")

# UI/Display/Driver
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Display/Display_functions.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Core/Display")

# UI/Core/Fonts
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Fonts/Font.cpp")

# UI/Core/Gesture
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Gesture/gesture_driver.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Gesture/gesture_functions.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Core/Gesture/")

# UI/Core/Gif
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Gif/Gif.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Gif/GifDecoder.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Gif/lzwread.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Core/Gif")

# UI/Core/Graphics
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Graphics/graphics.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Graphics/GraphicsMemoryHeap.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Graphics/pal_graphics.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Core/Graphics")

# UI/Core/Ink
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Ink/ink_driver.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Ink/ink_functions.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Core/Ink")

# UI/Core/Jpeg
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jbytearraydatasrc.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcapimin.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcapistd.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jccoefct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jccolor.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcdctmgr.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jchuff.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcinit.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcmainct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcmarker.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcmaster.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcomapi.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcparam.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcphuff.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcprepct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jcsample.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jctrans.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdapimin.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdapistd.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdcoefct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdcolor.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jddctmgr.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdhuff.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdinput.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdmainct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdmarker.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdmaster.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdmerge.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdphuff.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdpostct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdsample.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jdtrans.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jerror.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jfdctflt.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jfdctfst.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jfdctint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jidctflt.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jidctfst.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jidctint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jidctred.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jmemmgr.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jmemtinyclr.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/Jpeg.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jquant1.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jquant2.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/jutils.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/mcbcr.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/mfint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/miint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/pfint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/piint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg/transupp.c")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Core/Jpeg")

# UI/Core/Native
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Native/graphics_native.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Native/graphics_native_Bitmap.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Native/graphics_native_Font.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Native/touch_native.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Native/touch_native_Touch_Ink.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Native/touch_native_Touch_TouchCollectorConfiguration.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Native/touch_native_Touch_TouchEventProcessor.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/Native/touch_native_Touch_TouchPanel.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Core/Native")

# UI/Core/TouchPanel
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/TouchPanel/touchpanel_Driver.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Core/TouchPanel/touchpanel_functions.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Core/TouchPanel")

# UI/Devices/Display
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Devices/Display/Display_ILI9341.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Devices/Display")

# UI/Devices/Touch
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Devices/Touch/Touch_XPT2046.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Devices/Touch")

# UI/Interfaces
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Interfaces")

# Target Board Support
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/${Target_Graphics_Support}")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/${Target_Touch_Support}")

# make var global
#__________________
set(Graphics_Sources ${Graphics_Sources} CACHE INTERNAL "make global")
set(Graphics_Includes ${Graphics_Includes} CACHE INTERNAL "make global")


