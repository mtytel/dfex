#ifndef ALIASER_H
#define ALIASER_H

#include <stdlib.h>
#include <math.h>
#include "Modifier.h"

class Aliaser : virtual public Modifier {
public:

    Aliaser() : mOffset(0), mCurSamp(0), Modifier::Modifier(2) { }
    ~Aliaser() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Aliaser(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    float mOffset;
    sample_t mCurSamp;
};

#endif
