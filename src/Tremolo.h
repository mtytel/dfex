#ifndef TREMOLO_H
#define TREMOLO_H

#include <stdlib.h>
#include "WaveMaker.h"
#include "Effect.h"

class Tremolo : public Effect {
public:

    Tremolo() : mFPC(1), mOffset(0), Effect::Effect() {
        mCycle = WaveMaker::create_wave(WaveMaker::kSine, mFPC, 0);
    }

    ~Tremolo() { free(mCycle); }

    const Class *GetClass() const { return &mClass; }
    static Object *newInstance() { return new Tremolo(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setWave(int fpc, int wave); 

protected:

    static Class mClass;

    sample_t* mCycle;
    jack_nframes_t mFPC; // Frames per cycle
    long mOffset;

    std::istream &Read(std::istream &);
    std::ostream &Write(std::ostream &) const;
};

#endif
