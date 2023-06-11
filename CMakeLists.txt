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
        main.cpp
        app_globals.cpp
        app_globals.hpp
        csa_object.cpp
        csa_object.hpp
        framebuffer.cpp
        framebuffer.hpp
        doc_character.cpp
        doc_character.hpp
        doc_row.cpp
        doc_row.hpp
        document.cpp
        document.hpp
        document_engine.cpp
        document_engine.hpp
        widget_engine.cpp
        widget_engine.hpp
        widget_callback.cpp
        widget_callback.hpp
        inputbox_keyboard_callback.cpp
        inputbox_keyboard_callback.hpp
        inputbox_sample_callback.cpp
        inputbox_sample_callback.hpp
        inputbox_engine.cpp
        inputbox_engine.hpp
        keyboard_engine.hpp
        keyboard_engine.cpp
        keyboard_callback.hpp
        keyboard_message.cpp
        keyboard_message.hpp
        keyboard_callback.cpp
        menu_keyboard_callback.cpp
        menu_keyboard_callback.hpp
        menu_sample_callback.cpp
        menu_sample_callback.hpp
        menu_engine.cpp
        menu_engine.hpp
        msgbox_engine.hpp
        msgbox_keyboard_callback.cpp
        msgbox_keyboard_callback.hpp
        msgbox_sample_callback.cpp
        msgbox_sample_callback.hpp
        msgbox_engine.cpp
        splashbox_engine.cpp
        splashbox_engine.hpp
        textview_keyboard_callback.cpp
        textview_keyboard_callback.hpp
        text_engine.cpp
        text_engine.hpp
        textview_engine.cpp
        textview_engine.hpp
        video_engine.cpp
        video_engine.hpp
        lcd4x20_inputbox.cpp
        lcd4x20_inputbox.hpp
        lcd4x20_menu.cpp
        lcd4x20_menu.hpp
        lcd4x20_msgbox.cpp
        lcd4x20_msgbox.hpp
        lcd4x20_splashbox.cpp
        lcd4x20_splashbox.hpp
        lcd4x20_textview.cpp
        lcd4x20_textview.hpp
        console_video.cpp
        console_video.hpp
        vt100_utils.cpp
        vt100_utils.hpp
        rpi2040_uart.cpp
        rpi2040_uart.hpp
        rpi2040_uart_keyboard.cpp
        rpi2040_uart_keyboard.hpp
        rpi2040_uart_video.cpp
        rpi2040_uart_video.hpp

        )
foreach(name IN ITEMS main)
    add_executable(${name} ${SOURCES})
    pico_enable_stdio_uart(${name} 1)
    pico_enable_stdio_usb(${name} 0)
    #target_link_libraries(${name} PRIVATE pico_stdlib littlefs-lib stdinit-lib)
    target_link_libraries(${name} PRIVATE pico_stdlib)
    pico_add_extra_outputs(${name})
endforeach()
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

