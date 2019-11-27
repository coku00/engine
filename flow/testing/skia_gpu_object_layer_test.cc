// Copyright 2019 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/flow/testing/skia_gpu_object_layer_test.h"

#include "flutter/fml/time/time_delta.h"

namespace flutter {
namespace testing {

SkiaGPUObjectLayerTest::SkiaGPUObjectLayerTest()
    : unref_queue_(fml::MakeRefCounted<SkiaUnrefQueue>(
          GetCurrentTaskRunner(),
          fml::TimeDelta::FromSeconds(0))) {}

void SkiaGPUObjectLayerTest::TearDown() {
  unref_queue_ = nullptr;
}

}  // namespace testing
}  // namespace flutter
