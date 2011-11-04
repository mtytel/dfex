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

#ifndef MEMOIZER_H
#define MEMOIZER_H

#include <string.h>

#include "Setup.h"

#define MAXMEMORY 4800000

class Memoizer {
public:

    Memoizer() : mOffset(0) {
        memset(mMemory, 0, MAXMEMORY * 3 * sizeof(sample_t));
    }

    virtual ~Memoizer() { }

    virtual void storeSamples(const sample_t *in, int num);
    const sample_t* getPastSamples(int num);

protected:

    sample_t mMemory[MAXMEMORY * 3];
    long mOffset;
};

#endif
