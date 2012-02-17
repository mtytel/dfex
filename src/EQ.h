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

#ifndef EQ_H
#define EQ_H

#include "Effect.h"

class EQ : public Effect {
  public:
    EQ(int startOff = 1, int endOff = 1);
    virtual ~EQ();

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new EQ(); }

    void process(const sample_t* in, sample_t* out, int num);

  protected:
    Processor *mStartOff, *mEndOff;
    static Class cls;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
