#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H

#include <string>
#include "NPC.h"

class NPCFactory {
public:
    static NPC* createNPC(const std::string& type, const std::string& name, int x, int y);
};

#endif // NPC_FACTORY_H
