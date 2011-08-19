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

#ifndef STUTTER_H
#define STUTTER_H

#include <stdlib.h>
#include <math.h>
#include "Parameter.h"
#include "EffectsList.h"

#define MEMORYSIZE 4800000

class Stutter : virtual public EffectsList {
public:

    Stutter(float fpc = 5000) : mSingle(0), mOffset(0), mCycleOffset(0) {
        memset(mMemory, 0, MEMORYSIZE * 2 * sizeof(sample_t));
        memset(mBuffer, 0, MAXBUFFER * sizeof(sample_t));
        mFPC = new Parameter(fpc);
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Stutter(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setOffset(int offset) { mOffset = offset % MEMORYSIZE; }

protected:

    static Class cls;

    sample_t mMemory[MEMORYSIZE * 2];
    sample_t mBuffer[MAXBUFFER];
    int mSingle;
    long mOffset, mCycleOffset;
    Parameter *mFPC;

    virtual std::istream &read(std::istream &);
    virtual std::ostream &write(std::ostream &) const;
};

#endif
