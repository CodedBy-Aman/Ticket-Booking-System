#include <vector>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };

class PriceCalculator {
public:
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

    double price(SeatType type) const {
        if (type == SeatType::SILVER) return SILVER_PRICE;
        if (type == SeatType::GOLD) return GOLD_PRICE;
        return PLATINUM_PRICE;
    }

    double calculate(const vector<SeatType>& types) const {
        double total = 0;
        for (auto type : types) total += price(type);
        return total;
    }
};
