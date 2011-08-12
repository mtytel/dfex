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

#ifndef SWITCH_H
#define SWITCH_H

#include <string>
#include "Effect.h"

#define CONT "-"
#define END "end"
#define NUMEFFECTS 3

class Switch : public Effect {
public:

    static const std::string mappings[NUMEFFECTS];

    Switch() : mCur(0), Effect::Effect() { 
        memset(mEffects, 0, NUMEFFECTS * sizeof(Effect*));
    }
    ~Switch() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Switch(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setEffect(int id, Effect *e) { mEffects[id] = e; }
    void keyInput(char c);

protected:

    static Class cls;

    Effect *mEffects[NUMEFFECTS];
    int mCur;
};

#endif
