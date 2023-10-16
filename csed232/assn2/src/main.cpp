#include <iostream>

#include "option.hpp"

using std::cout;
using std::endl;
using std::make_unique;
using std::unique_ptr;

int main(int argc, char** argv) {
  option<int> a = some<int>(5);
  option<FILE*> b = none<FILE*>();
  option<unique_ptr<char>> c = some<unique_ptr<char>>(make_unique<char>('c'));
  cout << a.unwrap_or(0) 
    << b.opt_or(none<FILE*>()).is_none()
    << **c.as_ref().expect("programmer-defined")
    << endl;
  return 0;
}
