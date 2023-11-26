set(tgt ${CMAKE_PROJECT_NAME})

add_executable(${tgt})

pico_generate_pio_header(${tgt} ${CMAKE_CURRENT_LIST_DIR}/counter.pio)
target_sources(${tgt} PRIVATE main.c)

pico_enable_stdio_usb(${tgt} 1)
pico_enable_stdio_uart(${tgt} 0)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${tgt})

target_link_libraries(${tgt} PRIVATE pico_stdlib hardware_pio)

#
# On chip debug configuration
#
find_program(OPENOCD_EXECUTABLE openocd)
if(OPENOCD_EXECUTABLE)
    add_custom_target(upload
        COMMAND ${OPENOCD_EXECUTABLE}
                -f interface/cmsis-dap.cfg
                -f target/rp2040.cfg
                -c 'adapter speed 5000'
                -c 'program $<TARGET_FILE:${tgt}> verify reset exit'
        DEPENDS ${tgt})
endif()

#
# Installation
#
install(TARGETS ${tgt} DESTINATION ${CMAKE_BUILD_TYPE})
install(FILES
    $<TARGET_FILE_DIR:${tgt}>/$<TARGET_NAME:${tgt}>.uf2
    DESTINATION ${CMAKE_BUILD_TYPE})
