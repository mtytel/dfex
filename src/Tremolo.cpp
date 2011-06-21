/* Tremolo.cpp - tremolo implemented with different wave forms
 * Author: Matthew Tytel
 */

#include "Tremolo.h"

using namespace std;

Class Tremolo::cls(string("Tremolo"), newInstance);

void Tremolo::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) {
        out[i] = in[i] * (1 - mWet) + in[i] * mCycle[mOffset++] * mWet;

        if (mOffset >= mFPC)
            mOffset = 0;
    }
}

void Tremolo::setWave(int fpc, int wave) {

    mWave = wave;
    mFPC = fpc;
    sample_t* tmp = mCycle;

    mCycle = WaveMaker::create_wave(mWave, mFPC, 0);
    free(tmp);
}

istream &Tremolo::Read(istream &is) {

    Effect::Read(is);
    is >> mFPC >> mWave;
    setWave(mFPC, mWave);

    return is;
}

ostream &Tremolo::Write(ostream &os) const {

    Effect::Write(os);
    os << mFPC << ' ' << mWave << endl;

    return os;
}
