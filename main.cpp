#include <iostream>
#include <thread>
#include <vector>
#include "STVector.h"


class Wallet {
private:
    int money_ = 10000;
    //std::vector<int> _movements; //Of money
    STVector<int> _movements;
    std::mutex _mutex;
public:
    Wallet() {};
    const int getMoney() const {return money_;}
    const unsigned long getNumbersOfMovements() { return _movements.size();};
    void addMoney(const unsigned int amount) {
        _movements.push_back(amount);
        std::lock_guard<std::mutex> guard(_mutex);
        for (int i = 0; i < amount; ++i)
        {
            money_++;
        }
    }

    void spendMoney(const unsigned int amount) {
        _movements.push_back(-amount);
        std::lock_guard<std::mutex> guard(_mutex);
        for (int i = 0; i < amount; ++i)
        {
            money_--;
        }
    }
};

unsigned long testWallet(unsigned int movements, unsigned int amount) {
    Wallet wallet;
    std::vector<std::thread> threads;
    for (int i = 0; i < movements; ++i)
    {
        threads.push_back(std::thread(&Wallet::addMoney, &wallet, amount));
    }

    for (int i = 0; i < threads.size(); ++i)
    {
        threads[i].join();
    }

    return wallet.getNumbersOfMovements();
}

int main() {

    for (int i = 0; i < 1000; ++i)
    {
        int movements = 2;
        int amount = 10000;
        int tMovements = testWallet(movements, amount);
        if (movements != tMovements)
        {
            std::cout << "Error in simulation " << i << ", the number of movements is: " << tMovements << std::endl;
        }
    }
    std::cout << "Simulation over" << std::endl;
    getchar();


    return 0;
}