//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#define NDEBUG

#include <cassert>
#include <cstddef>
#include <iostream>
using namespace std;

int main() {
  assert(1 == 0 && "This is never true");    // will be triggered
  cout << "Hello World" << endl;
  return 0;
}
