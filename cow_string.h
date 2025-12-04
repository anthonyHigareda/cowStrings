// cow_string.h: copy-on-write strings

#ifndef _cow_string_h
#define _cow_string_h

#include "generic_string.h"

class cow_string : public generic_string {
public:
  cow_string(const char* text = "");

  // memory management
  virtual ~cow_string();
  cow_string(const cow_string &src);
  cow_string& operator=(const cow_string &src);

  // access operations
  char& operator[](int index) override;
  const char& operator[](int index) const override;
  const char* c_str() const override;

private:
  struct shareable_string {
    int count = 0;
    char *contents = nullptr;
    shareable_string(const char *text);
    ~shareable_string();
  } *underlying_string = nullptr;
};

#endif
