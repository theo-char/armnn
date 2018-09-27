//
// Copyright © 2017 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "NeonBaseMergerWorkload.hpp"

namespace armnn
{

class NeonMergerFloatWorkload : public NeonBaseMergerWorkload<DataType::Float16, DataType::Float32>
{
public:
    using NeonBaseMergerWorkload<DataType::Float16, DataType::Float32>::NeonBaseMergerWorkload;
    virtual void Execute() const override;
};

} //namespace armnn