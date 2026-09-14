#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TicketPrinter {
public:
    void print(int bookingId, const string& movie, const string& screen,
               const string& time, const vector<int>& seats, double amount) const {
        cout << "\n=============== TICKET ===============\n";
        cout << "Booking ID : " << bookingId << "\n";
        cout << "Movie      : " << movie << "\n";
        cout << "Screen     : " << screen << "\n";
        cout << "Time       : " << time << "\n";
        cout << "Seats      : ";
        for (int seat : seats) cout << seat << " ";
        cout << "\nTotal      : Rs." << amount << "\n";
        cout << "======================================\n";
    }
};
