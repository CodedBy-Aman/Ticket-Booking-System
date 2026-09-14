#include <iostream>
#include <string>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    int number;
    SeatType type;

public:
    Seat(int number, SeatType type) : number(number), type(type) {}

    int getNumber() const { return number; }
    SeatType getType() const { return type; }

    string getTypeName() const {
        if (type == SeatType::SILVER) return "SILVER";
        if (type == SeatType::GOLD) return "GOLD";
        return "PLATINUM";
    }
};
