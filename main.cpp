#include "ClaudiaCalc.h"
#include <spdlog/spdlog.h>

int main() {
    spdlog::set_level(spdlog::level::debug);
    ClaudiaCalc calc;
    calc.drawLine();
    calc.displayRegisters();
    return 0;
}
