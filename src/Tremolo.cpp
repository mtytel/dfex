#include "Tremolo.h"

using namespace std;

void Tremolo::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) {
        out[i] = in[i] * (mWet - 1) + in[i] * mCycle[mOffset++] * mWet;

        if (mOffset >= mFPC)
            mOffset = 0;
    }
}
