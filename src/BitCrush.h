#ifndef BITCRUSH_H
#define BITCRUSH_H

#include <stdlib.h>
#include <math.h>
#include "Effect.h"

class BitCrush : public Effect {
public:
    void process(const sample_t* in, sample_t* out, int num);

    BitCrush(int bits, char zero = 1, float wet = 1) : 
     Effect::Effect(wet) { mPossible = pow(2, bits) + zero; }

    ~BitCrush() {}

protected:
    int mPossible;
};

#endif
