
cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR} CACHE PATH "" FORCE)

set(PICO_SDK_PATH ${CMAKE_SOURCE_DIR}/pico-sdk)
set(PICO_PLATFORM rp2040)
set(PICO_BOARD pico)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-swm-ex26a C CXX ASM)
set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_compile_options(-Wall -Wextra $<$<CONFIG:RELEASE>:-Werror>)

add_subdirectory(src)
