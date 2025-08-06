#-- Service --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.18)
SET(CMAKE_TOOLCHAIN_FILE gcc_cm4f.cmake)
set(PROJECT_NAME K19xxVK035_AM32)
project(${PROJECT_NAME} C CXX ASM)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#-- Project config -------------------------------------------------------------

PROJECT(template)                   # Project name
SET(MCUNAME         K1921VK035)     # MCU name
SET(OSECLK_VAL      0)              # OSECLK value in Hz (0 if disconnected)
SET(SYSCLK          PLL)            # SYSCLK source: PLL, OSI, OSE
SET(CKO             NONE)           # Clockout source: PLL, OSI, OSE, NONE (no clockout)
SET(RETARGET        0)              # Enable(1) or disable(0) printf retarget
SET(RETARGET_USE    UART)           # ITM or UART printf retarget
SET(PRINTF_FLOAT    0)              # Enable(1) or disable(0) printf float support
SET(SCANF_FLOAT     0)              # Enable(1) or disable(0) scanf float support

#-- Defines --------------------------------------------------------------------

ADD_DEFINITIONS(-D${MCUNAME})
ADD_DEFINITIONS(-DOSECLK_VAL=${OSECLK_VAL})
ADD_DEFINITIONS(-DSYSCLK_${SYSCLK})
ADD_DEFINITIONS(-DCKO_${CKO})

#-- Project paths --------------------------------------------------------------

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
add_library(SOURCES INTERFACE)
add_library(BOOTLOADER INTERFACE)
include(${CMAKE_CURRENT_SOURCE_DIR}/arm-gcc-toolchain.cmake)
#-- Include dirs ---------------------------------------------------------------

#add_subdirectory(platform)

target_include_directories(SOURCES
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Inc
        ${CMAKE_SOURCE_DIR}/Mcu/K19XXVK035/Inc
        ${CMAKE_CURRENT_SOURCE_DIR}/Platform/CMSIS/Core/Include/
        ${CMAKE_CURRENT_SOURCE_DIR}/Platform/Device/NIIET/K1921VK035/Include/
        ${CMAKE_CURRENT_SOURCE_DIR}/Platform/plib/inc/
)

