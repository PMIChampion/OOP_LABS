#ifndef VISITOR_H
#define VISITOR_H

class Elf;
class Robber;
class Squirrel;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(Elf& elf) = 0;
    virtual void visit(Robber& robber) = 0;
    virtual void visit(Squirrel& squirrel) = 0;
};

#endif // VISITOR_H
