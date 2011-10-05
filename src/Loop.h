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

#ifndef LOOP_H
#define LOOP_H

#include <stdlib.h>
#include <math.h>

#include "Effect.h"

#define DEFAULTSIZE 4800000

class SingleLoop {
public:

    SingleLoop() : mOffset(0), mSize(DEFAULTSIZE), mSpeed(1) { 
        mMemory = (sample_t*)malloc(DEFAULTSIZE * sizeof(sample_t));
    }

    ~SingleLoop() { 
        free(mMemory);
    }

    sample_t operator[](int i) { return mMemory[i % mSize]; }
    void appen

protected:

    long mOffset;
    long mSize;
    float mSpeed;

    sample_t *mMemory;
};

class Loop : public Effect {
public:

    Loop() : mSpeed(1) { }

    ~Loop() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Loop(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setOffset(int offset) { mOffset = offset % MEMORYSIZE; }

protected:

    static Class cls;

    float mSpeed;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif

