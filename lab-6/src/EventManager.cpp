#include "EventManager.h"
#include <algorithm>

void EventManager::attach(Observer* observer) {
    observers.push_back(observer);
}

void EventManager::detach(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void EventManager::notify(const std::string& eventMessage) {
    for (Observer* observer : observers) {
        observer->update(eventMessage);
    }
}
