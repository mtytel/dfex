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

#include "Feedback.h"

using namespace rapidxml;

Class Feedback::cls(std::string("Feedback"), newInstance);

sample_t Delay::getVal(sample_t curSamp) {

    if (!mSingle)
        return curSamp;

    if (++mCycleOffset >= mCurPeriod * mProcessors.size())
        mCycleOffset = 0;

    return mCycleOffset >= mCurPeriod ? 0 : curSamp;
}

void Feedback::process(const sample_t* in, sample_t* out, int num) {
    float decay = .5;

    // add input to feedback
    for (int i = 0; i < num; i++)
        out[i] = in[i] + (mMemLen > delay ? pop()*decay : 0);

    // run through inner process - faking this for now

    // copy output into feedback for future feedback
    for (int i = 0; i < num, i++)
        push(out[i]);
}


xml_node<> &Delay::read(xml_node<> &inode) {

    ProcessorList::read(inode);
    free(mPeriod);
    mPeriod = Processor::tryReadProcessor(inode, "delay", DEFAULTDELAY);
    
    xml_node<> *singNode = inode.first_node("single");
    mSingle = singNode ? 1 : 0;

    return inode;
}

xml_node<> &Delay::write(xml_node<> &onode) const {

    return onode;
}
