#ifndef ALIASOSCILLATOR_H
#define ALIASOSCILLATOR_H

#include <stdlib.h>
#include "Aliaser.h"
#include "Oscillator.h"

class AliasOscillator : public Aliaser, public Oscillator {
public:

    AliasOscillator() : Oscillator::Oscillator(2.0, 32.0) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new AliasOscillator(); }

protected:

    static Class cls;
};

#endif
