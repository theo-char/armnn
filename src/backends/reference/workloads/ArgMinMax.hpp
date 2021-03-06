//
// Copyright © 2019 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "armnn/Tensor.hpp"
#include "armnn/Descriptors.hpp"

#include "Decoders.hpp"

namespace armnn
{

void ArgMinMax(Decoder<float>& in, int32_t* out, const TensorInfo& inputTensorInfo,
               const TensorInfo& outputTensorInfo, ArgMinMaxFunction function, int axis);

} //namespace armnn

