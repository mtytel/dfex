#ifndef SAMPLEOSCILLATOR_H
#define SAMPLEOSCILLATOR_H

#include <stdlib.h>
#include "SampleRate.h"
#include "Oscillator.h"

class SampleOscillator : public SampleRate, public Oscillator {
public:

    SampleOscillator() : Oscillator::Oscillator(2.0, 32.0) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new SampleOscillator(); }

protected:

    static Class cls;
};

#endif
