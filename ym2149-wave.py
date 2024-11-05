import numpy as np
from scipy.io import wavfile

# If your sample output is too slow or too fast try exporting your .wav file at different frequencies.

def convert_pcm_to_array(filename, output_range=(0, 15)):
    # Step 1: Read the PCM file (assuming it's a WAV file)
    sample_rate, data = wavfile.read(filename)
    
    # Step 2: If stereo, take only one channel
    if data.ndim > 1:
        data = data[:, 0]
    
    # Step 3: Normalize data to 0-15 range
    data_min, data_max = data.min(), data.max()
    scaled_data = (data - data_min) / (data_max - data_min)  # Scale to 0.0 - 1.0
    quantized_data = np.round(scaled_data * (output_range[1] - output_range[0]))  # Scale to 0-15 range
    
    # Convert to integers and constrain values
    quantized_data = np.clip(quantized_data, output_range[0], output_range[1]).astype(int)
    
    # Step 4: Print the array and the count of integers
    array_str = ", ".join(map(str, quantized_data))
    print(f"Array: {array_str}")
    print(f"Count of integers in array: {len(quantized_data)}")

# Use the function
convert_pcm_to_array('path to .wav')

# Outputs 'PROGMEM const char' values and 'const int' length value for YM2149 code samples.
