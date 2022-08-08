//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include <iostream>
#include <string>
#include <mpi.h>

int main(int argc, char* argv[]) {
  MPI::Init();

  int token     = 0;
  size_t rounds = 1;
  if (argc >= 2) rounds = std::stol(argv[1]);

  int myrank = MPI::COMM_WORLD.Get_rank();
  int mysize = MPI::COMM_WORLD.Get_size();

  // Fix me
  int left  = myrank+1;
  int right = myrank-1;
  if (0 == myrank) {
    left  = 1;
    right = 3;
  } else if (3 == myrank)
  {
    left = 0;
    right = 2;	
  }  

  // 0 -> 1 -> 2 -> 3 -> 0
  while (rounds--) {

    if (0 == myrank) {
      std::cout << myrank << ": sending  " << token << std::endl;

      MPI::COMM_WORLD.Send(&token, 1, MPI::INT, left, 321);         // myrank -> myrank + 1
      MPI::COMM_WORLD.Recv(&token, 1, MPI::INT, right, 321);

      std::cout << myrank << ": received " << token << std::endl;
      ++token;
    } else {
      MPI::COMM_WORLD.Recv(&token, 1, MPI::INT, right, 321);        // 
      std::cout << myrank << ": received " << token << std::endl;
      ++token;
      std::cout << myrank << ": sending  " << token << std::endl;   
      MPI::COMM_WORLD.Send(&token, 1, MPI::INT, left, 321);          // myrank -> myrank + 1       (2 -> 3)
    }
  }

  MPI::Finalize();

  return 0;
}
