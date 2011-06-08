#include "Tremolo.h"

using namespace std;

Class Tremolo::mClass(string("Tremolo"), newInstance);

void Tremolo::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) {
        out[i] = in[i] * (1 - mWet) + in[i] * mCycle[mOffset++] * mWet;

        if (mOffset >= mFPC)
            mOffset = 0;
    }
}

void Tremolo::setWave(int fpc, int wave) {

    mFPC = fpc;
    sample_t* tmp = mCycle;

    mCycle = WaveMaker::create_wave(wave, mFPC, 0);
    free(tmp);
}

istream &Tremolo::Read(istream &in) {
    return in;
}

ostream &Tremolo::Write(ostream &out) const {
    return out;
}
