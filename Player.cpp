#include "Player.h"

Player::Player(const std::string& playerName, int initialHealth, int initialHunger, int initialAttackPower, int initialActions)
    : name(playerName), health(initialHealth), hunger(initialHunger), attackPower(initialAttackPower), actionsPerDay(initialActions), maxHealth(initialHealth) {}

Player::~Player() {}

void Player::showStatus() const {
    std::cout << "====================" << "\n";
    std::cout << "Player status: \n";
    std::cout << "Name: " << getName() << "\n";
    if (getHealth() > 0) {
        std::cout << "Health: " << getHealth() << "/" << maxHealth << "\n";
        std::cout << "Hunger: " << hunger << "\n";
        std::cout << "Energy: " << actionsPerDay << "\n";
        std::cout << "====================" << "\n";
    }
    else {
        std::cout << "Player is dead.\n";
    }
}

void Player::adjustHunger(int amount) {
    hunger += amount;
    if (hunger < 0) {
        hunger = 0;
    }
    else if (hunger > 100) hunger = 100;

    // Effects on health if hunger is too high or too low (you can adjust thresholds here)
    if (hunger >= 80) {
        decreaseHealth(5); // Hunger decreases health when it's too high
    }
    else if (hunger <= 20) {
        decreaseHealth(3); // Hunger decreases health when it's too low
    }
}
void Player::defend(int damage) {
    // Reduce damage by a fixed amount or percentage
    int reducedDamage = static_cast<int>(damage * 0.5);  // 50% damage reduction
    decreaseHealth(reducedDamage);  // Apply reduced damage to player
}

void Player::decreaseHealth(int damage) {
    health -= damage;
    if (health < 0) health = 0;
    std::cout << name << " took " << damage << " damage! Health: " << health << "/" << maxHealth << "\n";
}

void Player::decreaseActions() {
    if (actionsPerDay > 0) {
        --actionsPerDay;
        std::cout << "Actions left: " << actionsPerDay << "\n";
    }
    else {
        std::cout << "No actions remaining!\n";
    }
}

bool Player::isAlive() const {
    return health > 0;
}

void Player::restoreHealth(int amount) {
    if (amount <= 0) {
        std::cout << "Invalid amount to restore.\n";
        return;
    }

    health += amount;
    if (health > maxHealth) {
        health = maxHealth;  // Cap the health at maxHealth
    }

    std::cout << name << " restores " << amount << " health points.\n";
    std::cout << "Current health: " << health << "/" << maxHealth << "\n";
}

void Player::restoreHunger(int amount)
{
    hunger += amount;
    if (hunger > maxHunger) hunger = maxHunger; // Cap hunger to maxHunger
    std::cout << "Hunger restored by " << amount << ". Current hunger: " << hunger << "\n";
}

int Player::getHealth() const {
    return health;
}

std::string Player::getName() const {
    return name;
}

int Player::getAttackPower() const {
    return attackPower;
}

void Player::collectItem(const Item& item) {
    inventory.push_back(item);
    std::cout << "You added a " << item.getName() << " to your inventory.\n";
}
void Player::useItem(int itemIndex) {
    if (itemIndex < 0 || itemIndex >= inventory.size()) {
        std::cout << "Invalid item index.\n";
        return;
    }

    Item item = inventory[itemIndex];
    std::cout << "Using item: " << item.getName() << "\n";

    // Restore health and hunger based on item type
    if (item.getHealthRestore() > 0) {
        restoreHealth(item.getHealthRestore());
    }
    if (item.getHungerRestore() > 0) {
        adjustHunger(item.getHungerRestore());
    }

    // Remove the used item from the inventory
    inventory.erase(inventory.begin() + itemIndex);
}
void Player::showInventory() const
{
    if (inventory.empty()) {
        std::cout << "You have no items in your inventory.\n";
    }
    else {
        std::cout << "Your inventory:\n";
        for (size_t i = 0; i < inventory.size(); ++i) {
            std::cout << i + 1 << ". " << inventory[i].getName() << ": " << inventory[i].getDescription() << "\n";
        }
    }
}

int Player::getHunger() const {
    return hunger;
}

int Player::getActions() const {
    return actionsPerDay;
}

void Player::restoreActions() {
    actionsPerDay = maxActionsPerDay;  // Restore the max actions for the next day
    std::cout << "Actions restored. You have " << actionsPerDay << " actions for today.\n";
}

