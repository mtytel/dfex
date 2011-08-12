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

#ifndef EFFECTSLIST_H
#define EFFECTSLIST_H

#include <vector>
#include <stdlib.h>

#include "Modifier.h"
#include "WaveMaker.h"

#define CONT "-"
#define MOD "+"
#define END "end"

class Series;

class EffectsList : public Effect {
public:

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new EffectsList(); }

    void addEffect(Effect* e);
    void createList(Class *cls, int waveType, int num);
    void readWaveModifier(std::istream &is, std::vector<Series*> *fx); 
    int size() { return mEffects.size(); }

protected:

    static Class cls;

    std::vector<Effect*> mEffects;

    std::istream &read(std::istream &);
    std::ostream &write(std::ostream &) const;
};

#endif
