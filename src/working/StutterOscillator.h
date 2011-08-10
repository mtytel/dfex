#ifndef STUTTEROSCILLATOR_H
#define STUTTEROSCILLATOR_H

#include <stdlib.h>
#include "Stutter.h"
#include "Oscillator.h"

class StutterOscillator : public Stutter, public Oscillator {
public:

    StutterOscillator() : Oscillator::Oscillator(5000, 50000) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new StutterOscillator(); }

protected:

    static Class cls;
    virtual std::istream &read(std::istream &);
    virtual std::ostream &write(std::ostream &) const;
};

#endif
