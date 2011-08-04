#ifndef PROCESS_H
#define PROCESS_H

#include <jack/jack.h>
#include <string.h>
#include <stdlib.h>

typedef jack_default_audio_sample_t sample_t;

class Process {
public:

    static sample_t linearInterpolate(sample_t, sample_t, float);
    static void combine(const sample_t* one, sample_t* two, int num);
};

#endif
