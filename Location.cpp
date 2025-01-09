#include "Location.h"
#include "Enemy.h"      // Include Enemy class
#include "BattleSystem.h"  // Include a battle system or related logic

Location::Location(const std::string& filename) {
    readLocationsFromFile(filename);  // Read locations from the given file
}

Location::~Location() {}

void Location::readLocationsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string name, description;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }

    while (std::getline(file, name) && std::getline(file, description)) {
        locations.push_back({ name, description });
    }

    file.close();
}

void Location::discoverLocation() {
    if (!hasMoreLocationsToDiscover()) {
        std::cout << "All locations have already been discovered.\n";
        return;
    }

    for (auto& loc : locations) {
        if (std::find_if(discoveredLocations.begin(), discoveredLocations.end(),
            [&loc](const auto& discovered) { return discovered.first == loc.first; }) == discoveredLocations.end()) {
            discoveredLocations.push_back(loc);
            std::cout << "New location discovered: " << loc.first << "!\n";
            std::cout << "Description: " << loc.second << "\n";
            return;
        }
    }
}

void Location::visitLocation(int index, Player& player) {
    if (index < 1 || index > discoveredLocations.size()) {
        std::cout << "Invalid location number.\n";
        return;
    }

    // Adjust index for 0-based indexing
    const auto& loc = discoveredLocations[index - 1];
    std::cout << "You are visiting " << loc.first << ": " << loc.second << "\n";

    // Handle interactions at the selected location
    handleInteraction(loc, player);
}

void Location::handleInteraction(const std::pair<std::string, std::string>& location, Player& player) {
    std::cout << "While exploring " << location.first << ", you...\n";
    std::cout << "1. Search for resources\n";
    std::cout << "2. Look for enemies\n";
    std::cout << "3. Rest\n";

    int interactionChoice;
    std::cin >> interactionChoice;

    int randomResource = rand() % 3;

    switch (interactionChoice) {
    case 1:
        std::cout << "You found some useful resources at " << location.first << "!\n";

        // Randomly generate a resource (food, water, or herbs)
        if (randomResource == 0) {
            // Food item
            Item food("Food", "A delicious meal", 20, 30);  // Restores 20 health, 30 hunger
            player.restoreHealth(food.getHealthRestore());
            player.restoreHunger(food.getHungerRestore());
        }
        else if (randomResource == 1) {
            // Water item
            Item water("Water", "Refreshing drink", 0, 20);  // Restores 20 hunger
            player.restoreHunger(water.getHungerRestore());
        }
        else {
            // Herbs item
            Item herbs("Herbs", "A bundle of healing herbs", 10, 10);  // Restores 10 health and hunger
            player.restoreHealth(herbs.getHealthRestore());
            player.restoreHunger(herbs.getHungerRestore());
        }
        break;

    case 2: {
        std::cout << "You encounter an enemy at " << location.first << "!\n";

        // Generate a random enemy for the encounter (or any logic to choose enemies)
        Enemy enemy("Wild Boar", 50, 10);  // Example enemy with name, health, and attack power
        BattleSystem battleSystem(player, enemy);

        // Start the battle and process the result
        battleSystem.startBattle();
        if (player.getHealth() > 0) {
            std::cout << "You defeated the enemy!\n";
        }
        else {
            std::cout << "You were defeated by the enemy...\n";
        }
        break;
    }

    case 3:
        std::cout << "You take a moment to rest and recover.\n";
        player.restoreHealth(10);  // Example logic to restore player health
        break;

    default:
        std::cout << "You decide to do nothing and move on.\n";
        break;
    }
}

bool Location::isDiscovered(const std::string& name) const {
    for (const auto& loc : discoveredLocations) {
        if (loc.first == name) {
            return true;
        }
    }
    return false;
}

bool Location::hasMoreLocationsToDiscover() const {
    return discoveredLocations.size() < locations.size();
}

void Location::displayLocations() const {
    std::cout << "Discovered locations:\n";
    for (size_t i = 0; i < discoveredLocations.size(); ++i) {
        std::cout << i + 1 << ". " << discoveredLocations[i].first << ": " << discoveredLocations[i].second << "\n";
    }
}

std::vector<std::pair<std::string, std::string>> Location::getDiscoveredLocations() const {
    return discoveredLocations;
}
