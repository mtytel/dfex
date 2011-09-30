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

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <stdlib.h>
#include "WaveMaker.h"
#include "Processor.h"
#include "Constant.h"

#define DEFAULTMIN 0.0
#define DEFAULTMAX 1.0
#define DEFAULTRATE 0.1

class Controller : public Processor {
public:

    static const std::string mappings[3];

    Controller(int rate = DEFAULTRATE, float min = DEFAULTMIN, 
     float max = DEFAULTMAX) : Processor::Processor(), mDir(0), 
     mCur(DEFAULTMAX) { 
        mMin = new Constant(min);
        mMax = new Constant(max);
        mRate = new Constant(rate);
    }

    ~Controller() {
        delete mMin;
        delete mMax;
        delete mRate;
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Controller(); }

    virtual void process(const sample_t* in, sample_t* out, int num);
    void keyInput(char c);

protected:

    static Class cls;

    Processor *mMin, *mMax, *mRate;
    int mDir;
    sample_t mCur;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
