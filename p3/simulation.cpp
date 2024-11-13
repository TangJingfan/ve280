#include <fstream>
#include <iostream>

void error_print(int argc, char* argv[], std::ifstream input_world,
                 std::ifstream input_summary) {
  // condition: too few arguments
  if (argc < 4) {
    std::cout << "Error: Missing arguments!" << std::endl;
    std::cout
        << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"
        << std::endl;
  }
  // condition: negative round input
  if (atoi(argv[3]) < 0) {
    std::cout << "Error: Number of simulation rounds is negative!" << std::endl;
  }
  // condition: failure of reading world file
  if (!input_world) {
    std::cout << "Error: Cannot open file " << argv[2] << " !" << std::endl;
  }
  // condiiton: failure of reading species summary
  if (!input_summary) {
    std::cout << "Error: Cannot open file " << argv[1] << " !" << std::endl;
  }
}