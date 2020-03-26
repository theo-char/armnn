//
// Copyright © 2020 Arm Ltd. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include <Layer.hpp>

namespace armnn
{

/// This layer converts data type BFloat16 to Float32.
class ConvertBf16ToFp32Layer : public Layer
{
public:
    /// Makes a workload for the ConvertBf16ToFp32 type.
    /// @param [in] factory The workload factory which will create the workload.
    /// @return A pointer to the created workload, or nullptr if not created.
    virtual std::unique_ptr<IWorkload> CreateWorkload(const IWorkloadFactory& factory) const override;

    /// Creates a dynamically-allocated copy of this layer.
    /// @param [in] graph The graph into which this layer is being cloned.
    ConvertBf16ToFp32Layer* Clone(Graph& graph) const override;

    /// Check if the input tensor shape(s)
    /// will lead to a valid configuration of @ref ConvertBf16ToFp32Layer.
    void ValidateTensorShapesFromInputs() override;

    void Accept(ILayerVisitor& visitor) const override;

protected:
    /// Constructor to create a ConvertBf16ToFp32Layer.
    /// @param [in] name Optional name for the layer.
    ConvertBf16ToFp32Layer(const char* name);

    /// Default destructor
    ~ConvertBf16ToFp32Layer() = default;
};

} // namespace