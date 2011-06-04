#ifndef WAVEMAKER_H
#define WAVEMAKER_H

#include <math.h>
#include <jack/jack.h>

#define PI 3.141529

typedef jack_default_audio_sample_t sample_t;

class WaveMaker {
public:
    enum {kSine, kSquare, kSaw};

    static sample_t* create_wave(int type, int frames, int neg);
};

#endif
