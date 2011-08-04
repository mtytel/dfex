#include "SampleRate.h"

using namespace std;

Class SampleRate::cls(string("SampleRate"), newInstance);

void SampleRate::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) {
        float ratio = getVal();

        if (++mOffset > ratio) { 
            mCurSamp = in[i];
            mOffset -= ratio;
        }
        out[i] = mCurSamp;
    }

    postProcess(in, out, num);
}

