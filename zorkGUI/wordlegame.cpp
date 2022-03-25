#include <iostream>
#include <fstream>
#include <QTextStream>
#include <QFile>
#include <unordered_map>
#include <cctype>
#include "mainwindow.h"
#include "dialogues.h"
#include "wordlegame.h"

using namespace std;

vector<string> wordlegame::allWords;
int wordlegame::triesRemaining;
wordlegame::status wordlegame::wordleStatus = wordlegame::STOP;
string wordlegame::targetWord;

// Basic comparison between two characters.
bool wordlegame::isEqualIgnoreCase(char& first, char& second) {
    return tolower(first) == tolower(second);
}

// Reading the file and initialising out allWords list.
void wordlegame::initWords(string fileName) {
    if(fileName.empty()) {
        string text;

        QFile file(":/text/text/wordle_words.txt");
        QTextStream in(&file);
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            while(!in.atEnd()) {
                wordlegame::allWords.push_back(in.readLine().toStdString());
            }
        }
        file.close();
    }
}

// Sets the status and initialises the wordle game.
void wordlegame::initWordleGame() {
    initWords("");
    wordlegame::wordleStatus = wordlegame::PROGRESS;
}

// This evaluates the user's input accordingly.
string wordlegame::evaluateInput(const string& input) {
    string output = "";
    unordered_map<char,int> letter_counts;
    string correctWord = wordlegame::targetWord;
    int correctLettersAmount = 0;

    // Checking if word given is the same size as the correct word.
    if(input.size() != correctWord.size()) {
        return "";
    }

    // Initialising the letter_counts map, pairing each letter with 1
    for(int i = 0; i < (int) correctWord.size(); i++) {
        char currentChar = tolower(correctWord.at(i));
        // If the letter does not exist yet, add it and pair it with the int 1
        // Otherwise, just add 1 to that entry.
        if(letter_counts.count(currentChar)){
            letter_counts[currentChar] += 1;
        }
        else{
            letter_counts.insert({currentChar, 1});
        }
    }

    for (int i = 0; i < (int) input.size(); i++) {
        char currentInputLetter = input.at(i);

        // If character is at correct index.
        if(wordlegame::isEqualIgnoreCase(currentInputLetter, correctWord.at(i))) {
            letter_counts[currentInputLetter] -= 1;
            output.push_back('[');
            output.push_back(currentInputLetter);
            output.push_back(']');
            correctLettersAmount++;
        }

        else if(letter_counts[currentInputLetter] > 0) {
            letter_counts[currentInputLetter] -= 1;
            output.push_back('{');
            output.push_back(currentInputLetter);
            output.push_back('}');
        }

        else {
            output.push_back(currentInputLetter);
        }
    }

    output = output + " DEV: " + correctWord + '\n';

    // If guess is correct status is set to success.
    if (correctLettersAmount == (int) correctWord.size()) {
        output += Dialogues::wordleSuccess;
        wordlegame::wordleStatus = wordlegame::SUCCESS;
    } else {
        // If not it will deduct a try and then stop if the user has no more tries left.
        wordlegame::triesRemaining--;

        if(wordlegame::triesRemaining <= 0) {
            output += Dialogues::wordleOutOfAttempts;
            wordlegame::wordleStatus = wordlegame::STOP;
        } else {
            output += Dialogues::printAttemptsLeft(wordlegame::triesRemaining);
        }
    }
    return output;
}

// Returns all words.
vector<string> wordlegame::getAllWords() {
    return wordlegame::allWords;
}

// Resets the wordle game.
void wordlegame::resetWordleGame() {
    wordlegame::triesRemaining = 5;
    wordlegame::targetWord = allWords.at(rand() % allWords.size());
}

// Returns wordle status.
wordlegame::status wordlegame::getWordleStatus() {
    return wordlegame::wordleStatus;
}
