#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string name;
    std::string description;
    int healthRestore;
    int hungerRestore;
    std::string type;  // Type of item (Weapon, Resource, Food, Tool, etc.)

public:
    // Constructor
    Item(const std::string& name, const std::string& description, int healthRestore = 0, int hungerRestore = 0, const std::string& type = "General");

    // Getter methods
    std::string getName() const;
    std::string getDescription() const;
    int getHealthRestore() const;
    int getHungerRestore() const;
    std::string getType() const;
};

#endif // ITEM_H
