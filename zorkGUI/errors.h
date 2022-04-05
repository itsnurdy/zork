#ifndef ERRORS_H
#define ERRORS_H

// This returns a string when there is a no room error.
class NoRoomError {
public:
    const char* whathappened(){
        return "There are no rooms in the direction you are trying to take. Maybe try something else?\n";
    }

};

#endif // ERRORS_H
