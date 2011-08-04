#include "Effect.h"

using namespace std;

Class Effect::cls(string("Effect"), newInstance);

Effect* Effect::readEffect(istream &is) {
    
    string clsName;
    is >> clsName;
    
    const Class *eCls = Class::ForName(clsName);
    if (!eCls) {
        cerr << "Error reading configuration: No Effect '" 
         << clsName << "'" << endl;
        exit(1);
    }
    Effect *e = dynamic_cast<Effect *>(eCls->NewInstance());
    is >> *e;

    return e;
}

void Effect::process(const sample_t* in, sample_t* out, int num) {
    memcpy(out, in, num * sizeof(sample_t));
    postProcess(in, out, num);
}

void Effect::postProcess(const sample_t* in, sample_t* out, int num) {
    for (int i = 0; i < num; i++)
        out[i] = out[i] * mWet + in[i] * (1 - mWet);
}

istream &Effect::read(istream &is) {
    
    is >> mWet;
    return is;
}

ostream &Effect::write(ostream &os) const {
    
    os << getClass()->GetName() << ' ' << mWet << ' '; 
    return os;
}
