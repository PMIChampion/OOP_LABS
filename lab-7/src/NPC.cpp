#include "NPC.h"
#include <cmath>
#include <random>

NPC::NPC(const std::string& name, int x, int y, int movementDistance, int killDistance)
    : name(name), x(x), y(y), movementDistance(movementDistance), killDistance(killDistance), isAlive(true) {}

std::string NPC::getName() const {
    return name;
}

int NPC::getX() const {
    return x;
}

int NPC::getY() const {
    return y;
}

int NPC::getMovementDistance() const {
    return movementDistance;
}

int NPC::getKillDistance() const {
    return killDistance;
}

bool NPC::getIsAlive() const {
    return isAlive;
}

void NPC::setIsAlive(bool alive) {
    isAlive = alive;
}

void NPC::move(int maxX, int maxY) {
    if (!isAlive) return;

    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> angleDist(0.0, 2 * M_PI);

    double angle = angleDist(generator);

    int dx = static_cast<int>(std::round(movementDistance * std::cos(angle)));
    int dy = static_cast<int>(std::round(movementDistance * std::sin(angle)));

    x += dx;
    y += dy;

    if (x < 0) x = 0;
    if (x > maxX) x = maxX;
    if (y < 0) y = 0;
    if (y > maxY) y = maxY;
}