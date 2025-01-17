// Copyright 2023 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.
//
// Auto-generated file. Do not edit!
//   Specification: test/f32-rsum.yaml
//   Generator: tools/generate-reduce-test.py


#include <gtest/gtest.h>

#include <xnnpack/common.h>
#include <xnnpack/isa-checks.h>

#include <xnnpack/microparams-init.h>
#include <xnnpack/reduce.h>
#include "rsum-microkernel-tester.h"


#if XNN_ARCH_ARM || XNN_ARCH_ARM64
  TEST(F32_RSUM__NEON_X4, batch_eq_4) {
    TEST_REQUIRES_ARM_NEON;
    RSumMicrokernelTester()
      .batch_size(4)
      .Test(xnn_f32_rsum_ukernel__neon_x4, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__NEON_X4, batch_div_4) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 8; batch_size < 40; batch_size += 4) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X4, batch_lt_4) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 1; batch_size < 4; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X4, batch_gt_4) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 5; batch_size < 8; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X4, scale) {
    TEST_REQUIRES_ARM_NEON;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(5)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__neon_x4, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_ARM || XNN_ARCH_ARM64


#if XNN_ARCH_ARM || XNN_ARCH_ARM64
  TEST(F32_RSUM__NEON_X8_ACC2, batch_eq_8) {
    TEST_REQUIRES_ARM_NEON;
    RSumMicrokernelTester()
      .batch_size(8)
      .Test(xnn_f32_rsum_ukernel__neon_x8_acc2, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__NEON_X8_ACC2, batch_div_8) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 16; batch_size < 80; batch_size += 8) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X8_ACC2, batch_lt_8) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 1; batch_size < 8; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X8_ACC2, batch_gt_8) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 9; batch_size < 16; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X8_ACC2, scale) {
    TEST_REQUIRES_ARM_NEON;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(9)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__neon_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_ARM || XNN_ARCH_ARM64


#if XNN_ARCH_ARM || XNN_ARCH_ARM64
  TEST(F32_RSUM__NEON_X12_ACC3, batch_eq_12) {
    TEST_REQUIRES_ARM_NEON;
    RSumMicrokernelTester()
      .batch_size(12)
      .Test(xnn_f32_rsum_ukernel__neon_x12_acc3, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__NEON_X12_ACC3, batch_div_12) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 24; batch_size < 120; batch_size += 12) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X12_ACC3, batch_lt_12) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 1; batch_size < 12; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X12_ACC3, batch_gt_12) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 13; batch_size < 24; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X12_ACC3, scale) {
    TEST_REQUIRES_ARM_NEON;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(13)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__neon_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_ARM || XNN_ARCH_ARM64


#if XNN_ARCH_ARM || XNN_ARCH_ARM64
  TEST(F32_RSUM__NEON_X16_ACC2, batch_eq_16) {
    TEST_REQUIRES_ARM_NEON;
    RSumMicrokernelTester()
      .batch_size(16)
      .Test(xnn_f32_rsum_ukernel__neon_x16_acc2, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__NEON_X16_ACC2, batch_div_16) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 32; batch_size < 160; batch_size += 16) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X16_ACC2, batch_lt_16) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 1; batch_size < 16; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X16_ACC2, batch_gt_16) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 17; batch_size < 32; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X16_ACC2, scale) {
    TEST_REQUIRES_ARM_NEON;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(17)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__neon_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_ARM || XNN_ARCH_ARM64


#if XNN_ARCH_ARM || XNN_ARCH_ARM64
  TEST(F32_RSUM__NEON_X16_ACC4, batch_eq_16) {
    TEST_REQUIRES_ARM_NEON;
    RSumMicrokernelTester()
      .batch_size(16)
      .Test(xnn_f32_rsum_ukernel__neon_x16_acc4, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__NEON_X16_ACC4, batch_div_16) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 32; batch_size < 160; batch_size += 16) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X16_ACC4, batch_lt_16) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 1; batch_size < 16; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X16_ACC4, batch_gt_16) {
    TEST_REQUIRES_ARM_NEON;
    for (size_t batch_size = 17; batch_size < 32; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__neon_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__NEON_X16_ACC4, scale) {
    TEST_REQUIRES_ARM_NEON;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(17)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__neon_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_ARM || XNN_ARCH_ARM64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_RSUM__SSE_X4, batch_eq_4) {
    TEST_REQUIRES_X86_SSE;
    RSumMicrokernelTester()
      .batch_size(4)
      .Test(xnn_f32_rsum_ukernel__sse_x4, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__SSE_X4, batch_div_4) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 8; batch_size < 40; batch_size += 4) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X4, batch_lt_4) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size < 4; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X4, batch_gt_4) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 5; batch_size < 8; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X4, scale) {
    TEST_REQUIRES_X86_SSE;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(5)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__sse_x4, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_RSUM__SSE_X8_ACC2, batch_eq_8) {
    TEST_REQUIRES_X86_SSE;
    RSumMicrokernelTester()
      .batch_size(8)
      .Test(xnn_f32_rsum_ukernel__sse_x8_acc2, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__SSE_X8_ACC2, batch_div_8) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 16; batch_size < 80; batch_size += 8) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X8_ACC2, batch_lt_8) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size < 8; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X8_ACC2, batch_gt_8) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 9; batch_size < 16; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X8_ACC2, scale) {
    TEST_REQUIRES_X86_SSE;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(9)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__sse_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_RSUM__SSE_X12_ACC3, batch_eq_12) {
    TEST_REQUIRES_X86_SSE;
    RSumMicrokernelTester()
      .batch_size(12)
      .Test(xnn_f32_rsum_ukernel__sse_x12_acc3, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__SSE_X12_ACC3, batch_div_12) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 24; batch_size < 120; batch_size += 12) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X12_ACC3, batch_lt_12) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size < 12; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X12_ACC3, batch_gt_12) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 13; batch_size < 24; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X12_ACC3, scale) {
    TEST_REQUIRES_X86_SSE;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(13)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__sse_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_RSUM__SSE_X16_ACC2, batch_eq_16) {
    TEST_REQUIRES_X86_SSE;
    RSumMicrokernelTester()
      .batch_size(16)
      .Test(xnn_f32_rsum_ukernel__sse_x16_acc2, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__SSE_X16_ACC2, batch_div_16) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 32; batch_size < 160; batch_size += 16) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X16_ACC2, batch_lt_16) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size < 16; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X16_ACC2, batch_gt_16) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 17; batch_size < 32; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X16_ACC2, scale) {
    TEST_REQUIRES_X86_SSE;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(17)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__sse_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_RSUM__SSE_X16_ACC4, batch_eq_16) {
    TEST_REQUIRES_X86_SSE;
    RSumMicrokernelTester()
      .batch_size(16)
      .Test(xnn_f32_rsum_ukernel__sse_x16_acc4, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__SSE_X16_ACC4, batch_div_16) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 32; batch_size < 160; batch_size += 16) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X16_ACC4, batch_lt_16) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 1; batch_size < 16; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X16_ACC4, batch_gt_16) {
    TEST_REQUIRES_X86_SSE;
    for (size_t batch_size = 17; batch_size < 32; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__sse_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__SSE_X16_ACC4, scale) {
    TEST_REQUIRES_X86_SSE;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(17)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__sse_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_RSUM__AVX_X8, batch_eq_8) {
    TEST_REQUIRES_X86_AVX;
    RSumMicrokernelTester()
      .batch_size(8)
      .Test(xnn_f32_rsum_ukernel__avx_x8, xnn_init_f32_scale_avx_params);
  }

  TEST(F32_RSUM__AVX_X8, batch_div_8) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 16; batch_size < 80; batch_size += 8) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x8, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X8, batch_lt_8) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 1; batch_size < 8; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x8, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X8, batch_gt_8) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 9; batch_size < 16; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x8, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X8, scale) {
    TEST_REQUIRES_X86_AVX;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(9)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__avx_x8, xnn_init_f32_scale_avx_params);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_RSUM__AVX_X16_ACC2, batch_eq_16) {
    TEST_REQUIRES_X86_AVX;
    RSumMicrokernelTester()
      .batch_size(16)
      .Test(xnn_f32_rsum_ukernel__avx_x16_acc2, xnn_init_f32_scale_avx_params);
  }

  TEST(F32_RSUM__AVX_X16_ACC2, batch_div_16) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 32; batch_size < 160; batch_size += 16) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x16_acc2, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X16_ACC2, batch_lt_16) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 1; batch_size < 16; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x16_acc2, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X16_ACC2, batch_gt_16) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 17; batch_size < 32; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x16_acc2, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X16_ACC2, scale) {
    TEST_REQUIRES_X86_AVX;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(17)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__avx_x16_acc2, xnn_init_f32_scale_avx_params);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_RSUM__AVX_X24_ACC3, batch_eq_24) {
    TEST_REQUIRES_X86_AVX;
    RSumMicrokernelTester()
      .batch_size(24)
      .Test(xnn_f32_rsum_ukernel__avx_x24_acc3, xnn_init_f32_scale_avx_params);
  }

  TEST(F32_RSUM__AVX_X24_ACC3, batch_div_24) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 48; batch_size < 240; batch_size += 24) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x24_acc3, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X24_ACC3, batch_lt_24) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 1; batch_size < 24; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x24_acc3, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X24_ACC3, batch_gt_24) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 25; batch_size < 48; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x24_acc3, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X24_ACC3, scale) {
    TEST_REQUIRES_X86_AVX;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(25)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__avx_x24_acc3, xnn_init_f32_scale_avx_params);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_RSUM__AVX_X32_ACC2, batch_eq_32) {
    TEST_REQUIRES_X86_AVX;
    RSumMicrokernelTester()
      .batch_size(32)
      .Test(xnn_f32_rsum_ukernel__avx_x32_acc2, xnn_init_f32_scale_avx_params);
  }

  TEST(F32_RSUM__AVX_X32_ACC2, batch_div_32) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 64; batch_size < 320; batch_size += 32) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x32_acc2, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X32_ACC2, batch_lt_32) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 1; batch_size < 32; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x32_acc2, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X32_ACC2, batch_gt_32) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 33; batch_size < 64; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x32_acc2, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X32_ACC2, scale) {
    TEST_REQUIRES_X86_AVX;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(33)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__avx_x32_acc2, xnn_init_f32_scale_avx_params);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_X86 || XNN_ARCH_X86_64
  TEST(F32_RSUM__AVX_X32_ACC4, batch_eq_32) {
    TEST_REQUIRES_X86_AVX;
    RSumMicrokernelTester()
      .batch_size(32)
      .Test(xnn_f32_rsum_ukernel__avx_x32_acc4, xnn_init_f32_scale_avx_params);
  }

  TEST(F32_RSUM__AVX_X32_ACC4, batch_div_32) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 64; batch_size < 320; batch_size += 32) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x32_acc4, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X32_ACC4, batch_lt_32) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 1; batch_size < 32; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x32_acc4, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X32_ACC4, batch_gt_32) {
    TEST_REQUIRES_X86_AVX;
    for (size_t batch_size = 33; batch_size < 64; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__avx_x32_acc4, xnn_init_f32_scale_avx_params);
    }
  }

  TEST(F32_RSUM__AVX_X32_ACC4, scale) {
    TEST_REQUIRES_X86_AVX;
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(33)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__avx_x32_acc4, xnn_init_f32_scale_avx_params);
    }
  }
