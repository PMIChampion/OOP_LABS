#ifndef ELF_H
#define ELF_H

#include "NPC.h"

class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y);
    void accept(Visitor& visitor) override;
    std::string getType() const override;
};

#endif // ELF_H
