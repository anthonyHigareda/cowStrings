// main driver for testing shareable_string class

// Simulate running the code on an input for a large-string editor
//   insert at line, update to line, print type operations
//   update: line number, column, change N chars to new text
//   i 3: insert text after line 3
//   u 12 24 5 new text: replace 5 chars starting at col 24 of line 12 with new text
//   d 15: delete line 15
//   p: print document
// Goal: support an editor

#include "cow_string.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cassert>

using namespace std;

void check_expected(const cow_string &s, int position, char target) {
  if ( s[position] != target )
    cout << "Unexpected character " << s[position] << " at position "
         << position << endl;
}

void run_checks() {
  {
    cow_string a("first"), b("second"), c("third"), d("fourth"), e("fifth");

    assert(a[0] == 'f');
    a[0] = 'F';
    e = d = c = b;
    c[1] = '3';
    c[3] = '0';
    check_expected(d, 0, 's');

    // make e use a separate buffer from the others
    char save = e[4];
    e[4] = 'x';
    e[4] = save;

    assert(strcmp(a.c_str(), "First") == 0);
    assert(a.length() == 5);
    assert(strcmp(b.c_str(), "second") == 0);
    assert(b.length() == 6);
    assert(strcmp(c.c_str(), "s3c0nd") == 0);
    assert(strcmp(d.c_str(), "second") == 0);
    assert(strcmp(e.c_str(), "second") == 0);
    assert(b.c_str() == d.c_str()); // underlying strings are the same
    assert(b.c_str() != e.c_str()); // these are distinct
    assert(b.length() == 6);
    assert(generic_string::unreleased_bytes() == 43);
  }

  assert(generic_string::unreleased_bytes() == 0);
}

void construct_text() {
  cow_string buffer[1000];
  int number_of_lines = 0;

  string cmd_line;
  getline(cin, cmd_line);
  while ( cin ) {
    stringstream line_reader(cmd_line);
    char cmd;
    int n;
    line_reader >> cmd >> n;
    assert(n >= 0);
    line_reader.ignore(1);      // skip any whitespace
    if ( cmd == 'a' ) { // append text n times
      string rest_of_line;
      getline(line_reader, rest_of_line);
      cow_string tmp(rest_of_line.c_str());
      cout << "> Adding " << n << " copies of " << tmp.c_str() << endl;
      for(int i = 0; i < n; ++i) {
        buffer[number_of_lines] = tmp;
        number_of_lines++;
      }
    } else if ( cmd == 'e' ) { // edit line number n
      int index;
      char new_value;
      line_reader >> index >> new_value;
      cout << "> Editing line " << n << " at " << index << " to "
           << new_value << endl;
      assert(n < number_of_lines);
      buffer[n][index] = new_value;
    } else if ( cmd == 'r' ) { // replace line n with new value
      string rest_of_line;
      getline(line_reader, rest_of_line);
      cow_string tmp(rest_of_line.c_str());
      cout << "> Replacing line " << n << " with " << tmp.c_str() << endl;
      buffer[n] = tmp;
    } else if ( cmd == 'd' ) { // delete line n
      cout << "> Deleting line " << n << endl;
      for(int i = n; i < number_of_lines - 1; i++)
        buffer[i] = buffer[i + 1];
    } else if ( cmd == 'p' ) { // print lines from n to end
      for(int i = n; i < number_of_lines; i++)
        cout << setw(3) << i << ". (" << setw(2) << buffer[i].length() << ") "
             << buffer[i].c_str() << endl;
    }
    getline(cin, cmd_line);
  }
  cout << "After constructing buffer, bytes allocated == "
       << generic_string::unreleased_bytes() << endl;
}

int main(int argc, char **args) {
  run_checks();

  if ( argc == 1 ) {
    construct_text();
    cout << "----------------------------------------" << endl;
    if ( cow_string::unreleased_bytes() == 0 )
      cout << "At end, all allocated data released." << endl;
    else
      cout << "ERROR: there are " << cow_string::unreleased_bytes()
           << " bytes that did not get released." << endl;
  }

  return 0;
}
