/*
 * (c) 2025, Infineon Technologies AG, or an affiliate of Infineon
 * Technologies AG. All rights reserved.
 * This software, associated documentation and materials ("Software") is
 * owned by Infineon Technologies AG or one of its affiliates ("Infineon")
 * and is protected by and subject to worldwide patent protection, worldwide
 * copyright laws, and international treaty provisions. Therefore, you may use
 * this Software only as provided in the license agreement accompanying the
 * software package from which you obtained this Software. If no license
 * agreement applies, then any use, reproduction, modification, translation, or
 * compilation of this Software is prohibited without the express written
 * permission of Infineon.
 *
 * Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
 * IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
 * THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
 * SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
 * Infineon reserves the right to make changes to the Software without notice.
 * You are responsible for properly designing, programming, and testing the
 * functionality and safety of your intended application of the Software, as
 * well as complying with any legal requirements related to its use. Infineon
 * does not guarantee that the Software will be free from intrusion, data theft
 * or loss, or other breaches ("Security Breaches"), and Infineon shall have
 * no liability arising out of any Security Breaches. Unless otherwise
 * explicitly approved by Infineon, the Software may not be used in any
 * application where a failure of the Product or any consequences of the use
 * thereof can reasonably be expected to result in personal injury.
 */

/** @file
 *
 */

#ifndef HPF_FX_H
#define HPF_FX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//
// Initialization of 4th-order Butterworth HPF implemented by two stages
// of Direct Form II biquads.
//
// Run hpf_design/design_hpf.m to generate coefficients corresponding
// to given sample rate and cutoff frequency.
//

