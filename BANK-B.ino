void playNoteB(byte note, byte velo, byte chan, int pitchBendValue) {

const uint8_t voltbl[32] = {0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x05, 0x06, 0x07, 0x09,
                            0x0B, 0x0D, 0x0F, 0x12, 0x16, 0x1A, 0x1F, 0x25, 0x2D, 0x35, 0x3F, 0x4C,
                            0x5A, 0x6A, 0x7F, 0x97, 0xB4, 0xD6, 0xFF, 0xFF};

    if (note < 24) return;
    setPinHigh(__LEDPORT__, __LED__);
    byte volume = map(velo, 0, 127, 0, 15);

// MIDI Channel 1
    if (chan == 0) {
    noteActiveA = 1;
    detuneActiveA = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;     
    noteA = note;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    int periodA = (tp[note]  + detuneValue) * pitchBendFactor;
    byte LSB = (periodA & 0xFF);
    byte MSB = ((periodA >> 8) & 0x0F);
    cli();
    setMixer(true, false, false, false, false, false);
    send_data(0x00, LSB);
    send_data(0x01, MSB);
    setVolume(0, volume);
    setEnvelope(0x6000, 0x4000); 
    sei();
    }
// MIDI Channel 2
    else if (chan == 1) {
    noteActiveB = 1;
    detuneActiveB = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;    
    noteB = note;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    int periodB = (tp[note]   + detuneValue) * pitchBendFactor;
    byte LSB = (periodB & 0xFF);
    byte MSB = ((periodB >> 8) & 0x0F);
    cli();
    setMixer(false, false, true, false, false, false);
    send_data(0x02, LSB);
    send_data(0x03, MSB);
    setVolume(1, volume);
    setEnvelope(0x00, 0x0E); 
    sei(); 
    }
 // MIDI Channel 3
    else if (chan == 2) {
      noteActiveC = 1;
    detuneActiveC = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;      
    noteC = note;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    int periodC = (tp[note] + detuneValue) * pitchBendFactor;
    byte LSB = (periodC & 0xFF);
    byte MSB = ((periodC >> 8) & 0x0F);
    cli();
    setMixer(false, false, false, false, true, false);
    send_data(0x04, LSB);
    send_data(0x05, MSB);
    setVolume(2, volume);
    setEnvelope(0x0800, 0x09);
    sei();
    }
// MIDI Channel 4
    else if (chan == 3) {
        if (mm3 == 0) {
            noteActiveA = 1;
            noteActiveB = 1;
            detuneActiveB = 1;
            arpeggioFlipMe = true;
            timerTicks = 0;
            arpeggioCounter = 0;          
            noteA = note;
            noteB = note;
            float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
            int periodA = tp[note] * pitchBendFactor;
            periodB = (tp[note] + (detuneValue  + 1)) * pitchBendFactor;
            byte ALSB = (periodA & 0x00FF);
            byte AMSB = ((periodA >> 8) & 0x000F);
            byte BLSB = (periodB & 0x00FF);
            byte BMSB = ((periodB >> 8) & 0x000F);
            cli();
            setMixer(true, false, true, false, true, false);
            send_data(0x00, ALSB);
            send_data(0x01, AMSB);
            send_data(0x02, BLSB);
            send_data(0x03, BMSB);
            setVolume(0, volume);
            setVolume(1, volume);
            setVolume(2, volume);
            setEnvelope(0x6000, 0x4000);
            sei();
        }
    }
// MIDI Channel 5
else if (chan == 4) { 
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 1;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;  
    noteA = note;
    noteB = note;
    noteC = note;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    int periodA = (tp[note] - 12) * pitchBendFactor;
    int periodB = (tp[note]) * pitchBendFactor;
    int periodC = (tp[note] + (detuneValue  + 1)) * pitchBendFactor;
    byte ALSB = (periodA & 0x00FF);
    byte AMSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, true, false);
    send_data(0x00, ALSB);
    send_data(0x01, AMSB);
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);
    setVolume(0, volume - 3);
    setVolume(1, volume);
    setVolume(2, volume - 3);
    setEnvelope(0xF000, 0x0A);
    sei();
}
// MIDI Channel 6
else if (chan == 5) { 
    noteActiveA = 1;
    detuneActiveA = 0;
    noteA = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = (envTp[note]  + detuneValue) * pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    cli();
    setMixer(true, false, false, false, false, false);
    send_data(0x00, LSB);
    send_data(0x01, MSB);
    send_data(0x0B, LSB);
    send_data(0x0C, MSB);
    setVolume(0, volume);
    setEnvelope(0x4000, 0x08);
    sei();
}
// MIDI Channel 7
else if (chan == 6) { 
    noteActiveA = 1;
    detuneActiveA = 0;
    noteA = note;
    noteB = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = (envTp[note] + detuneValue) * pitchBendFactor;
    periodB = (envTp[note]) * pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, false, false);
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x0B, LSB);
    send_data(0x0C, MSB);
    setVolume(0, volume);
    setVolume(1, volume);
    setEnvelope(0x4000, 0x08);
    sei();
}
// MIDI Channel 8
else if (chan == 7) { 
    noteActiveA = 1;
    noteActiveB = 1;
    detuneActiveC = 1;
    noteA = note;
    noteB = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = envTp[note]  * pitchBendFactor;
    periodB = ((tp[note - 12] + detuneValue) << 1)* pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, false, false);
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x0B, LSB);
    send_data(0x0C, MSB);
    setVolume(0, volume);
    setVolume(1, volume);
    setEnvelope(0x2000, 0x02);
    sei();
}
// MIDI Channel 9
else if (chan == 8) { 
    noteActiveA = 1;
    noteActiveB = 1;
    detuneActiveB = 1;
    noteA = note;
    noteB = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = envTp[note] * pitchBendFactor;
    periodB = (tp[note - 24]   + detuneValue) * pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, false, false); 
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x0B, LSB);
    send_data(0x0C, MSB);
    setVolume(0, volume - 2);
    setVolume(1, volume);
    setEnvelope(0x2000, 0x0F);
    sei();
}
// MIDI Channel 11
else if (chan == 10) { 
    noteActiveA = 1;
    detuneActiveA = 0;
    noteA = note;
    arpeggioFlipMe = true;
    arpeggioCounter = 0;
    timerTicks = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = (envTp[note] + detuneValue)  * pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    cli();
    setMixer(true, false, false, false, false, false);
    send_data(0x00, LSB);
    send_data(0x01, MSB);
    setVolume(0, volume);
    setEnvelope(0x2000, 0x0F);
    sei();
}
// MIDI Channel 12
else if (chan == 11) 
{
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 0;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    noteA = note;
    noteB = note;
    noteC = note;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = tp[note - 12] * pitchBendFactor;
    periodB = tp[note + 12] * pitchBendFactor;
    periodC = (tp[note] + detuneValue)  * pitchBendFactor;  
    byte ALSB = (periodA & 0x00FF);
    byte AMSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, true, false);
    send_data(0x08, 0x10);
    send_data(0x0B, BLSB);
    send_data(0x0C, BMSB);
    send_data(0x00, ALSB);
    send_data(0x01, AMSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);
    setVolume(0, volume);
    setVolume(1, volume);
    setVolume(2, volume);
    setEnvelope(0x4000, 0x06);
    sei();
}
// MIDI Channel 13
else if (chan == 12) 
{
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 0;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    noteA = note;
    noteB = note;
    noteC = note;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = tp[note - 12] * pitchBendFactor;
    periodB = tp[note - 12] * pitchBendFactor;
    periodC = (tp[note] + detuneValue)  * pitchBendFactor;  
    byte ALSB = (periodA & 0x00FF);
    byte AMSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);
    cli();
    setMixer(true, false, true, false, true, false);
    send_data(0x08, 0x10);
    send_data(0x0B, BLSB);
    send_data(0x0C, BMSB);
    send_data(0x00, ALSB);
    send_data(0x01, AMSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);
    setVolume(0, volume);
    setVolume(1, volume);
    setVolume(2, volume);
    setEnvelope(0x2000, 0x02);
    sei();
}
// MIDI Channel 14
else if (chan == 13) 
{
    noteActiveA = 1;
    noteA = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = (tp[note - 12] + detuneValue)  * pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA & 0x0F00) >> 8);
    cli(); 
    setMixer(true, false, false, false, false, false);
    send_data(0x00, LSB);
    send_data(0x01, MSB);
    setVolume(0, volume);
    setEnvelope(0x3000, 0x0F); 
    sei();
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
    // MIDI Channel 1
    if (chan == 0 && note == noteA) {
        noteActiveA = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        setVolume(0, 0); 
        setEnvelope(0x0000, 0x00);
        sei();
    }
    // MIDI Channel 2
    else if (chan == 1 && note == noteB) {
        noteActiveB = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteB = periodB = 0;
        cli();
        send_data(0x02, 0);
        send_data(0x03, 0);
        setVolume(1, 0); 
        setEnvelope(0x0000, 0x00);
        send_data(0x0D, 0);
        sei();
    }
    // MIDI Channel 3
    else if (chan == 2 && note == noteC) {
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteC = periodC = 0;
        cli();
        send_data(0x04, 0);
        send_data(0x05, 0); 
        setVolume(2, 0); 
        setEnvelope(0x0000, 0x00);
        sei();
    }
    // MIDI Channel 4
    else if (chan == 3 && note == noteA) {
        noteActiveA = 0;
        noteActiveB = 0;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0);
        setVolume(1, 0);
        setVolume(2, 0);
        sei();
    }
    // MIDI Channel 5
    else if (chan == 4 && note == noteA) {
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x04, 0);
        send_data(0x05, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0);
        setVolume(1, 0);
        setVolume(2, 0);
        sei();
    }
    // MIDI Channel 6
    else if (chan == 5 && note == noteA) {
        noteActiveA = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0); 
        sei();
    }
    // MIDI Channel 7
    else if (chan == 6 && note == noteA) {
        noteActiveA = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0);
        setVolume(1, 0);
        sei();
    }
    // MIDI Channel 8
    else if (chan == 7 && note == noteA) {
        noteActiveA = 0;
        noteActiveB = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0);
        setVolume(1, 0);
        sei();
    }
    // MIDI Channel 9
    else if (chan == 8 && note == noteA) {     
        noteActiveA = 0;
        noteActiveB = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        cli();
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x0D, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        setEnvelope(0x0000, 0x00);
        setVolume(0, 0);
        setVolume(1, 0);
        sei();
    }
    // MIDI Channel 11
    else if (chan == 10 && note == noteA) {     
        noteActiveA = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0; 
        cli(); 
        send_data(0x00, 0); 
        send_data(0x01, 0); 
        setEnvelope(0x0000, 0x00); 
        setVolume(0, 0); 
        sei(); 
    }
    // MIDI Channel 12
    else if (chan == 11 && note == noteA) {        
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0); 
        send_data(0x04, 0); 
        send_data(0x05, 0); 
        setEnvelope(0x0000, 0x00); 
        setVolume(0, 0); 
        setVolume(1, 0); 
        setVolume(2, 0); 
        sei(); 
    }
    // MIDI Channel 13
    else if (chan == 12 && note == noteA) {
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        arpeggioFlipMe = false;
        timerTicks = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x04, 0); 
        send_data(0x05, 0); 
        setEnvelope(0x0000, 0x00); 
        setVolume(0, 0); 
        setVolume(1, 0); 
        setVolume(2, 0); 
        sei(); 
    }
    // MIDI Channel 14
    else if (chan == 13 && note == noteA) {

    }
}
