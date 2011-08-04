#include "Process.h"

using namespace std;

void Process::combine(const sample_t* from, sample_t* to, int num) {
    for (int i = 0; i < num; i++)
        to[i] += from[i];
}

sample_t Process::linearInterpolate(sample_t left, sample_t right, float perc) {
    return perc * right + (1 - perc) * left;
}

