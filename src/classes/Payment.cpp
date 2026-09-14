class Payment {
public:
    // Abstraction: payment contract.
    virtual bool pay(double amount) = 0;
    virtual ~Payment() = default;
};
