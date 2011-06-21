/* Controller.h - Splits input into two effects and recombines when both finish
 *              For a split into multiple effects, use recursion
 * Author: Matthew Tytel
 */

#include "Controller.h"

using namespace std;

Class Controller::cls(string("Controller"), newInstance);

void Controller::process(const sample_t* in, sample_t* out, int num) {
    mLeft->process(in, out, num);
    mRight->process(in, mOutRight, num);
    
    for (int i = 0; i < num; i++)
        out[i] = (out[i] + mOutRight[i]) * mWet + in[i] * (1 - mWet);
}

istream &Controller::Read(istream &is) {

    Effect::Read(is);    
    Controller *root = 0;
    string cont;

    is >> cont;
    mLeft = Effect::readEffect(is);

    is >> cont;
    mRight = Effect::readEffect(is);

    for (is >> cont; cont == CONT; is >> cont) {
        root = new Controller();
        root->setLeft(mLeft);
        root->setRight(mRight);

        mLeft = root;
        mRight = Effect::readEffect(is);
    }

    return is;
}

ostream &Controller::Write(ostream &os) const {

    Effect::Write(os);
    os << endl << mLeft;
    os << mRight;
    os << END;

    return os;
}
