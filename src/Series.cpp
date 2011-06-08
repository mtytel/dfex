#include "Series.h"

using namespace std;

Class Series::mClass(string("Series"), newInstance);

void Series::process(const sample_t* in, sample_t* out, int num) {
    mFirst->process(in, mBuffer, num);
    mNext->process(mBuffer, out, num);

    for (int i = 0; i < num; i++)
        out[i] = out[i] * mWet + in[i] * (1 - mWet);
}


istream &Series::Read(istream &in) {
    return in;
}

ostream &Series::Write(ostream &out) const {
    return out;
}
