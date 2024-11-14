#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "world_type.h"

void check_argc(int argc) {
  if (argc < 4) {
    std::cout << "Error: Missing arguments!" << std::endl;
    std::cout
        << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]"
        << std::endl;
    exit(1);
  }
}

void check_round(int round) {
  if (round < 0) {
    std::cout << "Error: Number of simulation rounds is negative!" << std::endl;
    exit(1);
  }
}

void check_open_file(const std::string& file) {
  std::ifstream world_read;
  world_read.open(file);
  if (!world_read) {
    std::cout << "Error: Cannot open file " << file << std::endl;
    world_read.close();
    exit(1);
  }
  world_read.close();
}

void check_open_world(const std::string& world_file,
                      void (*fn)(const std::string& file)) {
  fn(world_file);
}

void check_open_summary(const std::string& summary_file,
                        void (*check_open_file)(const std::string& file)) {
  check_open_file(summary_file);
}

int read_height_from_line(std::ifstream& file) {
  std::string line_content;
  int value;
  if (getline(file, line_content)) {
    std::istringstream line_stream(line_content);
    line_stream >> value;
  }
  if (value < 1) {
    std::cout << "Error: The grid height is illegal!" << std::endl;
    exit(1);
  }
  return value;
}

int read_width_from_line(std::ifstream& file) {
  std::string line_content;
  int value;
  if (getline(file, line_content)) {
    std::istringstream line_stream(line_content);
    line_stream >> value;
  }
  if (value < 1) {
    std::cout << "Error: The grid width is illegal!" << std::endl;
    exit(1);
  }
  return value;
}

int read_file_lines(const std::string& filename) {
  std::ifstream file(filename);
  int line_number = 0;
  std::string line;
  while (std::getline(file, line)) {
    ++line_number;
  }
  file.close();
  return line_number;
}

int read_file_lines_until_empty(const std::string& filename) {
  std::ifstream read_file;
  read_file.open(filename);
  int line_count = 0;
  std::string line;
  while (std::getline(read_file, line)) {
    if (line.empty()) {
      break;
    }
    ++line_count;
  }
  read_file.close();
  return line_count;
}

void check_program_lines(const std::string& filename,
                         const std::string& species_name) {
  unsigned int lines = read_file_lines_until_empty(filename);
  if (lines > MAXPROGRAM) {
    std::cout << "Error: Too many instructions for species " << species_name
              << "!" << std::endl;
    std::cout << "Maximal number of instructions is " << MAXPROGRAM << "."
              << std::endl;
    exit(1);
  }
}

direction_t string_to_direction(const std::string& direction) {
  for (unsigned int q = 0; q < 4; ++q) {
    if (directName[q] == direction) {
      return static_cast<direction_t>(q);
    } else {
      continue;
    }
  }
  std::cout << "Error: Direction " << direction << " is not recognized!"
            << std::endl;
  exit(1);
}

opcode_t string_to_opcode(const std::string& command) {
  for (unsigned int i = 0; i < sizeof(opName) / sizeof(opName[0]); ++i) {
    if (opName[i] == command) {
      return static_cast<opcode_t>(i);
    }
  }
  std::cout << "Error: Instruction " << command << " is not recognized!"
            << std::endl;
  exit(1);
}

void check_creature_num(unsigned int num) {
  if (num > MAXCREATURES) {
    std::cout << "Error: Too many creatures!" << std::endl;
    std::cout << "Maximal number of creatures is " << MAXCREATURES << "."
              << std::endl;
  }
}
int string_to_species(const std::string& species_name, species_t species[],
                      unsigned int species_nums) {
  for (unsigned int i = 0; i < species_nums; i++) {
    if (species_name == species[i].name) {
      return i;
    }
  }
  std::cout << "Error: Species " << species_name << " not found!" << std::endl;
  exit(1);
}

void check_species_num(unsigned int num) {
  if (num > MAXSPECIES) {
    std::cout << "Error: Too many species!" << std::endl;
    std::cout << "Maximal number of species is " << MAXSPECIES << std::endl;
    exit(1);
  }
}

