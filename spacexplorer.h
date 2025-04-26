// spacexplorer.h

/*
Filename: spacexplorer.h
Description: This header file contains all necessary structure definitions and function 
             declarations used across the project. It defines the Game, Player, Junk, Asteroid, 
             and Alien data structures, along with constants for grid size, limits, and symbols. 
             It also includes function prototypes for core game logic, utility functions, and 
             additional features like alien encounters and recycling. 
Student: Suaod Alazemi
Date: 25/03/2025
*/

#ifndef SPACEXPLORER_H
#define SPACEXPLORER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MIN_GRID 18
#define MAX_GRID 30
#define MAX_JUNK 50
#define MAX_NAME 50
#define MAX_ALIENS 5

// Player data
typedef struct {
    int x, y;
    int fuel;
    int health;
    int junk_collected;
    int score;
} Player;

// Asteroid structure
typedef struct {
    int x, y;
    int dx, dy;
} Asteroid;

// Junk structure
typedef struct {
    int x, y;
    int active;
} Junk;

// Alien structure
typedef struct {
    int x, y;
    int active;
} Alien;

// Game data
typedef struct {
    int grid_size;
    int difficulty;
    char grid[MAX_GRID][MAX_GRID];
    Player player;
    Asteroid asteroid;
    Junk junk[MAX_JUNK];
    int junk_count;
    Alien aliens[MAX_ALIENS];
    int win_threshold;
} Game;

// Core functions
void initialize_game(Game *game);
void setup_difficulty(Game *game);
void draw_game(Game *game);
void move_player(Game *game, char input);
void move_asteroid(Game *game);
int check_collision(Game *game);
void update_resources(Game *game);
void check_game_state(Game *game, int *game_over, int *won);
void clear_input_buffer();

// Utility
void display_status(Game *game);
void show_health(Game *game);
void save_score(Game *game, char *name);
void read_intro();
void display_end_message(Game *game, int won);

// Features
void place_junk(Game *game);
void place_asteroid(Game *game);
void recycle_junk(Game *game);
void handle_alien_encounters(Game *game);
void spawn_aliens(Game *game);

// New fixes
void clamp_fuel(Game *game);
void handle_fuel_starvation(Game *game);
void reposition_asteroid_after_collision(Game *game);

#endif // SPACEXPLORER_H
