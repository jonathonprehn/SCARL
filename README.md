# SCARL
Specialized Robotics and Computing Language

The Specialized Robotics and Computing Language (SCARL) is a small language that is meant
to separate the logic of robot programming with the physical configuration of the device.
I am using it as a project to understand compiler design and implementation.

It is still early in development. At the moment, SCARL can compile to an intermediate
language called the Abstract Robot Control Language (ARCL). This can be executed by
the ARCL Virtual Machine (ARCLVM).

## Usage

SCARL is written in .srl files. See the SCARL_Grammar PDF for the grammar. To compile:

    scarlcompile file.srl -o file.rcl

ARCL code is placed in .rcl files. To link the ARCL code, you need a .dmap (mappings)
file that specifies the platform and the pins that devices are connected to (see examples).
Link a file with

    scarllink mappings.dmap file.rcl -o linked_file.rcl

Then execute linked files with the ARCLVM:

    arclvm linked_file.rcl

At the moment we can only compile and link to ARCL code, working on compiling/linking
to Atmel's AVR Assembler so it can execute on an Arduino.
