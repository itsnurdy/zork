#include "item.h"

// Default constructor.
Item::Item(string description, type ItemType) {
    this->description = description;
    this->itemType = ItemType;
}

// Default constructor with type.
Item::Item(string description, string usedDialogue, type ItemType) {
    this->description = description;
    this->usedDialogue = usedDialogue;
    this->itemType = ItemType;
}

// Copy constructor.
Item::Item(const Item& other) : description(other.description) {
    // Copies the item entirely.
}

// Returning dialogue.
string Item::getUsedDialogue() {
    return this->usedDialogue;
}

// Returning item type.
Item::type Item::getType() {
    return itemType;
}

// Returning short description.
string Item::getShortDescription() {
    return this->description;
}

// Returning long description.
string Item::getLongDescription() {
    return this->longDescription;
}
