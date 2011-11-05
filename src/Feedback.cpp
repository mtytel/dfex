/* 
 * Copyright 2011 Noura Howell
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

#include "Feedback.h"

using namespace rapidxml;

Class Feedback::cls(std::string("Feedback"), newInstance);


void Feedback::process(const sample_t* in, sample_t* out, int num) {

//    cout << endl << " Feedback::process " << endl;
    int i;

    sample_t delays[num];
    sample_t decays[num];
    const sample_t *memory;
    sample_t temp[num];
    
    mDelay->process(in, delays, num);

//    cout << endl << " mDelay->process " << endl;

    mCurDelay = round(delays[num - 1]);

    mDecay->process(in, decays, num);

//    cout << endl << " mDecay->process " << endl;

    // pull up feedback from memory
    memory = mMemory->getPastSamples(num);

//    cout << endl << " getPastSamples(num) " << endl;

    // add feedback to input
    for (i = 0; i < num; i++)
        temp[i] = in[i] + memory[i]*decays[i];

//    cout << endl << " added feedback to input " << endl;

    // run through inner process and send to output
    mProcess->process(temp, out, num);

//    cout << endl << " mProcess->process " << endl;

    // save output to memory for use as future feedback
    mMemory->storeSamples(out, num);

//    cout << endl << " storeSamples " << endl;
}


xml_node<> &Feedback::read(xml_node<> &inode) {

    free(mDelay);
    mDelay = Processor::tryReadProcessor(inode, "delay", DEFAULTDELAY); 
    
    free(mDecay);
    mDecay = Processor::tryReadProcessor(inode, "decay", DEFAULTDECAY);

    free(mProcess);
    mProcess = Processor::tryReadProcessor(inode, "process", DEFAULTPROCESS);

    return inode;
}

xml_node<> &Feedback::write(xml_node<> &onode) const {

    return onode;
}
