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
* $Created by: Xu Chen (email: hello_master1954@163.com) 2018-07-06
*/

#include "TSumByColumnTV.h"

namespace nts { // namespace nts(NiuTrans.Tensor)

/* 
case 1: test SumByColumnTV function
sum of a tensor and a vector (column vector) in a column by column manner
*/
bool TestSumByColumnTV1()
{
    /* a tensor of size (2, 4) */
    int aOrder = 2;
    int * aDimSize = new int[aOrder];
    aDimSize[0] = 2;
    aDimSize[1] = 4;

    int aUnitNum = 1;
    for (int i = 0; i < aOrder; i++)
        aUnitNum *= aDimSize[i];

    /* a tensor of size (2, 1) */
    int bOrder = 2;
    int * bDimSize = new int[bOrder];
    bDimSize[0] = 2;
    bDimSize[1] = 1;

    int bUnitNum = 1;
    for (int i = 0; i < bOrder; i++)
        bUnitNum *= bDimSize[i];

    /* a tensor of size (2, 4) */
    int cOrder = 2;
    int * cDimSize = new int[cOrder];
    cDimSize[0] = 2;
    cDimSize[1] = 4;

    int cUnitNum = 1;
    for (int i = 0; i < cOrder; i++)
        cUnitNum *= cDimSize[i];

    DTYPE aData[2][4] = { {0.0F, 1.0F, 2.0F, 3.0F},
                          {4.0F, 5.0F, 6.0F, 7.0F} };
    DTYPE bData[2][1] = { {1.0F},
                          {0.0F} };
    DTYPE answer[2][4] = { {1.0F, 2.0F, 3.0F, 4.0F},
                           {4.0F, 5.0F, 6.0F, 7.0F} };

    /* CPU test */
    bool cpuTest = true;

    /* create tensors */
    XTensor * a = NewTensor(aOrder, aDimSize);
    XTensor * b = NewTensor(bOrder, bDimSize);
    XTensor * c = NewTensor(cOrder, cDimSize);

    /* initialize variables */
    a->SetData(aData, aUnitNum);
    b->SetData(bData, bUnitNum);

    /* call SumByColumnTV function */
    _SumByColumnTV(a, b, c);

    /* check results */
    cpuTest = c->CheckData(answer, cUnitNum);

#ifdef USE_CUDA
    /* GPU test */
    bool gpuTest = true;

    /* create tensor */
    XTensor * aGPU = NewTensor(aOrder, aDimSize, X_FLOAT, 1.0F, 0);
    XTensor * bGPU = NewTensor(bOrder, bDimSize, X_FLOAT, 1.0F, 0);
    XTensor * cGPU = NewTensor(cOrder, cDimSize, X_FLOAT, 1.0F, 0);

    /* Initialize variables */
    aGPU->SetData(aData, aUnitNum);
    bGPU->SetData(bData, bUnitNum);
    cGPU->SetZeroAll();

    /* call SumByColumnTV function */
    _SumByColumnTV(aGPU, bGPU, cGPU);

    /* check results */
    gpuTest = cGPU->CheckData(answer, cUnitNum);

    /* destroy variables */
    delete a;
    delete b;
    delete c;
    delete aGPU;
    delete bGPU;
    delete cGPU;
    delete[] aDimSize;
    delete[] bDimSize;
    delete[] cDimSize;

    return cpuTest && gpuTest;
#else
    /* destroy variables */
    delete a;
    delete b;
    delete c;
    delete[] aDimSize;
    delete[] bDimSize;
    delete[] cDimSize;

    return cpuTest;
#endif // USE_CUDA
}

/* other cases */
/*
    TODO!!
*/

/* test for SumByColumnTV Function */
bool TestSumByColumnTV() 
{
    XPRINT(0, stdout, "[TEST SumByColumnTV] sum of a tensor and a vector (column vector) in a column by column manner \n");
    bool returnFlag = true, caseFlag = true;

    /* case 1 test */
    caseFlag = TestSumByColumnTV1();
    if (!caseFlag) {
        returnFlag = false;
        XPRINT(0, stdout, ">> case 1 failed!\n");
    }
    else
        XPRINT(0, stdout, ">> case 1 passed!\n");

    /* other cases test */
    /*
        TODO!!
    */

    if (returnFlag) {
        XPRINT(0, stdout, ">> All Passed!\n");
    }
    else
        XPRINT(0, stdout, ">> Failed!\n");

    XPRINT(0, stdout, "\n");

    return returnFlag;
}

} // namespace nts(NiuTrans.Tensor)
