#pragma once
#include <string>
#include "Player.h" // Include the player header for interactions

class Enemy {
private:
    std::string name;
    int health;
    int attackPower;

public:
    Enemy(const std::string& name, int health, int attackPower);
    ~Enemy();

    // Getters
    std::string getName() const;
    int getHealth() const;
    int getAttackPower() const;

    // Enemy actions
    void decreaseHealth(int damage);
    void attack(Player& player) const;

    // Display enemy details
    void display() const;

    // Check if the enemy is alive
    bool isAlive() const;
};
