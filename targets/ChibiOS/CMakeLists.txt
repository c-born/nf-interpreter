#
# Copyright (c) .NET Foundation and Contributors
# See LICENSE file in the project root for full license information.
#

include(FetchContent)
include(binutils.arm-none-eabi)
include(binutils.ChibiOS)
include(STM32_CubePackage)
include(NF_Utils)

# Define PLATFORM base path
set(BASE_PATH_FOR_PLATFORM ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

########################################################
# check availability of hex2dfu tool if specified
if(DEFINED TOOL_HEX2DFU_PREFIX)
    if(NOT EXISTS ${TOOL_HEX2DFU_PREFIX}/hex2dfu.exe AND NOT EXISTS ${TOOL_HEX2DFU_PREFIX}/hex2dfu)
        message(STATUS "")
        message(STATUS "Couldn't find the hex2dfu tool at the specified path: ${TOOL_HEX2DFU_PREFIX}/hex2dfu.exe or ${TOOL_HEX2DFU_PREFIX}/hex2dfu")
        message(STATUS "Make sure that the CMake option TOOL_HEX2DFU_PREFIX has the correct path.")
        message(STATUS "If you don't have this tool download it from https://github.com/nanoframework/nf-tools/releases")
        message(STATUS "")
        message(FATAL_ERROR "hex2dfu tool not found")
    else()
        set(HEX2DFU_TOOL_AVAILABLE TRUE CACHE INTERNAL "hex2dfu tool available")
    endif()
endif()

########################################################
# check availability of SRecord tool, if specified
if(DEFINED TOOL_SRECORD_PREFIX)
    if(NOT ((EXISTS ${TOOL_SRECORD_PREFIX}/srec_cat.exe) OR (EXISTS ${TOOL_SRECORD_PREFIX}/srec_cat)))
        message(STATUS "")
        message(STATUS "Couldn't find the srec_cat tool at the specified path: ${TOOL_SRECORD_PREFIX}/srec_cat.exe")
        message(STATUS "Make sure that the CMake option TOOL_SRECORD_PREFIX has the correct path.")
        message(STATUS "If you don't have this tool download it from https://sourceforge.net/projects/srecord/files/srecord-win32/")
        message(STATUS "")
        message(FATAL_ERROR "srec_cat tool not found")
    else()
        set(SRECORD_TOOL_AVAILABLE TRUE CACHE INTERNAL "srec_cat tool available")
    endif()
endif()

# check if RTOS_SOURCE_FOLDER was specified or if it's empty (default is empty)
set(NO_RTOS_SOURCE_FOLDER TRUE)
if(RTOS_SOURCE_FOLDER)
    if(NOT ${RTOS_SOURCE_FOLDER} STREQUAL "")
        set(NO_RTOS_SOURCE_FOLDER FALSE)
    endif()
endif()

# check if CHIBIOS-Contrib_SOURCE was specified or if it's empty (default is empty)
set(NO_CHIBIOS_CONTRIB_SOURCE TRUE)
if(CHIBIOS_CONTRIB_SOURCE)
    if(NOT ${CHIBIOS_CONTRIB_SOURCE} STREQUAL "")
        set(NO_CHIBIOS_CONTRIB_SOURCE FALSE)
    endif()
endif()

# ChibiOS version
set(RTOS_VERSION_EMPTY TRUE)

# check if build was requested with a specifc ChibiOS version
if(DEFINED RTOS_VERSION)
    if(NOT "${RTOS_VERSION}" STREQUAL "")
        set(RTOS_VERSION_EMPTY FALSE)
    endif()
endif()

# check if build was requested with a specifc ChibiOS version
if(RTOS_VERSION_EMPTY)
    # no ChibiOS version actualy specified, must be empty which is fine, we'll default to a known good version
    # WHEN CHANGING THIS MAKE SURE TO UPDATE THE DEV CONTAINERS
    set(RTOS_VERSION "stable_20.3.x")
endif()

if(NO_RTOS_SOURCE_FOLDER)
    # no CHIBIOS source specified, download it from it's repo
    message(STATUS "RTOS is: ChibiOS ${RTOS_VERSION} from nanoFramework GitHub repo")

    FetchContent_Declare(
        chibios
        GIT_REPOSITORY https://github.com/nanoframework/chibios
        GIT_TAG ${RTOS_VERSION}
    )

else()
    # ChibiOS source was specified

    # sanity check is source path exists
    if(EXISTS ${RTOS_SOURCE_FOLDER}/)
        message(STATUS "RTOS is: ChibiOS ${RTOS_VERSION} (source from: ${RTOS_SOURCE_FOLDER})")

        FetchContent_Declare(
            chibios
            GIT_REPOSITORY ${RTOS_SOURCE_FOLDER}
            GIT_TAG ${RTOS_VERSION}
        )

    else()
        message(FATAL_ERROR "Couldn't find ChibiOS source at ${RTOS_SOURCE_FOLDER}/")
    endif()

endif()

FetchContent_GetProperties(chibios)
FetchContent_Populate(chibios)

if(CHIBIOS_CONTRIB_REQUIRED)
    if(NO_CHIBIOS_CONTRIB_SOURCE)
        # no CHIBIOS_CONTRIB source specified, download it from it's repo

        FetchContent_Declare(
            chibios-contrib
            GIT_REPOSITORY https://github.com/nanoframework/ChibiOS-Contrib
            GIT_TAG nanoframework
        )

        message(STATUS "ChibiOS-Contrib from GitHub repo")

    else()
        # ChibiOS-Contrib source was specified

        # sanity check is source path exists
        if(EXISTS ${CHIBIOS_CONTRIB_SOURCE}/)
            message(STATUS "ChibiOS-Contrib (source from: ${CHIBIOS_CONTRIB_SOURCE})")

            FetchContent_Declare(
                chibios-contrib
                GIT_REPOSITORY ${CHIBIOS_CONTRIB_SOURCE}
                GIT_TAG nanoframework
            )

        else()
            message(FATAL_ERROR "Couldn't find ChibiOS-Contrib source at ${CHIBIOS_CONTRIB_SOURCE}/")
        endif()

    endif()

    FetchContent_GetProperties(chibios-contrib)
    FetchContent_Populate(chibios-contrib)

endif()


# include FatFS if SDCard or USB MSD are ON
if(NF_FEATURE_HAS_SDCARD OR NF_FEATURE_HAS_USB_MSD)

    # check if FATFS_SOURCE was specified or if it's empty (default is empty)
    set(NO_FATFS_SOURCE TRUE)
    if(FATFS_SOURCE)
        if(NOT ${FATFS_SOURCE} STREQUAL "")   
            set(NO_FATFS_SOURCE FALSE)
        endif()
    endif()

    # FatFS version
    set(FATFS_VERSION_EMPTY TRUE)

    # check if build was requested with a specifc FatFS version
    if(DEFINED FATFS_VERSION)
        if(NOT ${FATFS_VERSION} STREQUAL "")
            set(FATFS_VERSION_EMPTY FALSE)
        endif()
    endif()

    # check if build was requested with a specifc FatFS version
    if(FATFS_VERSION_EMPTY)
        # no FatFS version actualy specified, must be empty which is fine, we'll default to a known good version
        # WHEN CHANGING THIS MAKE SURE TO UPDATE THE DEV CONTAINERS
        set(FATFS_VERSION_TAG "R0.14")
    else()
        # set version 
        set(FATFS_VERSION_TAG ${FATFS_VERSION})
    endif()

    if(NO_FATFS_SOURCE)
        message(STATUS "FatFS ${FATFS_VERSION_TAG} from GitHub repo")

        FetchContent_Declare(
            fatfs
            GIT_REPOSITORY https://github.com/abbrev/fatfs.git
            GIT_TAG ${FATFS_VERSION_TAG}
        )

    else()
        # FatFS source was specified

        # sanity check is source path exists
        if(EXISTS ${FATFS_SOURCE}/)
            message(STATUS "FatFS ${FATFS_VERSION_TAG} source from: ${FATFS_SOURCE})")

            FetchContent_Declare(
                fatfs
                GIT_REPOSITORY ${FATFS_SOURCE}
                GIT_TAG ${FATFS_VERSION_TAG}
            )

        else()
            message(FATAL_ERROR "Couldn't find FatFS source at ${FATFS_SOURCE}/")
        endif()

    endif()

    FetchContent_GetProperties(fatfs)
    FetchContent_Populate(fatfs)

    # have to delete the ffconf.h template from the repo
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E remove ${fatfs_SOURCE_DIR}/source/ffconf.h
    )

