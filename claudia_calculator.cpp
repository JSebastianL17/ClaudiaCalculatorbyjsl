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

            
    void displayRegisters() const {
        std::cout << std::setprecision(3) << std::fixed;
        std::cout << "        A number = " << a_number;
        std::cout << "                B number = " << b_number;
        std::cout << "                C number = " << c_number;
        std::cout << "                D number = " << d_number << std::endl;
        spdlog::info("Registers updated: A={}, B={}, C={}, D={}", a_number, b_number, c_number, d_number);
    }
    
    void displayMenu() const {
        drawLine();
        std::cout << std::setw(58) << "ClaudiaCalc" << std::endl;
        drawLine();
        displayRegisters();
        drawLine();
        std::cout << "+        Add" << std::endl;
        std::cout << "-        Subtract" << std::endl;
        std::cout << "*        Multiply" << std::endl;
        std::cout << "/        Divide" << std::endl;
        std::cout << "a-d      Enter a number or string for A,B,C,D" << std::endl;
        std::cout << "1-4      Clear register A,B,C,D" << std::endl;
        std::cout << "m        Prints the menu" << std::endl;
        std::cout << "p        Prints the registers" << std::endl;
        std::cout << "q        Quits the app" << std::endl;
        drawLine();
        spdlog::info("Menu displayed");
    }
    