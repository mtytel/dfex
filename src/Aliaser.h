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

#ifndef ALIASER_H
#define ALIASER_H

#include <stdlib.h>
#include <math.h>
#include "Effect.h"

#define DEFAULTRATIO 2.0

class Aliaser : public Effect {
public:

    Aliaser(float ratio = DEFAULTRATIO) : mOffset(0), mCurSamp(0), 
     Effect::Effect() { 
        mRatio = new Constant(ratio);
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Aliaser(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    Processor *mRatio;
    float mOffset;
    sample_t mCurSamp;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