endif()

# if mbed TLS is enabled add it to the build
if(NF_SECURITY_MBEDTLS)

    # check if MBEDTLS_SOURCE was specified or if it's empty (default is empty)
    set(NO_MBEDTLS_SOURCE TRUE)

    if(MBEDTLS_SOURCE)
        if(NOT ${MBEDTLS_SOURCE} STREQUAL "")
            set(NO_MBEDTLS_SOURCE FALSE)
        endif()
    endif()

    # set tag for currently supported version
    # WHEN CHANGING THIS MAKE SURE TO UPDATE THE DEV CONTAINERS
    set(MBEDTLS_GIT_TAG "mbedtls-2.26.0")

    # set options for mbed TLS
    option(ENABLE_TESTING "no testing when building mbed TLS." OFF)

    if(NO_MBEDTLS_SOURCE)
        # no mbed TLS source specified, download it from it's repo
        message(STATUS "mbedTLS ${MBEDTLS_GIT_TAG} from GitHub repo")

        FetchContent_Declare(
            mbedtls
            GIT_REPOSITORY https://github.com/ARMmbed/mbedtls
            GIT_TAG ${MBEDTLS_GIT_TAG}
        )

    else()
        # mbedTLS source was specified
        # message(FATAL_ERROR ${mbedtls_SOURCE_DIR}") 

        # sanity check is source path exists
        if(EXISTS ${MBEDTLS_SOURCE}/)

            message(STATUS "mbedTLS ${FATFS_VERSION_TAG} (source from: ${MBEDTLS_SOURCE})")
            
            FetchContent_Declare(
                mbedtls
                GIT_REPOSITORY ${MBEDTLS_SOURCE}
                GIT_TAG ${MBEDTLS_GIT_TAG}
            )

        else()
            message(FATAL_ERROR "Couldn't find mbedTLS source at ${MBEDTLS_SOURCE}/")
        endif()

    endif()

    FetchContent_GetProperties(mbedtls)
    FetchContent_Populate(mbedtls)

    set(mbedTLS_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/3rdparty/humblelogging/include)
    set(mbedTLS_LIBRARIES ${CMAKE_SHARED_LIBRARY_PREFIX}mbedTLS${CMAKE_SHARED_LIBRARY_SUFFIX})

