#ifndef STUTTER_H
#define STUTTER_H

#include <stdlib.h>
#include "Effect.h"

class Stutter : public Effect {
public:
    void process(const sample_t* in, sample_t* out, int num);

    Stutter(int fpc, int numStutters, float wet = 1) : mFPC(fpc), mOffset(0), 
     mNumStutters(numStutters), mCurStutter(0), Effect::Effect(wet) {
        mMemory = (sample_t*)malloc(fpc * sizeof(sample_t));
    }

    ~Stutter() { free(mMemory); }

protected:
    sample_t* mMemory;
    jack_nframes_t mFPC; // Frames per cycle
    long mOffset;
    int mNumStutters;
    int mCurStutter;
};

#endif
