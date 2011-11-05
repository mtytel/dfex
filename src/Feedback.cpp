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

/* in progress 
Feedback::process(const sample_t* in, sample_t* out, int num) {
 
    sample_t delays[num];
    sample_t decays[num];
    sample_t sum[num];
    const sample_t *mem;

    mDelay->process(in, delays, num);
    uint mPrevDelay = round(delays[0]);
    uint mCurDelay = round(delays[num-1]);
    
    mDecay->process(in, decays, num);

    mem = mMemory->getPastSamples(num - mCurDelay????? think about this more);
    

}*/

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
}

/*
void Feedback::process(const sample_t* in, sample_t* out, int num) {

    int i;

    sample_t delays[num];
    sample_t decays[num];
    const sample_t *memory;
    sample_t temp[num];
    
    mDelay->process(in, delays, num);

    mCurDelay = round(delays[num - 1]);

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

    free(mDelay);
    mDelay = Processor::tryReadProcessor(inode, "delay", DEFAULTDELAY); 
    
    free(mDecay);
    mDecay = Processor::tryReadProcessor(inode, "decay", DEFAULTDECAY);

    free(mProcess);
    mProcess = Processor::tryReadProcessor(inode, "process", DEFAULTPROCESS);

    return inode;
}

xml_node<> &Feedback::write(xml_node<> &onode) const {

    return onode;
}