endif()

# set target base location
# this has to be set before the class library modules are pulled in
if(EXISTS ${CMAKE_SOURCE_DIR}/targets/ChibiOS/${TARGET_BOARD})
    # set target base location
    set(TARGET_BASE_LOCATION ${CMAKE_SOURCE_DIR}/targets/ChibiOS/${TARGET_BOARD} CACHE INTERNAL "make global")
else()
    # try to find board in the Community targets folder
    if(EXISTS ${CMAKE_SOURCE_DIR}/targets-community/ChibiOS/${TARGET_BOARD})
        # set target base location
        set(TARGET_BASE_LOCATION ${CMAKE_SOURCE_DIR}/targets-community/ChibiOS/${TARGET_BOARD} CACHE INTERNAL "make global")
    else()
        # board NOT found in targets folder
        # can't continue
        message(FATAL_ERROR "\n\nSorry but support for ${TARGET_BOARD} target is not available...\n\nYou can wait for that to be added or you might want to contribute and start working on a PR for that.\n\n")
    endif()
endif()

# set CMSIS RTOS include directory
include_directories( ${CMSIS_RTOS_INCLUDE_DIR})

# need to find board definition files (board.c and board.h)

# assume no community board... until proven otherwise
set(CHIBIOS_COMMUNITY_TARGET FALSE CACHE INTERNAL "Community target flag")

# start search in nanoFramework ChibiOS 'overlay' folder
if(EXISTS ${CMAKE_SOURCE_DIR}/targets/ChibiOS/_nf-overlay/os/hal/boards/${TARGET_BOARD})
    # board found
    # if it's on nF overlay board.c and board.h exist there for sure
    set(CHIBIOS_BOARD_DEFINITIONS_LOCATION "Board definition files taken from nanoFramework overlay" CACHE INTERNAL "Location of board definition files")
