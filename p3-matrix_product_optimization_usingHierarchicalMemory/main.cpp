//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//

#include <iostream>
#include <string>

int main(int argc, char* argv[])  {

  int size = std::stol(argv[argc-1]);

  std::cout << "size is " << size << std::endl;

  return  0;
}
