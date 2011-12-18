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

#include "Volume.h"

using namespace rapidxml;
using namespace std;

Class Volume::cls(string("Volume"), newInstance);

Volume::Volume(float vol) : Effect::Effect() { 
  mVol = new Constant(vol);
}

Volume::~Volume() {
  delete mVol;
}

void Volume::process(const sample_t* in, sample_t* out, int num) {
  sample_t vol[num];
  mVol->process(in, vol, num);

  for (int i = 0; i < num; i++)
    out[i] = in[i] * vol[i];

  postProcess(in, out, num);
}

xml_node<> &Volume::read(xml_node<> &inode) {
  Effect::read(inode);

  delete mVol;
  mVol = Processor::readParameter(inode, "volume", DEFAULTVOLUME);

  return inode;
}

xml_node<> &Volume::write(xml_node<> &onode) const {
  return onode;
}

