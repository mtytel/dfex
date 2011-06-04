#ifndef TREMOLO_H
#define TREMOLO_H

#include <stdlib.h>
#include "WaveMaker.h"
#include "Effect.h"

class Tremolo : public Effect {
public:
    void process(const sample_t* in, sample_t* out, int num);

    Tremolo(float fpc, int wave, float wet = 1) : mFPC(fpc), 
     mOffset(0), Effect::Effect(wet) {
        mCycle = WaveMaker::create_wave(wave, mFPC, 0);
    }

    ~Tremolo() { free(mCycle); }

protected:
    sample_t* mCycle;
    jack_nframes_t mFPC; // Frames per cycle
    long mOffset;
};

#endif
