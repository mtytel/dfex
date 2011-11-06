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
#include "Effect.h"
#include "Memory.h"
#include <iostream>

#define MEMORYSIZE 4800000
#define DEFAULTDELAY 5000
#define DEFAULTDECAY 0.5
#define DEFAULTPROCESS 1

using namespace std;

class Feedback : public Effect {
public:

    Feedback() {
        mMemory = new Memory();
    }

    virtual ~Feedback() {
        delete mDelay;
        delete mDecay;
        delete mProcess;
        delete mMemory;
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Feedback(); }

    void process(const sample_t* in, sample_t* out, int num);


protected:

    static Class cls;

    Processor *mDelay;
    Processor *mDecay;
    Processor *mProcess;

    Memory *mMemory;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
                    
