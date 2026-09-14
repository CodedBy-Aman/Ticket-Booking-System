#include <iostream>
#include <vector>
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

class Screen {
private:
    int screenNumber;
    vector<Seat> seats;

public:
    Screen(int screenNumber, int seatCount = 12) : screenNumber(screenNumber) {
        // Composition: Screen creates and owns its Seats.
        for (int i = 1; i <= seatCount; ++i) {
            SeatType type = (i <= 4) ? SeatType::SILVER :
                             (i <= 8) ? SeatType::GOLD : SeatType::PLATINUM;
            seats.emplace_back(i, type);
        }
    }

    int getScreenNumber() const { return screenNumber; }
    const vector<Seat>& getSeats() const { return seats; }

    const Seat* findSeat(int number) const {
        for (const auto& seat : seats)
            if (seat.getNumber() == number) return &seat;
        return nullptr;
    }
};
