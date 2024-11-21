#include "ConsoleLogger.h"
#include <iostream>

void ConsoleLogger::update(const std::string& eventMessage) {
    std::cout << eventMessage << std::endl;
}
