#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <stdlib.h>
#include "WaveMaker.h"
#include "Modifier.h"

class Oscillator : virtual public Modifier {
public:

    Oscillator(float min, float max) : mMin(min), mMax(max), mFPC(1), 
     mOffset(0), Modifier::Modifier(max) {
        mCycle = WaveMaker::createWave(WaveMaker::kSine, mFPC, mMax, mMin);
    }

    ~Oscillator() { free(mCycle); }

    virtual float getVal();
    void reloadWave(); 

protected:

    static Class cls;

    float mMax, mMin;
    sample_t* mCycle;
    jack_nframes_t mFPC; // Frames per cycle
    int mWave;
    long mOffset;

    std::istream &read(std::istream &);
    std::ostream &write(std::ostream &) const;
};

#endif
