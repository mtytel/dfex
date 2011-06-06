#include "Parallel.h"

using namespace std;

void Parallel::process(const sample_t* in, sample_t* out, int num) {
    mLeft->process(in, out, num);
    mRight->process(in, mOutRight, num);
    
    for (int i = 0; i < num; i++)
        out[i] = (out[i] + mOutRight[i]) * mWet + in[i] * (1 - mWet);
}
