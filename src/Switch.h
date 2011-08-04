#ifndef SWITCH_H
#define SWITCH_H

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

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Switch(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setEffect(int id, Effect *e) { mEffects[id] = e; }
    void keyInput(char c);

protected:

    static Class cls;

    Effect *mEffects[NUMEFFECTS];
    int mCur;

    std::istream &read(std::istream &);
    std::ostream &write(std::ostream &) const;
};

#endif
