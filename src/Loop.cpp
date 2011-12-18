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

#include "Loop.h"

using namespace std;
using namespace rapidxml;

Class Loop::cls(string("Loop"), newInstance);

Loop::Loop() : Parallel::Parallel(), mSilentId(DEFAULTSILENT), mTrackQuant(1),
               mLastVal(0), mLastButton(0) {
  mControl = new Constant(DEFAULTSILENT);
  addProcessor(new Processor());
}

Loop::~Loop() {
  delete mControl;
}

Loop::LoopTrack::LoopTrack(int quant) : mMemSize(DEFAULTSIZE),
                                        mRecLength(0), mOffset(0),
                                        mState(kRecording), mQuant(quant) {
  mMemory = (sample_t*)calloc(mMemSize, sizeof(sample_t));
}

Loop::LoopTrack::~LoopTrack() {
  free(mMemory);
}

void Loop::LoopTrack::process(const sample_t* in, sample_t* out, int num) {
  memset(out, 0, num * sizeof(size_t));

  if (mState == kRecording)
    record(in, num);
  else if (mState == kPlaying)
    playBack(out, num);
  else if (mState == kSilence)
    mOffset = (mOffset + num) % mRecLength;
}

void Loop::LoopTrack::record(const sample_t *in, int num) {
  mRecLength = mOffset + num;
  resize();

  memcpy(mMemory + mOffset, in, num * sizeof(sample_t));
  mOffset += num;
}

void Loop::LoopTrack::stopRecording() {
  mState = kPlaying;
  mRecLength = (mOffset / mQuant + 1) * mQuant;
  resize();
  cout << mQuant << endl;
}

void Loop::LoopTrack::playBack(sample_t *out, int num) {
  for (int i = 0; i < num; i++) {
    out[i] = mMemory[mOffset];
    mOffset = (mOffset + 1) % mRecLength;
  }
}

void Loop::LoopTrack::resize() {
  if (mMemSize < mRecLength) {

    mMemSize *= (mRecLength / mMemSize + 1);
    mMemory = (sample_t*)realloc(mMemory, mMemSize * sizeof(sample_t));
  }
}

void Loop::LoopTrack::toggle() {
  if (mState == kRecording)
    stopRecording();
  else if (mState == kPlaying)
    mState = kSilence;
  else if (mState == kSilence)
    mState = kPlaying;
}

void Loop::process(const sample_t* in, sample_t* out, int num) {
  sample_t control[num];
  mControl->process(in, control, num);
  controlResponse(control[num - 1]);

  Parallel::process(in, out, num);
  postProcess(in, out, num);
}

void Loop::controlResponse(char val) {
  if (val != mLastVal)
    buttonPushed(val >= 0 ? val : mLastVal);

  mLastVal = val;
}

void Loop::buttonPushed(char but) {
  if (but == mSilentId) {
    if (anyPlaying())
      silenceAll();
    else
      playAll();
  }
  else {
    map<int, LoopTrack*>::const_iterator found = mTrackMap.find(but);
    map<int, LoopTrack*>::const_iterator last = mTrackMap.find(mLastButton);
    int recording = last != mTrackMap.end() && last->second->isRecording();
    if (recording) {
      last->second->toggle();
      int length = last->second->getRecLength();
      mTrackQuant = mTrackQuant < length ? length : mTrackQuant;
    }

    if (found == mTrackMap.end()) {
      LoopTrack *newLoop = new LoopTrack(getMinQuant());
      mTrackMap[but] = newLoop;
      addProcessor(newLoop);
    }
    else if (!recording || mLastButton != but)
      found->second->toggle();
  }
  mLastButton = but;
}

int Loop::anyPlaying() {
  map<int, LoopTrack*>::const_iterator it;
  for (it = mTrackMap.begin(); it != mTrackMap.end(); it++) 
    if (it->second->isPlaying())
      return 1;

  return 0;
}

void Loop::silenceAll() {
  map<int, LoopTrack*>::const_iterator it, end = mTrackMap.end();
  for (it = mTrackMap.begin(); it != end; it++) 
    it->second->silence();
}

void Loop::playAll() {
  map<int, LoopTrack*>::const_iterator it, end = mTrackMap.end();
  for (it = mTrackMap.begin(); it != end; it++) 
    it->second->play();
}

xml_node<> &Loop::read(xml_node<> &inode) {
  xml_node<> *val = inode.first_node("silent");
  mSilentId = val ? atoi(val->value()) : DEFAULTSILENT;

  val = inode.first_node("quant");
  mTrackQuant = val ? atoi(val->value()) : 1;

  delete mControl;
  mControl = Processor::readParameter(inode, "control", DEFAULTSILENT);

  return inode;
}

xml_node<> &Loop::write(xml_node<> &onode) const {
  return onode;
}
