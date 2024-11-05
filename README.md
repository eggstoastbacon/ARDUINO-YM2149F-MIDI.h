# YM2149F ARDUINO

![Project Logo](link-to-logo) <!-- Logo soon -->

## Hardware Description

The YM2149F is an audio chip designed by Yamaha in the late 1970s, based on the AY-3-8910 sound chip from General Instrument. It was widely used in various 8-bit and 16-bit computers, consoles, and arcade machines, including the Atari ST, Amstrad CPC, and MSX series, due to its affordability and versatility for creating synthesized sounds.

### Key Features
- 3 Sound Channels: The YM2149F has three independent square wave generators, allowing it to produce three distinct tones simultaneously. Each channel can be independently controlled in terms of frequency and volume.

- Noise Generation: The chip includes a noise generator, which can be mixed with any of the three channels. This allows for the creation of percussion sounds and sound effects like explosions and engine noises.

- Programmable Volume Levels: Each channel has 16 levels of volume control, allowing dynamic adjustment of sound intensity.

- Envelope Generator: The YM2149F features an envelope generator that can apply varying shapes to control the amplitude of sounds over time. There are 16 envelope shapes that produce effects like fades, pulses, and sustained sounds, adding depth to the sound produced.

- Frequency Range: Each sound channel can be set to different frequencies, supporting a range of pitches that allow for the simulation of various musical notes.

- Compact Design: Its small form factor and relatively low power consumption made it a popular choice for compact and portable devices in the 1980s.

### Technical Details
Registers: The YM2149F is controlled through a set of registers. Different registers control the tone frequency, volume, noise, and envelope for each channel.
Clock Frequency: The chip typically operates at a clock frequency around 2 MHz, which is then divided internally to produce sound frequencies.
Control Interface: It uses a simple data and address bus interface, making it relatively easy to integrate with microprocessors for real-time sound control.

## Installation

'ARDUINO-YM2149.ino' - for the hardware
1. Clone this repository
2. Plug USB-C into a computer and with Arduino IDE set to Arduino Uno program the chip with the .ino file.

'ym2149-wave.py' creating your own samples
1. Prepare a short wave sample in a program like Audacity.
2. Edit the 'path to .wav' to point to the path of your .wav file.
3. Run the python script and copy paste the output

Outputs 'PROGMEM const char' values and 'const int' length value for YM2149 code samples. Paste over existing values or create new ones. Samples must be short as space is limited.

## Usage

The code has several comments to assist in creating your own presets. Code related to sound presets are located under playNote and stopNote sections. Both must be configured for each sound.

## Features

- **MIDI TRS**: MIDI IN and MIDI Thru by way of 3.5mm TRS ports. Midi Thru on all 16 MIDI channels.

- **14 Presets**: There is 1 preset for each MIDI Channel up to Channel 14.

- **3 Voice Polyphonic**: You can use 3 voice channels at once as long as all 3 are on different registers. For example MIDI Channels 1-3 all use the same preset but are on different voice channels and all 3 can be played concurrently.
- **Velocity**: Velocity is implimented for MIDI Ch. 1-4.

- **Pitch Bend**: All channels except ch 10. (samples) respond to pitch bend.

- **4 bit Samples**: Includes 5 short samples for drums on MIDI Ch. 10, add or replace them using the include python code.

- **Programming and MIDI Mode**: Use the switch to toggle between MIDI and programming mode. Programming is for flashing new code.
