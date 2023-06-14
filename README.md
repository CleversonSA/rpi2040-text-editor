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

* I´ll write better when I have a beta version

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
