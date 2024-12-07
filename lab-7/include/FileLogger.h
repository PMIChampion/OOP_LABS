#ifndef FILE_LOGGER_H
#define FILE_LOGGER_H

#include "Observer.h"
#include <fstream>

class FileLogger : public Observer {
private:
    std::ofstream logFile;
public:
    FileLogger(const std::string& filename);
    ~FileLogger();
    void update(const std::string& eventMessage) override;
};

#endif // FILE_LOGGER_H
