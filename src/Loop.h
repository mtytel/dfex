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
#include <map>

#include "Parallel.h"
#include "Constant.h"

#define DEFAULTSIZE 480000
#define DEFAULTSILENT 0
#define DEFAULTREVERSE 9

class Loop : public Parallel {
public:
    Loop(); 

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Loop(); }

    void process(const sample_t* in, sample_t* out, int num);
    void controlResponse(char val);

    int anyPlaying();
    int getMaxLength();
    void silenceAll();
    void playAll();

protected:

    class LoopTrack : public Processor {
    public:
        enum { kRecording, kPlaying, kSilence };

        LoopTrack(int quant = 1) : mMemSize(DEFAULTSIZE), mRecLength(0), 
         mOffset(0), mState(kRecording), mQuant(quant) { 

            mMemory = (sample_t*)calloc(mMemSize, sizeof(sample_t));
        }

        void process(const sample_t* in, sample_t* out, int num);
        void toggle();
        void silence() { mState = kSilence; }
        void play() { mState = kPlaying; }

        int isPlaying() { return mState == kPlaying; }
        int getRecLength() { return mRecLength; }

    protected:
    
        void record(const sample_t *in, int num);
        void stopRecording();
        void play(sample_t *out, int num);
        void resize();

        int mMemSize, mRecLength, mOffset, mState, mQuant;
        sample_t *mMemory;
    };

    static Class cls;

    Processor *mControl;
    int mSilent, mReverse;
    std::map<int, LoopTrack*> mTrackMap;
    char mLastVal;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif

