#ifndef NPC_H
#define NPC_H

#include <string>
#include "Visitor.h"

class NPC {
protected:
    std::string name;
    int x, y;

public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    std::string getName() const;
    int getX() const;
    int getY() const;

    virtual void accept(Visitor& visitor) = 0;
    virtual std::string getType() const = 0;
};

#endif // NPC_H
