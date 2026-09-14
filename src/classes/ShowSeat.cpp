#include <string>
using namespace std;

enum class SeatStatus { AVAILABLE, BOOKED };
enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    int number;
    SeatType type;
public:
    Seat(int number, SeatType type) : number(number), type(type) {}
    int getNumber() const { return number; }
    SeatType getType() const { return type; }
};

class ShowSeat {
private:
    const Seat* seat;
    SeatStatus status;

public:
    explicit ShowSeat(const Seat* seat) : seat(seat), status(SeatStatus::AVAILABLE) {}

    int getSeatNumber() const { return seat->getNumber(); }
    SeatType getSeatType() const { return seat->getType(); }
    bool isAvailable() const { return status == SeatStatus::AVAILABLE; }

    bool book() {
        if (!isAvailable()) return false;
        status = SeatStatus::BOOKED;
        return true;
    }

    void cancel() { status = SeatStatus::AVAILABLE; }
};
