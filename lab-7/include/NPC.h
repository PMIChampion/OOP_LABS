#ifndef NPC_H
#define NPC_H

#include <string>
#include "Visitor.h"

class NPC {
protected:
    std::string name;
    int x, y;
    int movementDistance; 
    int killDistance;     
    bool isAlive;         

public:
    NPC(const std::string& name, int x, int y, int movementDistance, int killDistance);
    virtual ~NPC() = default;

    std::string getName() const;
    int getX() const;
    int getY() const;
    int getMovementDistance() const;
    int getKillDistance() const;
    bool getIsAlive() const;
    void setIsAlive(bool alive);

    void move(int maxX, int maxY);
    virtual void accept(Visitor& visitor) = 0;
    virtual std::string getType() const = 0;
};

#endif // NPC_H
