#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "Observer.h"

class ConsoleLogger : public Observer {
public:
    void update(const std::string& eventMessage) override;
};

#endif // CONSOLE_LOGGER_H
