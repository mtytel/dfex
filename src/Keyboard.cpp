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
vector<KeyboardControl*> KeyboardStream::controllers;

Class KeyboardControl::cls(string("Keyboard"), newInstance);
/*const string KeyboardControl::mappings[3] = {
 "123\tqwaszx",
 "45678ertyuidfghjcvbn",
 "90-=op[]\\kl;'\nm,./"};
*/

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

void KeyboardStream::addController(KeyboardControl *controller) {

    boost::unique_lock<boost::shared_mutex> lock(KeyboardStream::mutex);
    KeyboardStream::controllers.push_back(controller);
}

void KeyboardControl::process(const sample_t* in, sample_t* out, int num) {
    
    for (int i = 0; i < num; i++)
        out[i] = mCur;
}

void KeyboardControl::keyInput(char c) {

    for (int i = 0; i < 3; i++) {
        if (mMappings[i].find(c) != string::npos)
            mCur = i;
    }
}

xml_node<> &KeyboardControl::read(xml_node<> &inode) {

    return inode;
}

xml_node<> &KeyboardControl::write(xml_node<> &onode) const {

    return onode;
}

