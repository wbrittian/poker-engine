/*functions.cpp*/

//
// helper functions for running game
//
// William Brittian
// 2025
//

#include "functions.hpp"

using namespace std;

// gets player name from terminal
string getName() {
    string name;
    bool correct = false;

    while (!correct) {
        cout << "please enter your name:" << endl;
        getline(cin, name);
        cout << endl;

        string ans;
        cout << "does this look right (y/n)? " << name << endl;
        getline(cin, ans);
        cout << endl;

        if (ans == "y") {
            correct = true;
        }
    }

    return name;
}

// prints out the main title screen
void printTitle() {
    cout << endl;
    cout << "----------------------------" << endl;
    cout << "         Welcome to         " << endl;
    cout << endl;
    cout << "****************************" << endl;

    cout << SPADE << SPADE << SPADE << SPADE << "  " << HEART << HEART << HEART << HEART << "  "
         << CHIP << "  " << CHIP << "  " << CLUB << CLUB << CLUB << CLUB << "  " << DIAMOND
         << DIAMOND << DIAMOND << DIAMOND << endl;

    cout << SPADE << "  " << SPADE << "  " << HEART << "  " << HEART << "  " << CHIP << " " << CHIP
         << "   " << CLUB << "     " << DIAMOND << "  " << DIAMOND << endl;

    cout << SPADE << SPADE << SPADE << SPADE << "  " << HEART << "  " << HEART << "  " << CHIP
         << CHIP << "    " << CLUB << CLUB << CLUB << CLUB << "  " << DIAMOND << DIAMOND << DIAMOND
         << DIAMOND << endl;

    cout << SPADE << "     " << HEART << "  " << HEART << "  " << CHIP << " " << CHIP << "   "
         << CLUB << "     " << DIAMOND << " " << DIAMOND << " " << endl;

    cout << SPADE << "     " << HEART << HEART << HEART << HEART << "  " << CHIP << "  " << CHIP
         << "  " << CLUB << CLUB << CLUB << CLUB << "  " << DIAMOND << "  " << DIAMOND << endl;

    cout << "****************************" << endl;
    cout << endl;
    cout << "   William Brittian 2025    " << endl;
    cout << "----------------------------" << endl;
    cout << endl;
}

void setColor(string color) {
    if (color == "red") {
        cout << "\033[31m";
    } else if (color == "green") {
        cout << "\033[32m";
    } else if (color == "black") {
        cout << "\033[0m";
    }
}

bool isInteger(const string& str) {
    stringstream ss(str);
    int i;
    char c;
    return (ss >> i) && (ss >> c).eof();
}