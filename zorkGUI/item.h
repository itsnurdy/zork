#ifndef ITEM_H
#define ITEM_H

#include <map>
#include <iostream>
using namespace std;


class ItemType {
public:
    enum type : int {HINT = 1, HEALTH = 2, MONEY = 4};
};

class Item : public ItemType {
    friend class ZorkUL;
protected:
    string description;
    string longDescription;

    float value;
    bool sellable;

    string usedDialogue;

    type itemType;

    string (*useFunc)(Item*);

public:
    Item (string description, float value);
    Item (string description, string usedDialogue, type ItemType);
    Item (string description, string usedDialogue);
    Item (string description);

    Item(const Item& other);

    string getShortDescription;
    string getLongDescription;
    float getValue;
    void setValue(float value);
    string getUsedDialogue();
    type getType();

};

class ConsumableItem : public Item {
public:
    void consumeItem();
};

#endif // ITEM_H
