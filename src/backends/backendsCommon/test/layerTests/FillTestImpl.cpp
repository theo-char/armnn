//
// Copyright © 2020 Arm Ltd and Contributors. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "FillTestImpl.hpp"

#include <backendsCommon/test/DataTypeUtils.hpp>
#include <backendsCommon/test/TensorCopyUtils.hpp>
#include <backendsCommon/test/WorkloadTestUtils.hpp>

#include <test/TensorHelpers.hpp>

template<armnn::DataType ArmnnType, typename T>
LayerTestResult<T, 4> SimpleFillTest(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager)
{
    IgnoreUnused(memoryManager);
    armnn::TensorInfo inputTensorInfo({4}, ArmnnType);
    inputTensorInfo.SetQuantizationScale(0.0f);

    armnn::TensorInfo outputTensorInfo({2, 2, 3, 2}, ArmnnType);
    outputTensorInfo.SetQuantizationScale(0.0f);

    auto input = MakeTensor<T, 1>(inputTensorInfo, ConvertToDataType<ArmnnType>(
        {2, 2, 3, 2},
        inputTensorInfo));

    LayerTestResult<T, 4> ret(outputTensorInfo);
        ret.outputExpected = MakeTensor<T, 4>(outputTensorInfo, ConvertToDataType<ArmnnType>(
        { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f },
        outputTensorInfo));

    std::unique_ptr<armnn::ITensorHandle> inputHandle = workloadFactory.CreateTensorHandle(inputTensorInfo);
    std::unique_ptr<armnn::ITensorHandle> outputHandle = workloadFactory.CreateTensorHandle(outputTensorInfo);

    armnn::FillQueueDescriptor data;
    data.m_Parameters.m_Value = 1.0f;
    armnn::WorkloadInfo info;
    AddInputToWorkload(data, info, inputTensorInfo, inputHandle.get());
    AddOutputToWorkload(data, info, outputTensorInfo, outputHandle.get());

    std::unique_ptr<armnn::IWorkload> workload = workloadFactory.CreateFill(data, info);

    inputHandle->Allocate();
    outputHandle->Allocate();

    CopyDataToITensorHandle(inputHandle.get(), &input[0]);

    workload->Execute();

    CopyDataFromITensorHandle(&ret.output[0][0][0][0], outputHandle.get());

    return ret;
}

//
// Explicit template specializations
//
template LayerTestResult<armnn::ResolveType<armnn::DataType::Float32>, 4>
SimpleFillTest<armnn::DataType::Float32>(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager);

template LayerTestResult<armnn::ResolveType<armnn::DataType::Float16>, 4>
SimpleFillTest<armnn::DataType::Float16>(
    armnn::IWorkloadFactory& workloadFactory,
    const armnn::IBackendInternal::IMemoryManagerSharedPtr& memoryManager);