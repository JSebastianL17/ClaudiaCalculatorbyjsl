#include "ClaudiaCalc.h"
#include "Register.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <map>

using namespace std;

void ClaudiaCalc::drawLine() const {
    cout << string(114, '-') << endl;
}

void ClaudiaCalc::displayRegisters() const {
    drawLine();
    cout << setw(65) << right << "ClaudiaCalc" << endl;
    drawLine();
    map<char, const Register*> regMap {{'A', &a}, {'B', &b}, {'C', &c}, {'D', &d}};
    for (auto& pair : regMap) {
        cout << pair.second->toDisplayString(pair.first) << "    ";
    }
    cout << endl;
    drawLine();
}

void ClaudiaCalc::displayMenu() const {
    displayRegisters();
    cout << "+        Add\n"
         << "-        Subtract\n"
         << "*        Multiply\n"
         << "/        Divide\n"
         << "a-d      Enter a number or string for A,B,C,D\n"
         << "1-4      Clear register A,B,C,D\n"
         << "m        Prints the menu\n"
         << "p        Prints the registers\n"
         << "q        Quits the app\n";
    drawLine();
}

Register& ClaudiaCalc::getRegister(char r) {
    switch (tolower(r)) {
        case 'a': return a;
        case 'b': return b;
        case 'c': return c;
        case 'd': return d;
        default: throw invalid_argument("Invalid register");
    }
}

void ClaudiaCalc::run() {
    displayMenu();
    string input;
    while (true) {
        cout << "\nEnter a command: ";
        getline(cin, input);
        if (input.empty()) continue;

        char command = tolower(input[0]);
        if (command == 'q') {
            cout << "Exiting ClaudiaCalc. Goodbye!" << endl;
            break;
        } else if (command >= 'a' && command <= 'd') {
            cout << "Enter a value for register " << (char)toupper(command) << ": ";
            string value;
            getline(cin, value);
            getRegister(command).setValue(value);
        } else if (command >= '1' && command <= '4') {
            char reg = 'a' + (command - '1');
            getRegister(reg).clear();
        } else if (command == '+' || command == '-' || command == '*' || command == '/') {
            char lhs, rhs;
            cout << "Enter a lhs register: ";
            cin >> lhs;
            cout << "Enter a rhs register: ";
            cin >> rhs;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            try {
                Register &regL = getRegister(lhs);
                Register &regR = getRegister(rhs);
                switch (command) {
                    case '+': regL.add(regR); break;
                    case '-': regL.subtract(regR); break;
                    case '*': regL.multiply(regR); break;
                    case '/': regL.divide(regR); break;
                }
            } catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
            }
        } else if (command == 'm') {
            displayMenu();
        } else if (command == 'p') {
            displayRegisters();
        } else {
            cout << "Invalid command. Press 'm' to see menu." << endl;
        }
    }
}