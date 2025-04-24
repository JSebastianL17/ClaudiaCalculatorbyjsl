// ClaudiaCalc.h
#ifndef CLAUDIACALC_H
#define CLAUDIACALC_H

#include <string>

const int LINE_WIDTH = 114;

class ClaudiaCalc {
private:
    double a_number;
    double b_number;
    double c_number;
    double d_number;

    void drawLine() const;
    void displayRegisters() const;
    void displayMenu() const;
    double& getRegister(char reg);

public:
    ClaudiaCalc(); 
    void run();    
};

#endif