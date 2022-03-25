#include "room.h"
#include "command.h"
#include "ZorkUL.h"

#include <string.h>
#include "dialogues.h"

Room::Room(string name, string description, string backgroundPath) {
    this->name = name;
    this->description = description;
    this->backgroundPath = backgroundPath;
}

Room::~Room() {

}

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

string Room::getShortDescription() {
    return description;
}

string Room::getLongDescription() {
    return "You are currently in: " + description + "\n" + exitString();
}

string Room::getBackgroundPath() {
    return this->backgroundPath;
}

string Room::exitString() {
    string returnString = "\nOptions for exiting this current location =";
    for (map<string, Room*>::iterator i = exits.begin(); i != exits.end(); i++)
        // Loop through map
        returnString += "  " + i->first;	// access the "first" element of the pair (direction as a string)
    return returnString;
}

Room* Room::nextRoom(string direction) {
    map<string, Room*>::iterator next = exits.find(direction); // returns an iterator for the "pair"
    if (next == exits.end())
        return NULL; // if exits.end() was returned, there's no room in that direction.
    return next->second; // If there is a room, remove the "second" (Room*)
                // part of the "pair" (<string, Room*>) and return it.
}
