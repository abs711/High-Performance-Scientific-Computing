
#ifndef AMATH583_FACE_DB_HPP
#define AMATH583_FACE_DB_HPP

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <unistd.h>

#include "amath583.hpp"


class face_db : public std::vector<Vector> {

public:
  face_db(const std::string& bin_file, size_t num_images, size_t height, size_t width) : std::vector<Vector>(0,Vector(0)) {

    int fd = open(bin_file.c_str(), O_RDONLY);

    struct stat s;
    fstat(fd, &s);
    size_t mapped_size = s.st_size;

    float *mapped_ptr = (float*)mmap(0, mapped_size, PROT_READ, MAP_FILE | MAP_PRIVATE, fd, 0);
    if ((long)mapped_ptr == -1) {
      perror("ick in face_db");
    }
    
    num_images = std::min(num_images, mapped_size / (sizeof(float)*height*width));
    
    for (size_t k = 0; k < num_images; ++k) {
      Vector img(height * width);
      for (size_t i = 0; i < height * width; ++i) {
	img(i) = mapped_ptr[i];
      }
      this->emplace_back(img);
      mapped_ptr += height*width;
    }

    munmap(mapped_ptr, mapped_size);
    close(fd);
  }


  

};



#endif // AMATH583_FACE_DB_HPP
