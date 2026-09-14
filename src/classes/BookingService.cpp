// BookingService is the orchestrator.
// It coordinates Show, PriceCalculator, Payment, Booking and TicketPrinter.
// It does not implement pricing or payment itself.
#include <iostream>
using namespace std;

class BookingService {
public:
    void description() const {
        cout << "BookingService: coordinates the end-to-end booking flow.\n";
    }
};
