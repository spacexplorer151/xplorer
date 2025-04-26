#include "spacexplorer.h"
#include <assert.h>
#include <stdio.h>

void test_movement_and_alien_collision() {
    printf("=== Testing Movement + Alien Collision Integration ===\n");
    Game game;
    initialize_game(&game);
    
    // Setup: Force player and alien to overlap
    game.aliens[0].x = game.player.x;
    game.aliens[0].y = game.player.y;
    game.aliens[0].active = 1;
    int initial_health = game.player.health;
    int initial_score = game.player.score;

    // Step 1: Move player (triggers collision check)
    move_player(&game, 'W');
    
    // Verify outcomes
    assert(game.player.health == initial_health - 10);  // Health penalty
    assert(game.player.score == initial_score + 20);    // Score boost
    assert(game.aliens[0].active == 0);                // Alien deactivated
    
    printf("Test Passed: Movement + Alien Collision\n");
}

void test_recycling_and_fuel_system() {
    printf("\n=== Testing Junk Recycling + Fuel Integration ===\n");
    Game game;
    initialize_game(&game);
    
    // Step 1: Simulate collecting 3 junk
    game.player.junk_collected = 3;
    game.player.fuel = 50;
    recycle_junk(&game);
    
    // Step 2: Move player 5 times
    for (int i = 0; i < 5; i++) {
        move_player(&game, 'D');
    }
    
    // Verify outcomes
    assert(game.player.fuel == 75);       // 80 (recycled) - 5 (moves)
    assert(game.player.health == 100);    // No health decay (fuel > 0)
    
    printf("Test Passed: Recycling + Fuel System\n");
}

void test_win_priority_over_collision() {
    printf("\n=== Testing Win Condition vs Asteroid Collision ===\n");
    Game game;
    initialize_game(&game);
    
    // Step 1: Force win condition
    game.player.junk_collected = game.win_threshold;
    
    // Step 2: Force asteroid collision
    game.asteroid.x = game.player.x;
    game.asteroid.y = game.player.y;
    
    // Step 3: Check game state
    int game_over = 0, won = 0;
    check_game_state(&game, &game_over, &won);
    
    // Verify win takes priority
    assert(game_over == 1 && won == 1);  
    printf("Test Passed: Win Condition Priority\n");
}

int main() {
    test_recycling_and_fuel_system();
    test_win_priority_over_collision();
    
    printf("\nAll integration tests passed!\n");
    return 0;
}