void check_creatures_legal(world_t world) {
  for (unsigned int j = 0; j < world.numCreatures; j++) {
    int row = world.creatures[j].location.r;
    int col = world.creatures[j].location.c;
    if (row >= (int)world.grid.height || col >= (int)world.grid.width ||
        row < 0 || col < 0) {
      std::cout << "Error: Creature (" << world.creatures[j].species->name
                << " " << directName[world.creatures[j].direction] << " "
                << world.creatures[j].location.r << " "
                << world.creatures[j].location.c << ") is out of bound!"
                << std::endl;
      std::cout << "The grid size is " << world.grid.height << "-by-"
                << world.grid.width << "." << std::endl;
      exit(1);
    }
    if (world.grid.squares[row][col] != nullptr) {
      std::cout << "Error: Creature (" << world.creatures[j].species->name
                << " " << directName[world.creatures[j].direction] << " "
                << world.creatures[j].location.r << " "
                << world.creatures[j].location.c << ") overlaps with creature ("
                << world.grid.squares[row][col]->species->name << " "
                << directName[world.grid.squares[row][col]->direction] << " "
                << world.creatures[j].location.r << " "
                << world.creatures[j].location.c << ")!" << std::endl;
      exit(1);
    }
    world.grid.squares[row][col] = &world.creatures[j];
  }
}

bool init_world(world_t& world, const std::string& summary_file,
                const std::string& world_file) {
  std::ifstream read_world;
  read_world.open(world_file);
  // get height and width of this world
  int height = read_height_from_line(read_world);
  int width = read_width_from_line(read_world);
  world.grid.height = height;
  world.grid.width = width;
  // get number of species and creature respectively
  world.numSpecies = read_file_lines(summary_file) - 1;
  world.numCreatures = read_file_lines(world_file) - 2;
  std::ifstream read_summary;
  read_summary.open(summary_file);
  // get the directory of program
  std::string directory;
  getline(read_summary, directory);
  std::string species_name;
  int species_count = 0;
  // finish target species
  while (getline(read_summary, species_name)) {
    species_t target;
    target.name = species_name;
    // confirm directory
    std::string program_file_name = directory + '/' + species_name;
    check_open_file(program_file_name);
    check_program_lines(program_file_name, species_name);
    // read files
    std::ifstream read_program_file;
    read_program_file.open(program_file_name);
    std::string program_line;
    int program_count = 0;
    // read program; stops when reading blank line
    while (getline(read_program_file, program_line) && !program_line.empty()) {
      std::istringstream program_line_extraction(program_line);
      std::string operation;
      unsigned int op_address = 0;
      program_line_extraction >> operation >> op_address;
      instruction_t program = {string_to_opcode(operation), op_address};
      target.program[program_count] = program;
      program_count++;
    }
    read_program_file.close();
    target.programSize = program_count;
    world.species[species_count] = target;
    species_count++;
    check_species_num(species_count);
  }
  read_summary.close();
  // read creatures from world file
  std::string world_line;
  int creature_count = 0;
  // read each line; stop when a line is blank
  while (getline(read_world, world_line) && !world_line.empty()) {
    std::string name;
    std::string direction;
    int height_location, width_location;
    std::istringstream world_info_extraction(world_line);
    world_info_extraction >> name >> direction >> height_location >>
        width_location;
    creature_t creature;
    creature.programID = 0;
    creature.direction = string_to_direction(direction);
    int species_index =
        string_to_species(name, world.species, world.numSpecies);
    creature.species = &world.species[species_index];
    creature.location = {height_location, width_location};
    world.creatures[creature_count] = creature;
    creature_count++;
    check_creature_num(creature_count);
  }
  // init the grid
  for (unsigned int k = 0; k < world.grid.height; k++) {
    for (unsigned int l = 0; l < world.grid.width; l++) {
      world.grid.squares[k][l] = nullptr;
    }
  }
  check_creatures_legal(world);
  return true;
}