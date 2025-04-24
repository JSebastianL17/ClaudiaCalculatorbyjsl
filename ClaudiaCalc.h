#ifndef CLAUDIACALC_H
#define CLAUDIACALC_H

const int LINE_WIDTH = 114;

class ClaudiaCalc {
private:
    double a;
    double b;
    double c;
    double d;

    void drawLine() const;
    void displayRegisters() const;
    void displayMenu() const;
    double& getRegister(char reg);

public:
    ClaudiaCalc();
    void run();
};

#endif
