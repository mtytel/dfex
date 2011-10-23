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

#ifndef VOLUME_H
#define VOLUME_H

#include <stdlib.h>

#include "Effect.h"

#define DEFAULTVOLUME 1.0

class Volume : public Effect {
public:

    Volume(float vol = 1.0) : Effect::Effect() { 
        mVol = new Constant(vol);
    }

    virtual ~Volume() {
        delete mVol;
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Volume(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    Processor *mVol;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
