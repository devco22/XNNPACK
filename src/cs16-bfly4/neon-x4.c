// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include <xnnpack/math.h>
#include <xnnpack/fft.h>

#include <arm_neon.h>

void xnn_cs16_bfly4_ukernel__neon_x4(
    size_t batch,
    size_t samples,
    int16_t* data,
    const int16_t* twiddle,
    size_t stride)
{
  assert(batch != 0);
  assert(samples != 0);
  assert(samples % (sizeof(int16_t) * 8) == 0);
  assert(data != NULL);
  assert(stride != 0);
  assert(twiddle != NULL);

  const int16x4_t vdiv4 = vdup_n_s16(8191);

  int16_t* data3 = data;
  do {
    int16_t* data0 = data3;
    int16_t* data1 = (int16_t*) ((uintptr_t) data0 + samples);
    int16_t* data2 = (int16_t*) ((uintptr_t) data1 + samples);
    data3 = (int16_t*) ((uintptr_t) data2 + samples);

    const int16_t* tw1 = twiddle;
    const int16_t* tw2 = twiddle;
    const int16_t* tw3 = twiddle;

    size_t s = samples;
    for (; s >= sizeof(int16_t) * 8; s -= sizeof(int16_t) * 8) {
      int16x4x2_t vout0 = vld2_s16(data0);
      int16x4x2_t vout1 = vld2_s16(data1);
      int16x4x2_t vout2 = vld2_s16(data2);
      int16x4x2_t vout3 = vld2_s16(data3);

      int16x8_t vtw1 = vreinterpretq_s16_u32(vld1q_dup_u32((const void*) tw1));
      int16x8_t vtw2 = vreinterpretq_s16_u32(vld1q_dup_u32((const void*) tw2));
      int16x8_t vtw3 = vreinterpretq_s16_u32(vld1q_dup_u32((const void*) tw3));
      tw1 = (const int16_t*) ((uintptr_t) tw1 + stride);
      tw2 = (const int16_t*) ((uintptr_t) tw2 + stride * 2);
      tw3 = (const int16_t*) ((uintptr_t) tw3 + stride * 3);
      vtw1 = vreinterpretq_s16_u32(vld1q_lane_u32((const void*) tw1, vreinterpretq_u32_s16(vtw1), 1));
      vtw2 = vreinterpretq_s16_u32(vld1q_lane_u32((const void*) tw2, vreinterpretq_u32_s16(vtw2), 1));
      vtw3 = vreinterpretq_s16_u32(vld1q_lane_u32((const void*) tw3, vreinterpretq_u32_s16(vtw3), 1));
      tw1 = (const int16_t*) ((uintptr_t) tw1 + stride);
      tw2 = (const int16_t*) ((uintptr_t) tw2 + stride * 2);
      tw3 = (const int16_t*) ((uintptr_t) tw3 + stride * 3);
      vtw1 = vreinterpretq_s16_u32(vld1q_lane_u32((const void*) tw1, vreinterpretq_u32_s16(vtw1), 2));
      vtw2 = vreinterpretq_s16_u32(vld1q_lane_u32((const void*) tw2, vreinterpretq_u32_s16(vtw2), 2));
      vtw3 = vreinterpretq_s16_u32(vld1q_lane_u32((const void*) tw3, vreinterpretq_u32_s16(vtw3), 2));
      tw1 = (const int16_t*) ((uintptr_t) tw1 + stride);
      tw2 = (const int16_t*) ((uintptr_t) tw2 + stride * 2);
      tw3 = (const int16_t*) ((uintptr_t) tw3 + stride * 3);
      vtw1 = vreinterpretq_s16_u32(vld1q_lane_u32((const void*) tw1, vreinterpretq_u32_s16(vtw1), 3));
      vtw2 = vreinterpretq_s16_u32(vld1q_lane_u32((const void*) tw2, vreinterpretq_u32_s16(vtw2), 3));
      vtw3 = vreinterpretq_s16_u32(vld1q_lane_u32((const void*) tw3, vreinterpretq_u32_s16(vtw3), 3));
      tw1 = (const int16_t*) ((uintptr_t) tw1 + stride);
      tw2 = (const int16_t*) ((uintptr_t) tw2 + stride * 2);
      tw3 = (const int16_t*) ((uintptr_t) tw3 + stride * 3);

      // Note 32767 / 4 = 8191.  Should be 8192.
      vout0.val[0] = vqrdmulh_s16(vout0.val[0], vdiv4);
      vout0.val[1] = vqrdmulh_s16(vout0.val[1], vdiv4);
      vout1.val[0] = vqrdmulh_s16(vout1.val[0], vdiv4);
      vout1.val[1] = vqrdmulh_s16(vout1.val[1], vdiv4);
      vout2.val[0] = vqrdmulh_s16(vout2.val[0], vdiv4);
      vout2.val[1] = vqrdmulh_s16(vout2.val[1], vdiv4);
      vout3.val[0] = vqrdmulh_s16(vout3.val[0], vdiv4);
      vout3.val[1] = vqrdmulh_s16(vout3.val[1], vdiv4);

      const int16x4x2_t vtw1ri = vuzp_s16(vget_low_s16(vtw1), vget_high_s16(vtw1));
      const int16x4x2_t vtw2ri = vuzp_s16(vget_low_s16(vtw2), vget_high_s16(vtw2));
      const int16x4x2_t vtw3ri = vuzp_s16(vget_low_s16(vtw3), vget_high_s16(vtw3));
      int32x4_t vacc0r = vmull_s16(vout1.val[0], vtw1ri.val[0]);
      int32x4_t vacc1r = vmull_s16(vout2.val[0], vtw2ri.val[0]);
      int32x4_t vacc2r = vmull_s16(vout3.val[0], vtw3ri.val[0]);
      int32x4_t vacc0i = vmull_s16(vout1.val[0], vtw1ri.val[1]);
      int32x4_t vacc1i = vmull_s16(vout2.val[0], vtw2ri.val[1]);
      int32x4_t vacc2i = vmull_s16(vout3.val[0], vtw3ri.val[1]);
      vacc0r = vmlsl_s16(vacc0r, vout1.val[1], vtw1ri.val[1]);
      vacc1r = vmlsl_s16(vacc1r, vout2.val[1], vtw2ri.val[1]);
      vacc2r = vmlsl_s16(vacc2r, vout3.val[1], vtw3ri.val[1]);
      vacc0i = vmlal_s16(vacc0i, vout1.val[1], vtw1ri.val[0]);
      vacc1i = vmlal_s16(vacc1i, vout2.val[1], vtw2ri.val[0]);
      vacc2i = vmlal_s16(vacc2i, vout3.val[1], vtw3ri.val[0]);
      int16x4_t vtmp0r = vrshrn_n_s32(vacc0r, 15);
      int16x4_t vtmp1r = vrshrn_n_s32(vacc1r, 15);
      int16x4_t vtmp2r = vrshrn_n_s32(vacc2r, 15);
      int16x4_t vtmp0i = vrshrn_n_s32(vacc0i, 15);
      int16x4_t vtmp1i = vrshrn_n_s32(vacc1i, 15);
      int16x4_t vtmp2i = vrshrn_n_s32(vacc2i, 15);

      const int16x4_t vtmp4r = vsub_s16(vtmp0r, vtmp2r);
      const int16x4_t vtmp4i = vsub_s16(vtmp0i, vtmp2i);
      const int16x4_t vtmp3r = vadd_s16(vtmp0r, vtmp2r);
      const int16x4_t vtmp3i = vadd_s16(vtmp0i, vtmp2i);

      const int16x4_t vtmp5r = vsub_s16(vout0.val[0], vtmp1r);
      const int16x4_t vtmp5i = vsub_s16(vout0.val[1], vtmp1i);
      vout0.val[0] = vadd_s16(vout0.val[0], vtmp1r);
      vout0.val[1] = vadd_s16(vout0.val[1], vtmp1i);

      vout2.val[0] = vsub_s16(vout0.val[0], vtmp3r);
      vout2.val[1] = vsub_s16(vout0.val[1], vtmp3i);
      vout0.val[0] = vadd_s16(vout0.val[0], vtmp3r);
      vout0.val[1] = vadd_s16(vout0.val[1], vtmp3i);

      vout1.val[0] = vadd_s16(vtmp5r, vtmp4i);
      vout1.val[1] = vsub_s16(vtmp5i, vtmp4r);
      vout3.val[0] = vsub_s16(vtmp5r, vtmp4i);
      vout3.val[1] = vadd_s16(vtmp5i, vtmp4r);

      vst2_s16(data0, vout0);  data0 += 8;
      vst2_s16(data1, vout1);  data1 += 8;
      vst2_s16(data2, vout2);  data2 += 8;
      vst2_s16(data3, vout3);  data3 += 8;
    }
  } while (--batch != 0);
}
