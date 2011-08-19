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

#include "Parameter.h"

using namespace std;

Class Parameter::cls(string("Parameter"), newInstance);

Parameter *Parameter::checkConstant(string *val) {

    float num = atof(val->c_str());

    if (num || (*val)[0] == '0')
        return new Parameter(num);
    
    return NULL;
}

Parameter *Parameter::readParameter(istream &is) {
    
    Parameter *p;
    string pName;
    is >> pName;

    p = checkConstant(&pName);
    if (p)
        return p;
    
    const Class *pCls = Class::ForName(pName);
    if (!pCls) {
        cerr << "Error reading configuration: No Parameter '" 
         << pName << "'" << endl;
        exit(1);
    }
    p = dynamic_cast<Parameter *>(pCls->NewInstance());
    is >> *p;

    return p;
}

istream &Parameter::read(istream &is) {

    is >> mVal;
    return is;
}

ostream &Parameter::write(ostream &os) const {

    os << mVal << " ";
    return os;
}

