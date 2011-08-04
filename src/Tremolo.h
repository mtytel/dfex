#ifndef TREMOLO_H
#define TREMOLO_H

#include <stdlib.h>
#include "Volume.h"
#include "Oscillator.h"

class Tremolo : public Volume, public Oscillator {
public:

    Tremolo() : Oscillator::Oscillator(0.0, 1.0) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Tremolo(); }

protected:

    static Class cls;
};

#endif
