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

#ifndef MODIFIER_H
#define MODIFIER_H

#include <stdlib.h>
#include "Effect.h"

class Modifier : public Effect {
public:

    Modifier(float val = 0) { mPar = new Parameter(val); }

    double getVal() { return mPar->getVal(); }
    void setVal(double val) { mPar->setVal(val); }

    void setParameter(Parameter *par) { free(mPar); mPar = par; }
    void setParameter(double val) { free(mPar); mPar = new Parameter(val); }
       
protected:

    Parameter *mPar;

    virtual std::istream &read(std::istream &);
    virtual std::ostream &write(std::ostream &) const;
};

#endif
