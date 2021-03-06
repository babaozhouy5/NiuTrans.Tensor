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
 * $Created by: Xu Chen (email: hello_master1954@163.com) 2018-12-10
 */

#ifndef __COMPARE_CUH__
#define __COMPARE_CUH__

#include "../../XTensor.h"

namespace nts{ // namespace nts(NiuTrans.Tensor)

#ifdef USE_CUDA

/* compare whether every entry is equal to the specified value (cuda kernel) */
__global__
void KernelEqual(DTYPE * a, DTYPE * b, DTYPE * number);
/* compare whether every entry is equal to the specified value (cuda version) */
void _CudaEqual(const XTensor * a, XTensor * b, DTYPE number);

/* compare whether every entry is not equal to the specified value (cuda kernel) */
__global__
void KernelNotEqual(DTYPE * a, DTYPE * b, DTYPE * number);
/* compare whether every entry is not equal to the specified value (cuda version) */
void _CudaNotEqual(const XTensor * a, XTensor * b, DTYPE number);

#endif // USE_CUDA

} // namespace nts(NiuTrans.Tensor)

#endif //end __COMPARE_CUH__