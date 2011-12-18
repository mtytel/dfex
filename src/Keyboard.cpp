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

#include "Keyboard.h"

using namespace std;
using namespace rapidxml;

boost::shared_mutex KeyboardStream::mutex;
vector<KeyboardStomp*> KeyboardStream::controllers;

Class KeyboardStomp::cls(string("KeyboardStomp"), newInstance);

void KeyboardStream::readKey() {
  char c = getch();
  boost::shared_lock<boost::shared_mutex> lock(KeyboardStream::mutex);

  for (uint i = 0; i < KeyboardStream::controllers.size(); i++)
    KeyboardStream::controllers[i]->keyInput(c);
}

void KeyboardStream::stream() {
  while (1) 
    readKey();
}

void KeyboardStream::addController(KeyboardStomp *controller) {
  boost::unique_lock<boost::shared_mutex> lock(KeyboardStream::mutex);
  KeyboardStream::controllers.push_back(controller);
}

KeyboardStomp::KeyboardStomp() : mCur(0), mToggle(0) { 
  KeyboardStream::addController(this); 

  mMapping.push_back("123\tqwaszx");
  mMapping.push_back("45678ertyuidfghjcvbn");
  mMapping.push_back("90-=op[]\\kl;'\nm,./");
}

void KeyboardStomp::process(const sample_t* in, sample_t* out, int num) {
  for (int i = 0; i < num; i++)
    out[i] = mCur;
}

void KeyboardStomp::keyInput(char c) {
  for (int i = 0; i < 3; i++) {
    if (mMapping[i].find(c) != string::npos) 
      mCur = (mToggle && mCur == i) ? kOff : i;
  }
}

xml_node<> &KeyboardStomp::read(xml_node<> &inode) {
  mToggle = inode.first_node("toggle") ? 1 : 0;
  return inode;
}

xml_node<> &KeyboardStomp::write(xml_node<> &onode) const {
  return onode;
}
