#include "spacexplorer.h"

/*
Filename: features.c
Description: This file introduces extended gameplay features like junk recycling, alien encounters, 
             and alien spawning logic. It adds extra layers of interaction and challenge, 
             making the game more dynamic and strategic. The functions here are modular and work 
             in tandem with core mechanics to enhance overall gameplay variety. It's also responsible for 
             managing special in-game effects when interacting with aliens or environmental events.
Student: Suaod Alazemi
Date:   05/04/2025
*/

void place_junk(Game *game) {
    for (int i = 0; i < game->junk_count; i++) {
        game->junk[i].x = rand() % game->grid_size;
        game->junk[i].y = rand() % game->grid_size;
        game->junk[i].active = 1;
    }
}

void place_asteroid(Game *game) {
    game->asteroid.x = rand() % game->grid_size;
    game->asteroid.y = rand() % game->grid_size;
}

void recycle_junk(Game *game) {
    if (game->player.junk_collected > 0) {
        game->player.fuel += 10 * game->player.junk_collected;
        game->player.score += 5 * game->player.junk_collected;
        printf("Recycled %d junk into fuel and score!\n", game->player.junk_collected);
        game->player.junk_collected = 0;
    } else {
        printf("No junk to recycle!\n");
    }
}

void spawn_aliens(Game *game) {
    for (int i = 0; i < MAX_ALIENS; i++) {
        game->aliens[i].x = rand() % game->grid_size;
        game->aliens[i].y = rand() % game->grid_size;
        game->aliens[i].active = 1;
    }
}

void handle_alien_encounters(Game *game) {
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (game->aliens[i].active &&
            game->aliens[i].x == game->player.x &&
            game->aliens[i].y == game->player.y) {
            game->player.health -= 10;
            game->player.score += 20;
            game->aliens[i].active = 0;
            printf("You encountered an alien! Health -10, Score +20\n");
        }
    }
}
