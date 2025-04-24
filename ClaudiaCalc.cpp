// ClaudiaCalc Part 2 - Complete C++ Implementation with OOP and String Support

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <cmath>
#include <sstream>

using namespace std;

const int LINE_WIDTH = 114;

enum RegType { NUMBER, STRING };

class Register {
private:
    float number;
    string str;
    RegType type;

public:
    Register() : number(0.0), str(""), type(NUMBER) {}

    void setValue(const string& input) {
        try {
            size_t idx;
            float val = stof(input, &idx);
            if (idx != input.size()) throw invalid_argument("not pure number");
            number = val;
            type = NUMBER;
        } catch (...) {
            str = input;
            type = STRING;
        }
    }

    void clear() {
        number = 0.0;
        str = "";
        type = NUMBER;
    }

    RegType getType() const { return type; }
    float getNumber() const { return number; }
    const string& getString() const { return str; }

    string toString() const {
        if (type == NUMBER) {
            ostringstream ss;
            ss << fixed << setprecision(3) << number;
            return ss.str();
        } else {
            return str;
        }
    }

    // String-specific operations
    void add(const Register& other) {
        if (type == STRING && other.type == STRING) {
            str += other.str;
        } else if (type == NUMBER && other.type == NUMBER) {
            number += other.number;
        } else {
            cout << "Error: Invalid addition between number and string." << endl;
        }
    }

    void subtract(const Register& other) {
        if (type == STRING && other.type == STRING) {
            size_t pos = str.find(other.str);
            if (pos != string::npos && (other.str.size() == 1 || str.substr(pos, other.str.size()) == other.str)) {
                str.erase(pos, other.str.size());
            } // else: keep original string
        } else if (type == NUMBER && other.type == NUMBER) {
            number -= other.number;
        } else {
            cout << "Error: Invalid subtraction between number and string." << endl;
        }
    }

    void multiply(const Register& other) {
        if (type == NUMBER && other.type == NUMBER) {
            number *= other.number;
        } else if (type == STRING && other.type == NUMBER) {
            int times = floor(other.number);
            if (times < 0) {
                cout << "Error: Cannot multiply string by negative number." << endl;
                return;
            }
            string result;
            for (int i = 0; i < times; ++i) result += str;
            str = result;
        } else if (type == NUMBER && other.type == STRING) {
            int times = floor(number);
            if (times < 0) {
                cout << "Error: Cannot multiply string by negative number." << endl;
                return;
            }
            string result;
            for (int i = 0; i < times; ++i) result += other.str;
            type = STRING;
            str = result;
        } else if (type == STRING && other.type == STRING) {
            string result;
            for (char c1 : str) {
                for (char c2 : other.str) {
                    result += c1;
                    result += c2;
                }
            }
            str = result;
        } else {
            cout << "Error: Invalid multiplication." << endl;
        }
    }

    void divide(const Register& other) {
        if (type == NUMBER && other.type == NUMBER) {
            if (other.number == 0.0f) {
                cout << "Error: Division by zero." << endl;
                return;
            }
            number /= other.number;
        } else {
            cout << "Error: Invalid division operation." << endl;
        }
    }
};

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

int main() {
    ClaudiaCalc calc;
    calc.run();
    return 0;
}