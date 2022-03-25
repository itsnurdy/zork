#ifndef ROOM_H_
#define ROOM_H_

#include <vector>
#include "stack.h"
#include "constants.h"
#include "item.h"
using namespace std;
using namespace Constants;

class RoomProperties {

public:
    virtual bool hasItems() = 0;

    enum roomType : int {NORMAL = 1, WORDLE = 2};
};

class Room : public RoomProperties {
    friend class ZorkUL;

protected:
    string name;
    string description;
    map<string, Room*> exits;
    string exitString();
    string backgroundPath;
    Room* nextRoom(string direction);
    roomType type;
    vector <Item*> itemsInRoom;

public:
    bool hasHiddenItems;

    // A room can either have a hidden item or clue.
    // Placed these in an union to save memory space, only one or the other is used.
    union {
        Item* hiddenItem;
        string hiddenClue;
    };

    Room(string name, string description, string backgroundPath, roomType type, bool hasHiddenItems);
    Room(const Room& other);

    virtual ~Room();

    void operator+(Item* item);

    void setExits(Room *north, Room *east, Room *south, Room *west);
    string getName();
    string getShortDescription();
    string getBackgroundPath();
    string displayItem();
    void removeItemFromRoom(int location);
    int numberOfItems();
    void addItem(Item *inItem);
    void setHiddenItem(Item* item);
    void setHiddenClue(string string);
    vector<Item*> getAllItems();
    void setAllItems(vector<Item*> items);
    void deleteAllItems();
    bool deleteItemByName(string name);
    int isItemInRoom(string inputString);
    roomType getRoomType();

    // Displaying different types of descriptions for different types of rooms.
    virtual string getLongDescription();
    bool hasItems() override;

};

// Room with rewards accordingly.
class RewardRoom {
public:
    enum type : int {ITEM, CLUE, NONE};
protected:
    union {
        Item* rewardedItem;
        string rewardedClue;
        vector<Item*> rewardedMultipleItems;
    };

public:
    Item* giveItemReward();
    string giveClueReward();
    vector<Item*> giveMultipleItems();

    type rewardType;
    RewardRoom();
    virtual ~RewardRoom();
};


class WordleRoom : public RewardRoom, public Room {

public:
    WordleRoom(string description, string backgroundPath, Item* item);
    WordleRoom(string name, string description, string backgroundPath, Item* item);
    WordleRoom(string name, string description, string backgroundPath, string clueReward);

};
#endif
