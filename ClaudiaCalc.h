#ifndef CLAUDIACALC_H
#define CLAUDIACALC_H

#include "Register.h"
#include <string>

inline const int LINE_WIDTH = 114; 

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