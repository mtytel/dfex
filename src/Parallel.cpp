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

#include "Parallel.h"

using namespace std;

Class Parallel::cls(string("Parallel"), newInstance);

void Parallel::process(const sample_t* in, sample_t* out, int num) {
    memset(out, 0, num * sizeof(sample_t));

    for (size_t i = 0; i < mProcessors.size(); i++) {
        mProcessors[i]->process(in, mBuffer, num);
        Process::combine(mBuffer, out, out, num);
    }
    postProcess(in, out, num);
}

