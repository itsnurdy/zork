#ifndef ERRORS_H
#define ERRORS_H

class NoRoomError {
public:
    const char* what(){
        return "There are no rooms in the direction you are trying to take. Maybe try something else?\n";
    }

};

#endif // ERRORS_H
