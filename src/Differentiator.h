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

#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include <stdlib.h>
#include <math.h>
#include "Effect.h"

class Differentiator : public Effect {
public:

    Differentiator() : Effect::Effect(), mLastSamp(0) { }
    virtual ~Differentiator() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Differentiator(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    sample_t mLastSamp;
};

#endif
