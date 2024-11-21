#include "FileLogger.h"

FileLogger::FileLogger(const std::string& filename) {
    logFile.open(filename, std::ios::app);
}

FileLogger::~FileLogger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void FileLogger::update(const std::string& eventMessage) {
    if (logFile.is_open()) {
        logFile << eventMessage << std::endl;
    }
}