#endif  // XNN_ARCH_X86 || XNN_ARCH_X86_64


#if XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD
  TEST(F32_RSUM__WASMSIMD_X4, batch_eq_4) {
    RSumMicrokernelTester()
      .batch_size(4)
      .Test(xnn_f32_rsum_ukernel__wasmsimd_x4, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__WASMSIMD_X4, batch_div_4) {
    for (size_t batch_size = 8; batch_size < 40; batch_size += 4) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X4, batch_lt_4) {
    for (size_t batch_size = 1; batch_size < 4; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X4, batch_gt_4) {
    for (size_t batch_size = 5; batch_size < 8; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X4, scale) {
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(5)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x4, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD


#if XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD
  TEST(F32_RSUM__WASMSIMD_X8_ACC2, batch_eq_8) {
    RSumMicrokernelTester()
      .batch_size(8)
      .Test(xnn_f32_rsum_ukernel__wasmsimd_x8_acc2, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__WASMSIMD_X8_ACC2, batch_div_8) {
    for (size_t batch_size = 16; batch_size < 80; batch_size += 8) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X8_ACC2, batch_lt_8) {
    for (size_t batch_size = 1; batch_size < 8; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X8_ACC2, batch_gt_8) {
    for (size_t batch_size = 9; batch_size < 16; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X8_ACC2, scale) {
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(9)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x8_acc2, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD


#if XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD
  TEST(F32_RSUM__WASMSIMD_X12_ACC3, batch_eq_12) {
    RSumMicrokernelTester()
      .batch_size(12)
      .Test(xnn_f32_rsum_ukernel__wasmsimd_x12_acc3, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__WASMSIMD_X12_ACC3, batch_div_12) {
    for (size_t batch_size = 24; batch_size < 120; batch_size += 12) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X12_ACC3, batch_lt_12) {
    for (size_t batch_size = 1; batch_size < 12; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X12_ACC3, batch_gt_12) {
    for (size_t batch_size = 13; batch_size < 24; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X12_ACC3, scale) {
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(13)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x12_acc3, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD


#if XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD
  TEST(F32_RSUM__WASMSIMD_X16_ACC2, batch_eq_16) {
    RSumMicrokernelTester()
      .batch_size(16)
      .Test(xnn_f32_rsum_ukernel__wasmsimd_x16_acc2, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__WASMSIMD_X16_ACC2, batch_div_16) {
    for (size_t batch_size = 32; batch_size < 160; batch_size += 16) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X16_ACC2, batch_lt_16) {
    for (size_t batch_size = 1; batch_size < 16; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X16_ACC2, batch_gt_16) {
    for (size_t batch_size = 17; batch_size < 32; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X16_ACC2, scale) {
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(17)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x16_acc2, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD


#if XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD
  TEST(F32_RSUM__WASMSIMD_X16_ACC4, batch_eq_16) {
    RSumMicrokernelTester()
      .batch_size(16)
      .Test(xnn_f32_rsum_ukernel__wasmsimd_x16_acc4, xnn_init_f32_scale_scalar_params);
  }

  TEST(F32_RSUM__WASMSIMD_X16_ACC4, batch_div_16) {
    for (size_t batch_size = 32; batch_size < 160; batch_size += 16) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X16_ACC4, batch_lt_16) {
    for (size_t batch_size = 1; batch_size < 16; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X16_ACC4, batch_gt_16) {
    for (size_t batch_size = 17; batch_size < 32; batch_size++) {
      RSumMicrokernelTester()
        .batch_size(batch_size)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }

  TEST(F32_RSUM__WASMSIMD_X16_ACC4, scale) {
    for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
      RSumMicrokernelTester()
        .batch_size(17)
        .scale(scale)
        .Test(xnn_f32_rsum_ukernel__wasmsimd_x16_acc4, xnn_init_f32_scale_scalar_params);
    }
  }
#endif  // XNN_ARCH_WASMSIMD || XNN_ARCH_WASMRELAXEDSIMD


TEST(F32_RSUM__SCALAR_X1, batch_eq_1) {
  RSumMicrokernelTester()
    .batch_size(1)
    .Test(xnn_f32_rsum_ukernel__scalar_x1, xnn_init_f32_scale_scalar_params);
}

TEST(F32_RSUM__SCALAR_X1, batch_gt_1) {
  for (size_t batch_size = 2; batch_size < 10; batch_size++) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x1, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X1, scale) {
  for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
    RSumMicrokernelTester()
      .batch_size(2)
      .scale(scale)
      .Test(xnn_f32_rsum_ukernel__scalar_x1, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X2_ACC2, batch_eq_2) {
  RSumMicrokernelTester()
    .batch_size(2)
    .Test(xnn_f32_rsum_ukernel__scalar_x2_acc2, xnn_init_f32_scale_scalar_params);
}

TEST(F32_RSUM__SCALAR_X2_ACC2, batch_div_2) {
  for (size_t batch_size = 4; batch_size < 20; batch_size += 2) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x2_acc2, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X2_ACC2, batch_lt_2) {
  for (size_t batch_size = 1; batch_size < 2; batch_size++) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x2_acc2, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X2_ACC2, batch_gt_2) {
  for (size_t batch_size = 3; batch_size < 4; batch_size++) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x2_acc2, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X2_ACC2, scale) {
  for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
    RSumMicrokernelTester()
      .batch_size(3)
      .scale(scale)
      .Test(xnn_f32_rsum_ukernel__scalar_x2_acc2, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X3_ACC3, batch_eq_3) {
  RSumMicrokernelTester()
    .batch_size(3)
    .Test(xnn_f32_rsum_ukernel__scalar_x3_acc3, xnn_init_f32_scale_scalar_params);
}

TEST(F32_RSUM__SCALAR_X3_ACC3, batch_div_3) {
  for (size_t batch_size = 6; batch_size < 30; batch_size += 3) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x3_acc3, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X3_ACC3, batch_lt_3) {
  for (size_t batch_size = 1; batch_size < 3; batch_size++) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x3_acc3, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X3_ACC3, batch_gt_3) {
  for (size_t batch_size = 4; batch_size < 6; batch_size++) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x3_acc3, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X3_ACC3, scale) {
  for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
    RSumMicrokernelTester()
      .batch_size(4)
      .scale(scale)
      .Test(xnn_f32_rsum_ukernel__scalar_x3_acc3, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X4_ACC2, batch_eq_4) {
  RSumMicrokernelTester()
    .batch_size(4)
    .Test(xnn_f32_rsum_ukernel__scalar_x4_acc2, xnn_init_f32_scale_scalar_params);
}

TEST(F32_RSUM__SCALAR_X4_ACC2, batch_div_4) {
  for (size_t batch_size = 8; batch_size < 40; batch_size += 4) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x4_acc2, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X4_ACC2, batch_lt_4) {
  for (size_t batch_size = 1; batch_size < 4; batch_size++) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x4_acc2, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X4_ACC2, batch_gt_4) {
  for (size_t batch_size = 5; batch_size < 8; batch_size++) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x4_acc2, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X4_ACC2, scale) {
  for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
    RSumMicrokernelTester()
      .batch_size(5)
      .scale(scale)
      .Test(xnn_f32_rsum_ukernel__scalar_x4_acc2, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X4_ACC4, batch_eq_4) {
  RSumMicrokernelTester()
    .batch_size(4)
    .Test(xnn_f32_rsum_ukernel__scalar_x4_acc4, xnn_init_f32_scale_scalar_params);
}

TEST(F32_RSUM__SCALAR_X4_ACC4, batch_div_4) {
  for (size_t batch_size = 8; batch_size < 40; batch_size += 4) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x4_acc4, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X4_ACC4, batch_lt_4) {
  for (size_t batch_size = 1; batch_size < 4; batch_size++) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x4_acc4, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X4_ACC4, batch_gt_4) {
  for (size_t batch_size = 5; batch_size < 8; batch_size++) {
    RSumMicrokernelTester()
      .batch_size(batch_size)
      .Test(xnn_f32_rsum_ukernel__scalar_x4_acc4, xnn_init_f32_scale_scalar_params);
  }
}

TEST(F32_RSUM__SCALAR_X4_ACC4, scale) {
  for (float scale = 0.3f; scale < 5.0f; scale *= 3.0f) {
    RSumMicrokernelTester()
      .batch_size(5)
      .scale(scale)
      .Test(xnn_f32_rsum_ukernel__scalar_x4_acc4, xnn_init_f32_scale_scalar_params);
  }
}