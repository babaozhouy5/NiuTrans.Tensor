/* NiuTrans.Tensor - an open-source tensor library
* Copyright (C) 2017, Natural Language Processing Lab, Northestern University.
* All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/*
* $Created by: XIAO Tong (email: xiaotong@mail.neu.edu.cn) 2018-04-24
*/

#ifndef __REDUCEMAX_CUH__
#define __REDUCEMAX_CUH__

#include "../reduce/ReduceMax.h"

namespace nts { // namespace nts(NiuTrans.Tensor)

#ifdef USE_CUDA

/* summation of a tensor and a vector (column vector) */
void _CudaSumByColumnTV(const XTensor * a, const XTensor * b, XTensor * c, DTYPE beta = (DTYPE)1.0);

#endif // USE_CUDA

} // namespace nts(NiuTrans.Tensor)

#endif // __REDUCEMAX_CUH__

