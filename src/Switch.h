/* Switch.h - Splits input into two effects and recombines when both finish
 * Author: Matthew Tytel
 */

#ifndef SWTICH_H
#define SWTICH_H

#include <string>
#include "Effect.h"

#define CONT "-"
#define END "end"
#define NUMEFFECTS 3

class Switch : public Effect {
public:

    static const std::string mappings[NUMEFFECTS];

    Switch() : mCur(0), Effect::Effect() { 
        memset(mEffects, 0, NUMEFFECTS * sizeof(Effect*));
    }
    ~Switch() { }

    const Class *GetClass() const { return &cls; }
    static Object *newInstance() { return new Switch(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setEffect(int id, Effect *e) { mEffects[id] = e; }
    void input(char c);

protected:

    static Class cls;

    Effect *mEffects[NUMEFFECTS];
    int mCur;

    std::istream &Read(std::istream &);
    std::ostream &Write(std::ostream &) const;
};

#endif
