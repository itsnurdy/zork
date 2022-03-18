#ifndef DIALOGUES_H
#define DIALOGUES_H

#include <string>
using std::string;

// Struct is containing dialogues and some printing functions.
struct Dialogues{
    static string printCurrentRoom(string& description);
    static string printAttemptsLeft(int& attemptsLeft);

    const static string welcome;
    const static string noMoreRooms;
    const static string inputError;
    const static string welcomeWordle;
    const static string wordleIncorrectInput;
    const static string wordleSuccess;
    const static string wordleOutOfAttempts;
}

#endif // DIALOGUES_H
