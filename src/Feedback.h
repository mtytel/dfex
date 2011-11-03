/* 
 * Copyright 2011 Noura Howell
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

#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <stdlib.h>
#include <math.h>
#include <queue>
#include "Effect.h"

#define MEMORYSIZE 4800000
#define DEFAULTDELAY 5000

class Feedback : public Effect {
public:

    Feedback(float delay = 5000) : mDelay(delay), mMemLen(0), mCurSamp(0) {
        memset(mBuffer, 0, MAXBUFFER * sizeof(sample_t));
    }

    virtual ~Feedback() {
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Feedback(); }

    void process(const sample_t* in, sample_t* out, int num);

    void push(sample_t s) {
        mMemory.push(s);
        mMemLen++;
    }

    sample_t pop() {
        mMemLen--;
        return mMemory.pop();
    }

protected:

    static Class cls;

    queue<sample_t> mMemory; // store output to feed back in to input
    int mMemLen;             // self-managed length of mMemory
    int mDelay;              // the delay before feeding mMemory back in

    sample_t mCurSamp;       // current sample we're working with

    sample_t* mBuffer[MAXBUFFER]; // temp storage while computing output

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
                    
