# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(teste_unitario_temperatura C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Adicione as bibliotecas
add_library(drivers STATIC
    drivers/temperature_sensor.c)

add_library(hal STATIC
    hal/ler_temperatura.c)

# Adicione o executável principal
add_executable(teste_unitario_temperatura app/main.c)

# Defina o executável de testes
add_library(run_tests 
    test/test_hal_temperature.c
    src/unity.c)

# Inclua os diretórios
include_directories(include src)

# Configure o programa principal
pico_set_program_name(teste_unitario_temperatura "teste_unitario_temperatura")
pico_set_program_version(teste_unitario_temperatura "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(teste_unitario_temperatura 0)
pico_enable_stdio_usb(teste_unitario_temperatura 0)

# Vincule as bibliotecas ao programa principal
target_link_libraries(teste_unitario_temperatura
    pico_stdlib
    hardware_adc
    drivers
    hal
)

# Vincule as bibliotecas ao executável de testes
target_link_libraries(run_tests
    hal
)

# Configure as dependências das bibliotecas
target_link_libraries(drivers
    PUBLIC
    pico_stdlib      # fornece o include de <pico/stdlib.h>, clocks etc.
    hardware_adc     # fornece o include de <hardware/adc.h>
    hal
)

# Adicione os includes padrão ao build
target_include_directories(teste_unitario_temperatura PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(run_tests PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Adicione configurações extras para o Pico
pico_add_extra_outputs(teste_unitario_temperatura)