/* NiuTrans.Tensor - an open-source tensor library
 * Copyright (C) 2018, Natural Language Processing Lab, Northestern University. 
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
 * $Created by: XIAO Tong (xiaotong@mail.neu.edu.cn) 2018-08-02
 */

#ifndef __T2TTRAINER_H__
#define __T2TTRAINER_H__

#include "T2TModel.h"

#include "../../tensor/function/FHeader.h"

#define MAX_SEQUENCE_LENGTH 1024 * 4

using namespace nts;

namespace transformer
{

/* node to keep batch information */
struct BatchNode
{
    /* begining position */
    int beg;

    /* end position */
    int end;

    /* maximum word number on the encoder side */
    int maxEnc;

    /* maximum word number on the decoder side */
    int maxDec;

    /* a key for sorting */
    int key;
};

/* trainer of the T2T model */
class T2TTrainer
{
public:
    /* paramter number */
    int argNum;

    /* parameter array */
    char ** argArray;

    /* buffer for loading words */
    int * buf;

    /* another buffer */
    int * buf2;

    /* batch buf */
    BatchNode * bufBatch;

    /* buffer size */
    int bufSize;

    /* size of batch buffer */
    int bufBatchSize;

    /* length of each sequence */
    int * seqLen;

    /* another array */
    int * seqLen2;

    /* offset of the first word for each sequence */
    int * seqOffset;

    /* number of sequences in the buffer */
    int nseqBuf;

    /* offset for next sequence in the buffer */
    int nextSeq;

    /* offset for next batch */
    int nextBatch;
    
    /* indicates whether the sequence is sorted by length */
    bool isLenSorted;
    
    /* dimension size of each inner layer */
    int d;
    
    /* step number of warm-up for training */
    int nwarmup;

    /* vocabulary size of the source side */
    int vSize;

    /* vocabulary size of the target side */
    int vSizeTgt;

    /* learning rate */
    float lrate;
    
    /* the parameter that controls the maximum learning rate in training */
    float lrbias;

    /* sentence batch size */
    int sBatchSize;

    /* word batch size */
    int wBatchSize;

    /* training epoch number */
    int nepoch;

    /* traing step number */
    int nstep;

    /* indicates whether we use adam */
    bool useAdam;

    /* hyper parameters of adam*/
    float adamBeta1;
    float adamBeta2;
    float adamDelta;
    float adamBeta1T;
    float adamBeta2T;

    /* list of the moment of the parameter matrics */
    XList moments;

    /* list of the 2nd order moment of the parameter matrics */
    XList moments2nd;

    /* indicates whether the data file is shuffled for training */
    bool isShuffled;
    
    /* the factor of label smoothing */
    DTYPE labelSmoothingP;

    /* number of steps after which we make a checkpoint */
    int nStepCheckpoint;

    /* indicates whether we make a checkpoint after each traing epoch */
    bool useEpochCheckpoint;
    
    /* number of batches on which we do model update */
    int updateStep;
    
    /* indicates whether we double the </s> symbol for the output of lms */
    bool isDoubledEnd;
    
    /* indicates whether we use batchsize = max * sc
       rather rather than batchsize = word-number, where max is the maximum
       length and sc is the sentence number */
    bool isSmallBatch;

    /* counterpart of "isSmallBatch" */
    bool isBigBatch;

    /* randomize batches */
    bool isRandomBatch;

    /* indicates whether we intend to debug the net */
    bool isDebugged;

    /* bucket size */
    int bucketSize;

public:
    /* constructor */
    T2TTrainer();

    /* de-constructor */
    ~T2TTrainer();

    /* initialize the trainer */
    void Init(int argc, char ** argv);

    /* train the model */
    void Train(const char * fn, const char * validFN, const char * modelFN, T2TModel * model);

    /* test the model */
    void Test(const char * fn, const char * ofn, T2TModel * model);

    /* make a checkpoint */
    void MakeCheckpoint(T2TModel * model, const char * validFN, const char * modelFN, const char * label, int id);

    /* load data to buffer */
    int LoadBuf(FILE * file, bool isSorted, int step);

    /* clear data buffer */
    void ClearBuf();

    /* load a batch of sequences */
    int LoadBatch(FILE * file, bool isLM,
                  XTensor * batchEnc, XTensor * paddingEnc, 
                  XTensor * batchDec, XTensor * paddingDec,
                  XTensor * gold, XTensor * label,
                  int * seqs,
                  int vsEnc, int vsDec, int sBatch, int wBatch, 
                  bool isSorted, int &ws, int &wCount,
                  int devID, XMem * mem, 
				  bool isTraining);

    /* load a batch of sequences (for language modeling) */
    int LoadBatchLM(FILE * file, 
                    XTensor * batchEnc, XTensor * paddingEnc,
                    XTensor * batchDec, XTensor * paddingDec,
                    XTensor * gold, XTensor * label,
                    int * seqs, int vs, int sBatch, int wBatch, 
                    bool isSorted, int &wCount,
                    int devID, XMem * mem, 
					bool isTraining);

    /* load a batch of sequences (for machine translation) */
    int LoadBatchMT(FILE * file, 
                    XTensor * batchEnc, XTensor * paddingEnc, 
                    XTensor * batchDec, XTensor * paddingDec,
                    XTensor * gold, XTensor * label,
                    int * seqs, int vsEnc, int vsDec, int sBatch, int wBatch, 
                    bool isSorted, int &ws, int &wCount,
                    int devID, XMem * mem, 
					bool isTraining);

    /* shuffle the data file */
    void Shuffle(const char * srcFile, const char * tgtFile);
    
    /* get word probabilities for a batch of sequences */
    float GetProb(XTensor * output, XTensor * gold, XTensor * wordProbs);

    /* update the model by delta rule */
    void Update(T2TModel * model, const float lr);

    /* prepare model for training */
    void PrepareModel(T2TModel * model);

    /* do padding on the output */
    void PadOutput(XTensor * output, XTensor * gold, XTensor * padding);
    
    /* recale the output and gold tensors for normalized loss */
    void RescaleOutput(XTensor * output, XTensor * gold, XTensor * padding);
    
    /* perform label smoothing */
    void LabelSmooth(XTensor * gold, XTensor * smoothed, DTYPE p);
};


}

#endif
