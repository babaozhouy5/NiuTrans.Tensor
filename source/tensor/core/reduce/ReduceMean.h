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

#ifndef __REDUCEMEAN_H__
#define __REDUCEMEAN_H__

#include "../../XTensor.h"

namespace nts{ // namespace nts(NiuTrans.Tensor)

/* 
get the mean value along a dimension of the tensor
For a 1-dimensional data array a, mean = (1/n) * sum_i input_i
*/
void _ReduceMean(const XTensor * input, XTensor * output, int dim);

/* 
get the mean value along a dimension of the tensor (return an XTensor structure)
make a new tenosr to keep the result and return it
For a 1-dimensional data array a, mean = (1/n) * sum_i input_i
*/
XTensor ReduceMean(const XTensor &input, int dim);

} // namespace nts(NiuTrans.Tensor)

#endif // __REDUCEMEAN_H__
