#ifndef BITCRUSH_H
#define BITCRUSH_H

#include <stdlib.h>
#include <math.h>
#include "Modifier.h"

class BitCrush : public Modifier {
public:

    BitCrush(float bits = 2) : Modifier::Modifier(bits) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new BitCrush(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;
};

#endif
