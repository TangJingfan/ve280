#ifndef SIMULATION_H
#define SIMULATION_H

#include <fstream>
#include <iostream>

#include "world_type.h"

void check_argc(int argc);
void check_round(int round);
void check_open_file(const std::string& file);
void check_open_world(const std::string& world_file,
                      void (*fn)(const std::string& file));
void check_open_summary(const std::string& summary_file,
                        void (*check_open_file)(const std::string& file));
int read_height_from_line(std::ifstream& file);
int read_width_from_line(std::ifstream& file);
int read_file_lines(const std::string& filename);
int read_file_lines_until_empty(const std::string& filename);
void check_program_lines(const std::string& filename,
                         const std::string& species_name);
direction_t string_to_direction(const std::string& direction);
opcode_t string_to_opcode(const std::string& command);
int string_to_species(const std::string& species_name, species_t species[],
                      unsigned int species_nums);
bool init_world(world_t& world, const std::string& summary_file,
                const std::string& world_file);
void check_creatures_legal(world_t world);
void check_species_num(unsigned int num);
void print_grid(const grid_t& grid);
void left(creature_t& target);
void ifempty(creature_t& target, grid_t& grid, unsigned int step);
void infect(creature_t& target, grid_t& grid, species_t list[]);
void right(creature_t& target);
void hop(creature_t& target, grid_t& grid);
void take_action(creature_t& target, world_t& world);
void simulate(world_t& world, int rounds, bool print_verbose);
std::string species_name_to_string(creature_t& target);
#endif