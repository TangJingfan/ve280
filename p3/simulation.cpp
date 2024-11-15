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
                        void (*fn)(const std::string& file)) {
  fn(summary_file);
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
  std::ifstream read_file;
  read_file.open(filename);
  int line_number = 0;
  std::string line;
  while (std::getline(read_file, line)) {
    ++line_number;
  }
  read_file.close();
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

std::string species_name_to_string(creature_t& target) {
  return target.species->name.substr(0, 2) + "_" +
         directShortName[target.direction];
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
    std::string name = world.creatures[j].species->name;
    std::string direction = directName[world.creatures[j].direction];
    // check out of bound
    if (row >= static_cast<int>(world.grid.height) ||
        col >= static_cast<int>(world.grid.width) || row < 0 || col < 0) {
      std::cout << "Error: Creature (" << name << " " << direction << " " << row
                << " " << col << ") is out of bound!" << std::endl;
      std::cout << "The grid size is " << world.grid.height << "-by-"
                << world.grid.width << "." << std::endl;
      exit(1);
    }
    // check overlap
    if (world.grid.squares[row][col] != nullptr) {
      std::cout << "Error: Creature (" << name << " " << direction << " " << row
                << " " << col << ") overlaps with creature ("
                << world.grid.squares[row][col]->species->name << " "
                << directName[world.grid.squares[row][col]->direction] << " "
                << row << " " << col << ")!" << std::endl;
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
    creature.programID = 1;
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
  // put creatures into grid
  for (unsigned int num = 0; num < world.numCreatures; num++) {
    world.grid.squares[world.creatures[num].location.r]
                      [world.creatures[num].location.c] = &world.creatures[num];
  }

  return true;
}

bool check_point_inside(int& row, int& col, grid_t& grid) {
  if (row >= 0 && row < static_cast<int>(grid.height) && col >= 0 &&
      col < static_cast<int>(grid.width)) {
    return true;
  }
  return false;
}

void natural_programID_update(creature_t& target) {
  target.programID = (target.programID + 1) % target.species->programSize;
  if (target.programID == 0) {
    target.programID = target.species->programSize;
  }
}

void hop(creature_t& target, grid_t& grid) {
  int direction_deltas[4][2] = {
      {0, 1},   // EAST (right)
      {1, 0},   // SOUTH (down)
      {0, -1},  // WEST (left)
      {-1, 0}   // NORTH (up)
  };
  int direction_index =
      target.direction;  // Assuming direction is an enum or integer 0-3
  // Calculate new row and column based on direction
  int new_r = target.location.r + direction_deltas[direction_index][0];
  int new_c = target.location.c + direction_deltas[direction_index][1];
  // check feasibility
  if (check_point_inside(new_r, new_c, grid) &&
      grid.squares[new_r][new_c] == nullptr) {
    // update location
    grid.squares[new_r][new_c] = &target;
    grid.squares[target.location.r][target.location.c] = nullptr;
    target.location.r = new_r;
    target.location.c = new_c;
  }
  natural_programID_update(target);
}

void left(creature_t& target) {
  switch (target.direction) {
    case EAST:
      target.direction = NORTH;
      break;
    case NORTH:
      target.direction = WEST;
      break;
    case WEST:
      target.direction = SOUTH;
      break;
    case SOUTH:
      target.direction = EAST;
      break;
    default:
      break;
  }
  natural_programID_update(target);
}

void right(creature_t& target) {
  switch (target.direction) {
    case EAST:
      target.direction = SOUTH;
      break;
    case NORTH:
      target.direction = EAST;
      break;
    case WEST:
      target.direction = NORTH;
      break;
    case SOUTH:
      target.direction = WEST;
      break;
    default:
      break;
  }
  natural_programID_update(target);
}

void print_grid(const grid_t& grid) {
  for (unsigned int i = 0; i < grid.height; i++) {
    for (unsigned int j = 0; j < grid.width; j++) {
      if (grid.squares[i][j] == nullptr) {
        std::cout << "____";
      } else {
        std::cout << species_name_to_string(*grid.squares[i][j]);
      }
      std::cout << " ";
    }
    std::cout << std::endl;
  }
}

void infect(creature_t& target, grid_t& grid, species_t list[]) {
  // Define direction deltas for EAST, WEST, NORTH, SOUTH
  int direction_deltas[4][2] = {
      {0, 1},   // EAST (right)
      {1, 0},   // SOUTH (down)
      {0, -1},  // WEST (left)
      {-1, 0}   // NORTH (up)
  };
  int direction_index =
      target.direction;  // Assuming direction is an enum or integer 0-3
  // Calculate new row and column based on direction
  int new_r = target.location.r + direction_deltas[direction_index][0];
  int new_c = target.location.c + direction_deltas[direction_index][1];
  // Ensure the new location is within bounds and not nullptr
  if (check_point_inside(new_r, new_c, grid) &&
      grid.squares[new_r][new_c] != nullptr) {
    grid.squares[new_r][new_c]->species = target.species;
    grid.squares[new_r][new_c]->programID = 1;
  }
  natural_programID_update(target);
}

void ifempty(creature_t& target, grid_t& grid, unsigned int step) {
  int direction_deltas[4][2] = {
      {0, 1},   // EAST (right)
      {1, 0},   // SOUTH (down)
      {0, -1},  // WEST (left)
      {-1, 0}   // NORTH (up)
  };
  int direction_index = target.direction;
  int new_r = target.location.r + direction_deltas[direction_index][0];
  int new_c = target.location.c + direction_deltas[direction_index][1];
  if (check_point_inside(new_r, new_c, grid) &&
      grid.squares[new_r][new_c] == nullptr) {
    target.programID = step;
  } else {
    natural_programID_update(target);
  }
}

void ifwall(creature_t& target, grid_t& grid, unsigned int step) {
  int direction_deltas[4][2] = {
      {0, 1},   // EAST (right)
      {1, 0},   // SOUTH (down)
      {0, -1},  // WEST (left)
      {-1, 0}   // NORTH (up)
  };
  int direction_index = target.direction;
  int new_r = target.location.r + direction_deltas[direction_index][0];
  int new_c = target.location.c + direction_deltas[direction_index][1];
  if (new_r == -1 || new_r == static_cast<int>(grid.height) || new_c == -1 ||
      new_c == static_cast<int>(grid.width)) {
    target.programID = step;
  } else {
    natural_programID_update(target);
  }
}

void ifsame(creature_t& target, grid_t& grid, unsigned int step) {
  int direction_deltas[4][2] = {
      {0, 1},   // EAST (right)
      {1, 0},   // SOUTH (down)
      {0, -1},  // WEST (left)
      {-1, 0}   // NORTH (up)
  };
  int direction_index = target.direction;
  int new_r = target.location.r + direction_deltas[direction_index][0];
  int new_c = target.location.c + direction_deltas[direction_index][1];
  if (check_point_inside(new_r, new_c, grid) &&
      grid.squares[new_r][new_c] != nullptr &&
      grid.squares[new_r][new_c]->species->name == target.species->name) {
    target.programID = step;
  } else {
    natural_programID_update(target);
  }
}

void ifenemy(creature_t& target, grid_t& grid, unsigned int step) {
  int direction_deltas[4][2] = {
      {0, 1},   // EAST (right)
      {1, 0},   // SOUTH (down)
      {0, -1},  // WEST (left)
      {-1, 0}   // NORTH (up)
  };
  int direction_index = target.direction;
  int new_r = target.location.r + direction_deltas[direction_index][0];
  int new_c = target.location.c + direction_deltas[direction_index][1];
  if (check_point_inside(new_r, new_c, grid) &&
      grid.squares[new_r][new_c] != nullptr &&
      grid.squares[new_r][new_c]->species->name != target.species->name) {
    target.programID = step;
  } else {
    natural_programID_update(target);
  }
}

void go(creature_t& target, unsigned int step) { target.programID = step; }

void take_action(creature_t& target, world_t& world) {
  opcode_t action = target.species->program[target.programID - 1].op;
  unsigned int address = target.species->program[target.programID - 1].address;
  std::cout << "Instruction " << target.programID << ": " << opName[action];
  if (address == 0) {
    std::cout << std::endl;
  } else {
    std::cout << " " << address << std::endl;
  }
  switch (action) {
    case HOP:
      hop(target, world.grid);
      break;
    case LEFT:
      left(target);
      break;
    case RIGHT:
      right(target);
      break;
    case INFECT:
      infect(target, world.grid, world.species);
      break;
    case IFEMPTY:
      ifempty(target, world.grid,
              target.species->program[target.programID - 1].address);
      break;
    case IFENEMY:
      ifenemy(target, world.grid,
              target.species->program[target.programID - 1].address);
      break;
    case IFSAME:
      ifsame(target, world.grid,
             target.species->program[target.programID - 1].address);
      break;
    case IFWALL:
      ifwall(target, world.grid,
             target.species->program[target.programID - 1].address);
      break;
    case GO:
      go(target, target.species->program[target.programID - 1].address);
      break;
    default:
      break;
  }
}

void simulate(world_t& world, int rounds) {
  for (int r = 0; r < rounds; r++) {
    std::cout << "Round " << (r + 1) << std::endl;
    for (unsigned int i = 0; i < world.numCreatures; i++) {
      species_t* current_creature_species = world.creatures[i].species;
      opcode_t current_op =
          current_creature_species->program[world.creatures[i].programID - 1]
              .op;
      std::cout << "Creature (" << current_creature_species->name << " "
                << directName[world.creatures[i].direction] << " "
                << world.creatures[i].location.r << " "
                << world.creatures[i].location.c
                << ") takes action:" << std::endl;
      while (current_op != HOP && current_op != LEFT && current_op != RIGHT &&
             current_op != INFECT) {
        take_action(world.creatures[i], world);
        current_creature_species = world.creatures[i].species;
        current_op =
            current_creature_species->program[world.creatures[i].programID - 1]
                .op;
      }
      // Now, execute the final action and stop if it's one of HOP, LEFT, RIGHT,
      // INFECT
      if (current_op == HOP || current_op == LEFT || current_op == RIGHT ||
          current_op == INFECT) {
        take_action(world.creatures[i], world);  // Take the final action
      }
      print_grid(world.grid);
    }
  }
}
