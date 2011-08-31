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

#include "WaveMaker.h"

using namespace std;

double WaveMaker::sine(double val) {
    return sin(val * 2 * PI) / 2 + 0.5;
}

double WaveMaker::cosine(double val) {
    return cos(val * 2 * PI) / 2 + 0.5;
}

double WaveMaker::square(double val) {
    return (val - floor(val)) < 0.5 ? 1 : 0;
}

double WaveMaker::sawRise(double val) {
    return val - floor(val);
}

double WaveMaker::sawFall(double val) {
    return 1 - sawRise(val);
}

waveFunction WaveMaker::getFunction(int type) {
    if (type == kOn)
        return on;
    if (type == kOff)
        return off;
    if (type == kSine)
        return sine;
    if (type == kCos)
        return cosine;
    if (type == kSquare)
        return square;
    if (type == kSawRise)
        return sawRise;
    return sawFall;
}

sample_t* WaveMaker::createWave(int type, int frames, float min, 
 float max, int offset) {

    sample_t* wave = (sample_t*)malloc(frames * sizeof(sample_t));
    waveFunction waveFunc = getFunction(type);
    float a = max - min;

    for (int i = offset; i < frames + offset; i++)
        wave[i] = a * waveFunc(1.0 * i / frames) + min;

    return wave;
}
