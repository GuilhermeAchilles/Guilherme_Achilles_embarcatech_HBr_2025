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

project(unidade_2_seguranca_io C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(unidade_2_seguranca_io app/main_subscribe.c )

add_library(connections STATIC connections/wifi_control.c connections/mqtt_comm.c)
add_library(driver STATIC driver/ssd1306.c driver/ssd1306_i2c.c)
add_library(hal STATIC hal/write_display.c)

pico_set_program_name(unidade_2_seguranca_io "unidade_2_seguranca_io")
pico_set_program_version(unidade_2_seguranca_io "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(unidade_2_seguranca_io 0)
pico_enable_stdio_usb(unidade_2_seguranca_io 1)

# Add the standard library to the build
target_link_libraries(unidade_2_seguranca_io
        pico_stdlib
        connections
        hal)

target_link_libraries(connections
        pico_stdlib
        pico_cyw43_arch_lwip_threadsafe_background
        pico_lwip_mqtt
        pico_lwip_mqtt
        pico_cyw43_driver
        hal
        driver
)

target_link_libraries(hal
        pico_stdlib
        driver
        )

target_link_libraries(driver
        pico_stdlib
        hardware_i2c
        )

# Add the standard include files to the build
target_include_directories(unidade_2_seguranca_io PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_include_directories(connections PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_include_directories(hal PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_include_directories(driver PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

# Add any user requested libraries
target_link_libraries(unidade_2_seguranca_io 
        )

pico_add_extra_outputs(unidade_2_seguranca_io)

