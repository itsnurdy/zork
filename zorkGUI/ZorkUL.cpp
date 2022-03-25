#include <iostream>
#include <cstdlib>
#include "mainwindow.h"

#include <QApplication>

#include <QTextStream>
#include <QDebug>
#include "dialogues.h"
#include "constants.h"
#include "errors.h"
#include "stack.h"
#include "item.h"
#include "ZorkUL.h"
#include "wordlegame.h"

using namespace std;
using namespace Constants;

// Initialising vectors and objects.
Parser *ZorkUL::parser;
Room *ZorkUL::currentRoom;
vector<Item*> ZorkUL::itemsInInventory;
vector<Room*> ZorkUL::allRooms;
Stack<Room*> ZorkUL::recentRooms;

int main(int argc, char *argv[]) {
    Parser* parser = new Parser();
    ZorkUL::setParser(parser);

    // For printing stuff in the output pane.
    QTextStream out(stdout);

    WordleGame *wordlegame = new WordleGame();
    QApplication a(argc, argv);
    MainWindow w;
    MainWindow *windowPtr = &w;

    w.show();
    w.clearConsole();

    ZorkUL::setAllRooms(ZorkUL::createRooms());

    ZorkUL::updateRoom(ZorkUL::getCurrentRoom(), windowPtr);
    string roomDescription = ZorkUL::getCurrentRoom()->getShortDescription();
    w.addStringToConsole(Dialogues::printCurrentRoom(roomDescription));

    delete wordlegame;
    delete ZorkUL::getParser();
    return a.exec();
}

// Default constructor.
ZorkUL::ZorkUL() {
    createRooms();
}

// This initialises EVERYTHING.
vector<Room*> ZorkUL::createRooms() {
    using namespace Constants;

    // Creates rooms and makes them with the 'new' keyword.
    Room *mainplace, *alleyway, *bridge, *computerroom, *creepyroom, *flowershop, *lakeview, *trainstation;

    mainplace = new Room("Main", RoomDialogues::mainplace, MAIN, Room::NORMAL, false);
    alleyway = new Room("AlleyWay", RoomDialogues::alleyway, ALLEYWAY, Room::NORMAL, false);
    bridge = new Room("Bridge", RoomDialogues::bridge, BRIDGE, Room::NORMAL, false);
    computerroom = new Room("Computer Room", RoomDialogues::computerroom, COMPUTERROOM, Room::NORMAL, false);
    creepyroom = new Room("Creepy Room", RoomDialogues::creepyroom, CREEPYROOM, Room::NORMAL, false);
    flowershop = new Room("Flowershop", RoomDialogues::flowershop, FLOWERSHOP, Room::NORMAL, false);
    lakeview = new Room("Lake View", RoomDialogues::lakeview, LAKEVIEW, Room::NORMAL, false);
    trainstation = new Room("Trainstation", RoomDialogues::trainstation, TRAINSTATION, Room::NORMAL, false);

    vector<Room*> allRooms;

    // Creating items and making them with the 'new' keyword.
    Item *pen, *copy, *mariohat;
    pen = new Item("Pen", Item::OBJECT);
    copy = new Item("Copy", Item::OBJECT);
    mariohat = new Item("Mario Hat", Item::OBJECT);

    // Adding items to rooms.
    *computerroom + mariohat;
    *trainstation + pen;
    *alleyway + copy;

    // Setting the exists for every room.
    mainplace->setExits(alleyway, computerroom, trainstation, flowershop);

    computerroom->setExits(NULL,NULL, creepyroom, mainplace);
    creepyroom->setExits(computerroom, NULL, NULL, NULL);

    alleyway->setExits(bridge, NULL, mainplace, NULL);
    bridge->setExits(NULL, NULL, alleyway, NULL);

    trainstation->setExits(mainplace,NULL,lakeview,NULL);
    lakeview->setExits(trainstation, NULL, NULL, NULL);

    flowershop->setExits(NULL, mainplace, NULL, NULL);

    // Adding all the rooms onto the vector called allRooms.
    allRooms.push_back(mainplace);
    allRooms.push_back(alleyway);
    allRooms.push_back(bridge);
    allRooms.push_back(computerroom);
    allRooms.push_back(creepyroom);
    allRooms.push_back(flowershop);
    allRooms.push_back(lakeview);
    allRooms.push_back(trainstation);

    // Default room set is mainplace.
    currentRoom = mainplace;

    return allRooms;
}

