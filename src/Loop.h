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
#define DEFAULTMODE 0

#define DEFAULTSTOPID 1
#define DEFAULTINDID 2
#define DEFAULTQUANTID 3
#define DEFAULTOVERDUBID 4

class Loop : public Parallel {
public:

    Loop() : Parallel::Parallel(), mMaxLength(1), mRec(0), 
     mStopId(DEFAULTSTOPID), mIndRecId(DEFAULTINDID), 
     mQuantRecId(DEFAULTQUANTID), mOverDubRecId(DEFAULTOVERDUBID) { 
        mLastId = mStopId;
        mSpeed = new Constant(DEFAULTSPEED);
        mMode = new Constant(DEFAULTMODE);
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Loop(); }

    void stopRec();
    void startRec(int mode);
    void startIndependentRec();
    void startQuantizedRec();
    void startOverDubRec();

    void process(const sample_t* in, sample_t* out, int num);

protected:

    class LoopTrack : public Processor {
    public:

        LoopTrack() : mOffset(0), mMemSize(DEFAULTSIZE), mRecLength(0) { }

        virtual void record(const sample_t *in, int size) = 0;
        void process(const sample_t* in, sample_t* out, int num);
        void resize();
        int getRecLength() { return mRecLength; }

    protected:

        int mOffset, mMemSize, mRecLength;
        float mSpeed;

        sample_t *mMemory;
    };


    class IndependentTrack : public LoopTrack {
    public:

        IndependentTrack() : LoopTrack::LoopTrack() {
            mMemory = (sample_t*)calloc(mMemSize, sizeof(sample_t));
        }
        ~IndependentTrack() { free(mMemory); }

        void record(const sample_t* in, int size);
    };


    class QuantizedTrack : public LoopTrack {
    public:

        QuantizedTrack(int quant = 1) : LoopTrack::LoopTrack() {
            mRecLength = mQuant = quant;
            mMemory = (sample_t*)calloc(mMemSize, sizeof(sample_t));
        }
        ~QuantizedTrack() { free(mMemory); }

        void record(const sample_t* in, int size);

    protected:
        
        int mQuant;
    };


    class OverDubTrack : public LoopTrack {
    public:

        OverDubTrack(int length) : LoopTrack::LoopTrack() {
            mMemSize = mRecLength = length;
            mMemory = (sample_t*)calloc(mMemSize, sizeof(sample_t));
        }
        ~OverDubTrack() { free(mMemory); }

        void record(const sample_t* in, int size);
    };

    static Class cls;

    Processor *mSpeed, *mMode;
    uint mMaxLength;
    LoopTrack *mRec;
    int mStopId, mIndRecId, mQuantRecId, mOverDubRecId, mLastId;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif

