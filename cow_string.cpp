// cow_string.cpp: implementation of copy-on-write strings

#include "cow_string.h"
#include <cstring>

cow_string::cow_string(const char* text) {
  // set up a shareable string for this text; the count will be 1
  underlying_string = new shareable_string(text);
}

cow_string::shareable_string::shareable_string(const char *text) : count(1) {
  int len = strlen(text) + 1;
  contents = new char[len];
  strcpy(contents, text);
  bytes_allocated += len + sizeof(int);
}

cow_string::shareable_string::~shareable_string() {
  int len = strlen(contents) + 1;
  delete [] contents;
  cow_string::bytes_allocated -= (len + sizeof(int));
}

cow_string::~cow_string() {
  // TODO: implement destructor; note the underlying_string is deleted only if
  //       the count drops below 1

}

cow_string::cow_string(const cow_string &src) {
  // TODO: implement the copy constructor. The copy will *share* the
  //       underlying string object, so the count needs to be updated
  //       to reflect that

}

cow_string& cow_string::operator=(const cow_string &src) {
  if ( this != &src ) {
    // TODO: implement the assignment, setting it up so the current
    //       object (this) shares the underlying_string with src.
    //       BUT: don't forget that this already has an underlying_string
    //       that needs to be released, first
    //       Also note the destination's length must be updated.

  }
  return *this;
}

const char& cow_string::operator[](int index) const {
  // in a const context, the string can't change, so no need to copy
  return underlying_string->contents[index];
}

char& cow_string::operator[](int index) {
  // TODO: implement indexing in a non-const context. If the count
  //       for underlying_string is greater than 1, you need to update
  //       that count and then create a *new* underlying string
  //       with the same contents (and with a count of 1)
  if ( underlying_string->count > 1 ) {
  }

  // at this point, we are sure the underlying string is used by just one
  //    object, so we can return a modifyiable reference to that character
  // TODO: add the return statement (see above for hints)

}

const char* cow_string::c_str() const {
  return underlying_string->contents;
}
