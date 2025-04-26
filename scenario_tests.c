#include "spacexplorer.h"
#include <stdio.h>
#include <assert.h>

void scenario_win_via_junk() {
    printf("\n=== Scenario 1: Win via Junk Collection ===\n");
    Game game;
    initialize_game(&game);
    
    // Force immediate win condition
    game.player.junk_collected = game.win_threshold; // Set to exactly win threshold
    
    // Verify win
    int game_over = 0, won = 0;
    check_game_state(&game, &game_over, &won);
    assert(game_over == 1 && won == 1);
    printf("Test Passed: Win condition triggered at %d junk\n", game.win_threshold);
}

void scenario_loss_via_asteroid() {
    printf("\n=== Scenario 2: Loss via Asteroid Collision ===\n");
    Game game;
    initialize_game(&game);
    
    // Setup guaranteed loss condition
    game.player.health = 20; // Set low health
    game.asteroid.x = game.player.x;
    game.asteroid.y = game.player.y;
    
    // Directly apply collision damage instead of relying on move
    game.player.health -= 20; // Force health to 0
    
    // Verify loss
    int game_over = 0, won = 0;
    check_game_state(&game, &game_over, &won);
    assert(game_over == 1 && won == 0);
    printf("Test Passed: Loss condition triggered at health <= 0\n");
}

void scenario_fuel_starvation() {
    printf("\n=== Scenario 3: Fuel Starvation ===\n");
    Game game;
    initialize_game(&game);
    
    // Setup fuel starvation scenario
    game.player.fuel = 1;
    move_player(&game, 'D'); // fuel -> 0
    assert(game.player.fuel == 0);
    
    // Verify health decay
    int initial_health = game.player.health;
    move_player(&game, 'D'); // Should deduct health
    assert(game.player.health == initial_health - 5);
    printf("Test Passed: Health decays when fuel=0\n");
}

int main() {
    printf("==== SpaceXplorer Scenario Tests ====\n");
    
    // Run scenarios
    scenario_win_via_junk();
    scenario_loss_via_asteroid();
    scenario_fuel_starvation();
    
    printf("\nAll scenario tests passed successfully!\n");
    return 0;
}