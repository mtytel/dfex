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

    int curOffset = mOffset, periodPrev = round(mCurPeriod);
    float periods[num];

    mPeriod->process(in, periods, num);
    mCurPeriod = round(periods[num - 1]);
    
    for (int i = 0; i < num; i++) {
        sample_t val = (mCycleOffset >= mCurPeriod && mSingle) ? 0 : in[i];
        mMemory[mOffset] = mMemory[mOffset + MEMORYSIZE] = val;

        if (++mOffset >= MEMORYSIZE)
            mOffset = 0;
        if (++mCycleOffset >= mCurPeriod * mProcessors.size())
            mCycleOffset = 0;
    }

    memset(out, 0, num * sizeof(sample_t));

    for (uint st = 0; st < mProcessors.size(); st++) {
        int stIndex = (MEMORYSIZE + curOffset - st * periodPrev) % MEMORYSIZE;

        sample_t fit[num];
        Process::fit(&mMemory[stIndex], fit, 
         num + st * (periodPrev - mCurPeriod), num);

        mProcessors[st]->process(fit, mBuffer, num);
        Process::combine(mBuffer, out, num);
    }

    postProcess(in, out, num);
}

xml_node<> &Delay::read(xml_node<> &inode) {

    ProcessorList::read(inode);

    free(mPeriod);
    mPeriod = Processor::tryReadProcessor(inode, "period", DEFAULTPERIOD);
    
    xml_node<> *singNode = inode.first_node("single");
    mSingle = singNode ? 1 : 0;

    return inode;
}

xml_node<> &Delay::write(xml_node<> &onode) const {

    return onode;
}
