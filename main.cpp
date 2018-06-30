#include <iostream>
#include <thread>
#include <vector>
#include "STVector.h"


static int mode = 0;

class Wallet {
private:
    std::vector<int> _movementsSTDVector; //Of money
    STVector<int> _movementsSTVector;
public:
    Wallet() {};
    const unsigned long getNumbersOfMovements() {
        if (mode == 0) {
            return _movementsSTVector.size();
        } else {
            return _movementsSTDVector.size();
        }

    };
    void addMoney(const unsigned int amount) {
        if (mode == 0) {
            _movementsSTVector.push_back(amount);
        } else {
            _movementsSTDVector.push_back(amount);
        }
    }

    void spendMoney(const unsigned int amount) {
        if (mode == 0) {
            _movementsSTVector.push_back(amount);
        } else {
            _movementsSTDVector.push_back(amount);
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
    std::cout << "\n-------------------------------------------------------------------------" << std::endl;
    std::cout << "This example checks that STVector class is safe thread unlike std::vector." << std::endl;
    std::cout << "The example simulates a wallet with movements of money positives and negatives\n" << std::endl;
    std::cout << "Please select a choose (0-1):" << std::endl;
    std::cout << "\t0 - the example is executed using the class STVector (SafeThread Vector)" << std::endl;
    std::cout << "\t1 - the example is executed using the class std::vector" << std::endl;
    std::cin >> mode;

    if (mode > 1)
    {
        std::cout << "The mode is not available" << std::endl;
        getchar();
        return 0;
    }

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