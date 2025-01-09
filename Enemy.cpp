#include "Enemy.h"
#include <iostream>

// Constructor
Enemy::Enemy(const std::string& name, int health, int attackPower)
    : name(name), health(health), attackPower(attackPower) {}

// Destructor
Enemy::~Enemy() {}

// Getters
std::string Enemy::getName() const {
    return name;
}

int Enemy::getHealth() const {
    return health;
}

int Enemy::getAttackPower() const {
    return attackPower;
}

// Take damage from the player
void Enemy::decreaseHealth(int amount) {
    if (amount < 0) {
        std::cerr << "Invalid damage amount: " << amount << ". Cannot decrease health by a negative value.\n";
        return;
    }

    health -= amount;
    if (health < 0) {
        health = 0;  // Ensure health doesn't go below zero
    }

    std::cout << name << " takes " << amount << " damage. Remaining health: " << health << "\n";
}

// Attack the player
void Enemy::attack(Player& player) const {
    std::cout << name << " attacks " << player.getName() << " for " << attackPower << " damage!\n";
    player.decreaseHealth(attackPower); // Assuming Player has a `takeDamage` method
}

// Display enemy details
void Enemy::display() const {
    std::cout << "Enemy: " << name << "\n"
        << "Health: " << health << "\n"
        << "Attack Power: " << attackPower << "\n";
}

// Check if the enemy is still alive
bool Enemy::isAlive() const {
    return health > 0;
}
