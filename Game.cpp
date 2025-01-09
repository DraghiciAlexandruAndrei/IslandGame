#include "Game.h"
#include "BattleSystem.h"  // Include BattleSystem for enemy encounters
#include "Enemy.h"

Game::Game() : isRunning(false), dayCounter(0), player("player", 100, 50, 20, 3), manager("locations.txt") {}

Game::~Game() {}

void Game::start() {
    isRunning = true;
    std::cout << "Welcome to island survival!" << "\n";
    char readStoryChoice;
    std::cout << "Do you want to read the background story before starting the game? (y/n): ";
    std::cin >> readStoryChoice;

    if (readStoryChoice == 'y' || readStoryChoice == 'Y') {
        readstory();  // Call the function to read and display the story
    }
    gameLoop();
}

void Game::gameLoop() {
    while (isRunning) {
        std::cout << "\n";
        showMenu();

        int choice;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        processInput(choice);
    }
    std::cout << "Ending Game" << "\n";
}

void Game::showMenu() {
    std::cout << "------MENU------" << "\n";
    std::cout << "Days survived: " << dayCounter << "\n";
    std::cout << "1. Show player status" << "\n";
    std::cout << "2. Explore the island" << "\n";
    std::cout << "3. Visit a discovered location" << "\n";
    std::cout << "4. Use item" << "\n";
    std::cout << "5. Rest" << "\n";
    std::cout << "6. End Game" << "\n";
}

void Game::rest() {
    std::cout << "You take a rest and regain your actions for the day.\n";
    player.restoreActions();
}

void Game::readstory()
{
    std::ifstream storyFile("story.txt");  // Open the story file

    if (storyFile.is_open()) {
        std::string line;
        while (std::getline(storyFile, line)) {
            std::cout << line << std::endl;  // Output each line of the story
        }
        storyFile.close();
    }
    else {
        std::cout << "Could not open the story file.\n";
    }

    std::cout << "Press any key to continue...\n";
    std::cin.ignore();  // Clear the input buffer
    std::cin.get();     // Wait for the user to press a key before continuing
}

void Game::processInput(int choice) {
    switch (choice) {
    case 1:
        player.showStatus();
        break;
    case 2:
        if (player.getActions() > 0) {
            exploreIsland();
        }
        else {
            std::cout << "You have no actions left for today.\n";
        }
        break;
    case 3:
        if (player.getActions() > 0) {
            visitLocation();
        }
        else {
            std::cout << "You have no actions left for today.\n";
        }
        break;
    case 4:
        player.showInventory();  // Show available items
        int itemChoice;
        std::cout << "Choose an item to use (enter the number): ";
        std::cin >> itemChoice;
        player.useItem(itemChoice - 1);  // Use the selected item (adjust index by -1)
        break;
        break;
    case 5:
        rest();
        player.restoreHealth(20);
        player.adjustHunger(-10);
        dayCounter++;
        break;
    case 6:
        std::cout << "Ending Game" << "\n";
        isRunning = false;
        break;
    default:
        std::cout << "Please choose a valid option.\n";
        break;
    }

    if (player.getHealth() <= 0) {
        std::cout << "You have succumbed to your injuries or hunger. Game Over.\n";
        isRunning = false;
    }

    if (dayCounter == 10) {
        std::cout << "You survived long enough for someone to find and save you! Congratulations!\n";
        isRunning = false;
    }
}

void Game::exploreIsland() {
    if (manager.hasMoreLocationsToDiscover()) {
        manager.discoverLocation();
        player.decreaseActions();

        // Randomly determine if the player finds something useful
        if (rand() % 3 == 0) {  // 33% chance to find an item
            int itemType = rand() % 3;
            if (itemType == 0) {
                // Fruit item (restores hunger)
                Item fruit("Mango", "A juicy mango that restores hunger.", 0, 20, "Fruit");
                player.collectItem(fruit);
            }
            else if (itemType == 1) {
                // Medicinal herb (restores health)
                Item herb("Healing Herb", "A herb known for its healing properties.", 20, 0, "Herb");
                player.collectItem(herb);
            }
            else {
                // Other resource
                Item resource("Wood", "A piece of wood, useful for crafting.", 0, 0, "Resource");
                player.collectItem(resource);
            }
        }

        // Randomly determine if an enemy encounter occurs
        if (rand() % 2 == 0) {  // 50% chance of encountering an enemy
            Enemy enemy("Wild Beast", 50, 15);  // Example enemy
            std::cout << "You encounter a " << enemy.getName() << " while exploring!\n";
            handleBattle(enemy);
        }
    }
    else {
        std::cout << "All locations have been discovered already.\n";
    }
}

void Game::visitLocation() {
    std::cout << "Which location would you like to visit?\n";
    manager.displayLocations();  // Display available locations
    int locationName;
    std::cin >> locationName;

    manager.visitLocation(locationName, player);  // Visit the location

    // Randomly determine if the player finds something useful
    if (rand() % 3 == 0) {  // 33% chance to find something useful
        int itemType = rand() % 3;
        if (itemType == 0) {
            // Fruit item (restores hunger)
            Item fruit("Apple", "A delicious apple that restores hunger.", 0, 15, "Fruit");
            player.collectItem(fruit);
        }
        else if (itemType == 1) {
            // Medicinal herb (restores health)
            Item herb("Healing Herb", "A herb known for its healing properties.", 25, 0, "Herb");
            player.collectItem(herb);
        }
        else {
            // Other resource
            Item resource("Stone", "A piece of stone, useful for crafting.", 0, 0, "Resource");
            player.collectItem(resource);
        }
    }

    player.decreaseActions();   
}

void Game::handleBattle(Enemy& enemy) {
    BattleSystem battleSystem(player, enemy);  // Initialize battle system
    battleSystem.startBattle();  // Start the battle

    if (player.getHealth() <= 0) {
        std::cout << "You were defeated by the " << enemy.getName() << ".\n";
        isRunning = false;  // End game if the player loses
    }
}
