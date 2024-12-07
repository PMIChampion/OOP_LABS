#include "NPCFactory.h"
#include "Elf.h"
#include "Robber.h"
#include "Squirrel.h"

NPC* NPCFactory::createNPC(const std::string& type, const std::string& name, int x, int y) {
    if (type == "Elf") {
        return new Elf(name, x, y);
    } else if (type == "Robber") {
        return new Robber(name, x, y);
    } else if (type == "Squirrel") {
        return new Squirrel(name, x, y);
    } else {
        return nullptr;
    }
}
