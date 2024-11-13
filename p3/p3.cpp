#include <simulation.h>
#include <world_type.h>

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
  std::ifstream input_world, input_summary;
  input_world.open(argv[2]);
  input_summary.open(argv[1]);
  input_world.close();
  input_summary.close();
}