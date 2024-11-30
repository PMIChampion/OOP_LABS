#include <gtest/gtest.h>
#include "Elf.h"
#include "Robber.h"
#include "Squirrel.h"
#include "CombatVisitor.h"
#include "EventManager.h"
#include "Observer.h"
#include <set>

class TestObserver : public Observer {
public:
    std::string lastMessage;
    void update(const std::string& eventMessage) override {
        lastMessage = eventMessage;
    }
};

TEST(CombatVisitorTest, ElfKillsRobber) {
    Elf elf("Legolas", 100, 100);
    Robber robber("Bandit", 105, 105);
    EventManager eventManager;
    std::set<NPC*> npcsToRemove;
    TestObserver observer;
    eventManager.attach(&observer);

    CombatVisitor visitor(elf, eventManager, npcsToRemove);
    robber.accept(visitor);

    EXPECT_EQ(observer.lastMessage, "Эльф Legolas убил Разбойника Bandit");
    EXPECT_EQ(npcsToRemove.size(), 1);
    EXPECT_TRUE(npcsToRemove.find(&robber) != npcsToRemove.end());
}

TEST(CombatVisitorTest, RobberKillsSquirrel) {
    Robber robber("Bandit", 100, 100);
    Squirrel squirrel("Sandy", 105, 105);
    EventManager eventManager;
    std::set<NPC*> npcsToRemove;
    TestObserver observer;
    eventManager.attach(&observer);

    CombatVisitor visitor(robber, eventManager, npcsToRemove);
    squirrel.accept(visitor);

    EXPECT_EQ(observer.lastMessage, "Разбойник Bandit убил Белку Sandy");
    EXPECT_EQ(npcsToRemove.size(), 1);
    EXPECT_TRUE(npcsToRemove.find(&squirrel) != npcsToRemove.end());
}

TEST(CombatVisitorTest, SquirrelKillsElf) {
    Squirrel squirrel("Sandy", 100, 100);
    Elf elf("Legolas", 105, 105);
    EventManager eventManager;
    std::set<NPC*> npcsToRemove;
    TestObserver observer;
    eventManager.attach(&observer);

    CombatVisitor visitor(squirrel, eventManager, npcsToRemove);
    elf.accept(visitor);

    EXPECT_EQ(observer.lastMessage, "Белка Sandy убила Эльфа Legolas");
    EXPECT_EQ(npcsToRemove.size(), 1);
    EXPECT_TRUE(npcsToRemove.find(&elf) != npcsToRemove.end());
}

TEST(CombatVisitorTest, NoOneDies) {
    Elf elf1("Legolas", 100, 100);
    Elf elf2("Elrond", 105, 105);
    EventManager eventManager;
    std::set<NPC*> npcsToRemove;
    TestObserver observer;
    eventManager.attach(&observer);

    CombatVisitor visitor(elf1, eventManager, npcsToRemove);
    elf2.accept(visitor);

    EXPECT_EQ(observer.lastMessage, "Эльф Elrond встретил Эльфа Legolas, никто не погиб");
    EXPECT_EQ(npcsToRemove.size(), 0);
}
