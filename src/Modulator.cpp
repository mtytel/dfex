#include "Modulator.h"

using namespace std;

Class Modulator::cls(string("Modulator"), newInstance);

float Modulator::getVal() {

    float fpc = mFPC->getVal();
    float val = mWaveFunc(1.0 * mOffset++ / fpc);

    if (mOffset >= fpc)
        mOffset = 0;

    return val * mMax->getVal() + (1 - val) * mMin->getVal();
}

void Modulator::setWave(int wave) {

    mWaveFunc = WaveMaker::getFunction(wave);
}

istream &Modulator::read(istream &is) {

    int wave;
    is >> wave;
    setWave(wave);

    free(mFPC);
    free(mMin);
    free(mMax);
    mFPC = readParameter(is);
    mMin = readParameter(is);
    mMax = readParameter(is);

    return is;
}

ostream &Modulator::write(ostream &os) const {

    os << mFPC << " " << mMin << " " << mMax << endl;
    return os;
}