else()
    # board NOT found in ChibiOS 'overlay'

    # try to find it in the target boards
    if(EXISTS ${CMAKE_SOURCE_DIR}/targets/ChibiOS/${TARGET_BOARD})
        # board found
        # check if the board definition files are available at the target folder
        if( EXISTS ${CMAKE_SOURCE_DIR}/targets/ChibiOS/${TARGET_BOARD}/board.c AND
            EXISTS ${CMAKE_SOURCE_DIR}/targets/ChibiOS/${TARGET_BOARD}/board.h)
            # definition files found
            set(CHIBIOS_BOARD_DEFINITIONS_LOCATION "Board definition files taken from target folder" CACHE INTERNAL "Location of board definition files")

        else()
            # board.c and board.h are NOT in the target folder, try to find them in the official distribution

            if(EXISTS ${chibios_SOURCE_DIR}/os/hal/boards/${TARGET_BOARD})
                # board found
                # if it's on the ChibiOS official distribution board.c and board.h exist here for sure
                set(CHIBIOS_BOARD_DEFINITIONS_LOCATION "Board definition files taken from official ChibiOS distribution" CACHE INTERNAL "Location of board definition files")

            else()
                # board NOT found in official distribution
                # quit now as there is no were else to search for these
                message(FATAL_ERROR "\n\nSorry but couldn't find definition files for ${TARGET_BOARD} in the available list of ChibiOS supported boards...\n\n")

            endif()
        endif()

    else()
        # try to find board in the Community targets folder
        if(EXISTS ${CMAKE_SOURCE_DIR}/targets-community/ChibiOS/${TARGET_BOARD})
            # set flag for this being a community board
            set(CHIBIOS_COMMUNITY_TARGET TRUE CACHE INTERNAL "Community target flag")
        else()
            # board NOT found in official distribution
            # quit now as there is no were else to search for these
            message(FATAL_ERROR "\n\nSorry but couldn't find definition files for ${TARGET_BOARD} in the available list of ChibiOS supported boards...\n\n")
        endif()

    endif()

endif()

# (default is OFF so STM Cube package is NOT included)
option(STM32_CUBE_PACKAGE_REQUIRED "option to include STM Cube pcakge in the build")
if(STM32_CUBE_PACKAGE_REQUIRED)
    ProcessSTM32CubePackage()
endif()

# if support for SPIFFS is enabled add it to the build
if(NF_FEATURE_USE_SPIFFS)

    # check if SPIFFS_SOURCE was specified or if it's empty (default is empty)
    set(NO_SPIFFS_SOURCE TRUE)

    if(SPIFFS_SOURCE)
        if(NOT ${SPIFFS_SOURCE} STREQUAL "")
            set(NO_SPIFFS_SOURCE FALSE)
        endif()
    endif()

    if(NO_SPIFFS_SOURCE)
        # no SPIFFS source specified, download it from it's repo
        message(STATUS "SPIFFS source from from GitHub repo")

        FetchContent_Declare(
            spiffs
            GIT_REPOSITORY https://github.com/nanoframework/spiffs
            GIT_TAG "nf-build"
        )

    else()
        # SPIFFS source was specified

        # sanity check is source path exists
        if(EXISTS ${SPIFFS_SOURCE}/)
            message(STATUS "SPIFFS source from: ${SPIFFS_SOURCE}")

            FetchContent_Declare(
                spiffs
                GIT_REPOSITORY ${SPIFFS_SOURCE}
                GIT_TAG "nf-build"
            )

        else()
            message(FATAL_ERROR "Couldn't find SPIFFS source at ${SPIFFS_SOURCE}/")
        endif()

    endif()
    
    FetchContent_GetProperties(spiffs)
    FetchContent_Populate(spiffs)

    add_subdirectory(_spiffs)

endif()

# add target ChibiOS dirs
add_subdirectory(_Include)
add_subdirectory(_common)
add_subdirectory(_nanoBooter)
add_subdirectory(_nanoCLR)

# board folder will be added in main CMakeList
