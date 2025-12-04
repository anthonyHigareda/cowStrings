// generic_string.h: base class for the strings

#ifndef _generic_string_h
#define _generic_string_h

class generic_string {
public:
  // constructor arguments: length of string, #bytes allocated for object
  generic_string(int len) : _length(len) { }
  virtual ~generic_string();

  // access/update operations
  // returns constant reference to a character in the string
  virtual const char& operator[](int index) const = 0;
  // returns a non-constant reference to a character in the string
  virtual char& operator[](int index) = 0;
  // returns the number of characters in the string
  int length() const { return _length; }
  // returns a pointer to the string contents as a null-terminated array of characters
  //   the string cannot be changed through this pointer and the pointer must not be
  //   saved in any structure
  virtual const char* c_str() const = 0;

protected:
  int _length;                  // number of characters in the string
  static int bytes_allocated;   // how many bytes allocated at any one time; must be 0 at end
public:
  static int unreleased_bytes() { return bytes_allocated; }
};

#endif
