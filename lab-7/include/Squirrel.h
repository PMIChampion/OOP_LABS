#ifndef SQUIRREL_H
#define SQUIRREL_H

#include "NPC.h"

class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, int x, int y);
    void accept(Visitor& visitor) override;
    std::string getType() const override;
};

#endif // SQUIRREL_H
