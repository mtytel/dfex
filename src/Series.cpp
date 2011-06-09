#include "Series.h"

using namespace std;

Class Series::cls(string("Series"), newInstance);

void Series::process(const sample_t* in, sample_t* out, int num) {
    mFirst->process(in, mBuffer, num);
    mNext->process(mBuffer, out, num);

    for (int i = 0; i < num; i++)
        out[i] = out[i] * mWet + in[i] * (1 - mWet);
}


istream &Series::Read(istream &is) {

    Effect::Read(is);    
    Series *root = 0;
    string cont;

    is >> cont;
    mFirst = Effect::readEffect(is);

    is >> cont;
    mNext = Effect::readEffect(is);

    for (is >> cont; cont == CONT; is >> cont) {
        root = new Series();
        root->setFirst(mFirst);
        root->setNext(mNext);

        mFirst = root;
        mNext = Effect::readEffect(is);
    }

    return is;
}

ostream &Series::Write(ostream &os) const {

    Effect::Write(os);
    os << endl << mFirst;
    os << mNext;
    os << END;

    return os;
}
