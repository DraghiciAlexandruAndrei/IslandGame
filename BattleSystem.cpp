#include "BattleSystem.h"

BattleSystem::BattleSystem(Player& player, Enemy& enemy)
    : player(player), enemy(enemy), battleOver(false) {}

void BattleSystem::startBattle() {
    std::cout << "A wild " << enemy.getName() << " appears!\n";
    std::cout << "Prepare for battle!\n";

    while (!isBattleOver()) {
        displayBattleStatus();
        playerTurn();
        if (isBattleOver()) break;

        enemyTurn();
    }

    endBattle();
}

bool BattleSystem::isBattleOver() const {
    return battleOver || player.getHealth() <= 0 || enemy.getHealth() <= 0;
}

void BattleSystem::playerTurn() {
    std::cout << "\nIt's your turn!\n";
    std::cout << "1. Attack\n";
    std::cout << "2. Defend\n";
    std::cout << "3. Use Item\n";
    std::cout << "4. Flee\n";

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1: {
        int damage = player.getAttackPower();
        if (rand() % 100 < 20) {  // 20% chance for a critical hit
            damage *= 2;
            std::cout << "Critical hit! ";
        }
        enemy.decreaseHealth(damage);
        std::cout << "You attack the " << enemy.getName() << " for " << damage << " damage!\n";
        break;
    }
    case 2:
        std::cout << "You brace yourself for the enemy's attack, reducing damage taken.\n";
        player.defend(enemy.getAttackPower());  // Player defends, reduces incoming damage
        break;
    case 3:
        useItem();  // Implement item usage logic (e.g., healing potion)
        break;
    case 4:
        flee();  // Attempt to flee
        break;
    default:
        std::cout << "Invalid choice. You lose your turn!\n";
        break;
    }
}

void BattleSystem::enemyTurn() {
    if (enemy.getHealth() <= 0) return;

    std::cout << "\nThe " << enemy.getName() << " strikes back!\n";
    int damage = enemy.getAttackPower();
    if (rand() % 100 < 10) {  // 10% chance for enemy to critically hit
        damage *= 2;
        std::cout << "Critical hit! ";
    }
    player.decreaseHealth(damage);
    std::cout << "The " << enemy.getName() << " deals " << damage << " damage to you!\n";
}

void BattleSystem::displayBattleStatus() const {
    std::cout << "\n------ Battle Status ------\n";
    std::cout << "Player: " << player.getHealth() << " HP\n";
    std::cout << "Enemy: " << enemy.getHealth() << " HP\n";
    std::cout << "---------------------------\n";
}

void BattleSystem::endBattle() {
    if (player.getHealth() <= 0) {
        std::cout << "You have been defeated by the " << enemy.getName() << "...\n";
    }
    else if (enemy.getHealth() <= 0) {
        std::cout << "You have defeated the " << enemy.getName() << "!\n";
    }
    else {
        std::cout << "The battle ended prematurely.\n";
    }
}

void BattleSystem::useItem() {
    std::cout << "You use an item to heal or boost your stats!\n";
    // Example item usage:
    // player.restoreHealth(20); // Heal player by 20 HP
}

void BattleSystem::flee() {
    std::cout << "You attempt to flee from the battle...\n";
    if (rand() % 100 < 50) {  // 50% chance to escape
        battleOver = true;
        std::cout << "You successfully escaped the battle!\n";
    }
    else {
        std::cout << "You failed to escape!\n";
    }
}
