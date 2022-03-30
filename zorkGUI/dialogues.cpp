#include "dialogues.h"

// Setting most dialogues to whatever strings I have chosen.
const string Dialogues::welcome = "This room contains a do or die wordle challenge, "
                                  "attempting and failing will boot you from the game.\n"
                                  "\nIf the letter inputed was correct it will have [] characters around it,"
                                  "if it is the correct letter but in wrong place it will have {} around it.";
const string Dialogues::inputError = "Invalid command, please try again.\n";
const string Dialogues::noMoreRooms = "No more areas this way. Try another direction.\n";
const string Dialogues::wordleIncorrectInput = "Please input a 5 letter word.\n";
const string Dialogues::wordleSuccess = "Congratulations! You have guessed the correct word!\n";
const string Dialogues::wordleOutOfAttempts = "Unlucky! You have run out of attempts, goodbye!\n";

// Printing the current room.
string Dialogues::printCurrentRoom(string& description){
    return "You are currently in: " + description + " What is your next move?\n";
}

// Printing the attempts left in the wordle game.
string Dialogues::printAttemptsLeft(int& attemptsLeft){
    return "You have " + std::to_string(attemptsLeft) + " tries left.\n";
}