#if 1
// cutoff = 60 Hz
#define HPF_A11_FX_8kHz (-32152)    // = (((int16_t)(-1.962403775249819f*16384))); // Q14
#define HPF_A12_FX_8kHz (31607)     // = (((int16_t)(0.964584709925638f*32768))); // Q15
#define HPF_A21_FX_8kHz (-31366)    // = (((int16_t)(-1.914461090592186f*16384))); // Q14
#define HPF_A22_FX_8kHz (30034)     // = (((int16_t)(0.916588743744223f*32768))); // Q15
#define HPF_GAIN_FX_8kHz (30811)    // = (((int16_t)(0.940280536598276f*32768))); // Q15
#define HPF_A11_FX_16kHz (-32466)   // = (((int16_t)(-1.981579078857877f*16384))); // Q14
#define HPF_A12_FX_16kHz (32182)    // = (((int16_t)(0.982129258043927f*32768))); // Q15
#define HPF_A21_FX_16kHz (-32061)   // = (((int16_t)(-1.956851282961522f*16384))); // Q14
#define HPF_A22_FX_16kHz (31371)    // = (((int16_t)(0.957394596552974f*32768))); // Q15
#define HPF_GAIN_FX_16kHz (31774)   // = (((int16_t)(0.969683064082197f*32768))); // Q15
#define HPF_A11_FX_44_1kHz (-32659)   // = (((int16_t)(-1.993405796331904f*16384))); // Q14
#define HPF_A12_FX_44_1kHz (32554)    // = (((int16_t)(0.993478635336752f*32768))); // Q15
#define HPF_A21_FX_44_1kHz (-32510)   // = (((int16_t)(-1.984255795249836f*16384))); // Q14
#define HPF_A22_FX_44_1kHz (32254)    // = (((int16_t)(0.984328299913841f*32768))); // Q15
#define HPF_GAIN_FX_44_1kHz (32404)   // = (((int16_t)(0.988892884048494f*32768))); // Q15
#define HPF_A11_FX_48kHz (-32668)   // = (((int16_t)(-1.993945397248702f*16384))); // Q14
#define HPF_A12_FX_48kHz (32571)    // = (((int16_t)(0.994006897117715f*32768))); // Q15
#define HPF_A21_FX_48kHz (-32530)   // = (((int16_t)(-1.985531185289479f*16384))); // Q14
#define HPF_A22_FX_48kHz (32295)    // = (((int16_t)(0.985592425636373f*32768))); // Q15
#define HPF_GAIN_FX_48kHz (32433)   // = (((int16_t)(0.989790719712775f*32768))); // Q15
#else
// cutoff = 120 Hz
#define HPF_A11_FX_8kHz (-31488)    // = (((int16_t)(-1.921908893578822f*16384))); // Q14
#define HPF_A12_FX_8kHz (30489)     // = (((int16_t)(0.930476416247046f*32768))); // Q15
#define HPF_A21_FX_8kHz (-30013)    // = (((int16_t)(-1.831853863092364f*16384))); // Q14
#define HPF_A22_FX_8kHz (27525)     // = (((int16_t)(0.840019936702488f*32768))); // Q15
#define HPF_GAIN_FX_8kHz (28969)    // = (((int16_t)(0.884092042866511f*32768))); // Q15
#define HPF_A11_FX_16kHz (-32152)   // = (((int16_t)(-1.962403775249819f*16384))); // Q14
#define HPF_A12_FX_16kHz (31607)    // = (((int16_t)(0.964584709925638f*32768))); // Q15
#define HPF_A21_FX_16kHz (-31366)   // = (((int16_t)(-1.914461090592186f*16384))); // Q14
#define HPF_A22_FX_16kHz (30034)    // = (((int16_t)(0.916588743744223f*32768))); // Q15
#define HPF_GAIN_FX_16kHz (30811)   // = (((int16_t)(0.940280536598276f*32768))); // Q15
#define HPF_A11_FX_44_1kHz (-32550)   // = (((int16_t)(-1.986709728726518*16384))); // Q14
#define HPF_A12_FX_44_1kHz (32342)    // = (((int16_t)(0.987000132577525*32768))); // Q15
#define HPF_A21_FX_44_1kHz (-32253)   // = (((int16_t)(-1.968613652455649*16384))); // Q14
#define HPF_A22_FX_44_1kHz (31748)    // = (((int16_t)(0.968901411144074*32768))); // Q15
#define HPF_GAIN_FX_44_1kHz (32044)   // = (((int16_t)(0.977908902328715*32768))); // Q15
#define HPF_A11_FX_48kHz (-32568)   // = (((int16_t)(-1.987804709796042f*16384))); // Q14
#define HPF_A12_FX_48kHz (32376)    // = (((int16_t)(0.988049970587248f*32768))); // Q15
#define HPF_A21_FX_48kHz (-32295)   // = (((int16_t)(-1.971148608851041f*16384))); // Q14
#define HPF_A22_FX_48kHz (31830)    // = (((int16_t)(0.971391814566878f*32768))); // Q15
#define HPF_GAIN_FX_48kHz (32102)   // = (((int16_t)(0.979685487190403f*32768))); // Q15
#endif

// Q safety shift for overlow protection during filtering
#define HPF_QS_8kHz (7)
#define HPF_QS_16kHz (8)
#define HPF_QS_44_1kHz (11)
#define HPF_QS_48kHz (11)

typedef struct 
{
    int16_t af[2*2];   /* filter coefficients */
    int16_t gainf;
    int16_t qs;
} ifx_afe_hpf_coeff_struct_t;

typedef struct
{
    int32_t wf[2][3];   /* filter states of one mic */
} ifx_afe_hpf_state_struct_t;

typedef struct
{
    ifx_afe_hpf_coeff_struct_t coeff;
    ifx_afe_hpf_state_struct_t state[2];   /* filter states of two mics */
} ifx_afe_hpf_struct_t;

void afe_hpf(int16_t* inbuf, int16_t* outbuf, uint32_t frame_size, ifx_afe_hpf_coeff_struct_t coef_mem, ifx_afe_hpf_state_struct_t* state_mem);

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif // HPF_FX_H
