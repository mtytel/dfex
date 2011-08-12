#include "Parallel.h"

using namespace std;

Class Parallel::cls(string("Parallel"), newInstance);

void Parallel::process(const sample_t* in, sample_t* out, int num) {

    memset(out, 0, num * sizeof(sample_t));

    for (int i = 0; i < mEffects.size(); i++) {
        mEffects[i]->process(in, mBuffer, num);
        Process::combine(mBuffer, out, num);
    }

    postProcess(in, out, num);
}

