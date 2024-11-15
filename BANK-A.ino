void playNote(byte note, byte velo, byte chan, int pitchBendValue) {

    if (note < 24) return; // Invalid note, exit function
    setPinHigh(__LEDPORT__, __LED__);
    volume = map(velo, 0, 127, 0, 14);

// MIDI Channel 1
    if (chan == 0) {
        noteActiveA = 1;
        detuneActiveA = 0;
        arpeggioFlipMe = true;
        timerTicks = 0;
        arpeggioCounter = 0;
        noteA = note;
        float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
        int periodA = (tp[note] + detuneValue) * pitchBendFactor;
        byte LSB = (periodA & 0x00FF);
        byte MSB = ((periodA & 0x0F00) >> 8);
        cli();
        send_data(0x00, LSB);
        send_data(0x01, MSB);
        send_data(0x08, volume);
        sei();
    }
// MIDI Channel 2
    else if (chan == 1) {
        noteActiveB = 1;
        detuneActiveB = 0;
        arpeggioFlipMe = true;
        timerTicks = 0;
        arpeggioCounter = 0;
        noteB = note;
        float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
        int periodB = (tp[note] + detuneValue) * pitchBendFactor; 
        byte LSB = (periodB & 0x00FF);
        byte MSB = ((periodB >> 8) & 0x000F);
        cli();
        send_data(0x02, LSB);
        send_data(0x03, MSB);
        send_data(0x09, volume);
        sei();
    }
// MIDI Channel 3
    else if (chan == 2) {
        noteActiveC = 1;
        detuneActiveC = 0;
        arpeggioFlipMe = true;
        timerTicks = 0;
        arpeggioCounter = 0;
        noteC = note;
        float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
        int periodC = (tp[note] + detuneValue) * pitchBendFactor;
        byte LSB = (periodC & 0x00FF);
        byte MSB = ((periodC >> 8) & 0x000F);
        cli();
        send_data(0x04, LSB);
        send_data(0x05, MSB);
        send_data(0x0A, volume);
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
            periodB = (tp[note] + detuneValue) * pitchBendFactor;           
            byte ALSB = (periodA & 0x00FF);
            byte AMSB = ((periodA >> 8) & 0x000F);
            byte BLSB = (periodB & 0x00FF);
            byte BMSB = ((periodB >> 8) & 0x000F);
            cli();
            send_data(0x00, ALSB);
            send_data(0x01, AMSB);
            send_data(0x02, BLSB);
            send_data(0x03, BMSB);
            send_data(0x08, volume);
            send_data(0x09, volume);
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
    int periodC = (tp[note] + detuneValue) * pitchBendFactor;

    byte ALSB = (periodA & 0x00FF);
    byte AMSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);

    cli();
    send_data(0x00, ALSB);
    send_data(0x01, AMSB);
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB); 
    send_data(0x08, volume);
    send_data(0x09, volume);
    send_data(0x0A, volume);
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
    periodA = envTp[note + detuneValue] * pitchBendFactor;
    periodB = envTp[note + 12] * pitchBendFactor;

    byte LSB = (periodA & 0x0000);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);

    cli();
    send_data(0x00, LSB);
    send_data(0x01, MSB);
    send_data(0x08, 0x10);
    send_data(0x0B, BLSB);
    send_data(0x0C, BMSB); 
    send_data(0x0D, 0b00001100);
    sei();
}
// MIDI Channel 7
else if (chan == 6) { 
    noteActiveA = 1;
    detuneActiveA = 0;
    noteA = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = (envTp[note + 24]) * pitchBendFactor;

    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);

    cli();
    send_data(0x08, 0x10);
    send_data(0x09, volume);
    send_data(0x0B, LSB);
    send_data(0x0C, MSB);
    send_data(0x0D, 0b00001010);
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
    periodB = ((tp[note - 12] + detuneValue) << 1)* pitchBendFactor ;

    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);

    cli();
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x08, 0x10);
    send_data(0x09, volume);
    send_data(0x0B, LSB);
    send_data(0x0C, MSB);
    send_data(0x0D, 0b00001100);
    sei();
}
// MIDI Channel 9
else if (chan == 8) {
    noteActiveA = 1;
    noteActiveB = 1;
    detuneActiveB = 0;
    noteA = note;
    noteB = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = envTp[note] * pitchBendFactor;
    periodB = tp[note - 24] * pitchBendFactor;

    byte LSB = (periodA & 0xFFFF);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);

    cli();
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x08, 0x10); 
    send_data(0x09, volume);
    send_data(0x0B, LSB);
    send_data(0x0C, MSB);
    send_data(0x0D, 0b00001110);
    sei();
}
// MIDI Channel 11
else if (chan == 10) {
    noteActiveA = 1;
    noteActiveC = 1;
    detuneActiveA = 0;
    noteA = note;
    noteC = note;
    arpeggioFlipMe = true;
    timerTicks = 0;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = envTp[note] * pitchBendFactor;
    periodC = tp[note] * pitchBendFactor;
    byte LSB = (periodA & 0x00FF);
    byte MSB = ((periodA >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);

    cli();
    send_data(0x08, 0x10);
    send_data(0x0D, 0b00001110);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);
    send_data(0x09, volume);
    send_data(0x0D, 0b00011100);
    send_data(0x00, LSB);
    send_data(0x01, MSB);
    sei();
}
// MIDI Channel 12
else if (chan == 11) 
{
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 0;
    timerTicks = 0;
    noteA = note;
    noteB = note;
    noteC = note;
    arpeggioFlipMe = true;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = tp[note - 12] * pitchBendFactor;
    periodB = tp[note + 12] * pitchBendFactor;
    periodC = tp[note] * pitchBendFactor;
    
    byte ALSB = (periodA & 0x00FF);
    byte AMSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF); 
    byte CMSB = ((periodC >> 8) & 0x000F);

    cli();
    send_data(0x08, 0x10);
    send_data(0x0B, BLSB);
    send_data(0x0C, BMSB);
    send_data(0x0D, 0b00001100);
    send_data(0x00, ALSB);
    send_data(0x01, AMSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);    
    sei();
}
// MIDI Channel 13
else if (chan == 12)
{
    noteActiveA = 1;
    noteActiveB = 1;
    noteActiveC = 1;
    detuneActiveC = 0;
    timerTicks = 0;
    noteA = note;
    noteB = note;
    noteC = note;
    arpeggioFlipMe = true;
    arpeggioCounter = 0;
    float pitchBendFactor = pow(2.0, pitchBendValue / pitchBendRange);
    periodA = tp[note - 12] * pitchBendFactor;    
    periodB = tp[note - 12] * pitchBendFactor;
    periodC = tp[note] * pitchBendFactor;
    
    byte ALSB = (periodA & 0x00FF);
    byte AMSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);

    cli();
    send_data(0x08, 0x10);
    send_data(0x0B, BLSB);
    send_data(0x0C, BMSB);
    send_data(0x00, ALSB);
    send_data(0x01, AMSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);
    send_data(0x0D, 0b00101100);
    sei();
}
// MIDI Channel 14
else if (chan == 13)
{
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
    int periodA = (tp[note]) * pitchBendFactor;
    int periodB = (tp[note]) * pitchBendFactor;
    int periodC = (tp[note] + detuneValue) * pitchBendFactor;

    byte ALSB = (periodA & 0x00FF);
    byte AMSB = ((periodA >> 8) & 0x000F);
    byte BLSB = (periodB & 0x00FF);
    byte BMSB = ((periodB >> 8) & 0x000F);
    byte CLSB = (periodC & 0x00FF);
    byte CMSB = ((periodC >> 8) & 0x000F);

    cli();
    send_data(0x00, ALSB);
    send_data(0x01, AMSB);
    send_data(0x02, BLSB);
    send_data(0x03, BMSB);
    send_data(0x04, CLSB);
    send_data(0x05, CMSB);
    send_data(0x08, volume);
    send_data(0x09, volume);
    send_data(0x0A, volume);
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
void stopNote(byte note, byte chan)
{
// MIDI Channel 1
    if (chan == 0 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteA = periodA = 0;
        arpeggioFlipMe = false;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        sei();
    }
// MIDI Channel 2
    else if (chan == 1 && note == noteB) {
        timerTicks = 0;
        noteActiveB = 0;
        noteB = periodB = 0;
        arpeggioFlipMe = false;
        cli();
        send_data(0x02, 0);
        send_data(0x03, 0);
        sei();
    }
// MIDI Channel 3
    else if (chan == 2 && note == noteC) {
        timerTicks = 0;
        noteActiveC = 0;
        noteC = periodC = 0;
        arpeggioFlipMe = false;
        cli();
        send_data(0x04, 0);
        send_data(0x05, 0);
        sei();
    }
// MIDI Channel 4
    else if (chan == 3 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        sei();
    }
// MIDI Channel 5
    else if (chan == 4 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
        arpeggioFlipMe = false;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x04, 0);
        send_data(0x05, 0);
        sei();
    }
// MIDI Channel 6
    else if (chan == 5 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteA = periodA = 0;
        arpeggioFlipMe = false;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        send_data(0x0D, 0); 
        send_data(0x08, 127);
        sei();
    }
// MIDI Channel 7
    else if (chan == 6 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteA = periodA = 0;
        arpeggioFlipMe = false;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        send_data(0x0D, 0);
        sei();
    }
// MIDI Channel 8
    else if (chan == 7 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        arpeggioFlipMe = false;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        send_data(0x0D, 0);
        send_data(0x08, AmaxVolume);
        sei();
    }
// MIDI Channel 9
    else if (chan == 8 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        arpeggioFlipMe = false;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x0D, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        send_data(0x08, AmaxVolume);
        sei();
    }
// MIDI Channel 11
    else if (chan == 10 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveC = 0;
        noteA = periodA = 0;
        noteC = periodC = 0;
        arpeggioFlipMe = false;
        cli();
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x04, 0);
        send_data(0x05, 0);
        send_data(0x0D, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        send_data(0x08, 0);
        sei();
    }
// MIDI Channel 12
    else if (chan == 11 && note == noteA) {        
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
        arpeggioFlipMe = false;

        cli(); 
        send_data(0x08, 0x00);
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x04, 0);
        send_data(0x05, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        send_data(0x0D, 0);
        sei();
    }
// MIDI Channel 13
    else if (chan == 12 && note == noteA) {
        timerTicks = 0;
        noteActiveA = 0;
        noteActiveB = 0;
        noteActiveC = 0;
        noteA = periodA = 0;
        noteB = periodB = 0;
        noteC = periodC = 0;
        arpeggioFlipMe = false;

        cli();
        send_data(0x08, 0x00);
        send_data(0x00, 0);
        send_data(0x01, 0);
        send_data(0x02, 0);
        send_data(0x03, 0);
        send_data(0x04, 0);
        send_data(0x05, 0);
        send_data(0x0B, 0);
        send_data(0x0C, 0);
        sei(); 
    }
// MIDI Channel 14
    else if (chan == 13 && note == noteA) {
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
        sei();
    }
}
