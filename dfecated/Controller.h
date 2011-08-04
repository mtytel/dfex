/* Controller.h - Splits input into two effects and recombines when both finish
 *              For a split into multiple effects, use recursion
 * Author: Matthew Tytel
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Effect.h"

#define CONT "-"
#define END "end"

class Controller : public Effect {
public:

    Controller() : mLeft(0), mRight(0), Effect::Effect() { }
    ~Controller() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Controller(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setLeft(Effect *left) { mLeft = left; }
    void setRight(Effect *right) { mRight = right; }

protected:

    static Class cls;

    Effect *mLeft;
    Effect *mRight;
    sample_t mOutRight[MAXBUFFER];

    std::istream &read(std::istream &);
    std::ostream &write(std::ostream &) const;
};

#endif
