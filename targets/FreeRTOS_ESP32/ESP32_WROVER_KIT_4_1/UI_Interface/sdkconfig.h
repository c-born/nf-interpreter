/*
 * Automatically generated file. DO NOT EDIT.
 * Espressif IoT Development Framework (ESP-IDF) Configuration Header
 */
#pragma once

 // The following #defines are referenced in cpu_start.c for various options.
 // These are not used.
 // GraphicsMemoryHeap.cpp will allocate/reallocate memory
 //
#define CONFIG_SPIRAM_SUPPORT 1
#define CONFIG_SPIRAM_BOOT_INIT 1  // esp_spiram_init_cache() called from cpu_start.c
#define CONFIG_SPIRAM_MEMTEST 1  // esp_spiram_test() called from cpu_start.c

#define CONFIG_SPIRAM_USE_CAPS_ALLOC 0 
#define CONFIG_SPIRAM_USE_MALLOC 0
#define CONFIG_SPIRAM_MALLOC_RESERVE_INTERNAL 0

// spiram_psram.c
#define CONFIG_SPIRAM_TYPE_ESPPSRAM32 1  // Set drive ability for 1.8v flash in 80Mhz.
#define CONFIG_BOOTLOADER_VDDSDIO_BOOST_1_9V 0  // For flash 80Mhz, we must update ldo voltage in case older version of bootloader didn't do this.

// spiram.c
#define CONFIG_SPIRAM_SPEED_80M 1 
#define CONFIG_SPIRAM_IGNORE_NOTFOUND 0

#define  CONFIG_SPIRAM_OCCUPY_SPI_HOST

#define  CONFIG_BOOTLOADER_VDDSDIO_BOOST_1_9V  // For flash 80Mhz, we must update ldo voltage in case older version of bootloader didn't do this.

//The SPI RAM can be accessed in multiple methods : by just having it available as an unmanaged
//memory region in the ESP32 memory map, by integrating it in the ESP32s heap as 'special' memory
//needing heap_caps_malloc to allocate, or by fully integrating it making malloc() also able to
//return SPI RAM pointers.

//config SPIRAM_USE_MEMMAP
//bool "Integrate RAM into ESP32 memory map"



//When used at 80 MHz clock speed, external RAM must also occupy either the HSPI or VSPI bus. 
//Select which SPI host will be used by CONFIG_SPIRAM_OCCUPY_SPI_HOST.


// ?????????
// To be checked what this means ?
//The bugs in this revision of silicon cause issues if certain sequences of machine instructions 
// operate on external memory. (ESP32 ECO 3.2). As a workaround, the GCC compiler received the 
// flag -mfix-esp32-psram-cache-issue to filter these sequences and only output the code that 
// can safely be executed. Enable this flag by checking CONFIG_SPIRAM_CACHE_WORKAROUND.

