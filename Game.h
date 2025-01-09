#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Player.h"
#include "Location.h"   // Include the Location class
#include "BattleSystem.h"  // Include the BattleSystem class
#include "Enemy.h"  // Include the Enemy class

class Game {
public:
    // Constructor and Destructor
    Game();
    ~Game();

    // Main game functions
    void start();  // Start the game
    void gameLoop();  // The main game loop
    void showMenu();  // Show the game menu
    void processInput(int choice);  // Process the player's input
    void rest();  // Rest to regain actions

    void readstory();
private:
    // Game state variables
    bool isRunning;  // If the game is running
    int dayCounter;  // Number of days survived
    Player player;  // Player object
    Location manager;  // Location manager for location handling

    // Game actions
    void exploreIsland();  // Explore the island and possibly encounter enemies
    void visitLocation();  // Visit a discovered location
    void handleBattle(Enemy& enemy);  // Handle an enemy encounter

};
