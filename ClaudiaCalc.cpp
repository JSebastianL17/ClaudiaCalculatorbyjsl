#include "Register.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

const int LINE_WIDTH = 114;

class ClaudiaCalc {
private:
    Register a, b, c, d;

    void drawLine() const {
        cout << '|' << string(LINE_WIDTH - 2, '-') << '|' << endl;
    }

    void displayRegisters() const {
        drawLine();
        cout << "|";
        cout << setw((LINE_WIDTH - 2) / 2 + 6) << right << "ClaudiaCalc" << setw((LINE_WIDTH - 2) / 2 - 6) << "|\n";
        drawLine();
        cout << "| A = " << setw(10) << a.toString()
             << "   B = " << setw(10) << b.toString()
             << "   C = " << setw(10) << c.toString()
             << "   D = " << setw(10) << d.toString() << " |\n";
        drawLine();
    }

    void displayMenu() const {
        displayRegisters();
        cout << "| +        Add\n";
        cout << "| -        Subtract\n";
        cout << "| *        Multiply\n";
        cout << "| /        Divide\n";
        cout << "| a-d      Enter a number or string for A,B,C,D\n";
        cout << "| 1-4      Clear register A,B,C,D\n";
        cout << "| m        Prints the menu\n";
        cout << "| p        Prints the registers\n";
        cout << "| q        Quits the app\n";
        drawLine();
    }

    Register& getRegister(char r) {
        switch (tolower(r)) {
            case 'a': return a;
            case 'b': return b;
            case 'c': return c;
            case 'd': return d;
            default: throw invalid_argument("Invalid register");
        }
    }

public:
    void run() {
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
                cout << "Enter value for register " << (char)toupper(command) << ": ";
                string value;
                getline(cin, value);
                getRegister(command).setValue(value);
            } else if (command >= '1' && command <= '4') {
                char reg = 'a' + (command - '1');
                getRegister(reg).clear();
                cout << "Register " << (char)toupper(reg) << " cleared.\n";
            } else if (command == '+' || command == '-' || command == '*' || command == '/') {
                char lhs, rhs;
                cout << "Enter first register: ";
                cin >> lhs;
                cout << "Enter second register: ";
                cin >> rhs;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                Register &regL = getRegister(lhs);
                Register &regR = getRegister(rhs);
                switch (command) {
                    case '+': regL.add(regR); break;
                    case '-': regL.subtract(regR); break;
                    case '*': regL.multiply(regR); break;
                    case '/': regL.divide(regR); break;
                }
            } else if (command == 'm') {
                displayMenu();
            } else if (command == 'p') {
                displayRegisters();
            } else {
                cout << "Invalid command. Press 'm' to see menu.\n";
            }
        }
    }
};
