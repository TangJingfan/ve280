#ifndef SIMULATION_H
#define SIMULATION_H

#include <fstream>
#include <iostream>

#include "world_type.h"

bool check_argc(int argc);
bool check_round(int round);
bool check_open_world(const std::string& world_file,
                      bool (*fn)(const std::string& file));
bool check_open_summary(const std::string& summary_file,
                        bool (*fn)(const std::string& file));
bool check_open_file(const std::string& file);
bool init_world(world_t& world, const std::string& summary_file,
                const std::string& world_file);
void print_grid(const grid_t& grid);
void simulate(world_t& world, int rounds, bool print_verbose);
#endif