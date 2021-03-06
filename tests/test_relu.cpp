// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2019 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "testutil.h"

#include "layer/relu.h"

static int test_relu(float slope, bool use_packing_layout)
{
    ncnn::Mat a = RandomMat(6, 7, 8);

    ncnn::ParamDict pd;
    pd.set(0, slope);//slope

    std::vector<ncnn::Mat> weights(0);
    ncnn::ModelBinFromMatArray mb(weights.data());

    ncnn::Option opt;
    opt.num_threads = 1;
    opt.use_fp16_packed = false;
    opt.use_fp16_storage = false;
    opt.use_fp16_arithmetic = false;
    opt.use_int8_storage = false;
    opt.use_int8_arithmetic = false;
    opt.use_packing_layout = use_packing_layout;

    int ret = test_layer<ncnn::ReLU>("ReLU", pd, mb, opt, a);
    if (ret != 0)
    {
        fprintf(stderr, "test_relu failed slope=%f use_packing_layout=%d\n", slope, use_packing_layout);
    }

    return ret;
}

static int test_relu_0()
{
    return 0
        || test_relu(0.f, false)
        || test_relu(0.1f, false)

        || test_relu(0.f, true)
        || test_relu(0.1f, true)
        ;
}

int main()
{
    SRAND(7767517);

    return test_relu_0();
}
