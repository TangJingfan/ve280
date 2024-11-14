#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "simulation.h"
#include "world_type.h"

int main(int argc, char* argv[]) {
  // check whether input is legal and well-prepared
  check_argc(argc);
  check_round(atoi(argv[3]));
  check_open_world(std::string(argv[2]), check_open_file);
  check_open_summary(std::string(argv[1]), check_open_file);
  world_t world;
}