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

#ifndef ROTATEDELAY_H
#define ROTEDELAY_H

#include <stdlib.h>
#include <math.h>
#include "ProcessorList.h"

#define MEMORYSIZE 4800000
#define DEFAULTPERIOD 5000
#define DEFAULTSPEED -2

class RotateDelay : public ProcessorList {
public:

    RotateDelay(float period = DEFAULTPERIOD, float speed = DEFAULTSPEED) :
     mOffset(0), mRotation(0), mCurPeriod(0) {
        memset(mMemory, 0, MEMORYSIZE * 2 * sizeof(sample_t));
        memset(mBuffer, 0, MAXBUFFER * sizeof(sample_t));
        mPeriod = new Constant(period);
        mSpeed = new Constant(speed);
    }

    virtual ~RotateDelay() {
        delete mPeriod;
        delete mSpeed;
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new RotateDelay(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    sample_t mMemory[MEMORYSIZE * 2];
    sample_t mBuffer[MAXBUFFER];
    long mOffset;
    float mRotation
    Processor *mPeriod, *mSpeed;
    sample_t mCurPeriod;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
