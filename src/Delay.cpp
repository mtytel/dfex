/* 
 * Copyright 2011 Matthew Tytel
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

#include "Delay.h"

using namespace rapidxml;

Class Delay::cls(std::string("Delay"), newInstance);

void Delay::process(const sample_t* in, sample_t* out, int num) {

    int curOffset = mOffset, fpcPrev = round(mCurFPC);
    float fpcs[num];

    mFPC->process(in, fpcs, num);
    mCurFPC = round(fpcs[num - 1]);
    
    for (int i = 0; i < num; i++) {
        sample_t val = (mCycleOffset >= mCurFPC && mSingle) ? 0 : in[i];
        mMemory[mOffset] = mMemory[mOffset + MEMORYSIZE] = val;

        if (++mOffset >= MEMORYSIZE)
            mOffset = 0;
        if (++mCycleOffset >= mCurFPC * mProcessors.size())
            mCycleOffset = 0;
    }

    memset(out, 0, num * sizeof(sample_t));

    for (int st = 0; st < mProcessors.size(); st++) {
        int stIndex = (MEMORYSIZE + curOffset - st * fpcPrev) % MEMORYSIZE;

        sample_t fit[num];
        Process::fit(&mMemory[stIndex], fit, num + st * (fpcPrev - mCurFPC), num);

        mProcessors[st]->process(fit, mBuffer, num);
        Process::combine(mBuffer, out, num);
    }

    postProcess(in, out, num);
}

xml_node<> &Delay::read(xml_node<> &inode) {
/*
    ProcessorList::read(is);
    free(mFPC);
    mFPC = Processor::readProcessor(is);
    is >> mSingle;
*/
    return inode;
}

xml_node<> &Delay::write(xml_node<> &onode) const {

    //ProcessorList::write(os);
    return onode;
}
