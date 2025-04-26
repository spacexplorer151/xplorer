#include "spacexplorer.h"
#include <assert.h>
#include <stdio.h>

void test_move_player() {
    printf("=== Testing move_player ===\n");
    Game game;
    initialize_game(&game);
    
    // Test Case 1: Move Up (W)
    game.player.x = 5;
    game.player.y = 5;
    move_player(&game, 'W');
    assert(game.player.y == 4); // Should move up
    assert(game.player.fuel == 99); // Fuel decremented
    printf("Test Case 1 (Move Up): Passed\n");
    
    // Test Case 2: Boundary Collision (Left Edge)
    game.player.x = 0;
    move_player(&game, 'A');
    assert(game.player.x == 0); // Should not move beyond left edge
    printf("Test Case 2 (Boundary): Passed\n");
}

void test_recycle_junk() {
    printf("\n=== Testing recycle_junk ===\n");
    Game game;
    initialize_game(&game);
    
    // Test Case 1: Recycle 3 Junk
    game.player.junk_collected = 3;
    game.player.fuel = 50;
    game.player.score = 0;
    recycle_junk(&game);
    assert(game.player.fuel == 80); // 50 + (3*10)
    assert(game.player.score == 15); // 0 + (3*5)
    assert(game.player.junk_collected == 0); // Reset to 0
    printf("Test Case 1 (Recycle 3 Junk): Passed\n");
    
    // Test Case 2: Recycle with No Junk
    game.player.junk_collected = 0;
    recycle_junk(&game);
    assert(game.player.fuel == 80); // Unchanged
    printf("Test Case 2 (No Junk): Passed\n");
}

void test_asteroid_collision() {
    printf("\n=== Testing asteroid_collision ===\n");
    Game game;
    initialize_game(&game);
    
    // Test Case 1: Player Collides with Asteroid
    game.player.x = game.asteroid.x;
    game.player.y = game.asteroid.y;
    int initial_health = game.player.health;
    move_player(&game, 'W'); // Any move triggers collision check
    assert(game.player.health == initial_health - 20); // Health penalty
    printf("Test Case 1 (Collision): Passed\n");
}

void test_win_condition() {
    printf("\n=== Testing win_condition ===\n");
    Game game;
    initialize_game(&game);
    
    // Test Case 1: Win by collecting junk threshold
    game.player.junk_collected = game.win_threshold;
    int game_over = 0, won = 0;
    check_game_state(&game, &game_over, &won);
    assert(game_over == 1 && won == 1);
    printf("Test Case 1 (Win): Passed\n");
}

void test_alien_encounter() {
    printf("\n=== Testing alien_encounter ===\n");
    Game game;
    initialize_game(&game);
    
    // Test Case 1: Player Collides with Alien
    game.aliens[0].x = game.player.x;
    game.aliens[0].y = game.player.y;
    game.aliens[0].active = 1;
    int initial_health = game.player.health;
    int initial_score = game.player.score;
    handle_alien_encounters(&game);
    assert(game.player.health == initial_health - 10); // Health penalty
    assert(game.player.score == initial_score + 20); // Score boost
    assert(game.aliens[0].active == 0); // Alien deactivated
    printf("Test Case 1 (Alien Encounter): Passed\n");
}

int main() {
    //test_move_player();
    //test_recycle_junk();
    //test_asteroid_collision();
    //test_win_condition();
    test_alien_encounter();
    
    //printf("\nAll tests passed!\n");
    return 0;
}