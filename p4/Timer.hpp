//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH_583_TIMER_HPP
#define AMATH_583_TIMER_HPP

#include <chrono>
#include <iostream>
#include <string>

class Timer {
private:
  typedef std::chrono::time_point<std::chrono::system_clock> time_t;

public:
  Timer() = default;

  time_t start() { return (startTime = std::chrono::system_clock::now()); }
  time_t stop() { return (stopTime = std::chrono::system_clock::now()); }
  double elapsed() { return std::chrono::duration_cast<std::chrono::milliseconds>(stopTime - startTime).count(); }

private:
  time_t startTime, stopTime;
};

class life_timer : public Timer {

public:
  life_timer(const std::string& msg = "") : msg_(msg) { Timer::start(); }
  ~life_timer() {
    Timer::stop();
    if (msg_ != "") {
      std::cout << "# [ " + msg_ + " ]: ";
    }
    std::cout << Timer::elapsed() << " ms" << std::endl;
  }

private:
  std::string msg_;
};

#endif    //  AMATH_583_TIMER_HPP
