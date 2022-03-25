#ifndef WORDLEGAME_H
#define WORDLEGAME_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class WordleGame {

public:
    enum status {STOP, PROGRESS, FAIL, SUCCESS};

private:
    static vector<string> allWords;
    static int triesRemaining;
    static void initWords(string filename);
    static string targetWord;
    static status wordleStatus;

public:
    static string evaluateInput(const string& input);
    static vector<string> getAllWords();
    static void resetWordleGame();
    static string checkGameStatus();
    static void initWordleGame();
    static status getWordleStatus();

    static bool isEqualIgnoreCase(char& first, char& second);
};

#endif // WORDLEGAME_H
