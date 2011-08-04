#include "BitCrush.h"

using namespace std;

Class BitCrush::cls(string("BitCrush"), newInstance);

void BitCrush::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) {
        float mult = getVal() / 2;
        float temp = round(mult * in[i]);
        out[i] = temp / mult;
    }

    postProcess(in, out, num);
}

