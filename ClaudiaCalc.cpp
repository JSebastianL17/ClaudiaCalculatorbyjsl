#include "ClaudiaCalc.h"
#include <iostream>
#include <iomanip>

void ClaudiaCalc::drawLine() const {
    std::cout << std::string(114, '-') << std::endl;
}

void ClaudiaCalc::displayRegisters() const {
    std::cout << std::setprecision(3) << std::fixed;
    std::cout << " A number = " << a_number << std::endl;
    std::cout << " B number = " << b_number << std::endl;
    std::cout << " C number = " << c_number << std::endl;
    std::cout << " D number = " << d_number << std::endl;
}
