#ifndef ROBBER_H
#define ROBBER_H

#include "NPC.h"

class Robber : public NPC {
public:
    Robber(const std::string& name, int x, int y);
    void accept(Visitor& visitor) override;
    std::string getType() const override;
};

#endif // ROBBER_H
