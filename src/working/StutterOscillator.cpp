#include "StutterOscillator.h"

using namespace std;

Class StutterOscillator::cls(string("StutterOscillator"), newInstance);

istream &StutterOscillator::read(istream &is) {

    Stutter::read(is);
    is >> mWave;
    reloadWave();
    return is;
}

ostream &StutterOscillator::write(ostream &os) const {

    Stutter::write(os);
    os << mWave;
    return os;
}

