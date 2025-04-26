#include "spacexplorer.h"
/*
Filename: main.c
Description: The entry point of the program. It handles the main game loop, user input, 
             and function calls that drive game progression. It continuously processes input, 
             updates the game state, redraws the grid, and checks for game over or win conditions. 
             This file orchestrates the overall flow of the game, tying all components together into a playable experience.
Student: Suaod Alazemi
Date: 13/04/2025
*/
/*
int main() {
    Game game;
    int game_over = 0, won = 0;
    char input;
    char name[MAX_NAME];

    read_intro();
    printf("Enter your name: ");
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "\n")] = 0;

    initialize_game(&game);

    while (!game_over) {
        draw_game(&game);
        display_status(&game);

        printf("Move (WASD), Check Health (H), Recycle (R), Quit (Q): ");
        scanf(" %c", &input);
        input = toupper(input);

        if (input == 'Q') break;

        switch (input) {
            case 'W':
            case 'A':
            case 'S':
            case 'D':
                move_player(&game, input);
                move_asteroid(&game);
                handle_alien_encounters(&game);
                break;
            case 'H':
                show_health(&game);
                break;
            case 'R':
                recycle_junk(&game);
                break;
            default:
                printf("Invalid input!\n");
        }

        check_game_state(&game, &game_over, &won);
    }

    display_end_message(&game, won);
    save_score(&game, name);

    return 0;
}
*/