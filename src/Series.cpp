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

#include "Series.h"

using namespace std;

Class Series::cls(string("Series"), newInstance);

void Series::process(const sample_t* in, sample_t* out, int num) {
    const sample_t* from = in;
    sample_t* to = mEffects.size() % 2 ? out : mBuffer;

    for (int i = 0; i < mEffects.size(); i++) {
        mEffects[i]->process(from, to, num);
        from = to;
        to = from == out ? mBuffer : out;
    }

    postProcess(in, out, num);
}

