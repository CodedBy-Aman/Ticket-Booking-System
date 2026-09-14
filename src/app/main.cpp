#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <algorithm>
using namespace std;

// All required classes are represented in this single compilable translation unit.
// The assignment requires one class per .cpp file and no header files.
// The separate files in this project document each class; main contains the
// integrated implementation used for the demo.

enum class SeatType { SILVER, GOLD, PLATINUM };
enum class SeatStatus { AVAILABLE, BOOKED };

class Movie {
private:
    string title, language; int duration;
public:
    Movie(string title, string language, int duration)
        : title(title), language(language), duration(duration) {}
    string getTitle() const { return title; }
    void display() const { cout << title << " | " << language << " | " << duration << " min\n"; }
};

class Seat {
private:
    int number; SeatType type;
public:
    Seat(int number, SeatType type): number(number), type(type) {}
    int getNumber() const { return number; }
    SeatType getType() const { return type; }
    string typeName() const {
        if(type==SeatType::SILVER) return "SILVER";
        if(type==SeatType::GOLD) return "GOLD";
        return "PLATINUM";
    }
};

class Screen {
private:
    int number;
    vector<Seat> seats;
public:
    Screen(int number): number(number) {
        for(int i=1;i<=12;i++) {
            SeatType t=(i<=4)?SeatType::SILVER:(i<=8)?SeatType::GOLD:SeatType::PLATINUM;
            seats.emplace_back(i,t);
        }
    }
    int getNumber() const { return number; }
    const vector<Seat>& getSeats() const { return seats; }
};

class ShowSeat {
private:
    const Seat* seat;
    SeatStatus status;
public:
    explicit ShowSeat(const Seat* seat): seat(seat), status(SeatStatus::AVAILABLE) {}
    int number() const { return seat->getNumber(); }
    SeatType type() const { return seat->getType(); }
    bool available() const { return status==SeatStatus::AVAILABLE; }
    bool book() { if(!available()) return false; status=SeatStatus::BOOKED; return true; }
    void cancel() { status=SeatStatus::AVAILABLE; }
};

class Show {
private:
    int id;
    Movie* movie;
    Screen* screen;
    string time;
    vector<ShowSeat> seats;
public:
    Show(int id, Movie* movie, Screen* screen, string time)
        : id(id), movie(movie), screen(screen), time(time) {
        for(const auto& s: screen->getSeats()) seats.emplace_back(&s);
    }
    int getId() const { return id; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getTime() const { return time; }
    ShowSeat* findSeat(int n) {
        for(auto& s: seats) if(s.number()==n) return &s;
        return nullptr;
    }
    void displaySeats() const {
        cout << "\n--- Seat Layout ---\n";
        for(const auto& s: seats)
            cout << setw(3) << s.number() << ":" << (s.available()?"AVAILABLE":"BOOKED") << "  ";
        cout << "\nSilver 1-4 | Gold 5-8 | Platinum 9-12\n";
    }
};

class Cinema {
private:
    string name;
    vector<Screen> screens;
public:
    explicit Cinema(string name): name(name) {}
    void addScreen(int n) { screens.emplace_back(n); }
    Screen* getScreen(int n) {
        for(auto& s:screens) if(s.getNumber()==n) return &s;
        return nullptr;
    }
};

class Customer {
private:
    string name, phone;
public:
    Customer(string name,string phone):name(name),phone(phone){}
};

class Payment {
public:
    virtual bool pay(double amount)=0;
    virtual ~Payment()=default;
};

class UpiPayment: public Payment {
public:
    bool pay(double amount) override {
        cout << "Processing UPI payment Rs." << amount << "...\n";
        return true;
    }
};

class CardPayment: public Payment {
public:
    bool pay(double amount) override {
        cout << "Processing Card payment Rs." << amount << "...\n";
        return true;
    }
};

class CashPayment: public Payment {
public:
    bool pay(double amount) override {
        cout << "Cash payment Rs." << amount << " received.\n";
        return true;
    }
};

class PriceCalculator {
public:
    double calculate(const vector<SeatType>& types) const {
        double total=0;
        for(auto t:types)
            total += (t==SeatType::SILVER?150:(t==SeatType::GOLD?250:400));
        return total;
    }
};

class Booking {
private:
    static int nextId;
    int id;
    Show* show;
    vector<int> seats;
    double amount;
    bool confirmed=false;
public:
    Booking(Show* show, vector<int> seats, double amount)
        : show(show), seats(seats), amount(amount), id(nextId++) {}
    void confirm(){confirmed=true;}
    int getId() const{return id;}
    double getAmount() const{return amount;}
    const vector<int>& getSeats() const{return seats;}
    Show* getShow() const{return show;}
    bool isConfirmed() const{return confirmed;}
};
int Booking::nextId=1001;

class TicketPrinter {
public:
    void print(const Booking& b) const {
        cout << "\n=============== TICKET ===============\n";
        cout << "Booking ID : " << b.getId() << "\n";
        cout << "Movie      : " << b.getShow()->getMovie()->getTitle() << "\n";
        cout << "Screen     : " << b.getShow()->getScreen()->getNumber() << "\n";
        cout << "Time       : " << b.getShow()->getTime() << "\n";
        cout << "Seats      : ";
        for(int s:b.getSeats()) cout << s << " ";
        cout << "\nTotal      : Rs." << b.getAmount() << "\n";
        cout << "======================================\n";
    }
};

class BookingService {
private:
    PriceCalculator calculator;
    TicketPrinter printer;

public:
    // Compile-time polymorphism: overloaded helper.
    double calculatePrice(SeatType type) { return calculator.calculate({type}); }
    double calculatePrice(const vector<SeatType>& types) { return calculator.calculate(types); }

