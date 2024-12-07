#include "CombatVisitor.h"
#include "Elf.h"
#include "Robber.h"
#include "Squirrel.h"

CombatVisitor::CombatVisitor(NPC& npc1, EventManager& eventManager, std::set<NPC*>& npcsToRemove)
    : npc1(npc1), eventManager(eventManager), npcsToRemove(npcsToRemove) {}

void CombatVisitor::visit(Elf& elf) {
    std::string message;
    if (npc1.getType() == "Robber") {
        message = "Эльф " + elf.getName() + " убил Разбойника " + npc1.getName();
        npcsToRemove.insert(&npc1);
    } else if (npc1.getType() == "Squirrel") {
        message = "Белка " + npc1.getName() + " убила Эльфа " + elf.getName();
        npcsToRemove.insert(&elf);
    } else {
        message = "Эльф " + elf.getName() + " встретил Эльфа " + npc1.getName() + ", никто не погиб";
    }
    eventManager.notify(message);
}

void CombatVisitor::visit(Robber& robber) {
    std::string message;
    if (npc1.getType() == "Squirrel") {
        message = "Разбойник " + robber.getName() + " убил Белку " + npc1.getName();
        npcsToRemove.insert(&npc1);
    } else if (npc1.getType() == "Elf") {
        message = "Эльф " + npc1.getName() + " убил Разбойника " + robber.getName();
        npcsToRemove.insert(&robber);
    } else {
        message = "Разбойник " + robber.getName() + " встретил Разбойника " + npc1.getName() + ", никто не погиб";
    }
    eventManager.notify(message);
}

void CombatVisitor::visit(Squirrel& squirrel) {
    std::string message;
    if (npc1.getType() == "Elf") {
        message = "Белка " + squirrel.getName() + " убила Эльфа " + npc1.getName();
        npcsToRemove.insert(&npc1);
    } else if (npc1.getType() == "Robber") {
        message = "Разбойник " + npc1.getName() + " убил Белку " + squirrel.getName();
        npcsToRemove.insert(&squirrel);
    } else {
        message = "Белка " + squirrel.getName() + " встретила Белку " + npc1.getName() + ", никто не погиб";
    }
    eventManager.notify(message);
}
