#include "dialogues.h"

const string Dialogues::welcome = "This is Wordleville, a harsh world"
                                  " where your status and prestige is determined by your Wordle skills."
                                  " Your father throws you off the train. \"If you can't"
                                  " earn at least $1000 tonight, don't even think about coming back to me.\""
                                  " You set off on your way...\n"
                                  "If you seek assistance, enter the 'info' command.\n";
const string Dialogues::inputError = "Invalid command, please try again.\n";
const string Dialogues::noMoreRooms = "No more areas this way. Try another direction.\n";
const string Dialogues::welcomeWordle = "It's a Wordle challenge! Input your attempt right now!\n";
const string Dialogues::wordleIncorrectInput = "Please input a 5 letter word.\n";
const string Dialogues::wordleSuccess = "Congratulations! You have guessed the correct word!\n";
const string Dialogues::wordleOutOfAttempts = "Unlucky! You have run out of attempts!\n";

string Dialogues::printCurrentRoom(string& description){
    return "You are currently in: " + description + ". What is your next move?\n";
}

string Dialogues::printAttemptsLeft(int& attemptsLeft){
    return "You have " + std::to_string(attemptsLeft) + " tries left.\n";
}
