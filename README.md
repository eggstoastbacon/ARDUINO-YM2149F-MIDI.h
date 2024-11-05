![Project Logo](ym2149f-logo.png) <!-- Logo soon -->

## Project Details

This project re-designs the hardware and software of the YM2149F for Arduino, inspired by Dansfing’s 2.1a version, which is driven by an ATMEGA328P chip and includes a CH430e TTL for USB programming. The original code was initially developed by Yukimizake, whose work inspired Dansfing. This version introduces several key changes:

- Relocates all user interface elements and inputs/outputs to the front of the board.
- Replaces the DIN5 connector with only 3.5mm TRS to conserve space.
- Adds more default sound presets.
- Reduces some larger samples to free up code space.
- Introduces MIDI-responsive velocity and pitch bend, with plans to support envelope control.
- Simplifies the process for converting and adding new samples.
- Backwards compatibility with Dansfing 2.1a minus the display board.
- Functional orientation will be horizontal.
- 3D printed bottom shell (will be open source when it is done).
- Open source board gerber (coming soon).
- Parts list (coming soon).
- All chips should be socketed for easy replacement.

## Project History

I first discovered the YM2149F through one of my favorite musicians and YouTube creators, Lab Rat Warfare. My first hardware build was the Dansfing 'Arduino USB MIDI YM2149F,' and I instantly fell in love with its sound. Inspired by Dansfing’s robust hardware and software design, I decided to create my own layout based on the Dansfing 2.1a version of the code and schematics. This re-design is a tribute to Dansfing’s solid work, which sounds fantastic and sparked my passion for the YM2149F.

## Project Goals

This project aims to create a plug-and-play YM2149F interface with as many direct MIDI controls as possible, including velocity, pitch, and envelope adjustments. The code will be detailed to allow others to modify existing sounds or create their own from scratch. I want users to be able to create and import custom sound samples easily. I may also add an OLED display, similar to Dansfing’s setup. I've included much of the code and hardware connections needed for the display, just in case it’s added in the future.

## YM2149F Hardware Description

The YM2149F is an audio chip designed by Yamaha in the late 1970s, based on the AY-3-8910 sound chip from General Instrument. It was widely used in various 8-bit and 16-bit computers, consoles, and arcade machines, including the Atari ST, Amstrad CPC, and MSX series, due to its affordability and versatility for creating synthesized sounds.

- 3 Sound Channels: The YM2149F has three independent square wave generators, allowing it to produce three distinct tones simultaneously. Each channel can be independently controlled in terms of frequency and volume.

- Noise Generation: The chip includes a noise generator, which can be mixed with any of the three channels. This allows for the creation of percussion sounds and sound effects like explosions and engine noises.

- Programmable Volume Levels: Each channel has 16 levels of volume control, allowing dynamic adjustment of sound intensity.

- Envelope Generator: The YM2149F features an envelope generator that can apply varying shapes to control the amplitude of sounds over time. There are 16 envelope shapes that produce effects like fades, pulses, and sustained sounds, adding depth to the sound produced.

- Frequency Range: Each sound channel can be set to different frequencies, supporting a range of pitches that allow for the simulation of various musical notes.

- Compact Design: Its small form factor and relatively low power consumption made it a popular choice for compact and portable devices in the 1980s.

Registers: The YM2149F is controlled through a set of registers. Different registers control the tone frequency, volume, noise, and envelope for each channel.
Clock Frequency: The chip typically operates at a clock frequency around 2 MHz, which is then divided internally to produce sound frequencies.
Control Interface: It uses a simple data and address bus interface, making it relatively easy to integrate with microprocessors for real-time sound control.

## Installation

'ARDUINO-YM2149.ino' - for the hardware:

1. Clone this repository.
2. Connect the USB-C cable to your computer and use the Arduino IDE set to Arduino Uno to program the chip with the .ino file.

'ym2149-wave.py' - creating your own samples:

1. Prepare a short WAV sample using a program like Audacity.
2. Modify the 'path to .wav' in the script to point to the location of your .wav file.
3. Run the Python script and copy the output.

The script will generate 'PROGMEM const char' values and 'const int' length values for YM2149 code samples. You can paste these over existing values or create new ones. Keep in mind that samples must be short due to limited space.
The code size cannot exceed 31.5 KB, the maximum code space for the ATMEGA328P.

## Usage

The code includes detailed comments to help you create custom presets. Code related to sound presets can be found in the playNote and stopNote sections, both of which need to be configured for each sound preset.

## Features

- **MIDI TRS**: MIDI IN and MIDI Thru via 3.5mm TRS ports, with MIDI Thru available on all 16 MIDI channels.

- **14 Presets**: Each MIDI channel up to Channel 14 has its own dedicated preset.

- **3 Voice Polyphonic**: Three voice channels can play simultaneously as long as they’re assigned to separate registers. For example, MIDI Channels 1-3 share the same preset but operate on different voice channels, allowing all three to play at once.

- **Velocity**: Velocity sensitivity is implemented for MIDI Channels 1-4. (Use the example to add it to other channels as needed.)

- **Pitch Bend**: Pitch bend is supported on all channels except Channel 10 (sample channel).

- **4 bit Samples**: Includes five short drum samples on MIDI Channel 10, with an option to add or replace them using the included Python script.

- **Programming and MIDI Mode**: Use the toggle switch to switch between MIDI mode and programming mode. Programming mode is for flashing new code.

## Presets (Each preset is on a different MIDI Channel)

- CH. 1: Voices 1 **Voice(A)** (MIDI velocity enabled): **Default Voice**, Ch. 1-3 can be played concurrently.
- CH. 2: Voices 1 **Voice(A)** (MIDI velocity enabled): **Default Voice**, Ch. 1-3 can be played concurrently.
- CH. 3: Voices 1 **Voice(A)** (MIDI velocity enabled): **Default Voice**, Ch. 1-3 can be played concurrently.
- CH. 4: Voices 2 **Voices(A and B)** (MIDI velocity enabled): **Gritty / Modulated**, Can be played concurrently with any preset with voices on (C).
- CH. 5: Voices 3 **Voices(A, B and C)** (No MIDI velocity): **Gritty / Modulated**, Cannot be played concurrently with other presets.
- CH. 6: Voices 1 **Voice(A)** (No MIDI velocity): **Gritty / Horn-Like / Modulated**, Can be played concurrently with any preset with voices on (B and C).
- CH. 7: Voices 1 **Voice(A)** (No MIDI velocity): **Gritty / Detuned**, Can be played concurrently with any preset with voices on (B and C).

## Contacts and Resources

Discord: https://discord.gg/32wfnbkCtE

Dansfing's builds and code: https://dansfing.uk

Dansfing USB MIDI YM2149, simple to build. (You may be able to get a pre-built USB MIDI for sale from Dansfing): https://dansfing.uk/ym2149f.php

Yukimizake build and code: https://electronicfields.wordpress.com/2012/04/09/ym2149-sound-generator-arduino-fast-pin-switching

Lab Rat Warfare: https://www.youtube.com/@LabRatWarfare
