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
  // init world_t
  world_t world;
  init_world(world, argv[1], argv[2]);
  std::cout << "Initial state" << std::endl;
  print_grid(world.grid);
  bool print_verbose = false;
  if ((std::string)argv[5] == "v" || (std::string)argv[5] == "verbose") {
    print_verbose = true;
  }

  simulate(world, atoi(argv[3]));
}