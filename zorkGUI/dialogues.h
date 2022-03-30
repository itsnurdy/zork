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
};

// Namespace for every single location with details about the locations.
namespace RoomDialogues {

    const string mainplace = "The main location which is a backalley"
                             " street behind a coffee shop where"
                             " you find yourself the most peaceful. ";
    const string trainstation = " A location where it is a cold, cold day at the "
                                " trainstation just waiting"
                                " for that train to show up. ";
    const string flowershop = " A location where there are lots of exotic fish and other creatures all engulfed by"
                              " flowers arround them, you spot a woman watering the amazing"
                              " flowers outside the shop. ";
    const string creepyroom = " This mystical place, you wonder what the hell is behind that"
                              " door on the left. The atmosphere is eerie. ";
    const string computerroom = " This room where everyone wants to be, lots of toy figures and"
                                " an undressed mario reading his emails. ";
    const string bridge = " An outside adventure, as you look out at the city you notice how the buildings suddenly at the press"
                          " of a button shut their power off.";
    const string alleyway = "This should be your favourite location, the small breeze in the wind knocking"
                            " down the pedals from the japaneese cherry trees.";
    const string lakeview = "As you look out you notice tall mountains behind the city, you notice this is the opposite angle"
                            " to the bridge angle.";

}
#endif // DIALOGUES_H
