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

class KeyboardStomp;

class KeyboardStream {
  public:
    static void stream();
    static void addController(KeyboardStomp*);

  protected:
    static boost::shared_mutex mutex;
    static std::vector<KeyboardStomp*> controllers;

    static void readKey();
};

class KeyboardStomp : public Processor {
  public:
    enum { kOff = -1 };

    KeyboardStomp();
    virtual ~KeyboardStomp() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new KeyboardStomp(); }

    void process(const sample_t* in, sample_t* out, int num);
    void keyInput(char c);

  protected:
    static Class cls;
    int mCur, mToggle;

    std::vector<std::string> mMapping;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
