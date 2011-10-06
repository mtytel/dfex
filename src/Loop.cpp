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

void Loop::LoopTrack::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) {
        mOffset %= mRecLength;
        out[i] = mMemory[mOffset++];
    }
}

void Loop::LoopTrack::resize() {

    mMemSize *= 2;
    mMemory = (sample_t*)realloc(mMemory, mMemSize * sizeof(sample_t));
}

void Loop::IndependentTrack::record(const sample_t *in, int num) {

    mRecLength = mOffset + num;
    while (mRecLength >= mMemSize)
        resize();

    memcpy(mMemory + mOffset, in, num * sizeof(sample_t));
}

void Loop::QuantizedTrack::record(const sample_t *in, int num) {

    while (mOffset + num >= mRecLength)
        mRecLength += mQuant;

    while (mRecLength >= mMemSize)
        resize();

    memcpy(mMemory + mOffset, in, num * sizeof(sample_t));
}

void Loop::OverDubTrack::record(const sample_t *in, int num) {

    int pos;
    for (int i = 0; i < num; i++) {
        pos  = (mOffset + i) % mRecLength;
        mMemory[pos] += in[i];
    }
}

void Loop::stopRec() {
    
    if (mRec) {
        uint recLength = mRec->getRecLength();
        mMaxLength = mMaxLength < recLength ? recLength : mMaxLength;
        mRec = 0;
    }
}

void Loop::startIndependentRec() {

    if (mRec) {
        stopRec();
        return;
    }

    mRec = new IndependentTrack();
    addProcessor(mRec);
}

void Loop::startQuantizedRec() {

    if (mRec) {
        stopRec();
        return;
    }

    mRec = new QuantizedTrack(mMaxLength);
    addProcessor(mRec);
}

void Loop::startOverDubRec() {

    if (mRec) {
        stopRec();
        return;
    }

    mRec = new OverDubTrack(mMaxLength);
    addProcessor(mRec);
}

void Loop::process(const sample_t* in, sample_t* out, int num) {

    sample_t mode[num];
    mMode->process(in, mode, num);

    if (!mRec) {
        if (mode[num - 1] == mIndRecId)
            startIndependentRec();
        else if (mode[num - 1] == mQuantRecId)
            startQuantizedRec();
        else if (mode[num - 1] == mOverDubRecId)
            startOverDubRec();
    }
    if (mRec) {
        if (mode[num - 1] == mStopId)
            stopRec();
        else
            mRec->record(in, num);
        
        Parallel::process(in, out, num);
    }
    else {
        Parallel::process(in, out, num);
        Process::combine(in, out, num);
    }

    
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

