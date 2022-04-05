// I mainly ported this file from the main zork project that was given but I do understand them and how it functions.

#ifndef COMMANDWORDS_H
#define COMMANDWORDS_H

#include <string>
#include <vector>
using namespace std;

class CommandWords {
private:
    // Define a static vector for our valid command words.
    // We'll populate this in the class constructor.
    static vector<string> validCommands;

public:
    CommandWords();
    string validCommandsToString();
};

#endif // COMMANDWORDS_H
