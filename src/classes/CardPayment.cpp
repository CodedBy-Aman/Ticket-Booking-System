#include <iostream>
#include <string>
using namespace std;

class Payment {
public:
    virtual bool pay(double amount) = 0;
    virtual ~Payment() = default;
};

class CardPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Card payment of Rs." << amount << " successful.\n";
        return true;
    }
};
