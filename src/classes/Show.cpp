#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum class SeatStatus { AVAILABLE, BOOKED };
enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    int number; SeatType type;
public:
    Seat(int number, SeatType type): number(number), type(type) {}
    int getNumber() const { return number; }
    SeatType getType() const { return type; }
};

class Screen {
private:
    int screenNumber; vector<Seat> seats;
public:
    Screen(int n, int count=12): screenNumber(n) {
        for(int i=1;i<=count;i++) {
            SeatType t=(i<=4)?SeatType::SILVER:(i<=8)?SeatType::GOLD:SeatType::PLATINUM;
            seats.emplace_back(i,t);
        }
    }
    int getScreenNumber() const { return screenNumber; }
    const vector<Seat>& getSeats() const { return seats; }
};

class ShowSeat {
private:
    const Seat* seat; SeatStatus status;
public:
    explicit ShowSeat(const Seat* s): seat(s), status(SeatStatus::AVAILABLE) {}
    int getSeatNumber() const { return seat->getNumber(); }
    SeatType getSeatType() const { return seat->getType(); }
    bool isAvailable() const { return status==SeatStatus::AVAILABLE; }
    bool book(){ if(!isAvailable()) return false; status=SeatStatus::BOOKED; return true; }
    void cancel(){ status=SeatStatus::AVAILABLE; }
};

class Movie {
private:
    string title, language; int duration;
public:
    Movie(string t,string l,int d):title(t),language(l),duration(d){}
    string getTitle()const{return title;}
};

class Show {
private:
    int id;
    Movie* movie;                 // Aggregation
    Screen* screen;               // Aggregation
    string startTime;
    vector<ShowSeat> showSeats;   // Composition

public:
    Show(int id, Movie* movie, Screen* screen, string startTime)
        : id(id), movie(movie), screen(screen), startTime(startTime) {
        for (const auto& seat : screen->getSeats())
            showSeats.emplace_back(&seat);
    }

    int getId() const { return id; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
    vector<ShowSeat>& getShowSeats() { return showSeats; }

    void displaySeats() const {
        cout << "\nSeat Layout (A=Available, B=Booked)\n";
        for (const auto& s : showSeats)
            cout << "[" << s.getSeatNumber() << ": "
                 << (s.isAvailable() ? "AVAILABLE" : "BOOKED") << "] ";
        cout << "\n";
    }

    ShowSeat* findShowSeat(int number) {
        for (auto& s : showSeats)
            if (s.getSeatNumber() == number) return &s;
        return nullptr;
    }
};
