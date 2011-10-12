/* 
 * Copyright 2011 Matthew Tytel
 *
 * dfex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dfex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dfex.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LOOP_H
#define LOOP_H

#include <stdlib.h>
#include <math.h>

#include "Parallel.h"
#include "Constant.h"

#define DEFAULTSIZE 480000
#define DEFAULTSPEED 1
#define DEFAULTMODE 1

#define DEFAULTSTOPID 1
#define DEFAULTINDID 2
#define DEFAULTQUANTID 4
#define DEFAULTOVERDUBID 3

class Loop : public Parallel {
public:

    Loop(); 

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Loop(); }

    void stopRec();
    void process(const sample_t* in, sample_t* out, int num);

protected:

    class LoopTrack : public Processor {
    public:

        LoopTrack() : mOffset(0), mMemSize(DEFAULTSIZE), mRecLength(0) { 
            mMemory = (sample_t*)calloc(mMemSize, sizeof(sample_t));
        }

        void independentRecord(const sample_t *in, int size);
        void quantizedRecord(const sample_t *in, int size, int quant);
        void overDubRecord(const sample_t *in, int size, int length);

        void process(const sample_t* in, sample_t* out, int num);
        void resize();
        void stop() { mSpeed = 0; }

        int isEmpty() { return mRecLength == 0; }
        int getRecLength() { return mRecLength; }

    protected:

        int mOffset, mMemSize, mRecLength;
        float mSpeed;

        sample_t *mMemory;
    };

    static Class cls;

    Processor *mSpeed, *mMode;
    uint mMaxLength;
    LoopTrack *mRec;
    int mStopId, mIndRecId, mQuantRecId, mOverDubRecId;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif

