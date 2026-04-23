/******************************************************************************
* File Name: cy_post_process.h
*
* Description: Post processing header file with data structures & APIs.
*
* Related Document: See README.md
*
*******************************************************************************
* (c) 2021, Infineon Technologies Company. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* ("Software"), is owned by Infineon Technologies Company (Infineon) or one of its
* subsidiaries and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software ("EULA").
*
* If no EULA applies, Infineon hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Infineon's integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Infineon.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Infineon
* reserves the right to make changes to the Software without notice. Infineon
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Infineon does
* not authorize its products for use in any products where a malfunction or
* failure of the Infineon product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Infineon's product in a High Risk Product, the manufacturer of such
* system or application assumes all risk of such use and in doing so agrees to
* indemnify Infineon against all liability.
*******************************************************************************/

/*******************************************************************************
* Include guard
*******************************************************************************/
#ifndef __CY_POST_PROCESS_H
#define __CY_POST_PROCESS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cy_errors.h"
#include "ifx_pre_post_process.h"

typedef struct
{
    int sampling_rate; // Sampling rate
    int number_of_classes; // Number of classes for post processing
    int frame_rate; // frame rate per second
    int lookback_buffer_length; // loockback buffer length, in samples
    int stacked_frame_delay; // NN stacked frame delay, in samples
    int detection_threshold; // upper 16bit is detection_threshold, lower 16bit is set (update) flag
} ifx_hmms_post_process_config_params_t;

typedef struct
{
    int configuration_version; // configuration version, 0 for manully generated parameter file
    int sampling_rate; // Sampling rate
    int frame_size; // audio frame size in samples
    int component_id; // component ID
    int num_parms; // number of parameters
    int ww_series; // number of repeated keywords
    int ww_tokens; // number of tokens per keyword
    int garbage_count_threshold; // garbage count threshold
    int garbage_count_2nd_threshold; // garbage count 2nd threshold
    int timeout_threshold; // timeout threshold
    int prob_thresholds[MAX_WW_TOKENS]; // probability thresholds for each keyword token
    int pass_count_thresholds[MAX_WW_TOKENS]; // pass count thresholds for each keyword token
    int gap_thresholds[MAX_WW_TOKENS]; // gap thresholds for each keyword token
} ifx_lpwwd_post_process_config_params_t;

typedef struct
{
    ifx_stc_pre_post_process_info_t pp_info;
    void* pp_handle;
} cy_inference_post_process_handle;

cy_rslt_t cy_inference_post_process_init(void* config, cy_inference_post_process_handle** handle, int32_t component_id);
cy_rslt_t cy_inference_post_process(cy_inference_post_process_handle* handle, IFX_PPINPUT_DATA_TYPE_T* output_score, int32_t* decision);
cy_rslt_t cy_inference_post_process_reset(cy_inference_post_process_handle* handle);
cy_rslt_t cy_inference_post_process_deinit(cy_inference_post_process_handle* handle);

#ifdef __cplusplus
}
#endif

#endif /*__CY_POST_PROCESS_H */
/* [] END OF FILE */
