cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)
set(PROJ_PATH                       ${CMAKE_CURRENT_SOURCE_DIR})
message("Build type: "              ${CMAKE_BUILD_TYPE})

#
# Core project settings
#
project(sample-project)
enable_language(C CXX ASM)

#
# Core MCU flags, CPU, instruction set and FPU setup
# Needs to be set properly for your MCU
#
set(CPU_PARAMETERS
    -mthumb

    # This needs attention to properly set for used MCU
    -mcpu=cortex-m0plus
    -mfloat-abi=soft
)

# Set linker script
set(linker_script_SRC               ${PROJ_PATH}/STM32G071G8UXN_FLASH.ld)
set(EXECUTABLE                      ${CMAKE_PROJECT_NAME})

#
# List of source files to compile
#
set(sources_SRCS
    ${PROJ_PATH}/Core/Src/gpio.c 
    ${PROJ_PATH}/Core/Src/main.c 
    ${PROJ_PATH}/Core/Src/stm32g0xx_it.c 
    ${PROJ_PATH}/Core/Src/syscalls.c 
    ${PROJ_PATH}/Core/Src/sysmem.c 
    ${PROJ_PATH}/Core/Src/system_stm32g0xx.c

    ${PROJ_PATH}/Core/Startup/startup_stm32g071g8uxn.s

    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_exti.c 
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_utils.c 
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_rcc.c 
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_pwr.c 
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Src/stm32g0xx_ll_gpio.c
)

#
# Include directories
#
set(include_path_DIRS
    ${PROJ_PATH}/Core/Inc
    ${PROJ_PATH}/Drivers/STM32G0xx_HAL_Driver/Inc
    ${PROJ_PATH}/Drivers/CMSIS/Include
    ${PROJ_PATH}/Drivers/CMSIS/Device/ST/STM32G0xx/Include
)

#
# Symbols definition
#
set(symbols_SYMB
"DEBUG"
"STM32G071xx"   # MCU family
"USE_FULL_LL_DRIVER"
"HSE_VALUE=16000000" #external crystal frequency (in Hz)
)

# Executable files
add_executable(${EXECUTABLE} ${sources_SRCS})

# Include paths
target_include_directories(${EXECUTABLE} PRIVATE ${include_path_DIRS})

# Project symbols
target_compile_definitions(${EXECUTABLE} PRIVATE ${symbols_SYMB})

# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    # Full debug configuration
    -Og -g3 -ggdb
)

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
    -T${linker_script_SRC}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    --specs=nosys.specs
    -u _printf_float                # STDIO float formatting support
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -lsupc++
    -Wl,--end-group
    -Wl,--print-memory-usage
)

# Execute post-build to print size
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
)

# Convert output to hex and binary
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
)

# Convert to bin file -> add conditional check?
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin
)