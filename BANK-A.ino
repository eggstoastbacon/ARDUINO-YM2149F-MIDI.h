void playNote(byte note, byte velo, byte chan, int pitchBendValue) {

    // Check if the note value is within the valid range
    if (note < 24) return; // Invalid note, exit function
    setPinHigh(__LEDPORT__, __LED__);
    // Ensure velocity is within the valid range
    volume = map(velo, 0, 127, 0, 15); // Scale velocity to volume range (0-15)

    // Handle MIDI Channel 1
    if (chan == 0) {
        noteActiveA = 1;
        detuneActiveA = 0;
        arpeggioFlipMe = true;
        timerTicks = 0;
        arpeggioCounter = 0; // Reset arpeggio counter
        noteA = note; // Set the note for Channel A
        float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
          // Calculate the period based on pitch bend value
        int periodA = (tp[note] + detuneValue) * pitchBendFactor; // Adjust the period based on pitch bend
        byte LSB = (periodA & 0x00FF); // Get the LSB of the period
        byte MSB = ((periodA & 0x0F00) >> 8); // Get the MSB of the period
        cli(); // Disable interrupts
        send_data(0x00, LSB); // Send LSB to register 0x00
        send_data(0x01, MSB); // Send MSB to register 0x01
        send_data(0x08, volume); // Send volume based on velocity
        sei(); // Enable interrupts
    }
    // Handle MIDI Channel 2
    else if (chan == 1) {
        noteActiveB = 1;
        detuneActiveB = 0;
        arpeggioFlipMe = true;
        timerTicks = 0;
        arpeggioCounter = 0; // Reset arpeggio counter
        noteB = note; // Set the note for Channel B       // Calculate the period based on pitch bend value
        float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
        int periodB = (tp[note] + detuneValue) * pitchBendFactor; 
        byte LSB = (periodB & 0x00FF); // Get the LSB of the period
        byte MSB = ((periodB >> 8) & 0x000F); // Get the MSB of the period
        cli(); // Disable interrupts
        send_data(0x02, LSB); // Send LSB to register 0x02
        send_data(0x03, MSB); // Send MSB to register 0x03
        send_data(0x09, volume); // comment to disable volume based on velocity
        sei(); // Enable interrupts
    }
    // Handle MIDI Channel 3
    else if (chan == 2) {
        noteActiveC = 1;
        detuneActiveC = 0;
        arpeggioFlipMe = true;
        timerTicks = 0;
        arpeggioCounter = 0; // Reset arpeggio counter
        noteC = note; // Set the note for Channel C
        float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
        int periodC = (tp[note] + detuneValue) * pitchBendFactor; // Retrieve the period for the note
        byte LSB = (periodC & 0x00FF); // Get the LSB of the period
        byte MSB = ((periodC >> 8) & 0x000F); // Get the MSB of the period
        cli(); // Disable interrupts
        send_data(0x04, LSB); // Send LSB to register 0x04
        send_data(0x05, MSB); // Send MSB to register 0x05
        send_data(0x0A, volume); // comment to disable volume based on velocity
        sei(); // Enable interrupts
    }
    // Handle MIDI Channel 4
    else if (chan == 3) {
        if (mm3 == 0) {
            noteActiveA = 1;
            noteActiveB = 1;
            detuneActiveB = 1;
            arpeggioFlipMe = true;
            timerTicks = 0;
            arpeggioCounter = 0; // Reset arpeggio counter
            noteA = note; // Set the note for Channel A
            noteB = note; // Set the note for Channel B
            float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
            int periodA = tp[note] * pitchBendFactor; // Retrieve the period for note A
            periodB = (tp[note] + detuneValue) * pitchBendFactor; // Apply detune for note B
            
            byte ALSB = (periodA & 0x00FF); // Get the LSB of period A
            byte AMSB = ((periodA >> 8) & 0x000F); // Get the MSB of period A
            byte BLSB = (periodB & 0x00FF); // Get the LSB of period B
            byte BMSB = ((periodB >> 8) & 0x000F); // Get the MSB of period B
            cli(); // Disable interrupts
            send_data(0x00, ALSB); // Send LSB of period A to register 0x00
            send_data(0x01, AMSB); // Send MSB of period A to register 0x01
            send_data(0x02, BLSB); // Send LSB of period B to register 0x02
            send_data(0x03, BMSB); // Send MSB of period B to register 0x03
            send_data(0x08, volume); // Set volume based on velocity for Channel A
            send_data(0x09, volume); // Set volume based on velocity for Channel B
            sei(); // Enable interrupts
        }
    }
    // Handle MIDI Channel 5
else if (chan == 4) { 
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter
    noteA = note; // Set the note for Channel A
    noteB = note; // Set the note for Channel B
    noteC = note; // Set the note for Channel C
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    int periodA = (tp[note] - 12) * pitchBendFactor;  // Retrieve the period for note A
    int periodB = (tp[note]) * pitchBendFactor; // Retrieve the period for note B
    int periodC = (tp[note] + detuneValue) * pitchBendFactor; // Retrieve the period for note C

    byte ALSB = (periodA & 0x00FF); // Get the LSB of period A
    byte AMSB = ((periodA >> 8) & 0x000F); // Get the MSB of period A
    byte BLSB = (periodB & 0x00FF); // Get the LSB of period B
    byte BMSB = ((periodB >> 8) & 0x000F); // Get the MSB of period B
    byte CLSB = (periodC & 0x00FF); // Get the LSB of period C
    byte CMSB = ((periodC >> 8) & 0x000F); // Get the MSB of period C

    cli(); // Disable interrupts
    send_data(0x00, ALSB); // Send LSB of period A to register 0x00
    send_data(0x01, AMSB); // Send MSB of period A to register 0x01
    send_data(0x02, BLSB); // Send LSB of period B to register 0x02
    send_data(0x03, BMSB); // Send MSB of period B to register 0x03
    send_data(0x04, CLSB); // Send LSB of period C to register 0x04
    send_data(0x05, CMSB); // Send MSB of period C to register 0x05
    send_data(0x08, volume); // Set volume based on velocity for Channel A
    send_data(0x09, volume); // Set volume based on velocity for Channel B
    send_data(0x0A, volume); // Set volume based on velocity for Channel C
    sei(); // Enable interrupts
}
else if (chan == 5) { // MIDI Channel 6
    noteActiveA = 1;
    detuneActiveA = 0;
    noteA = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    periodA = envTp[note + detuneValue] * pitchBendFactor;

    byte LSB = (periodA & 0x00FF); // Get LSB of period A
    byte MSB = ((periodA >> 8) & 0x000F); // Get MSB of period A

    cli(); // Disable interrupts 
    send_data(0x00, LSB); // Send LSB to register 0x0B
    send_data(0x01, MSB); // Send MSB to register 0x0C
    send_data(0x08, volume); // Set volume based on velocity for Channel A
    send_data(0x08, 0x10); // Enable envelope mode
    send_data(0x0B, LSB); // Send LSB to register 0x0B
    send_data(0x0C, MSB); // Send MSB to register 0x0C
    send_data(0x0D, 0b00001000); // Set attack and sustain
    sei(); // Enable interrupts
}
else if (chan == 6) { // MIDI Channel 7
    noteActiveA = 1;
    detuneActiveA = 0;
    noteA = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    periodA = (envTp[note + 24]) * pitchBendFactor;

    byte LSB = (periodA & 0x00FF); // Get LSB of period A
    byte MSB = ((periodA >> 8) & 0x000F); // Get MSB of period A

    cli(); // Disable interrupts
    send_data(0x08, 0x10); // Enable envelope mode
    send_data(0x09, 127); // Enable velocity volume
    send_data(0x0B, LSB); // Send LSB to register 0x0B
    send_data(0x0C, MSB); // Send MSB to register 0x0C
    send_data(0x0D, 0b00001010); // Set attack and sustain
    sei(); // Enable interrupts
}
else if (chan == 7) { // MIDI Channel 8
    noteActiveA = 1;
    noteActiveB = 1;
    detuneActiveC = 1;
    noteA = note;
    noteB = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    periodA = envTp[note]  * pitchBendFactor;
    periodB = ((tp[note - 12] + detuneValue) << 1)* pitchBendFactor ; // Apply detune and shift

    byte LSB = (periodA & 0x00FF); // Get LSB of period A
    byte MSB = ((periodA >> 8) & 0x000F); // Get MSB of period A
    byte BLSB = (periodB & 0x00FF); // Get LSB of period B
    byte BMSB = ((periodB >> 8) & 0x000F); // Get MSB of period B

    cli(); // Disable interrupts
    send_data(0x02, BLSB); // Send LSB of period B
    send_data(0x03, BMSB); // Send MSB of period B
    send_data(0x08, 0x10); // Enable envelope mode
    send_data(0x09, volume); // Enable velocity volume
    send_data(0x0B, LSB); // Send LSB of period A
    send_data(0x0C, MSB); // Send MSB of period A
    send_data(0x0D, 0b00001100); // Set attack and sustain
    sei(); // Enable interrupts
}
else if (chan == 8) { // MIDI Channel 9
    noteActiveA = 1;
    noteActiveB = 1;
    detuneActiveB = 0;
    noteA = note;
    noteB = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    periodA = envTp[note] * pitchBendFactor;
    periodB = tp[note - 24] * pitchBendFactor; // Retrieve period for note B

    byte LSB = (periodA & 0x00FF); // Get LSB of period A
    byte MSB = ((periodA >> 8) & 0x000F); // Get MSB of period A
    byte BLSB = (periodB & 0x00FF); // Get LSB of period B
    byte BMSB = ((periodB >> 8) & 0x000F); // Get MSB of period B

    cli(); // Disable interrupts
    send_data(0x02, BLSB); // Send LSB of period B
    send_data(0x03, BMSB); // Send MSB of period B
    send_data(0x08, 0x10); // Enable envelope mode
    send_data(0x09, volume); // Enable envelope mode
    send_data(0x0B, LSB); // Send LSB of period A
    send_data(0x0C, MSB); // Send MSB of period A
    send_data(0x0D, 0b00001110); // Set attack and sustain
    sei(); // Enable interrupts
}
else if (chan == 10) { // MIDI Channel 11 Clicks and Pops
    noteActiveA = 1;
    noteActiveC = 1;
    detuneActiveA = 0;
    noteA = note; // Set note for Channel A
    noteC = note; // Set note for Channel C
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    periodA = envTp[note] * pitchBendFactor; // Get period for note A
    periodC = tp[note] * pitchBendFactor; // Get period for note C
    byte LSB = (periodA & 0x00FF); // Get LSB of period A
    byte MSB = ((periodA >> 8) & 0x000F); // Get MSB of period A
    byte CLSB = (periodC & 0x00FF); // Get LSB of period C
    byte CMSB = ((periodC >> 8) & 0x000F); // Get MSB of period C

    cli(); // Disable interrupts
    send_data(0x08, 0x10); // Enable envelope mode
    send_data(0x0D, 0b00001110); // Set attack and sustain
    send_data(0x04, CLSB); // Send LSB of period C
    send_data(0x05, CMSB); // Send MSB of period C 
    send_data(0x09, volume); // Enable velocity volume
    //send_data(0x0D, 0); // Stop envelope effect
    send_data(0x0D, 0b00011100); // Set attack and sustain
    send_data(0x00, LSB); // Send LSB of period A
    send_data(0x01, MSB); // Send MSB of period A
    
 //   send_data(0x08, 0); // Enable envelope mode
 //   send_data(0x0D, 0); // Stop envelope effect
    sei(); // Enable interrupts
}
else if (chan == 11) // MIDI Channel 12
{
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 0;
    timerTicks = 0;
    noteA = note; // Set note for Channel A
    noteB = note; // Set note for Channel B
    noteC = note; // Set note for Channel C
    arpeggioFlipMe = true;
    arpeggioCounter = 0; // Reset arpeggio counter
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    periodA = tp[note - 12] * pitchBendFactor; // Get period for note A
    periodB = tp[note + 12] * pitchBendFactor; // Get period for note B
    periodC = tp[note] * pitchBendFactor; // Get period for note C
    
    byte ALSB = (periodA & 0x00FF); // Get LSB of period A
    byte AMSB = ((periodA >> 8) & 0x000F); // Get MSB of period A
    byte BLSB = (periodB & 0x00FF); // Get LSB of period B
    byte BMSB = ((periodB >> 8) & 0x000F); // Get MSB of period B
    byte CLSB = (periodC & 0x00FF); // Get LSB of period C
    byte CMSB = ((periodC >> 8) & 0x000F); // Get MSB of period C

    cli(); // Disable interrupts
    send_data(0x08, 0x10); // Enable envelope mode
    send_data(0x0B, BLSB); // Send LSB of period B
    send_data(0x0C, BMSB); // Send MSB of period B
    send_data(0x0D, 0b00001100); // Set attack and sustain
    send_data(0x00, ALSB); // Send LSB of period A
    send_data(0x01, AMSB); // Send MSB of period A
    send_data(0x04, CLSB); // Send LSB of period C
    send_data(0x05, CMSB); // Send MSB of period C    
    sei(); // Enable interrupts
}
else if (chan == 12) // MIDI Channel 13
{
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 0;
    timerTicks = 0;
    noteA = note; // Set note for Channel A
    noteB = note; // Set note for Channel B
    noteC = note; // Set note for Channel C
    arpeggioFlipMe = true;
    arpeggioCounter = 0; // Reset arpeggio counter
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    periodA = tp[note - 12] * pitchBendFactor; // Get period for note A    
    periodB = tp[note - 12] * pitchBendFactor; // Get period for note B
    periodC = tp[note] * pitchBendFactor;      // Get period for note C
    
    byte ALSB = (periodA & 0x00FF); // Get LSB of period A
    byte AMSB = ((periodA >> 8) & 0x000F); // Get MSB of period A
    byte BLSB = (periodB & 0x00FF); // Get LSB of period B
    byte BMSB = ((periodB >> 8) & 0x000F); // Get MSB of period B
    byte CLSB = (periodC & 0x00FF); // Get LSB of period C
    byte CMSB = ((periodC >> 8) & 0x000F); // Get MSB of period C

    cli(); // Disable interrupts
    send_data(0x08, 0x10); // Enable envelope mode
    send_data(0x0B, BLSB); // Send LSB of period B
    send_data(0x0C, BMSB); // Send MSB of period B
    send_data(0x00, ALSB); // Send LSB of period A
    send_data(0x01, AMSB); // Send MSB of period A
    send_data(0x04, CLSB); // Send LSB of period C
    send_data(0x05, CMSB); // Send MSB of period C
    send_data(0x0D, 0b00101100); // Set attack and sustain
    sei(); // Enable interrupts
}
else if (chan == 13) // MIDI Channel 14
{
    noteActiveA = 1;
    noteA = note;
    arpeggioFlipMe = true;
    arpeggioCounter = 0; // Reset arpeggio counter
    timerTicks = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    periodA = tp[note - 12] * pitchBendFactor;
    byte LSB = (periodA & 0x00FF); // Get LSB of period A
    byte MSB = ((periodA & 0x0F00) >> 8); // Get MSB of period A

    cli(); // Disable interrupts
    send_data(0x06, LSB); // Send LSB to register 0x00
    send_data(0x07, MSB); // Send MSB to register 0x01
    send_data(0x09, volume); // Set volume based on velocity
    //send_data(0x08, 0x10); // Enable envelope mode
    //send_data(0x0D, 0b00011000); // Set attack and sustain
    sei(); // Enable interrupts
}
}

