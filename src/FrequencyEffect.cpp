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

FrequencyEffect::FrequencyEffect() : Effect::Effect(), mOffset(0) { 

    mMemory = (sample_t*)calloc(TRANSFORMSIZE, sizeof(sample_t));
    mTransform = new complex<sample_t>[TRANSFORMSIZE];
    mModTransform = mTransform;

    for (int i = 0; i < TRANSFORMSIZE; i++)
        mTransform[i] *= 0;
}

FrequencyEffect::~FrequencyEffect() {

    free(mMemory);
    free(mTransform);
}

void FrequencyEffect::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) { 
        updateTransform(in[i]);
        out[i] = updateInverse();
    }
    
    postProcess(in, out, num);
}

void FrequencyEffect::modifyTransform() {
    //memcpy(mTransform, mModTrasform, TRANSFORMSIZE * sizeof(sample_t));
}

/*
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
}*/

/* Sliding Discrete Fourier Transform, starts with 0s */
void FrequencyEffect::updateTransform(sample_t next) {
    
    for (int f = 0; f < TRANSFORMSIZE; f++) {
        mTransform[f] = Process::euler(f) * 
         (mTransform[f] - mMemory[mOffset] + next);
    }

    mMemory[mOffset] = next;
    mOffset = (mOffset + 1) % TRANSFORMSIZE;
}

sample_t FrequencyEffect::updateInverse() {

    complex<sample_t> ret(0, 0);

    for (int f = 0; f < TRANSFORMSIZE; f++) 
        ret += mModTransform[f] * Process::euler(-f);

    return ret.real() / TRANSFORMSIZE;
}

