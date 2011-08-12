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

#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <stdlib.h>
#include "Class.h"

class Parameter : public Object {
public:

    Parameter(float val = 0) : mVal(val) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Parameter(); }
    static Parameter *checkConstant(std::string *val); 
    static Parameter *readParameter(std::istream &is);

    virtual float getVal() { return mVal; }
    virtual float setVal(float val) { mVal = val; }

    friend std::ostream &operator<<(std::ostream &os, const Parameter &b)
     {return b.write(os);}
    friend std::istream &operator>>(std::istream &is, Parameter &b)
     {return b.read(is);}

protected:

    static Class cls;

    double mVal;

    virtual std::istream &read(std::istream &);
    virtual std::ostream &write(std::ostream &) const;
};

#endif
