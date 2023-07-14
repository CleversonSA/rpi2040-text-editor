# Raspberry PI Pico 2040 "bare metal" text editor

Just a simple "bare metal" text editor for microcontroller (at this moment, Raspberry PI PICO 2040)

## Description

A simple project to create a text file editor for Raspberry PI Pico 2040 using serial or character LCD module (mine one is 20x40).

It´s not a Word processing (may be in future), because the PICO´s limitation, but It´s fun to build a text editor without a OS, that could operate on batteries, using a custom serial or USB Keyboard 

## Getting Started

### Dependencies

* You have to install de RPI Pico 2040 SDK in order to compile this project, I´ve used Windows 10 + Codeblocks + MinGW with a toolchain compiler

### Installing

* The application is in alpha stage. If you wanna check just for fun, all you need is a:

  
    1) Press BOOTSEL button on RPi Pico and upload to it the most recent file at "dist" dir (rpi2040_text_editor[...].uf2)
       

### Diagram for LCD 20x4

* This my actual setup for development at the breadboard. All you need is:
  
    1) Protoboard
    2) Raspberry PI PICO 2040 or Raspberry PI PICO 2040 W
    3) i2c Character LCD Driver board
    4) 20x4 Character LCD
    5) 4 x LEDs
    6) 4 x 220ohm resistor
    7) USB OTG Cable to connect keyboard
    8) External 5V power supply

![Alt text](/designs/lcd20x4_diagram.png?raw=true "Prototype wiring")

## Project Updates

* Checkout at my social media:
  1) Youtube channel: https://www.youtube.com/channel/UCeoMaWQm1lrNSY18bQhTeig
  2) Instagram: @pu5tos

## Authors

Contributors names and contact info

    - Cleverson S A (@pu5tos)

## License

This project is licensed under the APACHE 2.0 License - see the LICENSE.md file for details

