#include "spacexplorer.h"
/*
Filename: utils.c
Description: This utility file contains helper functions for displaying game status, reading user input, 
             and saving scores. Functions such as display_status(), show_health(), clear_input_buffer(), 
             and display_end_message() improve user experience by presenting information clearly. 
             These routines are separated from game logic to maintain clean code structure and separation of concerns.
Student: Suaod Alazemi
Date: 09/04/2025
*/
void display_status(Game *game) {
    printf("Fuel: %d | Health: %d | Junk: %d | Score: %d\n",
           game->player.fuel, game->player.health,
           game->player.junk_collected, game->player.score);
}

void show_health(Game *game) {
    printf("Health Check: %d\n", game->player.health);
}

void save_score(Game *game, char *name) {
    FILE *file = fopen("scores.txt", "a");
    if (file) {
        fprintf(file, "%s %d\n", name, game->player.score);
        fclose(file);
    } else {
        printf("Failed to save score.\n");
    }
}

void read_intro() {
    FILE *file = fopen("intro.txt", "r");
    if (file) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
        printf("\n\n");
    } else {
        // Fallback message
        printf("Welcome to SpaceXplorer!\nCollect junk, dodge asteroids, and manage your resources!\n\n");
    }
}

void display_end_message(Game *game, int won) {
    if (won) {
        printf("Congratulations! You won with a score of %d!\n", game->player.score);
    } else {
        printf("Game Over. Better luck next time.\n");
    }
}
