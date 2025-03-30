#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <spdlog/spdlog.h>

class ClaudiaCalc {
    private:
        double a_number = 0.000;
        double b_number = 0.000;
        double c_number = 0.000;
        double d_number = 0.000;
        
        void drawLine() const {
            std::cout << std::string(114, '-') << std::endl;
        }