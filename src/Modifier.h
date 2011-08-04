#ifndef MODIFIER_H
#define MODIFIER_H

#include <stdlib.h>
#include "WaveMaker.h"
#include "Effect.h"

class Modifier : virtual public Effect {
public:

    Modifier(float val = 0) : mVal(val), Effect::Effect() { }

    ~Modifier() { }

    virtual float getVal() { return mVal; }
    virtual float setVal(float val) { mVal = val; }

protected:

    static Class cls;

    float mVal;

    virtual std::istream &read(std::istream &);
    virtual std::ostream &write(std::ostream &) const;
};

#endif
