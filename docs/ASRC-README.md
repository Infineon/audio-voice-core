## ASRC (Asynchronous Sample Rate Converter)
This Utility library provides two essential functions for audio systems:
1. **Conversion between sampling rates:** Seamlessly converts audio streams between different sample rates (e.g., 16kHz to 48kHz), supporting a wide range from 8000 Hz up to 96000 Hz.
2. **Clock Drift Handling:** Dynamically compensates for clock drift between input and output devices, ensuring smooth audio playback and preventing buffer underflows/overflows.

It is designed for embedded platforms and can be used directly by applications for high-quality audio resampling and robust clock synchronization.

### Handling Clock Drift
In real-world audio systems, the input and output devices may have slightly different clock rates, causing their sample rates to drift apart over time. This can lead to buffer underflows, overflows, or audio glitches if not corrected.

The ASRC API allows you to compensate for clock drift by dynamically adjusting the output sample rate. You can set the drift in samples per second using the `IFX_SetClockDrift` function. The ASRC spreads this adjustment evenly across the output, ensuring smooth audio playback and preventing buffer issues.

For example, if the playback device's clock is running faster than the source, a positive drift value will generate extra samples to keep up. If the clock is slower, a negative drift value will remove samples. This feature is essential for long-running audio streams between devices with independent clocks, such as USB audio interfaces, wireless audio links, or multi-board embedded systems.


### Features
- Converts audio streams between different sample rates
- Supports input and output sample rates from **8000 Hz up to 96000 Hz**
- Maintains signal quality and minimizes aliasing
- Fixed-point implementation for embedded platforms
- Includes utility functions for math and filter operations

### Typical Application Flow

```c
#include "IFX_asrc.h"

// Allocate ASRC memory structure for each channel
struct IFX_ASRC_STRUCT asrcmem;

// Input and output buffers (int32_t)
int32_t input_buffer[INPUT_BUFFER_MAX];   // Input buffer
int32_t output_buffer[OUTPUT_BUFFER_MAX]; // Output buffer
int16_t input_length;                     // Number of input samples (1 to INPUT_BUFFER_MAX)
int16_t output_length;                    // Will hold number of output samples

// Step 1: Initialize ASRC for desired input/output sample rates
init_IFX_asrc(&asrcmem, 16000, 48000); // e.g., 16kHz to 48kHz

// Step 2: Set clock drift if needed (samples/sec, Q_CDPS=10)
// For example, to add +5 samples/sec drift:
IFX_SetClockDrift(&asrcmem, 5 << 10); // cdps = Actual_cdps * (1 << Q_CDPS)

// Step 3: Perform sample rate conversion
IFX_asrc(input_buffer, input_length, output_buffer, &output_length, &asrcmem);

// output_buffer now contains output_length samples at the output sample rate
```

### Integration Notes
- Ensure input and output buffers are properly allocated and sized for your frame configuration.
- Configure ASRC parameters according to your application requirements.
- Refer to the source code and API documentation for advanced usage and integration.