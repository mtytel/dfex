/* 
 * Copyright 2011 Noura Howell
 *
 * dfex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dfex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dfex.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Feedback.h"

using namespace rapidxml;

Class Feedback::cls(std::string("Feedback"), newInstance);


void Feedback::process(const sample_t* in, sample_t* out, int num) {

    float decays[num], delays[num];

    mDecay->process(in, decays, num);
    mDelay->process(in, delays, num);
 
    uint prevDelay = round(delays[0]);
    uint curDelay = round(delays[num-1]);
    int memStart = prevDelay + num;
    int memEnd = curDelay;
    int memNum = memStart - memEnd;

    int memBatchSize = memEnd > 0 ? memNum : memStart;
    int nBatches = memNum / memBatchSize;
    int ioBatchSize = num / nBatches;

    int ioStart = 0;
    for (ioStart = 0; ioStart < num; ioStart += ioBatchSize)
        process_batch(in+ioStart, out+ioStart, ioBatchSize, decays+ioStart, memStart, memBatchSize);

    //ioStart = nBatches * ioBatchSize; 
    int RmemBatchSize = memNum % memBatchSize;
    int RioBatchSize = num % nBatches;
    
    process_batch(in+ioStart, out+ioStart, RioBatchSize, decays+ioStart, memStart, RmemBatchSize); // I think the numbers are off 
}

void Feedback::process_batch(const sample_t* in, sample_t* out, int num, float* decays, int memStart, int memNum) {

    sample_t mem[num], sum[num];
    Process::fit(mMemory->getPastSamples(memStart), mem, memNum, num);
    for (int i = 0; i < num; i++)
        sum[i] = in[i] + mem[i] * decays[i];
    mProcess->process(sum, out, num);
    mMemory->storeSamples(out, num);
}

/* has separate sub function, but could still be more elegant
void Feedback::process(const sample_t* in, sample_t* out, int num) {

    float decays[num], delays[num];

    mDecay->process(in, decays, num);
    mDelay->process(in, delays, num);
 
    uint prevDelay = round(delays[0]);
    uint curDelay = round(delays[num-1]);
    int memStart = prevDelay + num;
    int memEnd = curDelay;
    int memNum = memStart - memEnd;

    if (memEnd > 0) {
        process_batch(in, out, num, decays, memStart, memNum);
    } else {
        
        int b = memNum / memStart;
        int numB = num / b;
        int bStart = 0;

        for (bStart = 0; bStart < num; bStart += numB)
            process_batch(in+bStart, out+bStart, numB, decays+bStart, memStart, memStart); // here too maybe.. ok i'll check

        bStart = b * numB;
        int r = memNum % memStart;
        int numR = num % b;

        process_batch(in+bStart, out+bStart, numR, decays+bStart, memStart, r); // I think the numbers are off 
    }
}*/

/* handles small batches but should have separate sub function
void Feedback::process(const sample_t* in, sample_t* out, int num) {

    float decays[num], delays[num];

    mDecay->process(in, decays, num);
    mDelay->process(in, delays, num);
 
    uint prevDelay = round(delays[0]);
    uint curDelay = round(delays[num-1]);
    int memStart = prevDelay + num;
    int memEnd = curDelay;
    int memNum = memStart - memEnd;

    if (-memStart + memNum <= 0) {

        sample_t mem[num], sum[num];

        Process::fit(mMemory->getPastSamples(memStart), mem, memNum, num);
        for (int i = 0; i < num; i++)
            sum[i] = in[i] + mem[i] * decays[i];
        mProcess->process(sum, out, num);
        mMemory->storeSamples(out, num);
    } else {
        
        int b = memNum / memStart;
        int numB = num / b;
        int inStart;
        sample_t mem[numB], sum[numB];

        for (int j = 0; j < b; j++) {
            inStart = j * numB;
            Process::fit(mMemory->getPastSamples(memStart), mem, memStart, numB);
            for (int i = 0; i < numB; i++)
                sum[i] = in[inStart + i] + mem[i] * decays[inStart + i];
            mProcess->process(sum, out + inStart, numB);
            mMemory->storeSamples(out + inStart, numB);
        }

        inStart = b * numB;
        int r = memNum % memStart;
        int numR = num % b;
        Process::fit(mMemory->getPastSamples(memStart), mem, r, numR);
        for (int i = 0; i < numR; i++)
            sum[i] = in[inStart + i] + mem[i] * decays[inStart + i];
        mProcess->process(sum, out + inStart, numR);
        mMemory->storeSamples(out + inStart, numR);
    }
}*/

/*
void Feedback::process(const sample_t* in, sample_t* out, int num) {
 
    sample_t delays[num], decays[num], sum[num], mem[num];

    mDelay->process(in, delays, num);
    mDecay->process(in, decays, num);
    
    uint prevDelay = round(delays[0]);
    uint curDelay = round(delays[num-1]);
    int memStart = prevDelay + num;
    int memEnd = curDelay;
    int memNum = memStart - memEnd;

    Process::fit(mMemory->getPastSamples(memStart), mem, memNum, num);

    for (int i = 0; i < num; i++)
        sum[i] = in[i] + mem[i] * decays[i];
    
    mProcess->process(sum, out, num);

    mMemory->storeSamples(out, num);
}*/

/*
void Feedback::process(const sample_t* in, sample_t* out, int num) {

    sample_t delays[num];
    sample_t decays[num];
    sample_t sum[1];
    const sample_t *mem;

    mDelay->process(in, delays, num);
    mDecay->process(in, decays, num);

    for (int i = 0; i < num; i++) {
        mem = mMemory->getPastSamples(delays[i]);
        sum[0] = in[i] + (mem[0])*decays[i];
        mProcess->process(sum, &(out[i]), 1);
    }
    mMemory->storeSamples(out, num);
}*/

/*
void Feedback::process(const sample_t* in, sample_t* out, int num) {

    int i;

    sample_t delays[num];
    sample_t decays[num];
    const sample_t *memory;
    sample_t temp[num];
    
    mDelay->process(in, delays, num);

    int mCurDelay = round(delays[num - 1]);

    mDecay->process(in, decays, num);

    // pull up feedback from memory
    memory = mMemory->getPastSamples(num);

    // add feedback to input
    for (i = 0; i < num; i++)
        temp[i] = in[i] + memory[i]*decays[i];

    // run through inner process and send to output
    mProcess->process(temp, out, num);

    // save output to memory for use as future feedback
    mMemory->storeSamples(out, num);

}*/


xml_node<> &Feedback::read(xml_node<> &inode) {

    delete mDelay;
    mDelay = Processor::readParameter(inode, "delay", DEFAULTDELAY); 
    
    delete mDecay;
    mDecay = Processor::readParameter(inode, "decay", DEFAULTDECAY);

    xml_node<> *procNode = inode.first_node("process");
    if (procNode)
        mProcess = Processor::readProcessor(*(procNode->first_node()));
    else
        mProcess = new Processor();

    return inode;
}

xml_node<> &Feedback::write(xml_node<> &onode) const {

    return onode;
}
