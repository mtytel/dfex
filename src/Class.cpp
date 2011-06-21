/* Class.cpp - reflection implemented for configuration files
 * Author: Matthew Tytel
 */

#include "Class.h"

Class *Class::mClsHead;

const Class *Class::ForName(const std::string &name) {
    Class *cur;

    for (cur = mClsHead; cur && cur->mName != name; cur = cur->mNext)
        ;

    return cur;
}

Object *Class::NewInstance() const {
    return mCreate();
}