target_sources(SOURCES
    INTERFACE
        Src/main.c
        Mcu/K19XXVK035/Src/ADC.c
        Mcu/K19XXVK035/Src/comparator.c
        Mcu/K19XXVK035/Src/eeprom.c
        Mcu/K19XXVK035/Src/IO.c
        Mcu/K19XXVK035/Src/phaseouts.c
        Mcu/K19XXVK035/Src/serial_telemetry.c
        Mcu/K19XXVK035/Src/K19xxVK035_it.c
        Mcu/K19XXVK035/Src/peripherals.c
        Src/dshot.c
        Src/firmwareversion.c
        Src/functions.c
        Src/signal.c
        Src/sounds.c

        Inc/common.h
        Inc/crsf.h
        Inc/dshot.h
        Inc/firmwareversion.h
        Inc/functions.h
        Inc/signal.h
        Inc/sounds.h
        Inc/targets.h

        Mcu/K19XXVK035/Inc/ADC.h
        Mcu/K19XXVK035/Inc/comparator.h
        Mcu/K19XXVK035/Inc/eeprom.h
        Mcu/K19XXVK035/Inc/IO.h
        Mcu/K19XXVK035/Inc/main.h
        Mcu/K19XXVK035/Inc/peripherals.h
        Mcu/K19XXVK035/Inc/phaseouts.h
        Mcu/K19XXVK035/Inc/serial_telemetry.h
        Mcu/K19XXVK035/Inc/version.h
        Mcu/K19XXVK035/Inc/WS2812.h
        Mcu/K19XXVK035/Inc/K19xxVK035_it.h
        
        Platform/CMSIS/Core/Include/cmsis_armcc.h
        Platform/CMSIS/Core/Include/cmsis_armclang.h
        Platform/CMSIS/Core/Include/cmsis_cmcpp.h
        Platform/CMSIS/Core/Include/cmsis_compiler.h
        Platform/CMSIS/Core/Include/cmsis_gcc.h
        Platform/CMSIS/Core/Include/cmsis_iccarm.h
        Platform/CMSIS/Core/Include/cmsis_version.h
        Platform/CMSIS/Core/Include/core_cm4.h
        Platform/CMSIS/Core/Include/mpu_armv7.h
        Platform/Device/NIIET/K1921VK035/Include/K1921VK035.h
        Platform/Device/NIIET/K1921VK035/Include/system_K1921VK035.h
        Platform/Device/NIIET/K1921VK035/Source/system_K1921VK035.c
        Platform/Device/NIIET/K1921VK035/Source/GCC/startup_K1921VK035.S

        Platform/plib/src/plib035_adc.c
        Platform/plib/src/plib035_can.c
        Platform/plib/src/plib035_dma.c
        Platform/plib/src/plib035_ecap.c
        Platform/plib/src/plib035_gpio.c
        Platform/plib/src/plib035_i2c.c
        Platform/plib/src/plib035_mflash.c
        Platform/plib/src/plib035_pmu.c
        Platform/plib/src/plib035_pwm.c
        Platform/plib/src/plib035_qep.c
        Platform/plib/src/plib035_rcu.c
        Platform/plib/src/plib035_spi.c
        Platform/plib/src/plib035_tmr.c
        Platform/plib/src/plib035_uart.c
        Platform/plib/src/plib035_wdt.c

        Platform/plib/inc/plib035.h
        Platform/plib/inc/plib035_adc.h
        Platform/plib/inc/plib035_assert.h
        Platform/plib/inc/plib035_can.h
        Platform/plib/inc/plib035_conf.h
        Platform/plib/inc/plib035_dma.h
        Platform/plib/inc/plib035_ecap.h
        Platform/plib/inc/plib035_gpio.h
        Platform/plib/inc/plib035_i2c.h
        Platform/plib/inc/plib035_mflash.h
        Platform/plib/inc/plib035_pmu.h
        Platform/plib/inc/plib035_pwm.h
        Platform/plib/inc/plib035_qep.h
        Platform/plib/inc/plib035_rcu.h
        Platform/plib/inc/plib035_spi.h
        Platform/plib/inc/plib035_tmr.h
        Platform/plib/inc/plib035_uart.h
        Platform/plib/inc/plib035_version.h
        Platform/plib/inc/plib035_wdt.h
)


#-- Options --------------------------------------------------------------------

# target_link_libraries(SOURCES
# INTERFACE
#     K1921VK035_SDK
# )

#-- Linker script --------------------------------------------------------------

set(LDSCRIPT_NO_BOOTLOADER "${CMAKE_SOURCE_DIR}/platform/Device/NIIET/K1921VK035/Source/GCC/K1921VK035_no_bootloader.ld")
set(LDSCRIPT_WITH_BOOTLOADER "${CMAKE_SOURCE_DIR}/platform/Device/NIIET/K1921VK035/Source/GCC/K1921VK035_bootloader.ld")
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LDSCRIPT} -Wl,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map -Wl,--print-memory-usage")

target_compile_definitions(SOURCES INTERFACE 
    #__NO_SYSTEM_INIT
    NO_BOOTLOADER
)

target_compile_definitions(BOOTLOADER INTERFACE 
    #__NO_SYSTEM_INIT
)

add_executable(1.0.0_no_bootloader)
target_link_libraries(1.0.0_no_bootloader SOURCES m)
gcc_generate_bin_file(TARGET 1.0.0_no_bootloader)
target_link_options(1.0.0_no_bootloader PRIVATE
    -T "${LDSCRIPT_NO_BOOTLOADER}"
    -Wl,-Map=${CMAKE_BINARY_DIR}/1.0.0_no_bootloader.map
    -Wl,--print-memory-usage
)
set_target_properties(1.0.0_no_bootloader PROPERTIES SUFFIX ".elf")

add_executable(1.0.0_bootloader)
target_link_libraries(1.0.0_bootloader SOURCES BOOTLOADER m)
gcc_generate_bin_file(TARGET 1.0.0_bootloader)
target_link_options(1.0.0_bootloader PRIVATE
    -T "${LDSCRIPT_WITH_BOOTLOADER}"
    -Wl,-Map=${CMAKE_BINARY_DIR}/1.0.0_bootloader.map
    -Wl,--print-memory-usage
)
set_target_properties(1.0.0_bootloader PROPERTIES SUFFIX ".elf")