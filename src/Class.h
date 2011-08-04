#ifndef CLASS_H
#define CLASS_H

#include <string>
#include <vector>

class Class;

class Object {
public:
    virtual const Class *getClass() const = 0;
};

class Class {
public:
    Class(const std::string &n, Object *(*c)()) : mName(n), mCreate(c) {
        Class *cur = mClsHead;

        if (!cur)
            mClsHead = this;
        else {
            for (; cur->mNext; cur = cur->mNext)
                ;
            cur->mNext = this;
        }
    }
    virtual Object *NewInstance() const;
    std::string GetName() const { return mName; }

    static const Class *ForName(const std::string &name);

protected:
    std::string mName;
    Object *(*mCreate)();
    Class *mNext;

    static Class *mClsHead;  
};

#endif
