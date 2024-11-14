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
opcode_t string_to_opcode(const std::string& command);
bool init_world(world_t& world, const std::string& summary_file,
                const std::string& world_file);
direction_t string_to_direction(const std::string& direction);
int string_to_species(const std::string& species_name, species_t species[],
                      unsigned int species_nums);
#endif