// Setting all rooms.
void ZorkUL::setAllRooms(vector<Room *> rooms) {
    ZorkUL::allRooms = rooms;
}

// Getting all rooms.
vector<Room*> ZorkUL::getAllRooms() {
    return ZorkUL::allRooms;
}

// Deleting all rooms and items.
void ZorkUL::deleteAll() {
    currentRoom = NULL;

    for(auto& room : ZorkUL::getAllRooms()) {
        delete room;
    }

    for(auto& item : ZorkUL::itemsInInventory) {
        delete item;
    }

    ZorkUL::getAllRooms().clear();
    ZorkUL::itemsInInventory.clear();
}

// Processing a command given by user.
string ZorkUL::processCommand(Command command, MainWindow *window) {
    string output = "";

    string commandWord = command.getCommandWord();

    if (commandWord.compare("info") == 0){
        output += printHelp();
        //return printHelp();
    }
    else if (commandWord.compare("go") == 0){

        try{
            // If the goRoom command is successful, return the room's long description.
            // Otherwise, throw an error message.
            if(goRoom(command)){
                ZorkUL::updateRoom(currentRoom, window);

                output += currentRoom->getLongDescription();
            }
            else{
                throw NoRoomError();
            }
        }
        catch(NoRoomError& errorMessage){
            output += errorMessage.what();
        }
    }
    else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord())
            output += "Overdefined input. If you want to quit, please type 'quit' in the input console or click the 'quit' button.";
        else{
            ZorkUL::deleteAll();
        }

        exit(0); /**signal to quit*/
    }
    else if (commandWord.compare("map") == 0) {
        if (command.hasSecondWord()) {
            output += "Overdefined input. If you want to use map, please type 'map' in the input console.";
        } else {
            output += "If you look to your left you will notice the current map of the game. \n\n"
                      "You are currently in: "
                      + currentRoom->getName() +
                      ". \n"
                      + currentRoom->exitString();
            window->updateBackground(MAP);
        }
    }

    return output;
}

// Getting the current room.
Room *ZorkUL::getCurrentRoom() {
    return ZorkUL::currentRoom;
}

// Outputing all the commands available.
string ZorkUL::printHelp() {
    string output = "";
    output += "Valid inputs are: ";
    output += ZorkUL::parser->commandsInString();
    return output;
}

// Main bit of the go command.
bool ZorkUL::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        return false;
    }

    string direction = command.getSecondWord();

    Room* previousRoom = currentRoom;

    // Going back to the previous room.
    if(direction.compare("back") == 0){
        Room* nextRoom = recentRooms.pop();
        if(nextRoom != NULL){
            currentRoom = nextRoom;
            return true;
        }
        else{
            return false;
        }

    }
    else{
        // Try to leave current room.
        Room* nextRoom = currentRoom->nextRoom(direction);

        if (nextRoom == NULL){
            return false;
        } else {
            currentRoom = nextRoom;
            recentRooms.push(previousRoom);
            return true;
        }
    }
}

// Updates the current room and background.
void ZorkUL::updateRoom(Room *room, MainWindow *window) {
    currentRoom = room;
    window->updateBackground(room->getBackgroundPath());
}

// Finding a specific item index in the itemsInInventory vector.
int ZorkUL::findItem(const string& item) {
    int sizeItems = (int) (ZorkUL::itemsInInventory.size());

    if (ZorkUL::itemsInInventory.size() < 1) {
        return -1;
    }

    else if (ZorkUL::itemsInInventory.size() > 0) {
        int x = 0;
        for (int n = sizeItems; n > 0; n--) {
            int tempFlag = item.compare(ZorkUL::itemsInInventory[x]->getShortDescription());
            if (tempFlag == 0) {
                return x;
            }
            x++;
        }
    }

    return -1;
}

// Parser set and get commands.
void ZorkUL::setParser(Parser *parser){
    ZorkUL::parser = parser;
}

Parser* ZorkUL::getParser(){
    return ZorkUL::parser;
}
