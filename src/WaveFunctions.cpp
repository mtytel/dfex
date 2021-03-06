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

#include "WaveFunctions.h"

using namespace std;

double WaveFunctions::sine(double val) {
  return sin(val * 2 * PI) / 2 + 0.5;
}

double WaveFunctions::cosine(double val) {
  return cos(val * 2 * PI) / 2 + 0.5;
}

double WaveFunctions::square(double val) {
  return (val - floor(val)) < 0.5 ? 1 : 0;
}

double WaveFunctions::sawRise(double val) {
  return val - floor(val);
}

double WaveFunctions::sawFall(double val) {
  return 1 - sawRise(val);
}

double WaveFunctions::cosWindow(double val) {
  return 1 - cosine(val);
}

  waveFunction WaveFunctions::getFunction(int type) {
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

waveFunction WaveFunctions::getFunction(const string &name) {
  if (name.substr(0, 2).compare("on") == 0)
    return on;
  if (name.substr(0, 3).compare("off") == 0)
    return off;
  if (name.substr(0, 3).compare("sin") == 0)
    return sine;
  if (name.substr(0, 3).compare("cos") == 0)
    return cosine;
  if (name.substr(0, 3).compare("squ") == 0)
    return square;
  if (name.substr(0, 4).compare("sawr") == 0)
    return sawRise;
  return sawFall;
}

