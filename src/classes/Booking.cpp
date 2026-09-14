#include <vector>
#include <string>
using namespace std;

class Booking {
public:
    enum class Status { PENDING, CONFIRMED, CANCELLED };

private:
    static int nextBookingId;
    int bookingId;
    string movieTitle, screen, time;
    vector<int> seatNumbers;
    double totalAmount;
    Status status;

public:
    Booking(string movieTitle, string screen, string time,
            vector<int> seats, double amount)
        : bookingId(nextBookingId++), movieTitle(movieTitle),
          screen(screen), time(time), seatNumbers(seats),
          totalAmount(amount), status(Status::PENDING) {}

    int getBookingId() const { return bookingId; }
    const string& getMovieTitle() const { return movieTitle; }
    const string& getScreen() const { return screen; }
    const string& getTime() const { return time; }
    const vector<int>& getSeats() const { return seatNumbers; }
    double getTotalAmount() const { return totalAmount; }

    void confirm() { status = Status::CONFIRMED; }
    void cancel() { status = Status::CANCELLED; }
    bool isConfirmed() const { return status == Status::CONFIRMED; }
};

int Booking::nextBookingId = 1001;
