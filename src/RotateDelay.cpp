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

#include "RotateDelay.h"

using namespace rapidxml;
using namespace std;

Class RotateDelay::cls(std::string("RotateDelay"), newInstance);

void RotateDelay::process(const sample_t* in, sample_t* out, int num) {

    sample_t periods[num], speeds[num], fit[num], buffer[num];
    mSpeed->process(in, speeds, num);
    sample_t curSpeed = speeds[num - 1];

    mPeriod->process(in, periods, num);
    uint prevPeriod = round(periods[0]);
    uint curPeriod = round(periods[num - 1]);
    
    mMemory->storeSamples(in, num);
    memset(out, 0, num * sizeof(sample_t));

    for (uint st = 0; st < mProcessors.size(); st++) {
        int startOffset = (int)round(mRotation + st * prevPeriod) % 
         (prevPeriod * mProcessors.size());
        int endOffset = ((int)round(mRotation + st * curPeriod) % 
         (curPeriod * mProcessors.size())) - curSpeed * num;
        int procSize = startOffset - endOffset;
        const sample_t *sampStart = mMemory->getPastSamples(startOffset);

        Process::fit(sampStart, fit, procSize, num);
        mProcessors[st]->process(fit, buffer, num);
        Process::combine(buffer, out, out, num);
    }

    mRotation *= 1.0 * curPeriod / prevPeriod;
    mRotation += num - curSpeed * num;
    if (mRotation >= curPeriod * mProcessors.size())
        mRotation -= curPeriod * mProcessors.size();
    else if (mRotation < 0)
        mRotation += curPeriod * mProcessors.size();

    postProcess(in, out, num);
}

xml_node<> &RotateDelay::read(xml_node<> &inode) {

    ProcessorList::read(inode);

    delete mPeriod;
    mPeriod = Processor::tryReadProcessor(inode, "period", DEFAULTPERIOD);

    delete mSpeed;
    mSpeed = Processor::tryReadProcessor(inode, "speed", DEFAULTSPEED);
    
    return inode;
}

xml_node<> &RotateDelay::write(xml_node<> &onode) const {

    return onode;
}
