/* Template.h - template for new effects
 * Author: Matthew Tytel
 */

#include "Template.h"

using namespace std;

Class Template::cls(string("Template"), newInstance);

//This is your effect implementation
void Template::process(const sample_t* in, sample_t* out, int num) {

    memcpy(out, in, num * sizeof(sample_t));
    //Replace above line with effect implementation
}

istream &Template::Read(istream &is) {

    Effect::Read(is);
    //Insert data reading unique to your effect
    //is >> someMemberData;
    
    return is;
}

ostream &Template::Write(ostream &os) const {

    Effect::Write(os);
    //Insert data writing unique to your effect
    //os << someMemberData << endl;

    return os;
}
