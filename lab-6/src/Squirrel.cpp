#include "Squirrel.h"
#include "Visitor.h"

Squirrel::Squirrel(const std::string& name, int x, int y)
    : NPC(name, x, y) {}

void Squirrel::accept(Visitor& visitor) {
    visitor.visit(*this);
}

std::string Squirrel::getType() const {
    return "Squirrel";
}
