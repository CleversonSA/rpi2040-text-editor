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
        inputbox_engine.cpp
        inputbox_engine.hpp
        keyboard_engine.cpp
        keyboard_engine.hpp
        menu_engine.cpp
        menu_engine.hpp
        msgbox_engine.cpp
        msgbox_engine.hpp
        splashbox_engine.cpp
        splashbox_engine.hpp
        text_engine.cpp
        text_engine.hpp
        textview_engine.cpp
        textview_engine.hpp
        video_engine.cpp
        video_engine.hpp
        console_video.cpp
        console_video.hpp
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

