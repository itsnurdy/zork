#ifndef ZORKUL_H
#define ZORKUL_H
#include "parser.h"
#include "mainwindow.h"
#include "room.h"
#include "stack.h"

using namespace std;

class ZorkUL {
private:
    static Room *currentRoom;
    static vector<Room*> allRooms;

    void printWelcome();
    static string printHelp();
    static string printAllItems();
    static bool goRoom(Command command);
    static Parser *parser;
    static Stack<Room*> recentRooms;

    static vector<Item*> itemsInInventory;

public:

    ZorkUL();

    static void updateRoom(Room *room, MainWindow *window);
    static string processCommand(Command command, MainWindow *window);
    static Room *getCurrentRoom();
    static void addItem(Item*);
    static int findItem(const string& item);
    static void deleteItemIndex(int index);
    static void deleteItemName(const string& item);
    static vector<Room*> createRooms();
    static void setAllRooms(vector<Room*> rooms);
    static vector<Room*> getAllRooms();
    static void deleteAll();
    static void setParser(Parser* parser);
    static Parser* getParser();
};


#endif // ZORKUL_H
