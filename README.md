# libdsmi

This is a fork of 0xtob's DSMI library, providing MIDI support for the DS.

The following communication methods are supported:

- DSerial Edge
- Wireless access point (via DSMIDIWiFi)

This version of libdsmi is maintained for the [BlocksDS](https://blocksds.github.io/docs/) toolchain; a [devkitARM](https://devkitpro.org/) version 
is available on the `devkitARM` branch.

## Building the server

Install Meson and Qt6 (qt6-base), then:

    $ meson setup build
    $ cd build
    $ ninja
