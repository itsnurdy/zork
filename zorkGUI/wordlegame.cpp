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

vector<string> WordleGame::allWords;
int WordleGame::triesRemaining;
WordleGame::status WordleGame::wordleStatus = WordleGame::STOP;
string WordleGame::targetWord;

// Basic comparison between two characters.
bool WordleGame::isEqualIgnoreCase(char& first, char& second) {
    return tolower(first) == tolower(second);
}

// Reading the file and initialising out allWords list.
void WordleGame::initWords(string fileName) {
    if(fileName.empty()) {
        string text;

        QFile file(":/text/text/wordle_words.txt");
        QTextStream in(&file);
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            while(!in.atEnd()) {
                WordleGame::allWords.push_back(in.readLine().toStdString());
            }
        }
        file.close();
    }
}

// Sets the status and initialises the wordle game.
void WordleGame::initWordleGame() {
    initWords("");
    WordleGame::wordleStatus = WordleGame::PROGRESS;
}

// This evaluates the user's input accordingly.
string WordleGame::evaluateInput(const string& input) {
    string output = "[] -> correct letter and position\n"
            "{} -> correct letter, wrong position\n\n";
    unordered_map<char,int> letter_counts;
    string wordGiven = input;
    string correctWord = WordleGame::targetWord;
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
        if(WordleGame::isEqualIgnoreCase(currentInputLetter, correctWord.at(i))) {
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

// Development purposes.
//    output = output + " correct: " + correctWord + '\n';

    // If guess is correct status is set to success.
    if (correctLettersAmount == (int) correctWord.size()) {
        output = Dialogues::wordleSuccess;
        WordleGame::wordleStatus = WordleGame::SUCCESS;
    } else {
        // If not it will deduct a try and then stop if the user has no more tries left.
        WordleGame::triesRemaining--;

        if(WordleGame::triesRemaining <= 0) {
            output += Dialogues::wordleOutOfAttempts;
            WordleGame::wordleStatus = WordleGame::STOP;
        } else {
            output += Dialogues::printAttemptsLeft(WordleGame::triesRemaining);
        }
    }
    return output;
}

// Returns all words.
vector<string> WordleGame::getAllWords() {
    return WordleGame::allWords;
}

// Resets the wordle game.
void WordleGame::resetWordleGame() {
    WordleGame::triesRemaining = 5;
    WordleGame::targetWord = allWords.at(rand() % allWords.size());
}

// Returns wordle status.
WordleGame::status WordleGame::getWordleStatus() {
    return WordleGame::wordleStatus;
}
