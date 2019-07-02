#
# Copyright (c) 2019 The nanoFramework project contributors
# See LICENSE file in the project root for full license information.
#
#

# UI/Graphics/Core
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Graphics.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/GraphicsMemoryHeap.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core")

# UI/Graphics/Core/Support/Bmp
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Bmp/Bitmap_Decoder.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Bmp")

# UI/Graphics/Core/Support/Fonts
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Fonts/Font.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Fonts")

# UI/Graphics/Core/Support/Gif
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Gif/Gif.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Gif/GifDecoder.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Gif/lzwread.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Gif")

# UI/Graphics/Core/Support/Jpeg
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jbytearraydatasrc.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcapimin.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcapistd.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jccoefct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jccolor.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcdctmgr.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jchuff.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcinit.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcmainct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcmarker.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcmaster.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcomapi.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcparam.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcphuff.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcprepct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jcsample.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jctrans.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdapimin.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdapistd.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdcoefct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdcolor.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jddctmgr.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdhuff.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdinput.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdmainct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdmarker.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdmaster.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdmerge.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdphuff.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdpostct.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdsample.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jdtrans.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jerror.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jfdctflt.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jfdctfst.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jfdctint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jidctflt.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jidctfst.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jidctint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jidctred.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jmemmgr.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jmemtinyclr.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/Jpeg.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jquant1.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jquant2.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/jutils.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/mcbcr.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/mfint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/miint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/pfint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/piint.c")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg/transupp.c")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Core/Support/Jpeg")

# UI/Graphics/Core/Displays
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Displays/${Graphics_Display}")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Displays")

# UI/Graphics/Native
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Native/graphics_native.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Native/graphics_native_Bitmap.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Native/graphics_native_Font.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/Graphics/Native")

# UI/TouchPanel/Core/Support
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Core/Support/Gesture/Gesture.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Core/Support/Gesture")

# UI/TouchPanel/Core/Support
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Core/Support/Ink/Ink.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Core/Support/Ink")

# UI/TouchPanel/Core
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Core/TouchPanel.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Core")

# UI/TouchPanel/Devices
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Devices/${Touch_Device}")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Devices")

# UI/TouchPanel/Interfaces
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Interfaces")

# UI/TouchPanel/Native
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Native/TouchPanel_native.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Native/TouchPanel_native_Touch_Ink.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Native/TouchPanel_native_Touch_TouchCollectorConfiguration.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Native/TouchPanel_native_Touch_TouchEventProcessor.cpp")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Native/TouchPanel_native_Touch_TouchPanel.cpp")
list(APPEND Graphics_Includes "${PROJECT_SOURCE_DIR}/src/UI/TouchPanel/Native")


# Target Board Support
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/${Target_Graphics_Memory}")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/${Target_Display_Interface}")
list(APPEND Graphics_Sources "${PROJECT_SOURCE_DIR}/${Target_TouchPanel_Interface}")

# make var global
#__________________
set(Graphics_Sources ${Graphics_Sources} CACHE INTERNAL "make global")
set(Graphics_Includes ${Graphics_Includes} CACHE INTERNAL "make global")


