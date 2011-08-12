#ifndef ALIASER_H
#define ALIASER_H

#include <stdlib.h>
#include <math.h>
#include "Modifier.h"

class Aliaser : public Modifier {
public:

    Aliaser(float ratio = 2.0) : mOffset(0), mCurSamp(0), 
     Modifier::Modifier(ratio) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Aliaser(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    float mOffset;
    sample_t mCurSamp;
};

#endif
