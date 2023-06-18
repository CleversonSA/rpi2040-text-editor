# Raspberry PI Pico 2040 "bare metal" text editor

A simple, almost "bare metal" plain file text editor for Raspberry PI PICO 2040.

## Description

A simple project to create a text file editor for Raspberry PI Pico 2040 using serial or character LCD module (mine one is 20x40).

It´s not a Word processing (may be in future), because the PICO´s limitation, but It´s fun to build a text editor without a OS, that could operate on batteries, using a custom serial or USB Keyboard (future yet).

It´s in alpha stages yet, a lot of bugs, but I´ll improve this project in my spare time. The whole project has:

- Text file I/O logic architeture layer
- Widgets architeture layer (yes, msgbox, inputbox, textview, splashview, menus...to use with serial or a LCD or VGA, maybe).
- Keyboard architeture layer(I could use serial, usb, or implement a PS/2 keyboard support, even a custom one).
- Framebuffer render architeture layer (I could output the screen in serial or console, LCD, in future).
-

## Getting Started

### Dependencies

* You have to install de RPI Pico 2040 SDK in order to compile this project, I´ve used Windows 10 + Codeblocks + MinGW with a toolchain compiler

### Installing

* The application is in alpha stage. If you wanna check just for fun, all you need is a:

    - RPI 2040 board (with or wihout wifi, does not matter).
    - A USB-Serial dongle
    - Putty terminal (Windows) or stty (Linux/MAX)

    1) Press BOOTSEC button on RPi Pico and upload to it the most recent file at "dist" dir (rpi2040_text_editor_x.x.x.uf2)
    2) Wire TX/RX/GND pins of UART 1 of Rpi Board to the USB-Serial dongle (beware the voltage, Rpi Pico is 3.3v only, with my generic dongle, I have no problems with voltage, but you could use a bidirectional logic converter (5v-3.3v) for more security)
    3) Open terminal app and set baud rate to 115200 (VT100 style compatible)
    4) Turn on the RPi and a editor window will be rendered
    5) Type and fun.

## Help

Any advise for common problems or issues.
```
command to run if program contains helper info
```

## Authors

Contributors names and contact info

ex. Cleverson S A
ex. @pu5tos

## Version History

* 0.5.3
    * Basic of basic text editing, no saving, serial UART only
    * See [commit change]() or See [release history]()
* 0.1
    * Initial Release

## License

This project is licensed under the APACHE 2.0 License - see the LICENSE.md file for details

## Acknowledgments

Inspiration, code snippets, etc.
