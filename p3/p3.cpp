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
  if (!check_argc(argc)) {
    return 0;
  }
  if (!check_round(atoi(argv[3]))) {
    return 0;
  }
  if (!check_open_world(std::string(argv[2]), check_open_file)) {
    return 0;
  }
  if (!check_open_summary(std::string(argv[1]), check_open_file)) {
    return 0;
  }
  // init world_t
  world_t world;
  if (!init_world(world, argv[1], argv[2])) {
    return 0;
  }
  std::cout << "Initial state" << std::endl;
  print_grid(world.grid);
  bool print_verbose = false;
  if (argc > 4 && argv[4] != nullptr) {
    std::string arg4(argv[4]);
    if (arg4 == "v" || arg4 == "verbose") {
      print_verbose = true;
    }
  }
  simulate(world, atoi(argv[3]), print_verbose);
}