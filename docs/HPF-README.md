## HPF (High-Pass Filter)

The HPF module provides high-pass filtering for audio signals. It attenuates low-frequency components and reduces unwanted low-frequency noise, improving audio quality before further processing or output. Below is a typical initialization and frame-by-frame processing flow using the provided API.

**Technical Details:**
- 4th-order Butterworth High-Pass Filter (HPF) for audio signals
- Hardcoded coefficients for sample rates: 16kHz, 44.1kHz, and 48kHz
- Cutoff frequency: **60 Hz** for all supported sample rates
- To enable HPF functionality, add `ENABLE_IFX_PRE_PROCESS_HPF` define in your application makefile.
- Fixed-point implementation for embedded platforms
- Implemented using two stages of Direct Form II biquads

### Makefile Configuration

To enable HPF functionality in your application, add the following define to your makefile:

```makefile
DEFINES += ENABLE_IFX_PRE_PROCESS_HPF
```

### Typical Application Flow

```c
#include <stdio.h>
#include <stdlib.h>
#include "ifx_sp_utils.h"
#include "ifx_pre_post_process.h"

int32_t hpf_config_prms[] = {
    0,      // configuration version
    16000,  // sampling rate
    160,    // input frame size
    IFX_PRE_PROCESS_IP_COMPONENT_HPF, // IP component ID: preprocess HPF
    0       // number of parameters
};

int hpf_example_app(void)
{
    uint32_t ErrIdx = 0;
    int ret;
    void *model_xx_obj;
    ifx_stc_pre_post_process_info_t hpf_info;
    int16_t *in_buffer_fixed16, *out_buffer_fixed16;

    // Step 1: Parse and get required memory for HPF configuration
    ret = ifx_pre_post_process_parse(hpf_config_prms, &hpf_info);
    if (ret != 0) {
        printf("Error! HPF parse failed! Error code=%x\n", ret);
        return -1;
    }

    // Step 2: Allocate memory
    hpf_info.memory.persistent_mem_pt = malloc(hpf_info.memory.persistent_mem);
    hpf_info.memory.scratch_mem_pt = malloc(hpf_info.memory.scratch_mem);
    out_buffer_fixed16 = malloc(hpf_info.output_size * sizeof(int16_t));
    if (!hpf_info.memory.persistent_mem_pt || !hpf_info.memory.scratch_mem_pt || !out_buffer_fixed16) {
        printf("Error! HPF memory allocation failed!\n");
        return -1;
    }

    // Step 3: Initialize HPF
    ErrIdx = ifx_pre_post_process_init(hpf_config_prms, &model_xx_obj, &hpf_info);
    if (ErrIdx) {
        printf("Error! HPF initialization failed! Error code=%x\n", ErrIdx);
        return -1;
    }

    // Step 4: Process audio frames (example for one frame, mono channel)
    // in_buffer_fixed16: assign input audio frame (mono)
    // For stereo, provide both input and output buffers for the second channel.
    ErrIdx = ifx_time_pre_process(in_buffer_fixed16, NULL, model_xx_obj, IFX_PRE_PROCESS_IP_COMPONENT_HPF, out_buffer_fixed16, NULL);
    if (ErrIdx != IFX_SP_ENH_SUCCESS) {
        printf("HPF processing failed! Error code=%x\n", ErrIdx);
        return -1;
    }

    // Step 5: Cleanup
    free(hpf_info.memory.scratch_mem_pt);
    free(hpf_info.memory.persistent_mem_pt);
    free(out_buffer_fixed16);
    return 0;
}
```

### Integration Notes

**Integration Notes:**
- Ensure input and output buffers are properly allocated and sized for your frame configuration.
- Use the provided configuration parameters and API for initialization and processing.
- The configuration parameters should match your sample rate and frame size requirements.
- HPF is commonly used to remove DC offset and low-frequency noise from audio signals.
- The 60 Hz cutoff frequency is suitable for removing power line interference and other low-frequency artifacts.

### Supported Sample Rates

The HPF module supports the following sample rates with pre-calculated coefficients:
- 16 kHz
- 44.1 kHz
- 48 kHz