/* StutterExtend.cpp - takes input from one section of time,
 *             then repeats it a given amount of times increasing volume
 *             each iteration.
 * Author: Matthew Tytel
 */

#include "StutterExtend.h"
#include <stdio.h>

using namespace std;

Class StutterExtend::cls(string("StutterExtend"), newInstance);

void StutterExtend::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) {

        if (mInputEnabled) 
            mMemory[mOffset] = in[i];

        out[i] = 0;

        for (int past = 0; past < mRatio; past++) {
            float pos = 1.0 * (mOffset % mFPC) / mRatio + past * mFPC;
            sample_t val = Effect::linearInterpolate(
             mMemory[(int)pos], mMemory[(int)pos + 1], pos - (int)pos);

            out[i] += val;
        }
   
        mOffset = (mOffset + 1) % (mFPC * mRatio);
        if (!mOffset)
            printf("Wrapped\n");
        
        out[i] = out[i] * mWet + in[i] * (1 - mWet);
    }
}

void StutterExtend::setFPC(int fpc) {

    mFPC = fpc;
    mMemory = (sample_t*)realloc(mMemory, mFPC * mRatio * sizeof(sample_t));
    memset(mMemory, 0, mFPC * mRatio * sizeof(sample_t));
}

istream &StutterExtend::Read(istream &is) {

    Effect::Read(is);
    is >> mFPC >> mRatio;
    setFPC(mFPC);
    
    return is;
}

ostream &StutterExtend::Write(ostream &os) const {

    Effect::Write(os);
    os << mFPC << ' ' << mRatio << endl;

    return os;
}
