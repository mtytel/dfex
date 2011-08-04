#ifndef BITOSCILLATOR_H
#define BITOSCILLATOR_H

#include <stdlib.h>
#include "BitCrush.h"
#include "Oscillator.h"

class BitOscillator : public BitCrush, public Oscillator {
public:

    BitOscillator() : Oscillator::Oscillator(2.0, 16.0) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new BitOscillator(); }

protected:

    static Class cls;
};

#endif
