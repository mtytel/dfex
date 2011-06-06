#ifndef SERIES_H
#define SERIES_H

#include "Effect.h"

class Series : public Effect {
public:
    void process(const sample_t* in, sample_t* out, int num);

    Series(Effect *first, Effect *next, float wet = 1) : mFirst(first),
     mNext(next), Effect::Effect(wet) { }

    ~Series() {}

protected:
    Effect *mFirst;
    Effect *mNext;
    sample_t mBuffer[MAXBUFFER];
};

#endif
