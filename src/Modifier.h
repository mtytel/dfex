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
