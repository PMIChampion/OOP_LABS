#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <vector>
#include "Observer.h"

class EventManager {
private:
    std::vector<Observer*> observers;
public:
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify(const std::string& eventMessage);
};

#endif // EVENT_MANAGER_H
