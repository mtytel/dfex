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

#include "Class.h"

using namespace std;

Class *Class::mClsHead;

Class::Class(const string &n, Object *(*c)()) : mName(n), mCreate(c) {
  Class *cur = mClsHead;

  if (!cur)
    mClsHead = this;
  else {
    for (; cur->mNext; cur = cur->mNext)
      ;
    cur->mNext = this;
  }
}

const Class *Class::ForName(const string &name) {
  Class *cur = 0;

  for (cur = mClsHead; cur && cur->mName != name; cur = cur->mNext)
    ;

  return cur;
}

Object *Class::NewInstance() const {
  return mCreate();
}
