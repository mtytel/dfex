#ifndef PARALLEL_H
#define PARALLEL_H

#include "Effect.h"

class Parallel : public Effect {
public:
    void process(const sample_t* in, sample_t* out, int num);

    Parallel(Effect *left, Effect *right, float wet = 1) : mLeft(left),
     mRight(right), Effect::Effect(wet) { }

    ~Parallel() {}

protected:
    Effect *mLeft;
    Effect *mRight;
    sample_t mOutRight[MAXBUFFER];
};

#endif
