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
    
    double& getRegister(char reg) {
        switch(reg) {
            case 'a': return a_number;
            case 'b': return b_number;
            case 'c': return c_number;
            case 'd': return d_number;
            default: return a_number;
        }
    }

    public:
    void run() {
        spdlog::info("ClaudiaCalc started");
        displayMenu();

        char command;
        bool running = true;
        
        while (running) {
            std::cout << "Enter a command: ";
            std::cin >> command;
            command = tolower(command);
            
            switch(command) {
                case '+': case '-': case '*': case '/': {
                    char lhs, rhs;
                    std::cout << "Enter a lhs register: ";
                    std::cin >> lhs;
                    std::cout << "Enter a rhs register: ";
                    std::cin >> rhs;
                    
                    lhs = tolower(lhs);
                    rhs = tolower(rhs);
                    
                    if (command == '/' && getRegister(rhs) == 0) {
                        spdlog::error("Division by zero attempted");
                        std::cout << "Error: Division by zero." << std::endl;
                    } else {
                        switch (command) {
                            case '+': a_number = getRegister(lhs) + getRegister(rhs); break;
                            case '-': a_number = getRegister(lhs) - getRegister(rhs); break;
                            case '*': a_number = getRegister(lhs) * getRegister(rhs); break;
                            case '/': a_number = getRegister(lhs) / getRegister(rhs); break;
                        }
                        spdlog::info("Operation {} between {} and {}", command, lhs, rhs);
                        displayRegisters();
                    }
                    break;
                }
                case 'a': case 'b': case 'c': case 'd': {
                    double value;
                    std::cout << "Enter a value for register " << command << ": ";
                    std::cin >> value;
                    getRegister(command) = value;
                    spdlog::info("Value {} set to register {}", value, command);
                    displayRegisters();
                    break;
                }
                case '1': case '2': case '3': case '4': {
                    char reg = 'a' + (command - '1');
                    getRegister(reg) = 0.000;
                    spdlog::info("Register {} cleared", reg);
                    std::cout << "Register " << reg << " cleared" << std::endl;
                    displayRegisters();
                    break;