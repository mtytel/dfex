#include "Stutter.h"

using namespace std;

void Stutter::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) {
        if (mCurStutter) 
            out[i] = mMemory[mOffset];
        else
            out[i] = mMemory[mOffset] = in[i];

        if (++mOffset >= mFPC) {
            mOffset = 0;
            mCurStutter = (mCurStutter + 1) % mNumStutters;
        }

        out[i] = out[i] * mWet + in[i] * (1 - mWet);
    }
}
