#include "spacexplorer.h"

/*
Filename: game.c
Description: This file implements the core game mechanics. It contains functions for initializing the game state, 
             handling player movement, asteroid behavior, collision detection, and updating resources like fuel and health. 
             It also includes logic for determining game win/lose conditions. This is the heart of the gameplay system, 
             handling all logic that governs the in-game experience.
Student: Suaod Alazemi
Date: 30/03/2025
*/

void initialize_game(Game *game) {
    srand(time(NULL));
    setup_difficulty(game);

    game->player.x = game->grid_size / 2;
    game->player.y = game->grid_size / 2;
    game->player.fuel = 100;
    game->player.health = 100;
    game->player.junk_collected = 0;
    game->player.score = 0;
    game->win_threshold = 10;

    place_junk(game);
    place_asteroid(game);
    spawn_aliens(game);
}

void draw_game(Game *game) {
    system("cls"); // Use for Windows

    memset(game->grid, '.', sizeof(game->grid));

    game->grid[game->player.y][game->player.x] = 'P';

    for (int i = 0; i < game->junk_count; i++) {
        if (game->junk[i].active)
            game->grid[game->junk[i].y][game->junk[i].x] = 'J';
    }

    game->grid[game->asteroid.y][game->asteroid.x] = 'X';

    for (int i = 0; i < MAX_ALIENS; i++) {
        if (game->aliens[i].active)
            game->grid[game->aliens[i].y][game->aliens[i].x] = 'A';
    }

    for (int y = 0; y < game->grid_size; y++) {
        for (int x = 0; x < game->grid_size; x++) {
            printf("%c ", game->grid[y][x]);
        }
        printf("\n");
    }
}

void setup_difficulty(Game *game) {
    int choice;
    do {
        printf("Choose difficulty (1=Easy, 2=Medium, 3=Hard): ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 3);

    switch (choice) {
        case 1: game->grid_size = 18; game->difficulty = 1; break;
        case 2: game->grid_size = 24; game->difficulty = 2; break;
        case 3: game->grid_size = 30; game->difficulty = 3; break;
    }

    game->junk_count = MAX_JUNK / game->difficulty;
}

void move_player(Game *game, char input) {
    int dx = 0, dy = 0;

    switch (input) {
        case 'W': dy = -1; break;
        case 'S': dy = 1; break;
        case 'A': dx = -1; break;
        case 'D': dx = 1; break;
    }

    int new_x = game->player.x + dx;
    int new_y = game->player.y + dy;

    if (new_x >= 0 && new_x < game->grid_size && new_y >= 0 && new_y < game->grid_size) {
        game->player.x = new_x;
        game->player.y = new_y;
    }

    game->player.fuel--;
    if (game->player.fuel < 0) {
        game->player.health -= 5;
    }

    for (int i = 0; i < game->junk_count; i++) {
        if (game->junk[i].active &&
            game->junk[i].x == game->player.x &&
            game->junk[i].y == game->player.y) {
            game->junk[i].active = 0;
            game->player.junk_collected++;
            game->player.score += 10;
        }
    }

    if (game->player.x == game->asteroid.x &&
        game->player.y == game->asteroid.y) {
        game->player.health -= 20;
        game->asteroid.x = rand() % game->grid_size;
        game->asteroid.y = rand() % game->grid_size;
    }
}

void move_asteroid(Game *game) {
    game->asteroid.x = rand() % game->grid_size;
    game->asteroid.y = rand() % game->grid_size;
}

void check_game_state(Game *game, int *game_over, int *won) {
    if (game->player.health <= 0 || game->player.fuel <= -50) {
        *game_over = 1;
        *won = 0;
    } else if (game->player.junk_collected >= game->win_threshold) {
        *game_over = 1;
        *won = 1;
    }
}
