#include "Robber.h"
#include "Visitor.h"

Robber::Robber(const std::string& name, int x, int y)
    : NPC(name, x, y, 10, 10) {}

void Robber::accept(Visitor& visitor) {
    visitor.visit(*this);
}

std::string Robber::getType() const {
    return "Robber";
}
