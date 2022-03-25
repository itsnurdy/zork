#include "item.h"

Item::Item(string description, float value) {
    this->description = description;
    this->value = value;
}

Item::Item(string description, string usedDialogue, type ItemType) {
    this->description = description;
    this->usedDialogue = usedDialogue;
    this->itemType = ItemType;
}

Item::Item(string description, string usedDialogue) {
    this->description = description;
    this->usedDialogue = usedDialogue;
}

Item::Item(const Item& other) : description(other.description), value(other.value) {
    // Copies the item entirely.
}

void Item::setValue(float value) {
    if (value > 9999 || value < 0)
        return;
    else
       this->value = value;
}

string Item::getUsedDialogue() {
    return this->usedDialogue;
}

Item::type Item::getType() {
    return itemType;
}
