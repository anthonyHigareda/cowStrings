// generic_string.cpp: implementation of copy-on-write strings

#include "generic_string.h"

int generic_string::bytes_allocated = 0;

generic_string::~generic_string() { }
