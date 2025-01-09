#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include <iostream>
#include <cstdlib>
#include "Player.h"
#include "Enemy.h"

class BattleSystem {
public:
    BattleSystem(Player& player, Enemy& enemy);

    void startBattle();    // Start the battle
    bool isBattleOver() const;   // Check if the battle is over
    void playerTurn();     // Handle the player's turn
    void enemyTurn();      // Handle the enemy's turn
    void displayBattleStatus() const; // Display battle status
    void endBattle();      // End the battle

private:
    void useItem();        // Handle item usage (e.g., herbs)
    void flee();           // Handle flee mechanic
    Player& player;        // Reference to the player object
    Enemy& enemy;          // Reference to the enemy object
    bool battleOver;       // Battle state flag
};

#endif // BATTLE_SYSTEM_H
