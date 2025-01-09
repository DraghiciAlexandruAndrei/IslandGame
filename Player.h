#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Item.h"
class Player {
public:
    // Constructor and Destructor
    Player(const std::string& playerName, int initialHealth, int initialHunger, int initialAttackPower, int initialActions);
    ~Player();

    // Core Methods
    void showStatus() const;  // Display player status
    void decreaseHealth(int damage);  // Decrease health when damage is taken
    void restoreHealth(int amount);  // Restore health up to max health
    void restoreHunger(int amount);  //Restore hunger up to max hunger
    void adjustHunger(int amount);  // Adjust hunger and affect health accordingly
    void decreaseActions();  // Decrease available actions for the day
    void restoreActions();  // Restore actions for the next day
    void defend(int damage);// Guard in battle take less damage
    // Utility Methods
    bool isAlive() const;  // Check if the player is still alive
    int getHealth() const;  // Get the current health of the player
    int getHunger() const;  // Get the current hunger level
    int getActions() const;  // Get the number of actions left
    std::string getName() const;  // Get the player's name
    int getAttackPower() const;  // Get the player's attack power

    // Inventory Methods
    void collectItem(const Item& item);  // Add item to inventory
    void useItem(int itemIndex);  // Use item from inventory by name
    void showInventory() const; // Show inventory

private:
    std::string name;  // Player's name
    int health;  // Current health
    int hunger;  // Current hunger level
    int attackPower;  // Player's attack power
    int actionsPerDay;  // Actions left for the day 
    const int maxHealth;  // Maximum health
    const int maxActionsPerDay = 3;  // Max actions per day
    std::vector<Item> inventory;
    const int maxHunger = 100; //Maximum hunger
    Item* equippedWeapon;
};