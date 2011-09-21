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

#include "Switch.h"

using namespace std;

Class Switch::cls(string("Switch"), newInstance);
const string Switch::mappings[NUMEFFECTS] = {
 "123\tqwaszx",
 "45678ertyuidfghjcvbn",
 "90-=op[]\\kl;'\nm,./"};

void Switch::process(const sample_t* in, sample_t* out, int num) {
    
    mProcessors[mCur]->process(in, out, num);
    postProcess(in, out, num);
}

void Switch::keyInput(char c) {

    for (int i = 0; i < NUMEFFECTS; i++) {
        if (mappings[i].find(c) != string::npos)
            mCur = i;
    }
}

