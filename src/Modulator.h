#ifndef MODULATOR_H
#define MODULATOR_H

#include <stdlib.h>
#include "WaveMaker.h"
#include "Parameter.h"

class Modulator : public Parameter {
public:

    Modulator(float min = 0, float max = 0, int fpc = 1) :  mOffset(0), 
     Parameter::Parameter(max) { 
        mMin = new Parameter(min);
        mMax = new Parameter(max);
        mFPC = new Parameter(fpc);
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Modulator(); }

    virtual float getVal();
    void setWave(int wave);

protected:

    static Class cls;

    Parameter *mMin, *mMax, *mFPC;
    long mOffset;
    waveFunction mWaveFunc;

    std::istream &read(std::istream &);
    std::ostream &write(std::ostream &) const;
};

#endif
