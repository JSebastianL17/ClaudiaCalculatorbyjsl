// Register.h
#ifndef REGISTER_H
#define REGISTER_H

#include <string>

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
    std::string toDisplayString(char regName) const; // 👈 nueva función

    void add(const Register& other);
    void subtract(const Register& other);
    void multiply(const Register& other);
    void divide(const Register& other);
};

#endif