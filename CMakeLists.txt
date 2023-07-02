cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(skizi C CXX ASM)
pico_sdk_init()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPICO_USE_MALLOC_MUTEX=1")
#add_subdirectory(littlefs-lib)
#add_subdirectory(stdinit-lib)
set(SOURCES
        tusb_config.h
        rpi2040_sdk/hid_app.cpp
        main.cpp
        app_globals.cpp
        app_globals.hpp
        csa_object.cpp
        csa_object.hpp
        video/framebuffer.cpp
        video/framebuffer.hpp
        document/doc_character.cpp
        document/doc_character.hpp
        document/doc_row.cpp
        document/doc_row.hpp
        document/document.cpp
        document/document.hpp
        engine/document_engine.cpp
        engine/document_engine.hpp
        engine/widget_engine.cpp
        engine/widget_engine.hpp
        engine/widget_callback.cpp
        engine/widget_callback.hpp
        keyboard/inputbox_keyboard_callback.cpp
        keyboard/inputbox_keyboard_callback.hpp
        engine/inputbox_engine.cpp
        engine/inputbox_engine.hpp
        engine/keyboard_engine.hpp
        engine/keyboard_engine.cpp
        keyboard/keyboard_callback.hpp
        keyboard/keyboard_message.cpp
        keyboard/keyboard_message.hpp
        keyboard/keyboard_callback.cpp
        keyboard/menu_keyboard_callback.cpp
        keyboard/menu_keyboard_callback.hpp
        engine/menu_engine.cpp
        engine/menu_engine.hpp
        engine/msgbox_engine.hpp
        keyboard/msgbox_keyboard_callback.cpp
        keyboard/msgbox_keyboard_callback.hpp
        engine/msgbox_engine.cpp
        engine/splashbox_engine.cpp
        engine/splashbox_engine.hpp
        keyboard/textview_keyboard_callback.cpp
        keyboard/textview_keyboard_callback.hpp
        keyboard/textengine_keyboard_callback.cpp
        keyboard/textengine_keyboard_callback.hpp
        engine/text_render_engine.cpp
        engine/text_render_engine.hpp
        engine/text_persistence_engine.cpp
        engine/text_persistence_engine.hpp
        rpi2040/rpi2040_text_engine.cpp
        rpi2040/rpi2040_text_engine.hpp
        engine/textview_engine.cpp
        engine/textview_engine.hpp
        engine/video_engine.cpp
        engine/video_engine.hpp
        widgets/lcd4x20_inputbox.cpp
        widgets/lcd4x20_inputbox.hpp
        widgets/lcd4x20_menu.cpp
        widgets/lcd4x20_menu.hpp
        widgets/lcd4x20_msgbox.cpp
        widgets/lcd4x20_msgbox.hpp
        widgets/lcd4x20_splashbox.cpp
        widgets/lcd4x20_splashbox.hpp
        widgets/lcd4x20_textview.cpp
        widgets/lcd4x20_textview.hpp
        video/console_video.cpp
        video/console_video.hpp
        utils/vt100_utils.cpp
        utils/vt100_utils.hpp
        rpi2040/rpi2040_uart.cpp
        rpi2040/rpi2040_uart.hpp
        rpi2040/rpi2040_uart_keyboard.cpp
        rpi2040/rpi2040_uart_keyboard.hpp
        rpi2040/rpi2040_uart_video.cpp
        rpi2040/rpi2040_uart_video.hpp
        rpi2040/rpi2040_usb_keyboard.cpp
        rpi2040/rpi2040_usb_keyboard.hpp
        littlefs/lfs.c
        littlefs/lfs.h
        littlefs/lfs_util.c
        littlefs/lfs_util.h
        engine/disk_engine.h
        engine/disk_engine.cpp
        rpi2040/rpi2040_disk_engine.hpp
        rpi2040/rpi2040_disk_engine.cpp
        )
foreach(name IN ITEMS main)
    add_executable(${name} ${SOURCES})
    pico_enable_stdio_uart(${name} 1)
    pico_enable_stdio_usb(${name} 0)
    #target_link_libraries(${name} PRIVATE pico_stdlib littlefs-lib stdinit-lib)
    target_link_libraries(${name} PRIVATE
            pico_stdlib
            tinyusb_host
            tinyusb_board
            hardware_flash
            )
    target_include_directories(main PRIVATE ${CMAKE_CURRENT_LIST_DIR})
    pico_add_extra_outputs(${name})
endforeach()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

