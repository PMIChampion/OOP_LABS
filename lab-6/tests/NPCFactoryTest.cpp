#include <gtest/gtest.h>
#include "NPCFactory.h"
#include "Elf.h"
#include "Robber.h"
#include "Squirrel.h"

TEST(NPCFactoryTest, CreateElf) {
    NPC* npc = NPCFactory::createNPC("Elf", "Legolas", 100, 200);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Elf");
    EXPECT_EQ(npc->getName(), "Legolas");
    EXPECT_EQ(npc->getX(), 100);
    EXPECT_EQ(npc->getY(), 200);
    delete npc;
}

TEST(NPCFactoryTest, CreateRobber) {
    NPC* npc = NPCFactory::createNPC("Robber", "Bandit", 150, 250);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Robber");
    EXPECT_EQ(npc->getName(), "Bandit");
    EXPECT_EQ(npc->getX(), 150);
    EXPECT_EQ(npc->getY(), 250);
    delete npc;
}

TEST(NPCFactoryTest, CreateSquirrel) {
    NPC* npc = NPCFactory::createNPC("Squirrel", "Sandy", 200, 300);
    ASSERT_NE(npc, nullptr);
    EXPECT_EQ(npc->getType(), "Squirrel");
    EXPECT_EQ(npc->getName(), "Sandy");
    EXPECT_EQ(npc->getX(), 200);
    EXPECT_EQ(npc->getY(), 300);
    delete npc;
}

TEST(NPCFactoryTest, CreateInvalidType) {
    NPC* npc = NPCFactory::createNPC("Dragon", "Smaug", 100, 100);
    EXPECT_EQ(npc, nullptr);
}
