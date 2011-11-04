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
#include <iostream>

#define MEMORYSIZE 4800000
#define DEFAULTDELAY 5000
#define DEFAULTDECAY 0.5
#define DEFAULTPROCESS 1

using namespace std;

class Feedback : public Effect {
public:

    Feedback() : mOffset(0) {
        cout << endl << " Feedback() " << endl;
        memset(mBuffer, 0, MAXBUFFER * sizeof(sample_t) * 2);
        cout << endl << " memset buffer " << endl;
    }

    virtual ~Feedback() {
        delete mDelay;
        delete mDecay;
        delete mProcess;
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Feedback(); }

    void process(const sample_t* in, sample_t* out, int num);


protected:

    static Class cls;

    int mOffset;

    Processor *mDelay;
    int mCurDelay;

    Processor *mDecay;
    float mCurDecay;

    Processor *mProcess;

    sample_t mBuffer[MAXBUFFER * 2];

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
                    
