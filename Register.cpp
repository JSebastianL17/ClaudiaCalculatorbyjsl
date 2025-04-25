#include "Register.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>

Register::Register() : number(0.0), str(""), type(NUMBER) {}

void Register::setValue(const std::string& input) {
    try {
        size_t idx;
        float val = std::stof(input, &idx);
        if (idx != input.size()) throw std::invalid_argument("Not a pure number");
        number = val;
        type = NUMBER;
    } catch (...) {
        str = input;
        type = STRING;
    }
}

void Register::clear() {
    number = 0.0;
    str = "";
    type = NUMBER;
}

RegType Register::getType() const { return type; }
float Register::getNumber() const { return number; }
const std::string& Register::getString() const { return str; }

std::string Register::toString() const {
    if (type == NUMBER) {
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(3) << number;
        return ss.str();
    } else {
        return str;
    }
}

std::string Register::toDisplayString(char regName) const {
    std::ostringstream ss;
    ss << regName << " " << (type == NUMBER ? "number = " : "string = ") << toString();
    return ss.str();
}

void Register::add(const Register& other) {
    if (type == STRING && other.type == STRING) {
        str += other.str;
    } else if (type == NUMBER && other.type == NUMBER) {
        number += other.number;
    } else {
        std::cout << "Error: Invalid addition between number and string." << std::endl;
    }
}

void Register::subtract(const Register& other) {
    if (type == STRING && other.type == STRING) {
        size_t pos = str.find(other.str);
        if (pos != std::string::npos) {
            str.erase(pos, other.str.size());
        }
    } else if (type == NUMBER && other.type == NUMBER) {
        number -= other.number;
    } else {
        std::cout << "Error: Invalid subtraction between number and string." << std::endl;
    }
}

void Register::multiply(const Register& other) {
    if (type == NUMBER && other.type == NUMBER) {
        number *= other.number;
    } else if (type == STRING && other.type == NUMBER) {
        int times = std::floor(other.number);
        if (times < 0) {
            std::cout << "Error: Cannot multiply string by negative number." << std::endl;
            return;
        }
        std::string result;
        for (int i = 0; i < times; ++i) result += str;
        str = result;
    } else if (type == NUMBER && other.type == STRING) {
        int times = std::floor(number);
        if (times < 0) {
            std::cout << "Error: Cannot multiply string by negative number." << std::endl;
            return;
        }
        std::string result;
        for (int i = 0; i < times; ++i) result += other.str;
        type = STRING;
        str = result;
    } else if (type == STRING && other.type == STRING) {
        std::string result;
        for (char c1 : str) {
            for (char c2 : other.str) {
                result += c1;
                result += c2;
            }
        }
        str = result;
    } else {
        std::cout << "Error: Invalid multiplication." << std::endl;
    }
}

void Register::divide(const Register& other) {
    if (type == NUMBER && other.type == NUMBER) {
        if (other.number == 0.0f) {
            std::cout << "Error: Division by zero." << std::endl;
            return;
        }
        number /= other.number;
    } else {
        std::cout << "Error: Invalid division operation." << std::endl;
    }
}