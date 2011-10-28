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

#ifndef PROCESS_H
#define PROCESS_H

#include <math.h>
#include <jack/jack.h>
#include <string.h>
#include <stdlib.h>

typedef jack_default_audio_sample_t sample_t;

class Process {
public:

    static sample_t linearInterpolate(sample_t, sample_t, float);
    static void combine(const sample_t*, const sample_t*, sample_t*, int);
    static void fit(const sample_t*, sample_t*, int, int);
    static void power(const sample_t*, sample_t*, float, int);
    static void invert(const sample_t*, sample_t*, int);
};

#endif
