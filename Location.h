#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include "Player.h"  // Include Player class
#include "Enemy.h"   // Include Enemy class (used for encounters)
#include "BattleSystem.h"  // Include BattleSystem class for handling combat

class Location {
public:
    // Constructor and Destructor
    Location(const std::string& filename);
    ~Location();

    // Core Methods
    void discoverLocation();  // Discover a new location
    void visitLocation(int index, Player& player);  // Visit a discovered location

    // Utility Methods
    bool isDiscovered(const std::string& name) const;  // Check if a location is discovered
    void displayLocations() const;  // Display all locations
    bool hasMoreLocationsToDiscover() const;  // Check if there are more locations to discover
    std::vector<std::pair<std::string, std::string>> getDiscoveredLocations() const;  // Get discovered locations

private:
    // Internal Methods
    void readLocationsFromFile(const std::string& filename);  // Read locations from a file
    void handleInteraction(const std::pair<std::string, std::string>& location, Player& player);  // Handle interactions at a location

    // Member Variables
    std::vector<std::pair<std::string, std::string>> locations;  // All locations (name and description)
    std::vector<std::pair<std::string, std::string>> discoveredLocations;  // Locations that have been discovered
};
