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
 * $Created by: Xu Chen (email: hello_master1954@163.com) 2018-09-18
 */

#ifndef __GATHER_H__
#define __GATHER_H__

#include "../../XTensor.h"

namespace nts { // namespace nts(NiuTrans.Tensor)

/* gather selected sub-tensors */
void _Gather(XTensor * s, XTensor * t, int dim, int * srcIndex, int indexSize);

/* gather selected sub-tensors */
void _Gather(const XTensor * s, XTensor * t, XTensor * srcIndex);

/* gather selected sub-tensors (return an XTensor structure)
   make a new tensor to keep the result and return it */
XTensor Gather(XTensor &s, XTensor &index);

} // namespace nts(NiuTrans.Tensor)

#endif // __GATHER_H__