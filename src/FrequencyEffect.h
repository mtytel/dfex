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

// Using a Sli

#ifndef FREQUENCYEFFECT_H
#define FREQUENCYEFFECT_H
#define TRANSFORMSIZE 1024

#include "Effect.h"

class FrequencyEffect : public Effect {
public:

    FrequencyEffect() : Effect::Effect(), mOffset(0) { 
        mMemory = (sample_t*)malloc(TRANSFORMSIZE * sizeof(sample_t));
        mTransform = (std::complex<sample_t>*)malloc(TRANSFORMSIZE *
         sizeof(std::complex<sample_t>));
    }

    virtual ~FrequencyEffect() { 
        free(mMemory);
        free(mTransform);
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new FrequencyEffect(); }

    virtual void process(const sample_t* in, sample_t* out, int num);
    void initialTransform(const sample_t* in);
    void updateTransform(sample_t next);

protected:

    static Class cls;

    std::complex<sample_t> *mTransform;
    sample_t *mMemory;

    uint mOffset;
};

#endif
