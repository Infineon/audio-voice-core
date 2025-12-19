## Automatic Gain Control (AGC)


The AGC (Automatic Gain Control) algorithm automatically adjusts the gain of the input audio signal to maintain a consistent output level. The following example demonstrates a typical AGC application flow, including configuration, memory management, initialization, and frame-by-frame processing.

**Technical Details:**
- The AGC supports both mono and stereo channels with 16K sampling rate and 160 sample (i.e. 10ms) frame size.
- To enable AGC functionality, add `ENABLE_IFX_AGC` define in your application makefile.
- AGC parameters such as attack time, release time, target level, maximum gain, and ratio are configurable.
- The algorithm works frame-by-frame, analyzing the input signal level and applying gain adjustments based on the difference from the target level.
- Attack and release times control how quickly the gain responds to increases or decreases in signal level, preventing abrupt changes and preserving audio quality.
- Functions are provided for initialization, configuration, and processing of audio frames.
- The code is modular, allowing integration into larger audio processing pipelines.

### Makefile Configuration

To enable AGC functionality in your application, add the following define to your makefile:

```makefile
DEFINES += ENABLE_IFX_AGC
```

### High-Level Application Code Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "ifx_pre_post_process.h"
#include "ifx_sp_utils_priv.h"

int32_t post_proc_agc_prms[] = {
    0,     // configuration version
    16000, // sampling rate
    160,   // input frame size
    IFX_POST_PROCESS_IP_COMPONENT_AGC, // AGC component ID
    AGC_PARMS_SIZE, // number of parameters
    15,    // snr_th
    21,    // th_rel
    1,     // att_time_ms
    30,    // release_time_ms
    5,     // ratio
    15,    // Mgain_dB
    0      // smooth_mode
};

int agc_example_app(void)
{
    uint32_t ErrIdx = 0;
    int ret;
    void *model_xx_obj = NULL;
    ifx_stc_pre_post_process_info_t post_proc_agc_info;
    int16_t *input_frame;   // assign input audio frame
    int16_t *output_frame;  // allocate output buffer

    // Step 1: Parse and get required memory for AGC configuration
    ret = ifx_pre_post_process_parse(post_proc_agc_prms, &post_proc_agc_info);
    if (ret != 0) {
        printf("AGC parse failed! Error code=%x\n", ret);
        return -1;
    }

    // Step 2: Allocate memory
    post_proc_agc_info.memory.persistent_mem_pt = malloc(post_proc_agc_info.memory.persistent_mem);
    post_proc_agc_info.memory.scratch_mem_pt = malloc(post_proc_agc_info.memory.scratch_mem);
    output_frame = malloc(post_proc_agc_info.output_size * sizeof(int16_t));
    if (!post_proc_agc_info.memory.persistent_mem_pt || !post_proc_agc_info.memory.scratch_mem_pt || !output_frame) {
        printf("AGC memory allocation failed!\n");
        return -1;
    }

    // Step 3: Initialize AGC
    ErrIdx = ifx_pre_post_process_init(post_proc_agc_prms, &model_xx_obj, &post_proc_agc_info);
    if (ErrIdx) {
        printf("AGC initialization failed! Error code=%x\n", ErrIdx);
        return -1;
    }

    // Step 4: Set the target level and audio mode ( SPEECH_MODE, MUSIC_MODE)
    float agc_target_level = 0.0f;
    ErrIdx = ifx_agc_set_target_level_and_mode(model_xx_obj, agc_target_level, SPEECH_MODE);
    if (ErrIdx != IFX_SP_ENH_SUCCESS) {
        printf("AGC set_target_level_and_mode failed! Error code=%x\n", ErrIdx);
        return -1;
    }

    // Step 6: Run AGC processing (example for one frame)
    ErrIdx = ifx_time_post_process(input_frame, model_xx_obj, IFX_POST_PROCESS_IP_COMPONENT_AGC, output_frame);
    if (ErrIdx != IFX_SP_ENH_SUCCESS) {
        printf("AGC processing failed! Error code=%x\n", ErrIdx);
        return -1;
    }

    // Step 5: Free memory
    free(post_proc_agc_info.memory.scratch_mem_pt);
    free(post_proc_agc_info.memory.persistent_mem_pt);
    free(output_frame);
    return 0;
}
```