set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_SIZE arm-none-eabi-size)

set(CMAKE_EXECUTABLE_SUFFIX ".elf")
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

add_compile_options(
    -mthumb
    -mcpu=cortex-m4
    -mfloat-abi=hard
    -mfpu=fpv4-sp-d16
    -ffunction-sections
    -fdata-sections
    -specs=nosys.specs
    -specs=nano.specs
)

function(gcc_generate_bin_file)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs)
    cmake_parse_arguments(GEN_BIN "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    
    add_custom_command(
        TARGET ${GEN_BIN_TARGET}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Generating flash image ${GEN_BIN_TARGET}.bin"
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${GEN_BIN_TARGET}> ${GEN_BIN_TARGET}.bin
        BYPRODUCTS ${GEN_BIN_TARGET}.bin
    )
endfunction()
