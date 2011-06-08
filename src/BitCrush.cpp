#include "BitCrush.h"

using namespace std;

Class BitCrush::mClass(string("BitCrush"), newInstance);

void BitCrush::process(const sample_t* in, sample_t* out, int num) {
    for (int i = 0; i < num; i++) {
        float tempVal = round((mPossible - 1) * (in[i] + 1) / 2);
        out[i] = (tempVal * 2 / (mPossible - 1) - 1) * mWet;
        out[i] += in[i] * (1 - mWet);
    }
}

istream &BitCrush::Read(istream &in) {
    return in;
}

ostream &BitCrush::Write(ostream &out) const {
    return out;
}
