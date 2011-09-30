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

#include "FrequencyEffect.h"

using namespace std;

Class FrequencyEffect::cls(std::string("FrequencyEffect"), newInstance);

void FrequencyEffect::process(const sample_t* in, sample_t* out, int num) {

    Effect::process(in, out, num);
    postProcess(in, out, num);
}

void FrequencyEffect::initialTransform(const sample_t *in) {

    memcpy(mMemory, in, TRANSFORMSIZE * sizeof(sample_t));
    mOffset = 0;

    for (int f = 0; f < TRANSFORMSIZE; f++) {
        mTransform[f].real() = 0;
        mTransform[f].imag() = 0;

        for (int x = 0; x < TRANSFORMSIZE; x++) 
            mTransform[f] += 
             Process::euler(1.0f * f * x / TRANSFORMSIZE) * in[x];
    }
}

void FrequencyEffect::updateTransform(sample_t next) {
    
    for (int f = 0; f < TRANSFORMSIZE; f++) {
        mTransform[f] = Process::euler(1.0 * f / TRANSFORMSIZE) * 
         (mTransform[f] - mMemory[mOffset] + next);
    }

    mMemory[mOffset++] = next;
}
