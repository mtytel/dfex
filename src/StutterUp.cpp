/* StutterUp.cpp - takes input from one section of time,
 *             then repeats it a given amount of times increasing volume
 *             each iteration.
 * Author: Matthew Tytel
 */

#include "StutterUp.h"

using namespace std;

Class StutterUp::cls(string("StutterUp"), newInstance);

void StutterUp::process(const sample_t* in, sample_t* out, int num) {

    float mult = 0;
    for (int i = 0; i < num; i++) {

        mMemory[mCurStutter * mFPC + mOffset] = in[i];
        out[i] = 0;

        for (int st = 0; st < mNumStutter; st++) {
            mult = ((mNumStutter + mCurStutter - st) % mNumStutter + 1) * 
             1.0 / mNumStutter; 
            out[i] += mult * mMemory[st * mFPC + mOffset];
        }

        if (++mOffset >= mFPC) {
            mOffset = 0;
            mCurStutter = (mCurStutter + 1) % mNumStutter;
        }

        out[i] = out[i] * mWet + in[i] * (1 - mWet);
    }
}

void StutterUp::setFPC(int fpc) {

    mFPC = fpc;
    mMemory = (sample_t*)realloc(mMemory, fpc * mNumStutter * sizeof(sample_t));
    memset(mMemory, 0, fpc * mNumStutter * sizeof(sample_t));
}

istream &StutterUp::Read(istream &is) {

    Effect::Read(is);
    is >> mFPC >> mNumStutter;
    setFPC(mFPC);
    
    return is;
}

ostream &StutterUp::Write(ostream &os) const {

    Effect::Write(os);
    os << mFPC << ' ' << mNumStutter << endl;

    return os;
}
