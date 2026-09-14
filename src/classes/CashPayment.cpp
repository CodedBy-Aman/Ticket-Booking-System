#include <iostream>
using namespace std;

class Payment {
public:
    virtual bool pay(double amount) = 0;
    virtual ~Payment() = default;
};

class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Cash payment of Rs." << amount << " received.\n";
        return true;
    }
};
