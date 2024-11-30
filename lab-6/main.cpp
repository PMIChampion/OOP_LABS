#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <set>
#include <fstream>
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

int main() {
    vector<NPC*> npcList;
    EventManager eventManager;
    ConsoleLogger consoleLogger;
    FileLogger fileLogger("log.txt");
    eventManager.attach(&consoleLogger);
    eventManager.attach(&fileLogger);

    while (true) {
        cout << "Меню:\n";
        cout << "1. Добавить NPC\n";
        cout << "2. Сохранить NPC в файл\n";
        cout << "3. Загрузить NPC из файла\n";
        cout << "4. Показать список NPC\n";
        cout << "5. Запустить боевой режим\n";
        cout << "6. Выход\n";
        cout << "Выберите опцию: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            string type, name;
            int x, y;
            cout << "Введите тип NPC (Elf, Robber, Squirrel): ";
            cin >> type;
            cout << "Введите имя NPC: ";
            cin >> name;
            bool nameExists = false;
            for (const auto& npc : npcList) {
                if (npc->getName() == name) {
                    nameExists = true;
                    break;
                }
            }
            if (nameExists) {
                cout << "NPC с таким именем уже существует!\n";
                continue;
            }
            cout << "Введите координаты x и y (0 <= x <= 500, 0 <= y <= 500): ";
            cin >> x >> y;
            if (x < 0 || x > 500 || y < 0 || y > 500) {
                cout << "Координаты вне допустимого диапазона!\n";
                continue;
            }
            NPC* npc = NPCFactory::createNPC(type, name, x, y);
            if (npc) {
                npcList.push_back(npc);
                cout << "NPC успешно добавлен.\n";
            } else {
                cout << "Некорректный тип NPC!\n";
            }
        } else if (choice == 2) {
            ofstream outFile("npcs.txt");
            for (const auto& npc : npcList) {
                outFile << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << "\n";
            }
            outFile.close();
            cout << "NPC сохранены в файл npcs.txt\n";
        } else if (choice == 3) {
            ifstream inFile("npcs.txt");
            if (!inFile) {
                cout << "Файл npcs.txt не найден!\n";
                continue;
            }
            for (auto& npc : npcList) {
                delete npc;
            }
            npcList.clear();
            string type, name;
            int x, y;
            while (inFile >> type >> name >> x >> y) {
                NPC* npc = NPCFactory::createNPC(type, name, x, y);
                if (npc) {
                    npcList.push_back(npc);
                }
            }
            inFile.close();
            cout << "NPC загружены из файла npcs.txt\n";
        } else if (choice == 4) {
            cout << "Список NPC:\n";
            for (const auto& npc : npcList) {
                cout << "Тип: " << npc->getType() << ", Имя: " << npc->getName() << ", Координаты: (" << npc->getX() << ", " << npc->getY() << ")\n";
            }
        } else if (choice == 5) {
            cout << "Введите дальность боя: ";
            double combatRange;
            cin >> combatRange;
            set<NPC*> npcsToRemove;

            for (size_t i = 0; i < npcList.size(); ++i) {
                for (size_t j = i + 1; j < npcList.size(); ++j) {
                    NPC* npc1 = npcList[i];
                    NPC* npc2 = npcList[j];
                    double dx = npc1->getX() - npc2->getX();
                    double dy = npc1->getY() - npc2->getY();
                    double distance = sqrt(dx * dx + dy * dy);
                    if (distance <= combatRange) {
                        CombatVisitor visitor1(*npc1, eventManager, npcsToRemove);
                        npc2->accept(visitor1);

                        CombatVisitor visitor2(*npc2, eventManager, npcsToRemove);
                        npc1->accept(visitor2);
                    }
                }
            }

            for (auto it = npcList.begin(); it != npcList.end();) {
                if (npcsToRemove.find(*it) != npcsToRemove.end()) {
                    delete *it;
                    it = npcList.erase(it);
                } else {
                    ++it;
                }
            }

            cout << "Бои завершены.\n";
        } else if (choice == 6) {
            break;
        } else {
            cout << "Некорректный выбор!\n";
        }
    }

    for (auto& npc : npcList) {
        delete npc;
    }

    return 0;
}
