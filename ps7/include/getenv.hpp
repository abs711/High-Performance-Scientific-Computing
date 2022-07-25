//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//
#ifndef AMATH583_GETENV_HPP
#define AMATH583_GETENV_HPP

#include <cstdlib>
#include <iostream>
#include <string>

std::string _getenv(const char* in) {
  char* gotten = std::getenv(in);
  if (NULL == gotten) {
    return std::string("");
  } else {
    return std::string(gotten);
  }
}

std::string getenv(const std::string& in) {
  if (NULL == in.c_str()) {
    return std::string("");
  }
  return _getenv(in.c_str());
}

#endif    // !AMATH583_GETENV_HPP