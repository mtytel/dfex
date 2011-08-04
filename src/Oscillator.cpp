#include "Oscillator.h"

using namespace std;

Class Oscillator::cls(string("Oscillator"), newInstance);

float Oscillator::getVal() {

    float val = mCycle[mOffset++];
    if (mOffset >= mFPC)
        mOffset = 0;

    return val;
}

void Oscillator::reloadWave() {

    sample_t* tmp = mCycle;
    mCycle = WaveMaker::createWave(mWave, mFPC, mMax, mMin);
    free(tmp);
}

istream &Oscillator::read(istream &is) {

    Effect::read(is);
    is >> mWave >> mFPC;
    reloadWave();

    return is;
}

ostream &Oscillator::write(ostream &os) const {

    Effect::write(os);
    os << mFPC << ' ' << mWave << endl;

    return os;
}