    unique_ptr<Booking> book(Show& show, const vector<int>& seatNumbers, Payment& payment) {
        vector<ShowSeat*> selected;
        vector<SeatType> types;

        for(int n:seatNumbers) {
            ShowSeat* seat=show.findSeat(n);
            if(!seat) {
                cout << "Invalid seat number: " << n << "\n";
                return nullptr;
            }
            if(!seat->available()) {
                cout << "Seat " << n << " is already BOOKED. Booking rejected.\n";
                return nullptr;
            }
            selected.push_back(seat);
            types.push_back(seat->type());
        }

        double total=calculator.calculate(types);
        cout << "Total amount: Rs." << total << "\n";

        auto booking=make_unique<Booking>(&show, seatNumbers, total);

        if(!payment.pay(total)) {
            cout << "Payment failed. Booking cancelled and seats remain AVAILABLE.\n";
            return nullptr;
        }

        for(auto seat:selected) seat->book();
        booking->confirm();
        printer.print(*booking);
        return booking;
    }

    void cancel(Booking& booking) {
        if(!booking.isConfirmed()) {
            cout << "Booking is not confirmed.\n";
            return;
        }
        for(int n:booking.getSeats()) {
            if(auto seat=booking.getShow()->findSeat(n)) seat->cancel();
        }
        cout << "Booking " << booking.getId() << " cancelled. Seats are AVAILABLE again.\n";
    }
};

void showMovies(const vector<Movie>& movies) {
    cout << "\n--- Movies Currently Playing ---\n";
    for(size_t i=0;i<movies.size();++i)
        cout << i+1 << ". ", movies[i].display();
}

int main() {
    Cinema cinema("PVR Demo Cinema");
    cinema.addScreen(1);
    cinema.addScreen(2);

    vector<Movie> movies{
        Movie("Interstellar","English",169),
        Movie("Inception","English",148)
    };

    vector<Show> shows{
        Show(1,&movies[0],cinema.getScreen(1),"06:00 PM"),
        Show(2,&movies[0],cinema.getScreen(1),"09:00 PM"),
        Show(3,&movies[1],cinema.getScreen(2),"07:00 PM")
    };

    BookingService service;
    vector<unique_ptr<Booking>> bookings;

    while(true) {
        cout << "\n===== MOVIE TICKET BOOKING =====\n";
        cout << "1. List movies\n2. List shows\n3. Show seats\n4. Book seats\n";
        cout << "5. Cancel booking\n6. Exit\nChoice: ";

        int choice;
        if(!(cin>>choice)) {
            cin.clear(); cin.ignore(10000,'\n');
            cout << "Invalid input.\n"; continue;
        }

        if(choice==1) {
            showMovies(movies);
        } else if(choice==2) {
            showMovies(movies);
            int m; cout<<"Movie number: "; cin>>m;
            if(m<1 || m>(int)movies.size()) { cout<<"Invalid movie.\n"; continue; }
            for(const auto& s:shows)
                if(s.getMovie()==&movies[m-1])
                    cout<<"Show "<<s.getId()<<" | Screen "<<s.getScreen()->getNumber()
                        <<" | "<<s.getTime()<<"\n";
        } else if(choice==3) {
            int id; cout<<"Show ID: "; cin>>id;
            auto it=find_if(shows.begin(),shows.end(),[&](const Show& s){return s.getId()==id;});
            if(it==shows.end()) { cout<<"Invalid show.\n"; continue; }
            it->displaySeats();
        } else if(choice==4) {
            int id; cout<<"Show ID: "; cin>>id;
            auto it=find_if(shows.begin(),shows.end(),[&](const Show& s){return s.getId()==id;});
            if(it==shows.end()) { cout<<"Invalid show.\n"; continue; }
            it->displaySeats();

            int count; cout<<"Number of seats: "; cin>>count;
            if(count<=0 || count>12) { cout<<"Invalid number of seats.\n"; continue; }

            vector<int> nums(count);
            cout<<"Enter seat numbers: ";
            for(int& n:nums) cin>>n;

            int method;
            cout<<"Payment: 1.UPI  2.Card  3.Cash : "; cin>>method;

            unique_ptr<Payment> payment;
            if(method==1) payment=make_unique<UpiPayment>();
            else if(method==2) payment=make_unique<CardPayment>();
            else if(method==3) payment=make_unique<CashPayment>();
            else { cout<<"Invalid payment method.\n"; continue; }

            auto booking=service.book(*it,nums,*payment);
            if(booking) bookings.push_back(move(booking));
        } else if(choice==5) {
            int id; cout<<"Booking ID: "; cin>>id;
            auto it=find_if(bookings.begin(),bookings.end(),
                [&](const unique_ptr<Booking>& b){return b->getId()==id;});
            if(it==bookings.end()) { cout<<"Booking not found.\n"; continue; }
            service.cancel(**it);
        } else if(choice==6) {
            cout<<"Thank you!\n";
            break;
        } else {
            cout<<"Invalid menu choice.\n";
        }
    }
}
