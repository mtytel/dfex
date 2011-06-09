#include "Parallel.h"

using namespace std;

Class Parallel::cls(string("Parallel"), newInstance);

void Parallel::process(const sample_t* in, sample_t* out, int num) {
    mLeft->process(in, out, num);
    mRight->process(in, mOutRight, num);
    
    for (int i = 0; i < num; i++)
        out[i] = (out[i] + mOutRight[i]) * mWet + in[i] * (1 - mWet);
}

istream &Parallel::Read(istream &is) {

    Effect::Read(is);    
    Parallel *root = 0;
    string cont;

    is >> cont;
    mLeft = Effect::readEffect(is);

    is >> cont;
    mRight = Effect::readEffect(is);

    for (is >> cont; cont == CONT; is >> cont) {
        root = new Parallel();
        root->setLeft(mLeft);
        root->setRight(mRight);

        mLeft = root;
        mRight = Effect::readEffect(is);
    }

    return is;
}

ostream &Parallel::Write(ostream &os) const {

    Effect::Write(os);
    os << endl << mLeft;
    os << mRight;
    os << END;

    return os;
}
