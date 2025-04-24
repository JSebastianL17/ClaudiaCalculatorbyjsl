#include "ClaudiaCalc.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

ClaudiaCalc::ClaudiaCalc() : a(0.0), b(0.0), c(0.0), d(0.0) {}

void ClaudiaCalc::drawLine() const {
    cout << string(LINE_WIDTH, '-') << endl;
}

void ClaudiaCalc::displayRegisters() const {
    cout << fixed << setprecision(3);
    cout << " A = " << a << endl;
    cout << " B = " << b << endl;
    cout << " C = " << c << endl;
    cout << " D = " << d << endl;
}

void ClaudiaCalc::displayMenu() const {
    drawLine();
    cout << "ClaudiaCalc Menu" << endl;
    drawLine();
    cout << "a-d : Enter a number for register A-D" << endl;
    cout << "1-4 : Clear register A-D" << endl;
    cout << "+   : Add B to A" << endl;
    cout << "-   : Subtract B from A" << endl;
    cout << "*   : Multiply A by B" << endl;
    cout << "/   : Divide A by B" << endl;
    cout << "m   : Display menu" << endl;
    cout << "p   : Display registers" << endl;
    cout << "q   : Quit" << endl;
    drawLine();
}

double& ClaudiaCalc::getRegister(char reg) {
    switch (tolower(reg)) {
        case 'a': return a;
        case 'b': return b;
        case 'c': return c;
        case 'd': return d;
        default:
            throw invalid_argument("Invalid register");
    }
}

void ClaudiaCalc::run() {
    displayMenu();
    char command;
    while (true) {
        cout << "\nEnter a command: ";
        cin >> command;
        command = tolower(command);

        if (command == 'q') {
            cout << "Exiting ClaudiaCalc. Goodbye!" << endl;
            break;
        } else if (command >= 'a' && command <= 'd') {
            double value;
            cout << "Enter a value for register " << char(toupper(command)) << ": ";
            while (!(cin >> value)) {
                cout << "Invalid input. Please try again: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            getRegister(command) = value;
        } else if (command >= '1' && command <= '4') {
            char reg = 'a' + (command - '1');
            getRegister(reg) = 0.0;
            cout << "Register " << char(toupper(reg)) << " cleared." << endl;
        } else if (command == '+' || command == '-' || command == '*' || command == '/') {
            try {
                double& regA = getRegister('a');
                double& regB = getRegister('b');
                if (command == '+') {
                    regA += regB;
                } else if (command == '-') {
                    regA -= regB;
                } else if (command == '*') {
                    regA *= regB;
                } else if (command == '/') {
                    if (regB == 0.0) {
                        cout << "Error: Division by zero is not allowed." << endl;
                        continue;
                    }
                    regA /= regB;
                }
                cout << "Operation complete. New value of A: " << fixed << setprecision(3) << regA << endl;
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
        } else if (command == 'm') {
            displayMenu();
        } else if (command == 'p') {
            displayRegisters();
        } else {
            cout << "Invalid command. Please try again." << endl;
        }
    }
}
