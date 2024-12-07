#ifndef COMBAT_VISITOR_H
#define COMBAT_VISITOR_H

#include "Visitor.h"
#include "NPC.h"
#include "EventManager.h"
#include <set>

class CombatVisitor : public Visitor {
private:
    NPC& npc1;
    EventManager& eventManager;
    std::set<NPC*>& npcsToRemove;
public:
    CombatVisitor(NPC& npc1, EventManager& eventManager, std::set<NPC*>& npcsToRemove);
    void visit(Elf& elf) override;
    void visit(Robber& robber) override;
    void visit(Squirrel& squirrel) override;
};

#endif // COMBAT_VISITOR_H
