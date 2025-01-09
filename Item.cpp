#include "Item.h"

Item::Item(const std::string& name, const std::string& description, int healthRestore, int hungerRestore, const std::string& type)
    : name(name), description(description), healthRestore(healthRestore), hungerRestore(hungerRestore), type(type) {}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

int Item::getHealthRestore() const {
    return healthRestore;
}

int Item::getHungerRestore() const {
    return hungerRestore;
}

std::string Item::getType() const {
    return type;
}
