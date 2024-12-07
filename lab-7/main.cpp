#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <fstream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <queue>
#include <chrono>
#include <random>
#include <atomic>
#include "NPC.h"
#include "Elf.h"
#include "Robber.h"
#include "Squirrel.h"
#include "NPCFactory.h"
#include "EventManager.h"
#include "ConsoleLogger.h"
#include "FileLogger.h"
#include "CombatVisitor.h"

using namespace std;
std::vector<NPC*> npcList;
std::shared_mutex npcMutex;      
std::mutex coutMutex;            

struct FightTask {
    NPC* attacker;
    NPC* defender;
};

std::queue<FightTask> fightQueue;
std::mutex fightQueueMutex;      

std::atomic<bool> gameRunning(true); 

void npcMovementThread(int maxX, int maxY) {
    while (gameRunning) {
        {
            std::shared_lock<std::shared_mutex> readLock(npcMutex);
            for (auto& npc : npcList) {
                if (npc->getIsAlive()) {
                    npc->move(maxX, maxY);
                }
            }
        }

        {
            std::shared_lock<std::shared_mutex> readLock(npcMutex);
            for (size_t i = 0; i < npcList.size(); ++i) {
                NPC* npc1 = npcList[i];
                if (!npc1->getIsAlive()) continue;
                for (size_t j = i + 1; j < npcList.size(); ++j) {
                    NPC* npc2 = npcList[j];
                    if (!npc2->getIsAlive()) continue;

                    int dx = npc1->getX() - npc2->getX();
                    int dy = npc1->getY() - npc2->getY();
                    double distance = std::sqrt(dx * dx + dy * dy);

                    if (distance <= std::min(npc1->getKillDistance(), npc2->getKillDistance())) {
                        std::lock_guard<std::mutex> queueLock(fightQueueMutex);
                        fightQueue.push({npc1, npc2});
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void npcFightThread() {
    while (gameRunning) {
        FightTask task;
        {
            std::lock_guard<std::mutex> queueLock(fightQueueMutex);
            if (!fightQueue.empty()) {
                task = fightQueue.front();
                fightQueue.pop();
            } else {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                continue;
            }
        }

        NPC* attacker = task.attacker;
        NPC* defender = task.defender;

        {
            std::shared_lock<std::shared_mutex> readLock(npcMutex);
            if (!attacker->getIsAlive() || !defender->getIsAlive()) {
                continue;
            }
        }

        static thread_local std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<int> diceDist(1, 6);

        int attackRoll = diceDist(generator);
        int defenseRoll = diceDist(generator);

        if (attackRoll > defenseRoll) {
            std::lock_guard<std::shared_mutex> writeLock(npcMutex);
            defender->setIsAlive(false);

            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << attacker->getType() << " " << attacker->getName()
                      << " убил " << defender->getType() << " " << defender->getName()
                      << std::endl;
        } else {

            std::lock_guard<std::mutex> coutLock(coutMutex);
            std::cout << defender->getType() << " " << defender->getName()
                      << " выжил при атаке " << attacker->getType() << " " << attacker->getName()
                      << std::endl;
        }
    }
}


int main() {
    const int maxX = 100;
    const int maxY = 100;

    {
        std::lock_guard<std::shared_mutex> writeLock(npcMutex);
        static thread_local std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<int> distX(0, maxX);
        std::uniform_int_distribution<int> distY(0, maxY);
        std::uniform_int_distribution<int> typeDist(0, 2); 

        for (int i = 0; i < 50; ++i) {
            int x = distX(generator);
            int y = distY(generator);
            std::string name = "NPC_" + std::to_string(i + 1);
            int type = typeDist(generator);

            NPC* npc = nullptr;
            if (type == 0) {
                npc = new Elf(name, x, y);
            } else if (type == 1) {
                npc = new Robber(name, x, y);
            } else if (type == 2) {
                npc = new Squirrel(name, x, y);
            }
            npcList.push_back(npc);
        }
    }

    std::thread movementThread(npcMovementThread, maxX, maxY);
    std::thread fightThread(npcFightThread);

    auto startTime = std::chrono::steady_clock::now();

    while (gameRunning) {
        {
            std::shared_lock<std::shared_mutex> readLock(npcMutex);
            std::lock_guard<std::mutex> coutLock(coutMutex);

            std::cout << "---------------------------------" << std::endl;
            std::cout << "Состояние карты:" << std::endl;
            for (const auto& npc : npcList) {
                if (npc->getIsAlive()) {
                    std::cout << npc->getType() << " " << npc->getName()
                              << " (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
                }
            }
            std::cout << "---------------------------------" << std::endl;
        }

        auto currentTime = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count() >= 30) {
            gameRunning = false;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    movementThread.join();
    fightThread.join();

    {
        std::shared_lock<std::shared_mutex> readLock(npcMutex);
        std::cout << "Игра окончена. Выжившие NPC:" << std::endl;
        for (const auto& npc : npcList) {
            if (npc->getIsAlive()) {
                std::cout << npc->getType() << " " << npc->getName()
                          << " (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
            }
        }
    }

    for (auto& npc : npcList) {
        delete npc;
    }

    return 0;
}
