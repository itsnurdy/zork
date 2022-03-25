#include "room.h"
#include "command.h"
#include "ZorkUL.h"

#include <string.h>
#include "dialogues.h"

vector <Item*> itemsInRoom;

/* --------------------------------------- */
/* THIS SECTION COVERS SIMPLE ROOM METHODS */
/* --------------------------------------- */

// Default constructor.
Room::Room(string name, string description, string backgroundPath, roomType type, bool hasHiddenItems) {
    this->name = name;
    this->description = description;
    this->backgroundPath = backgroundPath;
    this->type = type;
    this->hasHiddenItems = hasHiddenItems;
}

// Copy constructor that checks if there are items or clues.
Room::Room(const Room& other) {
    if(hasHiddenItems) {
        return;
    }
    else {
        this->itemsInRoom = other.itemsInRoom;
        this->hiddenClue = other.hiddenClue;
    }
}

// Deletes all the items and clears the list. A destructor.
Room::~Room() {
    for(auto& item : this->getAllItems()) {
        delete item;
    }
    this->getAllItems().clear();
}

// Setting the room exits.
void Room::setExits(Room *north, Room *east, Room *south, Room *west) {
    if (north != NULL)
        exits["north"] = north;
    if (east != NULL)
        exits["east"] = east;
    if (south != NULL)
        exits["south"] = south;
    if (west != NULL)
        exits["west"] = west;
}

// Returning the name of room.
string Room::getName() {
    return name;
}

// Returning short description of room.
string Room::getShortDescription() {
    return description;
}

// Returning long description which includes exits info.
string Room::getLongDescription() {
    return "You are currently in: " + description + "\n" + exitString();
}

// Returning the backgroundpath for a specific room.
string Room::getBackgroundPath() {
    return this->backgroundPath;
}

// Returning the exits information for a specifc room.
string Room::exitString() {
    string returnString = "\nOptions for exiting this current location =";
    for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
        // Loop through map
        returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
    return returnString;
}

// Discovering the next room in the specific direction.
Room* Room::nextRoom(string direction) {
    map<string, Room*>::iterator next = exits.find(direction); // returns an iterator for the "pair"
    if (next == exits.end())
        return NULL; // if exits.end() was returned, there's no room in that direction.
    return next->second; // If there is a room, remove the "second" (Room*)
                // part of the "pair" (<string, Room*>) and return it.
}

// Returns the room type.
Room::roomType Room::getRoomType() {
    return this->type;
}

/* ------------------------- */
/* THIS SECTION COVERS ITEMS */
/* ------------------------- */

// Adding an item to a room.
void Room::addItem(Item *inItem) {
    itemsInRoom.push_back(inItem);
    if(this->hasHiddenItems == false) {
        this->hasHiddenItems = true;
    }
}

// Displaying the items in the room.
string Room::displayItem() {
    string tempString = "Items in room: ";
    int sizeItems = (int) (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        tempString = "There are no items in this room.";
    }
    else if (itemsInRoom.size() > 0) {
        int x = 0;
        for (int n = sizeItems; n > 0; n--) {
            tempString = tempString + itemsInRoom[x]->getShortDescription() + " " ;
            x++;
        }
    }
    return tempString;
}

// Operator for adding items.
void Room::operator+(Item *item) {
    this->addItem(item);
}

// Setting all items to whatever list of items we want.
void Room::setAllItems(vector<Item*> items) {
    this->itemsInRoom = items;
}

// Returns all items.
vector<Item*> Room::getAllItems() {
    return this->itemsInRoom;
}

// Delete all items.
void Room::deleteAllItems() {
    for(auto& item : this->getAllItems()) {
        delete item;
    }
    this->getAllItems().clear();
}

// Delete a specific item by name.
bool Room::deleteItemByName(string name) {
    vector<Item*> items = this->getAllItems();
    for (int i = 0; i < (int) (items.size()); i++) {
        if(items.at(i)->getShortDescription().compare(name) == 0) {
            delete items.at(i);
            items.erase(items.begin() + 1);
            this->setAllItems(items);
            return true;
        }
    }
    return false;
}

// Check if room has items.
bool Room::hasItems() {
    if(itemsInRoom.size() != 0) {
        return true;
    }
    return false;
}

// Returns the position the item is in if its in the room.
int Room::isItemInRoom(string inputString) {
    int sizeItems = (int) (itemsInRoom.size());
    if (itemsInRoom.size() < 1) {
        return -1;
    } else if (itemsInRoom.size() > 0) {
        int x = 0;
        for (int n = sizeItems; n > 0; n--) {
            // Compare inString with short description of item.
            int tempFlag = inputString.compare(itemsInRoom[x]->getShortDescription());
            if (tempFlag == 0) {
                return x;
            }
            x++;
        }
    }
    return -1;
}

/* --------------------------- */
/* THIS SECTION COVERS REWARDS */
/* --------------------------- */

// Default constructors.
RewardRoom::RewardRoom() {}
RewardRoom::~RewardRoom() {}

// Giving a clue to player.
string RewardRoom::giveClueReward(){
    string reward = "";
    if(this->rewardType == CLUE){
        reward = this->rewardedClue;
    }
    return reward;
}

// Giving an item to a player.
Item* RewardRoom::giveItemReward(){
    Item* reward = NULL;
    if(this->rewardType == ITEM){
        reward = this->rewardedItem;
        this->rewardedItem = NULL;
    }
    return reward;
}

/* ------------------------------ */
/* THIS SECTION COVERS WORDLEROOM */
/* ------------------------------ */

// Default constructor with an item as a reward.
WordleRoom::WordleRoom(string name, string description, string backgroundPath,
                       Item* item) : Room(name, description, backgroundPath, WORDLE, false) {
    this->rewardType = ITEM;
    this->RewardRoom::rewardedItem = item;
}

// Default constructor with a clue as a reward.
WordleRoom::WordleRoom(string name, string description, string backgroundPath,
                       string clueReward) : Room(name, description, backgroundPath, WORDLE, false) {
    this->rewardType = CLUE;
    this->RewardRoom::rewardedClue = clueReward;
}
