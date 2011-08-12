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

#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>

class Class;

class Object {
public:
    virtual const Class *getClass() const = 0;
};

class Class {
public:
    Class(const std::string &n, Object *(*c)()) : mName(n), mCreate(c) {
        Class *cur = mClsHead;

        if (!cur)
            mClsHead = this;
        else {
            for (; cur->mNext; cur = cur->mNext)
                ;
            cur->mNext = this;
        }
    }
    virtual Object *NewInstance() const;
    std::string GetName() const { return mName; }

    static const Class *ForName(const std::string &name);

protected:
    std::string mName;
    Object *(*mCreate)();
    Class *mNext;

    static Class *mClsHead;  
};

#endif
