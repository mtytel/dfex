#include "Parallel.h"

using namespace std;

Class Parallel::mClass(string("Parallel"), newInstance);

void Parallel::process(const sample_t* in, sample_t* out, int num) {
    mLeft->process(in, out, num);
    mRight->process(in, mOutRight, num);
    
    for (int i = 0; i < num; i++)
        out[i] = (out[i] + mOutRight[i]) * mWet + in[i] * (1 - mWet);
}

istream &Parallel::Read(istream &in) {
    return in;
}

ostream &Parallel::Write(ostream &out) const {
    return out;
}
