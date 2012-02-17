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

#include "EQ.h"

using namespace rapidxml;
using namespace std;

Class EQ::cls(string("EQ"), newInstance);

EQ::EQ(int startOff, int endOff) : Effect::Effect() {
  mStartOff = new Constant(startOff);
  mEndOff = new Constant(endOff);
}

EQ::~EQ() {
}

void EQ::process(const sample_t* in, sample_t* out, int num) {
  sample_t input[num], transform[num], startOff[num], endOff[num];
  mStartOff->process(in, startOff, num);
  mEndOff->process(in, endOff, num);
  memcpy(input, in, num * sizeof(sample_t));

  for (int period = 2; period < num; period *= 2) {
    int num_waves = num / period;
    for (int i = 0; i < num_waves; i++) {
      sample_t sum = (input[i * 2] + input[i * 2 + 1]) / 2;
      sample_t difference = (input[i * 2] - input[i * 2 + 1]) / 2;
      transform[i] = sum;
      transform[num_waves + i] = difference;
    }
    memcpy(input, transform, num_waves * 2 * sizeof(sample_t));
  }

  for (int i = num / startOff[0]; i < num / endOff[0]; i++)
    transform[i] = 0;

  memset(out, 0, num * sizeof(sample_t));
  for (int i = 0; i < num; i++) {
    out[i] = transform[0];
    for (int period = num; period > 1; period /= 2) {
      int num_waves = num / period;
      int wave_offset = i / period;
      int mult = i % period < period / 2 ? 1 : -1;;
      out[i] += transform[num_waves + wave_offset] * mult;
    }
  }
}

xml_node<> &EQ::read(xml_node<> &inode) {
  Effect::read(inode);

  delete mStartOff;
  mStartOff = Processor::readParameter(inode, "startOff", 1);
  delete mEndOff;
  mEndOff = Processor::readParameter(inode, "endOff", 1);
  return inode;
}

xml_node<> &EQ::write(xml_node<> &onode) const {
  return onode;
}
