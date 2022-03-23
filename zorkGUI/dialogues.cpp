#include "dialogues.h"

const string Dialogues::welcome = "This is a do or die wordle challenge,"
                                  " attempting and failing will boot you from the video game.";
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
