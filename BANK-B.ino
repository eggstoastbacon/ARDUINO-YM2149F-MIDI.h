void playNoteB(byte note, byte velo, byte chan, int pitchBendValue) {

  // Volume table for YM2149 logarithmic scaling
const uint8_t voltbl[32] = {0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x05, 0x06, 0x07, 0x09,
                            0x0B, 0x0D, 0x0F, 0x12, 0x16, 0x1A, 0x1F, 0x25, 0x2D, 0x35, 0x3F, 0x4C,
                            0x5A, 0x6A, 0x7F, 0x97, 0xB4, 0xD6, 0xFF, 0xFF};

// Helper function to set volume based on YM2149 volume table

    // Check if the note value is within the valid range
    if (note < 24) return; // Invalid note, exit function
    setPinHigh(__LEDPORT__, __LED__);
    // Ensure velocity is within the valid range
    byte volume = map(velo, 0, 127, 0, 15); // Scale velocity to volume range (0-15)

    // Handle MIDI Channel 1
    if (chan == 0) {
    noteActiveA = 1;
    detuneActiveA = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter        
    noteA = note; // Set the note for Channel B

    // Calculate pitch bend
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    int periodA = tp[note + detuneValue] * pitchBendFactor; // Retrieve the period for the note
    byte LSB = (periodA & 0xFF); // Get the LSB of the period
    byte MSB = ((periodA >> 8) & 0x0F); // Get the MSB of the period

    cli(); // Disable interrupts to ensure stable transmission

    // Set the mixer register to enable tone only on Channel B (no noise)
    setMixer(true, false, false, false, false, false); // Enable tone and noise on Channel B only
    // Set frequency (period) for Channel C
    send_data(0x00, LSB);  // Send LSB to register 0x04 for Channel B
    send_data(0x01, MSB);  // Send MSB to register 0x05 for Channel B
    // Set volume for Channel C using the new function
    setVolume(0, volume); // Channel C, volume level 15 (maximum)
    // Optionally, set an envelope to test sound shaping on Channel B
    setEnvelope(0x6000, 0x4000); 
    sei(); // Re-enable interrupts
    sei(); // Enable interrupts
    }
    // Handle MIDI Channel 2
    else if (chan == 1) {
    noteActiveB = 1;
    detuneActiveB = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter        
    noteB = note; // Set the note for Channel B

    // Calculate pitch bend
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    int periodB = tp[note + detuneValue] * pitchBendFactor; // Retrieve the period for the note
    byte LSB = (periodB & 0xFF); // Get the LSB of the period
    byte MSB = ((periodB >> 8) & 0x0F); // Get the MSB of the period

    cli(); // Disable interrupts to ensure stable transmission

    // Set the mixer register to enable tone only on Channel B (no noise)
    setMixer(false, false, true, false, false, false); // Enable tone and noise on Channel B only

    // Set frequency (period) for Channel C
    send_data(0x02, LSB);  // Send LSB to register 0x04 for Channel B
    send_data(0x03, MSB);  // Send MSB to register 0x05 for Channel B

    // Set volume for Channel C using the new function
    setVolume(1, volume); // Channel C, volume level 15 (maximum)

    // Optionally, set an envelope to test sound shaping on Channel B
    setEnvelope(0x00, 0x0E); 
    sei(); // Re-enable interrupts
    }
    // Handle MIDI Channel 3
    else if (chan == 2) {
      noteActiveC = 1;
    detuneActiveC = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter        
    noteC = note; // Set the note for Channel C

    // Calculate pitch bend
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    int periodC = tp[note + detuneValue] * pitchBendFactor; // Retrieve the period for the note
    byte LSB = (periodC & 0xFF); // Get the LSB of the period
    byte MSB = ((periodC >> 8) & 0x0F); // Get the MSB of the period
    cli(); // Disable interrupts to ensure stable transmission
    setMixer(false, false, false, false, true, false); // Enable tone and noise on Channel C only
    send_data(0x04, LSB);  // Send LSB to register 0x04 for Channel C
    send_data(0x05, MSB);  // Send MSB to register 0x05 for Channel C
    setVolume(2, volume); // Channel C, volume level 15 (maximum)
    setEnvelope(0x0800, 0x09); // Example envelope frequency and shape (adjust as needed)
    sei(); // Re-enable interrupts
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
            setMixer(true, false, true, false, true, false); // Enable tone and noise on Channel ABC
            send_data(0x00, ALSB); // Send LSB of period A to register 0x00
            send_data(0x01, AMSB); // Send MSB of period A to register 0x01
            send_data(0x02, BLSB); // Send LSB of period B to register 0x02
            send_data(0x03, BMSB); // Send MSB of period B to register 0x03
            setVolume(0, volume); // Channel A, volume level 15 (maximum)
            setVolume(1, volume); // Channel B, volume level 15 (maximum)
            setVolume(2, volume); // Channel C, volume level 15 (maximum)
            setEnvelope(0x6000, 0x4000); // Example envelope frequency and shape (adjust as needed)
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
    setMixer(true, false, true, false, true, false); // Enable tone and noise on Channel ABC
    send_data(0x00, ALSB); // Send LSB of period A to register 0x00
    send_data(0x01, AMSB); // Send MSB of period A to register 0x01
    send_data(0x02, BLSB); // Send LSB of period B to register 0x02
    send_data(0x03, BMSB); // Send MSB of period B to register 0x03
    send_data(0x04, CLSB); // Send LSB of period C to register 0x04
    send_data(0x05, CMSB); // Send MSB of period C to register 0x05
    setVolume(0, volume - 3); // Channel A, volume level 15 (maximum)
    setVolume(1, volume); // Channel B, volume level 15 (maximum)
    setVolume(2, volume - 3); // Channel C, volume level 15 (maximum)
    setEnvelope(0xF000, 0x0A); // Example envelope frequency and shape (adjust as needed)
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
    setMixer(true, false, false, false, false, false); // Enable tone and noise on Channel ABC
    send_data(0x00, LSB); // Send LSB to register 0x0B
    send_data(0x01, MSB); // Send MSB to register 0x0C
    send_data(0x0B, LSB); // Send LSB to register 0x0B
    send_data(0x0C, MSB); // Send MSB to register 0x0C
    setVolume(0, volume); // Channel A, volume level 15 (maximum)
    setEnvelope(0x4000, 0x08);
    sei(); // Enable interrupts
}
else if (chan == 6) { // MIDI Channel 7
    noteActiveA = 1;
    detuneActiveA = 0;
    noteA = note;
    noteB = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    periodA = (envTp[note]) * pitchBendFactor;
    periodB = (envTp[note]) * pitchBendFactor;

    byte LSB = (periodA & 0x00FF); // Get LSB of period A
    byte MSB = ((periodA >> 8) & 0x000F); // Get MSB of period A
    byte BLSB = (periodB & 0x00FF); // Get LSB of period A
    byte BMSB = ((periodB >> 8) & 0x000F); // Get MSB of period A

    cli(); // Disable interrupts
    setMixer(true, false, true, false, false, false); // Enable tone and noise on Channel ABC
    send_data(0x02, BLSB); // Send LSB to register 0x0B
    send_data(0x03, BMSB); // Send MSB to register 0x0C
    send_data(0x0B, LSB); // Send LSB to register 0x0B
    send_data(0x0C, MSB); // Send MSB to register 0x0C
    setVolume(0, volume); // Channel A, volume level 15 (maximum)
    setVolume(1, volume); // Channel A, volume level 15 (maximum)
    setEnvelope(0x4000, 0x08); // Slower decay with smooth fade
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
    setMixer(true, false, true, false, false, false); // Enable tone and noise on Channel AB
    send_data(0x02, BLSB); // Send LSB of period B
    send_data(0x03, BMSB); // Send MSB of period B
    send_data(0x08, 0x10); // Enable envelope mode
    send_data(0x0B, LSB); // Send LSB of period A
    send_data(0x0C, MSB); // Send MSB of period A
    setVolume(0, volume); // Channel A, volume level 15 (maximum)
    setVolume(1, volume); // Channel A, volume level 15 (maximum)
    setEnvelope(0x2000, 0x02);
    sei(); // Enable interrupts
}
else if (chan == 8) { // MIDI Channel 9
    noteActiveA = 1;
    noteActiveB = 1;
    detuneActiveB = 1;
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
    setMixer(true, false, true, false, false, false); // Enable tone and noise on Channel AB
    send_data(0x02, BLSB); // Send LSB of period B
    send_data(0x03, BMSB); // Send MSB of period B
    send_data(0x08, 0x10); // Enable envelope mode
    send_data(0x0B, LSB); // Send LSB of period A
    send_data(0x0C, MSB); // Send MSB of period A
    setVolume(0, volume - 2); // Channel A, volume level 15 (maximum)
    setVolume(1, volume); // Channel B, volume level 15 (maximum)
    setEnvelope(0x2000, 0x0F);
    sei(); // Enable interrupts
}
else if (chan == 10) { // MIDI Channel 11 Clicks and Pops
    noteActiveA = 1;
    detuneActiveA = 0;
    noteA = note; // Set note for Channel A
    arpeggioFlipMe = true;
    arpeggioCounter = 0; // Reset arpeggio counter
    timerTicks = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange); // Adjust frequency based on pitch bend
    periodA = envTp[note] * pitchBendFactor; // Get period for note A
    byte LSB = (periodA & 0x00FF); // Get LSB of period A
    byte MSB = ((periodA >> 8) & 0x000F); // Get MSB of period A

    cli(); // Disable interrupts
    send_data(0x08, 0x10); // Enable envelope mode
    send_data(0x09, 127); // Enable velocity volume
    send_data(0x00, LSB); // Send LSB of period A
    send_data(0x01, MSB); // Send MSB of period A
    send_data(0x0D, 0b00111000); // Set attack and sustain
    sei(); // Enable interrupts
}
else if (chan == 11) // MIDI Channel 12
{
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 0;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter
    noteA = note; // Set note for Channel A
    noteB = note; // Set note for Channel B
    noteC = note; // Set note for Channel C
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
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter
    noteA = note; // Set note for Channel A
    noteB = note; // Set note for Channel B
    noteC = note; // Set note for Channel C
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
    timerTicks = 0;
    arpeggioCounter = 0; // Reset arpeggio counter
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
void stopNoteB(byte note, byte chan)
{
    // Check if the channel is 0 (MIDI Channel 1)
    if (chan == 0 && note == noteA) {
        // Stop note A
        noteActiveA = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0; // Reset note and period
        cli(); // Disable interrupts
        send_data(0x00, 0); // Stop Channel 2 frequency LSB
        send_data(0x01, 0); // Stop Channel 2 frequency MSB
        setVolume(0, 0); 
        setEnvelope(0x0000, 0x00); // Zero frequency and a neutral shape to stop the envelope
        send_data(0x0D, 0); // Stop envelope effect
        sei(); // Enable interrupts
    }
    // Check if the channel is 1 (MIDI Channel 2)
    else if (chan == 1 && note == noteB) {
        // Stop note B
        noteActiveB = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteB = periodB = 0; // Reset note and period
        cli(); // Disable interrupts
        send_data(0x02, 0); // Stop Channel 2 frequency LSB
        send_data(0x03, 0); // Stop Channel 2 frequency MSB
        setVolume(1, 0); 
        setEnvelope(0x0000, 0x00); // Zero frequency and a neutral shape to stop the envelope
        send_data(0x0D, 0); // Stop envelope effect
        sei(); // Enable interrupts
    }
    // Check if the channel is 2 (MIDI Channel 3)
    else if (chan == 2 && note == noteC) {
        // Stop note C
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteC = periodC = 0; // Reset note and period
        cli(); // Disable interrupts
        send_data(0x04, 0); // Stop Channel 3 frequency LSB
        send_data(0x05, 0); // Stop Channel 3 frequency MSB
        setVolume(2, 0); 
        setEnvelope(0x0000, 0x00); // Zero frequency and a neutral shape to stop the envelope
        send_data(0x0D, 0); // Stop envelope effect
        sei(); // Enable interrupts
    }
    // Check if the channel is 3 (MIDI Channel 4)
    else if (chan == 3 && note == noteA) {
        // Stop note A for channel 4
        noteActiveA = 0;
        noteActiveB = 0;
        timerTicks = 0;
        noteA = periodA = 0; // Reset note and period
        noteB = periodB = 0; // Stop note B as well
        cli(); // Disable interrupts
        send_data(0x00, 0); // Stop Channel 1 frequency LSB
        send_data(0x01, 0); // Stop Channel 1 frequency MSB
        send_data(0x02, 0); // Stop Channel 2 frequency LSB
        send_data(0x03, 0); // Stop Channel 2 frequency MSB
        setEnvelope(0x0000, 0x00); // Zero frequency and a neutral shape to stop the envelope
        setVolume(0, 0); // Channel A, volume level 15 (maximum)
        setVolume(1, 0); // Channel B, volume level 15 (maximum)
        setVolume(2, 0); // Channel C, volume level 15 (maximum)
        sei(); // Enable interrupts
    }
    // Check if the channel is 4 (MIDI Channel 5)
    else if (chan == 4 && note == noteA) {
        // Stop note A for channel 5
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0; // Reset note and period
        noteB = periodB = 0; // Stop note B
        noteC = periodC = 0; // Stop note C
        cli(); // Disable interrupts
        send_data(0x00, 0); // Stop Channel 1 frequency LSB
        send_data(0x01, 0); // Stop Channel 1 frequency MSB
        send_data(0x02, 0); // Stop Channel 2 frequency LSB
        send_data(0x03, 0); // Stop Channel 2 frequency MSB
        send_data(0x04, 0); // Stop Channel 3 frequency LSB
        send_data(0x05, 0); // Stop Channel 3 frequency MSB
        setEnvelope(0x0000, 0x00); // Zero frequency and a neutral shape to stop the envelope
        setVolume(0, 0); // Channel A, volume level 15 (maximum)
        setVolume(1, 0); // Channel B, volume level 15 (maximum)
        setVolume(2, 0); // Channel C, volume level 15 (maximum)
        sei(); // Enable interrupts
    }
    // Check if the channel is 5 (MIDI Channel 6)
    else if (chan == 5 && note == noteA) {
        // Stop note A for channel 6
        noteActiveA = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0; // Reset note and period
        cli(); // Disable interrupts
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x08, 0); 
        send_data(0x0B, 0); // Send LSB to register 0x0B
        send_data(0x0C, 0); // Send MSB to register 0x0C
        setEnvelope(0x0000, 0x00); // Zero frequency and a neutral shape to stop the envelope
        setVolume(0, 0); // Channel A, volume level 15 (maximum)
        sei(); // Enable interrupts
    }
    // Check if the channel is 6 (MIDI Channel 7)
    else if (chan == 6 && note == noteA) {
        // Stop note A for channel 7
        noteActiveA = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0; // Reset note and period
        cli(); // Disable interrupts
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        setEnvelope(0x0000, 0x00); // Zero frequency and a neutral shape to stop the envelope
        setVolume(0, 0); // Channel A, volume level 15 (maximum)
        setVolume(1, 0); // Channel A, volume level 15 (maximum)
        sei(); // Enable interrupts
    }
    // Check if the channel is 7 (MIDI Channel 8)
    else if (chan == 7 && note == noteA) {
        // Stop note A for channel 8
        noteActiveA = 0;
        noteActiveB = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0; // Reset note and period
        noteB = periodB = 0; // Stop note B
        cli(); // Disable interrupts
        send_data(0x02, 0); // Stop Channel 2 frequency LSB
        send_data(0x03, 0); // Stop Channel 2 frequency MSB
        send_data(0x0B, 0); // Stop period A
        send_data(0x0C, 0); // Stop period A
        setEnvelope(0x0000, 0x00); // Zero frequency and a neutral shape to stop the envelope
        setVolume(0, 0); // Channel A, volume level 15 (maximum)
        setVolume(1, 0); // Channel A, volume level 15 (maximum)
        sei(); // Enable interrupts
    }

    else if (chan == 8 && note == noteA) {     // (MIDI Channel 9)
        // Stop note A for channel 9
        noteActiveA = 0;
        noteActiveB = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0; // Reset note and period
        noteB = periodB = 0; // Stop note B
        cli(); // Disable interrupts
        send_data(0x02, 0); // Stop Channel 2 frequency LSB
        send_data(0x03, 0); // Stop Channel 2 frequency MSB
        send_data(0x0D, 0); // Stop envelope effect
        send_data(0x0B, 0); // Stop Channel 3 frequency LSB
        send_data(0x0C, 0); // Stop Channel 3 frequency MSB
        setEnvelope(0x0000, 0x00); // Zero frequency and a neutral shape to stop the envelope
        setVolume(0, 0); // Channel A, volume level 15 (maximum)
        setVolume(1, 0); // Channel A, volume level 15 (maximum)
        sei(); // Enable interrupts
    }
    else if (chan == 10 && note == noteA) {     // (MIDI Channel 11)
        noteActiveA = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0; // Reset note and period
        cli(); // Disable interrupts
        send_data(0x00, 0); // Stop Channel 1 frequency LSB
        send_data(0x01, 0); // Stop Channel 1 frequency MSB
        send_data(0x08, 0); // Turn envelope mode off
        sei(); // Enable interrupts
    }
    // Check if the channel is 11 (MIDI Channel 12)
    else if (chan == 11 && note == noteA) {        
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        // Reset note periods
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
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
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        // Reset note periods
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
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

    }
}
