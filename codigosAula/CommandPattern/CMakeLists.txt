set(ENV{ZEPHYR_BASE} /home/rodrigopex/MEGA/Venus/Projects/zephyr)
set(ENV{ZEPHYR_TOOLCHAIN_VARIANT} zephyr)
set(ENV{ZEPHYR_SDK_INSTALL_DIR} /home/rodrigopex/Tools/zephyr-sdk)

set(BOARD "bbc_microbit")

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(Display)

#message(WARNING "Main file: ${PROJECT_SOURCE_DIR}/src/main.c")

option(CONFIG_ASSERT "Enable assert feature." ON)
if(CONFIG_ASSERT)
    message(WARNING "
        ------------------------------------------------------------
        --- WARNING:  ASSERT() statements are ENABLED            ---
        --- The system will run more slowly and use more memory  ---
        ------------------------------------------------------------
        ")
    add_definitions(-D ASSERT_ENABLED)
endif()


include_directories(
    "${PROJECT_SOURCE_DIR}/include"
    )

list(APPEND SOURCES
    "${PROJECT_SOURCE_DIR}/src/uart_driver.c"
    "${PROJECT_SOURCE_DIR}/src/main.c"
    )

target_sources(app PRIVATE ${SOURCES})
