#include "Volume.h"

using namespace std;

Class Volume::cls(string("Volume"), newInstance);

void Volume::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++)
        out[i] = in[i] * getVal();

    postProcess(in, out, num);
}

