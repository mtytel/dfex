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

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <string>
#include <curses.h>
#include <boost/thread.hpp>
#include "Processor.h"

class KeyboardControl;

class KeyboardStream { 
public:
    
    static void stream();
    static void addController(KeyboardControl*);

protected:

    static boost::shared_mutex mutex;
    static std::vector<KeyboardControl*> controllers;

    static void readKey();
};

class KeyboardControl : public Processor {
public:

    KeyboardControl() : mCur(0) { 
        KeyboardStream::addController(this); 
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new KeyboardControl(); }

    void process(const sample_t* in, sample_t* out, int num);
    void keyInput(char c);

protected:

    static Class cls;
    int mCur;

    const std::vector<std::string> mMappings;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
