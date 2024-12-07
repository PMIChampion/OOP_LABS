#include "Elf.h"
#include "Visitor.h"

Elf::Elf(const std::string& name, int x, int y)
    : NPC(name, x, y, 10, 50) {}

void Elf::accept(Visitor& visitor) {
    visitor.visit(*this);
}

std::string Elf::getType() const {
    return "Elf";
}
