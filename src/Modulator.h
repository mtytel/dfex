#ifndef MODULATOR_H
#define MODULATOR_H

#include <stdlib.h>
#include "Volume.h"
#include "Oscillator.h"

class Modulator : public Volume, public Oscillator {
public:

    Modulator() : Oscillator::Oscillator(-1.0, 1.0) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Modulator(); }

protected:

    static Class cls;
};

#endif
