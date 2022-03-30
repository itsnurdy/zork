#ifndef ITEM_H
#define ITEM_H

#include <map>
#include <iostream>
using namespace std;


class ItemType {
public:
    enum type : int {HINT = 1, OBJECT = 2};
};

class Item : public ItemType {
    friend class ZorkUL;
protected:
    string description;
    string longDescription;
    string usedDialogue;
    type itemType;

public:
    Item (string description, type ItemType);
    Item (string description, string usedDialogue, type ItemType);

    Item(const Item& other);

    string getShortDescription();
    string getLongDescription();
    string getUsedDialogue();
    type getType();

};
#endif // ITEM_H
