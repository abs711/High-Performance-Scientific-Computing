//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2021
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <array>
#include <cstddef>
#include <iomanip>
#include <string>
#include <vector>

#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;

#include "Timer.hpp"

#include "AOS_Image.hpp"
#include "SOA_Image.hpp"
#include "Tensor_Image.hpp"

#include "blur.hpp"

int main(int argc, char* argv[]) {

  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " image" << std::endl;
    return -1;
  }

  std::string  in_image = argv[1];
  CImg<double> img(in_image.c_str());

  SOA_Image    soa_img    = to_soa(img);
  AOS_Image    aos_img    = to_aos(img);
  Tensor_Image tensor_img = to_tensor(img);

  std::cout << std::setw(12) << "SOA inner" ;
  std::cout << std::setw(12) << "SOA outer" ;
  std::cout << std::setw(12) << "AOS inner" ;
  std::cout << std::setw(12) << "AOS outer" ;
  std::cout << std::setw(12) << "Ten inner" ;
  std::cout << std::setw(12) << "Ten outer" ;
  std::cout << std::endl;

  SOA_Image blurred_0 = blur_0(soa_img);
  SOA_Image blurred_1 = blur_1(soa_img);
  AOS_Image blurred_2 = blur_2(aos_img);
  AOS_Image blurred_3 = blur_3(aos_img);
  Tensor_Image blurred_4 = blur_4(tensor_img);
  Tensor_Image blurred_5 = blur_5(tensor_img);
  std::cout << std::endl;

  CImg<double> out_0 = from_soa(blurred_0);
  CImg<double> out_1 = from_soa(blurred_1);
  CImg<double> out_2 = from_aos(blurred_2);
  CImg<double> out_3 = from_aos(blurred_3);
  CImg<double> out_4 = from_tensor(blurred_4);
  CImg<double> out_5 = from_tensor(blurred_5);

  out_0.save(("blurred_0_" + in_image).c_str());
  out_1.save(("blurred_1_" + in_image).c_str());
  out_2.save(("blurred_2_" + in_image).c_str());
  out_3.save(("blurred_3_" + in_image).c_str());
  out_4.save(("blurred_4_" + in_image).c_str());
  out_5.save(("blurred_5_" + in_image).c_str());

  return 0;
}
