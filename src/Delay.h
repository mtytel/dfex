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

#ifndef DELAY_H
#define DELAY_H

#include <stdlib.h>
#include <math.h>
#include "ProcessorList.h"
#include "Memory.h"

#define DEFAULTPERIOD 5000

class Delay : public ProcessorList {
  public:
    Delay(float period = DEFAULTPERIOD);
    virtual ~Delay();

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Delay(); }

    void granulate(const sample_t *in, sample_t *out, size_t per, int num);
    void process(const sample_t* in, sample_t* out, int num);

  protected:
    static Class cls;

    size_t mGranular, mGranularOffset;
    Processor *mPeriod;
    Memory *mMemory;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
