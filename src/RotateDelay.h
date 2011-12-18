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
#define ROTATEDELAY_H

#include <stdlib.h>
#include <math.h>

#include "ProcessorList.h"
#include "Memory.h"

#define DEFAULTPERIOD 5000
#define DEFAULTSPEED -1

class RotateDelay : public ProcessorList {
  public:
    RotateDelay(float period = DEFAULTPERIOD, float speed = DEFAULTSPEED);
    virtual ~RotateDelay();

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new RotateDelay(); }

    void process(const sample_t* in, sample_t* out, int num);

  protected:
    static Class cls;

    float mRotation;
    Processor *mPeriod, *mSpeed;
    Memory *mMemory;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
