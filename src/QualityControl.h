/* QualityControl.h - a bit crush effect
 * Author: Matthew Tytel
 */

#ifndef QUALITYCONTROL_H
#define QUALITYCONTROL_H

#include <stdlib.h>
#include <math.h>
#include "Effect.h"

class QualityControl : public Effect {
public:

    QualityControl() : mRatio(2), mPos(0), mCurVal(0), Effect::Effect() { }
    ~QualityControl() { }

    const Class *GetClass() const { return &cls; }
    static Object *newInstance() { return new QualityControl(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setQualityDecline(int ratio) { mRatio = ratio; }

protected:

    static Class cls;

    int mRatio, mPos;
    sample_t mCurVal;

    std::istream &Read(std::istream &);
    std::ostream &Write(std::ostream &) const;
};

#endif
