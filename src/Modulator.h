/* 
 * Copyright 2011 Matthew Tytel
 *
 * dfex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dfex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dfex.  If not, see <http://www.gnu.org/licenses/>.
 */

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
