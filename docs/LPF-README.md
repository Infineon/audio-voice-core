## LPF (Low-Pass Filter)

The LPF module provides low-pass filtering for audio signals. It attenuates high-frequency components and reduces noise, improving audio quality before further processing or output. Below is a typical initialization and frame-by-frame processing flow using the provided API.

**Technical Details:**
- 4th-order Butterworth Low-Pass Filter (LPF) for audio signals
- Hardcoded coefficients for sample rates: 16kHz, 44.1kHz, and 48kHz
- Cutoff frequency: **7000 Hz** for all supported sample rates
- To enable LPF functionality, add `ENABLE_IFX_PRE_PROCESS_ASRC_LPF` define in your application makefile.
- Fixed-point implementation for embedded platforms
- Supports mono and stereo channels

### Makefile Configuration

To enable LPF functionality in your application, add the following define to your makefile:

```makefile
DEFINES += ENABLE_IFX_PRE_PROCESS_ASRC_LPF
```

### Typical Application Flow

```c
#include <stdio.h>
#include <stdlib.h>
#include "ifx_sp_utils.h"
#include "ifx_pre_post_process.h"

int32_t lpf_config_prms[] = {
    0,      // configuration version
    16000,  // sampling rate
    160,    // input frame size
    IFX_PRE_PROCESS_IP_COMPONENT_ASRC_LPF, // IP component ID: preprocess LPF
    0       // number of parameters
};

int lpf_example_app(void)
{
    uint32_t ErrIdx = 0;
    int ret;
    void *model_xx_obj;
    ifx_stc_pre_post_process_info_t lpf_info;
    int16_t *in_buffer_fixed16, *out_buffer_fixed16;

    // Step 1: Parse and get required memory for LPF configuration
    ret = ifx_pre_post_process_parse(lpf_config_prms, &lpf_info);
    if (ret != 0) {
        printf("Error! LPF parse failed! Error code=%x\n", ret);
        return -1;
    }

    // Step 2: Allocate memory
    lpf_info.memory.persistent_mem_pt = malloc(lpf_info.memory.persistent_mem);
    lpf_info.memory.scratch_mem_pt = malloc(lpf_info.memory.scratch_mem);
    out_buffer_fixed16 = malloc(lpf_info.output_size * sizeof(int16_t));
    if (!lpf_info.memory.persistent_mem_pt || !lpf_info.memory.scratch_mem_pt || !out_buffer_fixed16) {
        printf("Error! LPF memory allocation failed!\n");
        return -1;
    }

    // Step 3: Initialize LPF
    ErrIdx = ifx_pre_post_process_init(lpf_config_prms, &model_xx_obj, &lpf_info);
    if (ErrIdx) {
        printf("Error! LPF initialization failed! Error code=%x\n", ErrIdx);
        return -1;
    }

    // Step 4: Process audio frames (example for one frame, mono channel)
    // in_buffer_fixed16: assign input audio frame (mono)
    // For stereo, provide both input and output buffers for the second channel.
    ErrIdx = ifx_time_pre_process(in_buffer_fixed16, NULL, model_xx_obj, IFX_PRE_PROCESS_IP_COMPONENT_ASRC_LPF, out_buffer_fixed16, NULL);
    if (ErrIdx != IFX_SP_ENH_SUCCESS) {
        printf("LPF processing failed! Error code=%x\n", ErrIdx);
        return -1;
    }

    // Step 5: Cleanup
    free(lpf_info.memory.scratch_mem_pt);
    free(lpf_info.memory.persistent_mem_pt);
    free(out_buffer_fixed16);
    return 0;
}
```

### Integration Notes

**Integration Notes:**
- Ensure input and output buffers are properly allocated and sized for your frame configuration.
- Use the provided configuration parameters and API for initialization and processing.
- The configuration parameters should match your sample rate and frame size requirements.
