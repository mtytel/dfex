#ifndef SAMPLERATE_H
#define SAMPLERATE_H

#include <stdlib.h>
#include <math.h>
#include "Modifier.h"

class SampleRate : virtual public Modifier {
public:

    SampleRate() : mOffset(0), mCurSamp(0), Modifier::Modifier(2) { }
    ~SampleRate() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new SampleRate(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    float mOffset;
    sample_t mCurSamp;
};

#endif
