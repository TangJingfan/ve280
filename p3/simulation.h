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
void init_world_number_info(world_t& world, const std::string& summary_file,
                            const std::string& world_file);
void check_species_num(int species_count);
void load_species_program(species_t& species,
                          const std::string& program_file_name);
void load_species(world_t& world, const std::string& summary_file);
void init_world_species(world_t& world, const std::string& summary_file);
bool load_creatures(world_t& world, std::ifstream& read_world);
void initialize_grid(grid_t& grid);
bool is_out_of_bounds(const creature_t& creature, const grid_t& grid);
void report_overlap_error(const creature_t& creature,
                          const creature_t& existing_creature);
void report_out_of_bounds_error(const creature_t& creature, const grid_t& grid);
void place_creatures_in_grid(world_t& world);
bool init_world(world_t& world, const std::string& summary_file,
                const std::string& world_file);
void init_world_grid_size(world_t& world, const std::string& world_file);
void init_world_numbers(world_t& world, const std::string& summary_file,
                        const std::string& world_file);
void init_world_species(world_t world, const std::string summary_file);
void init_world_creature(world_t world, const std::string world_file);
bool new_init_world(world_t& world, const std::string& summary_file,
                    const std::string& world_file);
#endif