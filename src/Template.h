/* Template.h - template for new effects
 * Author: Matthew Tytel
 */

#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "Effect.h"

class Template : public Effect {
public:

    Template() : mPossible(2), Effect::Effect() { }
    ~Template() { }

    const Class *GetClass() const { return &cls; }
    static Object *newInstance() { return new Template(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    int mPossible;

    std::istream &Read(std::istream &);
    std::ostream &Write(std::ostream &) const;
};

#endif
