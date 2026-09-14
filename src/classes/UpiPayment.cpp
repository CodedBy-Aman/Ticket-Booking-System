#include <iostream>
#include <string>
using namespace std;

class Payment {
public:
    virtual bool pay(double amount) = 0;
    virtual ~Payment() = default;
};

class UpiPayment : public Payment {
private:
    string upiId;
public:
    explicit UpiPayment(string upiId): upiId(upiId) {}
    bool pay(double amount) override {
        cout << "UPI payment of Rs." << amount << " successful.\n";
        return true;
    }
};
