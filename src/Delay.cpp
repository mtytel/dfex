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

#include "Delay.h"

using namespace rapidxml;

Class Delay::cls(std::string("Delay"), newInstance);

Delay::Delay(float period) : mGranular(0), mGranularOffset(0) {
  mPeriod = new Constant(period);
  mMemory = new Memory();
}

Delay::~Delay() {
  delete mPeriod;
  delete mMemory;
}

void Delay::granulate(const sample_t *in, sample_t *out, size_t per, int num) {

  for (int i = 0; i < num; i++) {
    if (mGranularOffset >= per * mProcessors.size())
      mGranularOffset = 0;

    out[i] = mGranularOffset++ >= per ? 0 : in[i];
  }
}

void Delay::process(const sample_t* in, sample_t* out, int num) {

  sample_t periods[num], fit[num], buffer[num];
  mPeriod->process(in, periods, num);
  size_t prevPeriod = round(periods[0]);
  size_t curPeriod = round(periods[num - 1]);

  if (mGranular) {
    sample_t granulated[num];
    granulate(in, granulated, curPeriod, num);
    mMemory->storeSamples(granulated, num);
  }
  else
    mMemory->storeSamples(in, num);

  memset(out, 0, num * sizeof(sample_t));

  for (size_t st = 0; st < mProcessors.size(); st++) {
    int offsetStart = st * prevPeriod + num;
    int offsetEnd = st * curPeriod;
    int procNum = offsetStart - offsetEnd;

    const sample_t *sampStart = mMemory->getPastSamples(offsetStart);
    Process::fit(sampStart, fit, procNum, num);
    mProcessors[st]->process(fit, buffer, num);
    Process::combine(buffer, out, out, num);
  }

  postProcess(in, out, num);
}

xml_node<> &Delay::read(xml_node<> &inode) {

  ProcessorList::read(inode);

  delete mPeriod;
  mPeriod = Processor::readParameter(inode, "period", DEFAULTPERIOD);

  xml_node<> *granNode = inode.first_node("granular");
  mGranular = granNode ? 1 : 0;

  return inode;
}

xml_node<> &Delay::write(xml_node<> &onode) const {

  return onode;
}
