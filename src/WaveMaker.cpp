
#include <stdlib.h>
#include "WaveMaker.h"

using namespace std;

sample_t* WaveMaker::create_wave(int type, int frames, int neg) {
    sample_t* wave = (sample_t*)malloc(frames * sizeof(sample_t));
    float k = (2 * PI) / frames;

    for (int i = 0; i < frames; i++) {
        if (type == kSine)
            wave[i] = sin(i * k);

        else if (type == kSquare)
            wave[i] = sin(i * k) >= 0 ? 1 : -1;

        else
            wave[i] = 2 * frames / i - 1;

        if (!neg)
            wave[i] = wave[i] / 2 + .5;
    }

    return wave;
}
