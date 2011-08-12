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

