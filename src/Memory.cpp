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

#include "Memory.h"

Memory::Memory() : mOffset(0) {
  memset(mMemory, 0, MAXMEMORY * 3 * sizeof(sample_t));
}

void Memory::storeSamples(const sample_t *in, int num) {
  for (int i = 0; i < num; i++) {
    mMemory[mOffset] = mMemory[mOffset + MAXMEMORY] =
      mMemory[mOffset + MAXMEMORY * 2] = in[i];
    mOffset = (mOffset + 1) % MAXMEMORY;
  }
}

const sample_t* Memory::getPastSamples(int num) {
  int index = (MAXMEMORY + mOffset - num) % MAXMEMORY;
  return &mMemory[MAXMEMORY + index];
}
