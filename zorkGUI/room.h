#ifndef ROOM_H_
#define ROOM_H_

#include <map>
#include <string>
#include <vector>
using namespace std;
using std::vector;

class Room {
    friend class ZorkUL;

protected:
    string name;
    string description;
    map<string, Room*> exits;
    string exitString();
    string backgroundPath;
    Room* nextRoom(string direction);


public:
    Room(string name, string description, string backgroundPath);

    virtual ~Room();

    void setExits(Room *north, Room *east, Room *south, Room *west);
    string getName();
    string getShortDescription();
    string getLongDescription();
    string getBackgroundPath();
    string displayItem();
    void removeItemFromRoom(int location);
};

#endif
