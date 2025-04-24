#ifndef CLAUDIACALC_H
#define CLAUDIACALC_H

#include <string>

const int LINE_WIDTH = 114;

enum RegType { NUMBER, STRING };

class Register {
private:
    float number;
    std::string str;
    RegType type;

public:
    Register();
    void setValue(const std::string& input);
    void clear();
    RegType getType() const;
    float getNumber() const;
    const std::string& getString() const;
    std::string toString() const;
    void add(const Register& other);
    void subtract(const Register& other);
    void multiply(const Register& other);
    void divide(const Register& other);
};

class ClaudiaCalc {
private:
    Register a, b, c, d;

    void drawLine() const;
    void displayRegisters() const;
    void displayMenu() const;
    Register& getRegister(char r);

public:
    void run();
};

#endif