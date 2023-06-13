#include "Plants&Zombies.h"
#include "Plants&Zombies.cpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <random>
using namespace std;

class Land {
public:
    std::vector<Zombies*> zombies;
    Plants* plant = nullptr;
};

class Game {
private:
    int numberOfLands;
    int numberOfZombies;
    std::vector<Plants> plants;
    std::vector<Land> lands;
    int playerLand;
    int playerMoney = 150;

public:
    Game() : numberOfLands(8), numberOfZombies(3), playerLand(7) {
        loadPlants();
    }

    void cleanUpZombies() {
        for (auto& land : lands) {
            for (auto& zombie : land.zombies) {
                delete zombie;
            }
        }
    }

    void start() {
        printWelcome();
        configureGame(); // input information
        printRules();
        pressAnyKeyToContinue();
        while (true) {
            // Add the rest of the game loop here
            printGameBoard();
            waitForPlayerChoice();
            // if (isGameOver())
            // {
            //     break;
            // }
        }
    }

    void printWelcome() {
        std::cout << "-----------------------------" << std::endl;
        std::cout << "|     Plants vs. Zombies     |" << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }

    int readIntegerInput(int min, int max, int defaultValue) {
        std::string input;
        std::getline(std::cin, input);

        if (input.empty()) {
            return defaultValue;
        }

        int intValue = std::stoi(input);

        if (intValue < min || intValue > max) {
            return defaultValue;
        }

        return intValue;
    }

    void configureGame() {
        std::cout << "Number of lands on the map (1-10, default: 8)...>";
        numberOfLands = readIntegerInput(1, 10, 8);

        std::cout << "Number of zombies on the map (1-10, default: 3)...>";
        numberOfZombies = readIntegerInput(1, 10, 3);

        // Resize lands and clear any previous zombies
        lands.resize(numberOfLands);
        for (auto& land : lands) {
            for (auto& zombie : land.zombies) {
                delete zombie;
            }
            land.zombies.clear();
        }

        for (int i = 0; i < numberOfZombies; ++i) {
            int landIndex = std::rand() % numberOfLands;
            lands[landIndex].zombies.push_back(new Zombies(i));
        }

        playerLand = std::rand() % numberOfLands;
    }

    void printRules() {
        std::cout << "=============================================================================" << std::endl;
        std::cout << "Plants vs. Zombies Rule:" << std::endl;
        std::cout << "\nHow to win:\n  (1) All zombies are dead.\n  (2) At least one plant is live.\n  (3) The number of dead bomb plants cannot exceed the number of zombies." << std::endl;
        std::cout << "\nHow to lose:\n  All plants are dead." << std::endl;
        std::cout << "=============================================================================" << std::endl;
    }

    void loadPlants() {
        std::ifstream file("plants.txt");
        std::string line;
        int i = 0;
        Plants* ptr[4];  // 創建一個名為ptr的Plants指標
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string tempCost;

            ss >> ptr[i]->catagory;
            ss >> ptr[i]->name;
            ss >> tempCost;
            tempCost.erase(std::remove(tempCost.begin(), tempCost.end(), '$'), tempCost.end()); // Remove dollar sign
            ptr[i]->cost = std::stoi(tempCost);
            ss >> ptr[i]->maxhp;
            //cin了 4 個屬性 catagory name cost maxhp 

            if (ptr[i]->catagory == 'C') {
            	//Sunflower sun;
            	Sunflower sun(ptr[i]->name);
            	ptr[i] = &sun;
                ss >> sun.maxcd >> sun.reward;
                //ss >> p[i]->maxcd >> p[i]->reward;
            }
            else if (ptr[i]->catagory == 'S') {
            	Shooter shoot(ptr[i]->name);
            	ptr[i] = &shoot;
                //ss >> ptr[i]->damage;
                ss >> shoot.damage;
            }
            else if (ptr[i]->catagory == 'B') {
            	Bomber bomb(ptr[i]->name);
            	ptr[i] = &bomb;
				ss>> bomb.life;
            }
            else if (ptr[i]->catagory == 'H') {
            	Healer heal(ptr[i]->name);
            	ptr[i] = &heal;
                ss >> heal.heal;
            }

            //plants.push_back(plant);
        }
    }

    void printGameBoard() {
        for (int i = 0; i < numberOfLands; ++i) {
            std::cout << "[" << i << "]";
            std::string occupants(numberOfZombies + 1, ' ');
            if (playerLand == i) {
                occupants[0] = '*';
            }
            for (int j = 0; j < numberOfZombies; ++j) {
                auto it = std::find_if(lands[i].zombies.begin(), lands[i].zombies.end(),
                                    [&j](const Zombies *z) { return z->getId() == j; });
                occupants[j + 1] = (it != lands[i].zombies.end()) ? ('0' + (*it)->getId()) : ' ';
            }
            if (lands[i].plant != nullptr) {
                std::cout << "{" << occupants << "}" << lands[i].plant->catagory << std::endl;
            } else {
                std::cout << "{" << occupants << "}Empty" << std::endl;
            }
        }
        std::cout << "------------------------------------------------" << std::endl;

        std::cout << "Zombie information:" << std::endl;
        for (int i = 0; i < numberOfZombies; ++i) {
            std::cout << "[" << i << "] Damage: 15 HP:" << std::string(40, '*') << std::endl;
        }
        std::cout << "================================================" << std::endl;

        /*for (int i = 0; i < int(plants.size()); ++i) {
            std::cout << "[" << i << "] " << plants[i].name << " $" << plants[i].cost << " HP: " << plants[i].maxhp;
            if (plants[i].catagory == 'C') {
                std::cout << " - gives $" << plants[i].val << " every " << plants[i].freq << " rounds";
            }
            else if (plants[i].category == 'S') {
                std::cout << " - gives " << plants[i].damage << " damage points";
            }
            else if (plants[i].type == 'B') {
                std::cout << " - gives " << plants[i].val << " damage points";
            }
            else if (plants[i].type == 'H') {
                std::cout << " - gives all your plants " << plants[i].val << " HP back.";
            }
            std::cout << std::endl;
        }*/
        std::cout << "================================================" << std::endl;
    }

    void clearConsole() {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
    }

    void pressAnyKeyToContinue() {
        std::cout << "pressAnyKeyToContinue . . .";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        clearConsole();
    }

    // TODO: Implement this function.
    void waitForPlayerChoice() {
        std::cout << "\nplayer $150:    Enter your choice (4 to give up, default: 4)...>";
        int playerChoice = readIntegerInput(0, 4, 4);
        pressAnyKeyToContinue();
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}
