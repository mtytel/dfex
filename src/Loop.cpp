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

#include "Loop.h"

using namespace std;
using namespace rapidxml;

Class Loop::cls(std::string("Loop"), newInstance);

Loop::Loop() : Parallel::Parallel(), mMaxLength(1), mRec(0), 
 mStopId(DEFAULTSTOPID), mIndRecId(DEFAULTINDID), 
 mQuantRecId(DEFAULTQUANTID), mOverDubRecId(DEFAULTOVERDUBID) { 
    mSpeed = new Constant(DEFAULTSPEED);
    mMode = new Constant(DEFAULTMODE);
    mRec = new LoopTrack();
    addProcessor(mRec);
}

void Loop::LoopTrack::process(const sample_t* in, sample_t* out, int num) {

    if (isEmpty())
        memcpy(out, in, num * sizeof(sample_t));
    else {
        for (int i = 0; i < num; i++) {
            mOffset %= mRecLength;
            out[i] = mMemory[mOffset++];
        }
    }
}

void Loop::LoopTrack::resize() {

    if (mMemSize < mRecLength) {

        mMemSize *= (mRecLength / mMemSize + 1);
        mMemory = (sample_t*)realloc(mMemory, mMemSize * sizeof(sample_t));
    }
}

void Loop::LoopTrack::independentRecord(const sample_t *in, int num) {

    mRecLength = mOffset + num;
    resize();

    memcpy(mMemory + mOffset, in, num * sizeof(sample_t));
}

void Loop::LoopTrack::quantizedRecord(const sample_t *in, int num, int quant) {

    mRecLength = quant * ((mOffset + num) / quant + 1);
    resize();

    memcpy(mMemory + mOffset, in, num * sizeof(sample_t));
}

void Loop::LoopTrack::overDubRecord(const sample_t *in, int num, int length) {

    mRecLength = length;
    resize();

    for (int i = 0; i < num; i++) {
        int pos = (mOffset + i) % mRecLength;
        mMemory[pos] += in[i];
    }
}

void Loop::stopRec() {
    
    if (mRec->isEmpty())
        return;

    uint recLength = mRec->getRecLength();
    mMaxLength = mMaxLength < recLength ? recLength : mMaxLength;

    mRec = new LoopTrack();
    addProcessor(mRec);
}

void Loop::process(const sample_t* in, sample_t* out, int num) {

    sample_t mode[num];
    mMode->process(in, mode, num);

    if (mode[num - 1] == mIndRecId) 
        mRec->independentRecord(in, num);
    else if (mode[num - 1] == mQuantRecId) 
        mRec->quantizedRecord(in, num, mMaxLength);
    else if (mode[num - 1] == mOverDubRecId) 
        mRec->overDubRecord(in, num, mMaxLength);
    else if (mode[num - 1] == mStopId)
        stopRec();

    Parallel::process(in, out, num);
    postProcess(in, out, num);
}

xml_node<> &Loop::read(xml_node<> &inode) {

    xml_node<> *val = inode.first_node("indrec");
    mIndRecId = val ? atoi(val->value()) : DEFAULTINDID;

    val = inode.first_node("quantrec");
    mQuantRecId = val ? atoi(val->value()) : DEFAULTQUANTID;

    val = inode.first_node("overdubrec");
    mOverDubRecId = val ? atoi(val->value()) : DEFAULTOVERDUBID;

    val = inode.first_node("stop");
    mStopId = val ? atoi(val->value()) : DEFAULTSTOPID;

    delete mMode;
    mMode = Processor::tryReadProcessor(inode, "reccontrol", DEFAULTMODE);
    delete mSpeed;
    mSpeed = Processor::tryReadProcessor(inode, "speedcontrol", DEFAULTSPEED);

    return inode;
}

xml_node<> &Loop::write(xml_node<> &onode) const {

    return onode;
}

