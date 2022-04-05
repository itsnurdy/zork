#include "parser.h"

Parser::Parser() {
    commands = new CommandWords();
}

Parser::~Parser(){
    delete commands;
}

Command* Parser::convertToCommand(string input){
    string word1 = "";
    string word2 = "";
    vector<string> words;

    // Size type is basically an int that's big enough to represent size of string.
    string::size_type pos = 0, last_pos = 0;

    pos = input.find_first_of(' ', last_pos);	// Find first space.
    // Npos tells us if there is no string found.
    if (pos == string::npos ) {
        words.push_back(input);    // Get the first (and only) word
    } else {
        words.push_back(input.substr(0, pos));
        words.push_back(input.substr(pos + 1, input.size() - pos - 1));
    }

    if (words.size() == 1) // Was only 1 word entered?
        word1 = words[0]; // Get first word.
    else if (words.size() >= 2) { // Were at least 2 words entered?
        word1 = words[0]; // Get first word
        word2 = words[1]; // Get second word
    }

    // note: We just ignore the rest of the input line.
    // Now check whether this word is known. If so, create a command with it.
    // If not, create a "nil" command (empty string for unknown command).

    return new Command(word1, word2);
}

string Parser::commandsInString(){
    return commands->validCommandsToString();
}