/**
 * @brief Stops a MIDI note for a specified channel.
 *
 * This function resets the note and period for the specified MIDI channel
 * and sends commands to stop the sound associated with that note.
 *
 * @param note The MIDI note number to stop.
 * @param chan The MIDI channel number corresponding to the note.
 */
void stopNote(byte note, byte chan)
{
    // Check if the channel is 0 (MIDI Channel 1)
    if (chan == 0 && note == noteA) {
        // Stop note A 
        timerTicks = 0;
        noteActiveA = 0;
        noteA = periodA = 0; // Reset note and period
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        send_data(0x00, 0); // Stop Channel 1 frequency LSB
        send_data(0x01, 0); // Stop Channel 1 frequency MSB
        sei(); // Enable interrupts
    }
    // Check if the channel is 1 (MIDI Channel 2)
    else if (chan == 1 && note == noteB) {
        // Stop note B
        timerTicks = 0;
        noteActiveB = 0;
        noteB = periodB = 0; // Reset note and period
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        send_data(0x02, 0); // Stop Channel 2 frequency LSB
        send_data(0x03, 0); // Stop Channel 2 frequency MSB
        sei(); // Enable interrupts
    }
    // Check if the channel is 2 (MIDI Channel 3)
    else if (chan == 2 && note == noteC) {
        // Stop note C
        timerTicks = 0;
        noteActiveC = 0;
        noteC = periodC = 0; // Reset note and period
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        send_data(0x04, 0); // Stop Channel 3 frequency LSB
        send_data(0x05, 0); // Stop Channel 3 frequency MSB
        sei(); // Enable interrupts
    }
    // Check if the channel is 3 (MIDI Channel 4)
    else if (chan == 3 && note == noteA) {
        // Stop note A for channel 4
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteA = periodA = 0; // Reset note and period
        noteB = periodB = 0; // Stop note B as well
        cli(); // Disable interrupts
        send_data(0x00, 0); // Stop Channel 1 frequency LSB
        send_data(0x01, 0); // Stop Channel 1 frequency MSB
        send_data(0x02, 0); // Stop Channel 2 frequency LSB
        send_data(0x03, 0); // Stop Channel 2 frequency MSB
        sei(); // Enable interrupts
    }
    // Check if the channel is 4 (MIDI Channel 5)
    else if (chan == 4 && note == noteA) {
        // Stop note A for channel 5
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        noteA = periodA = 0; // Reset note and period
        noteB = periodB = 0; // Stop note B
        noteC = periodC = 0; // Stop note C
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        send_data(0x00, 0); // Stop Channel 1 frequency LSB
        send_data(0x01, 0); // Stop Channel 1 frequency MSB
        send_data(0x02, 0); // Stop Channel 2 frequency LSB
        send_data(0x03, 0); // Stop Channel 2 frequency MSB
        send_data(0x04, 0); // Stop Channel 3 frequency LSB
        send_data(0x05, 0); // Stop Channel 3 frequency MSB
        sei(); // Enable interrupts
    }
    // Check if the channel is 5 (MIDI Channel 6)
    else if (chan == 5 && note == noteA) {
        // Stop note A for channel 6
        timerTicks = 0;
        noteActiveA = 0;
        noteA = periodA = 0; // Reset note and period
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x0B, 0); // Send LSB to register 0x0B
        send_data(0x0C, 0); // Send MSB to register 0x0C
        send_data(0x0D, 0); // Stop envelope effect
        send_data(0x08, 127); // Set maximum volume
        sei(); // Enable interrupts
    }
    // Check if the channel is 6 (MIDI Channel 7)
    else if (chan == 6 && note == noteA) {
        // Stop note A for channel 7
        timerTicks = 0;
        noteActiveA = 0;
        noteA = periodA = 0; // Reset note and period
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        send_data(0x00, 0); // Stop period A
        send_data(0x01, 0); // Stop period A
        send_data(0x0B, 0); // Stop period A
        send_data(0x0C, 0); // Stop period A
        send_data(0x0D, 0); // Stop envelope effect
        sei(); // Enable interrupts
    }
    // Check if the channel is 7 (MIDI Channel 8)
    else if (chan == 7 && note == noteA) {
        // Stop note A for channel 8
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteA = periodA = 0; // Reset note and period
        noteB = periodB = 0; // Stop note B
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        send_data(0x00, 0); // Stop Channel 2 frequency LSB
        send_data(0x01, 0); // Stop Channel 2 frequency MSB
        send_data(0x02, 0); // Stop Channel 2 frequency LSB
        send_data(0x03, 0); // Stop Channel 2 frequency MSB
        send_data(0x0B, 0); // Stop period A
        send_data(0x0C, 0); // Stop period A
        send_data(0x0D, 0); // Stop envelope effect
        send_data(0x08, AmaxVolume); // Set maximum volume
        sei(); // Enable interrupts
    }
    // Check if the channel is 8 (MIDI Channel 9)
    else if (chan == 8 && note == noteA) {
        // Stop note A for channel 9
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteA = periodA = 0; // Reset note and period
        noteB = periodB = 0; // Stop note B
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        send_data(0x00, 0); // Stop Channel 2 frequency LSB
        send_data(0x01, 0); // Stop Channel 2 frequency MSB
        send_data(0x02, 0); // Stop Channel 2 frequency LSB
        send_data(0x03, 0); // Stop Channel 2 frequency MSB
        send_data(0x0D, 0); // Stop envelope effect
        send_data(0x0B, 0); // Stop Channel 3 frequency LSB
        send_data(0x0C, 0); // Stop Channel 3 frequency MSB
        send_data(0x08, AmaxVolume); // Set maximum volume
        sei(); // Enable interrupts
    }
    // Check if the channel is 10 (MIDI Channel 11)
    else if (chan == 10 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveC = 0;
        noteA = periodA = 0; // Reset note and period
        noteC = periodC = 0; // Reset note and period
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        send_data(0x00, 0); // Stop Channel 1 frequency LSB
        send_data(0x01, 0); // Stop Channel 1 frequency MSB
        send_data(0x04, 0); // Stop Channel 3 frequency LSB
        send_data(0x05, 0); // Stop Channel 3 frequency MSB
        send_data(0x0D, 0); // Stop envelope effect
        send_data(0x0B, 0); // Stop Channel 3 frequency LSB
        send_data(0x0C, 0); // Stop Channel 3 frequency MSB
        send_data(0x08, 0); // Turn envelope mode off
        sei(); // Enable interrupts
    }
    // Check if the channel is 11 (MIDI Channel 12)
    else if (chan == 11 && note == noteA) {        
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        // Reset note periods
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        // Stop the envelope effect for all channels
        send_data(0x08, 0x00); // Turn envelope mode off
        // Send zero to all frequency registers to stop the sound
        send_data(0x00, 0); // Channel 1 frequency LSB
        send_data(0x01, 0); // Channel 1 frequency MSB
        send_data(0x02, 0); // Channel 2 frequency LSB
        send_data(0x03, 0); // Channel 2 frequency MSB
        send_data(0x04, 0); // Channel 3 frequency LSB
        send_data(0x05, 0); // Channel 3 frequency MSB
        send_data(0x0B, 0); // Stop envelope register
        send_data(0x0C, 0); // Stop envelope register
        send_data(0x0D, 0); // Stop envelope register
        sei(); // Enable interrupts
    }
    // Check if the channel is 12 (MIDI Channel 13)
    else if (chan == 12 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        // Reset note periods
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        // Stop the envelope effect for all channels
        send_data(0x08, 0x00); // Turn envelope mode off
        // Send zero to all frequency registers to stop the sound
        send_data(0x00, 0); // Channel 1 frequency LSB
        send_data(0x01, 0); // Channel 1 frequency MSB
        send_data(0x02, 0); // Channel 2 frequency LSB
        send_data(0x03, 0); // Channel 2 frequency MSB
        send_data(0x04, 0); // Channel 3 frequency LSB
        send_data(0x05, 0); // Channel 3 frequency MSB
        send_data(0x0B, 0); // Stop envelope register
        send_data(0x0C, 0); // Stop envelope register
        sei(); // Enable interrupts
    }
    // Check if the channel is 13 (MIDI Channel 14)
    else if (chan == 13 && note == noteA) {
        // Stop note A for channel 11        
        timerTicks = 0;
        noteActiveA = 0;
        arpeggioFlipMe = false;
        cli(); // Disable interrupts
        send_data(0x06, 0x00); // Stop Channel
        send_data(0x07, 0x00); // Stop Channel
        send_data(0x08, 0x00); // Stop Channel
        send_data(0x09, 0x00); // Stop Channel
        send_data(0x0A, 0x00); // Stop Channel
        send_data(0x0B, 0x00); // Stop Channel
        sei(); // Enable interrupts
    }
}
