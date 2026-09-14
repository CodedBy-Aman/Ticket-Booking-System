#include <iostream>
#include <string>
using namespace std;

// Encapsulation: Movie owns its private data.
class Movie {
private:
    string title, language;
    int duration;

public:
    Movie(string title, string language, int duration)
        : title(title), language(language), duration(duration) {}

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDuration() const { return duration; }

    void display() const {
        cout << title << " | " << language << " | " << duration << " min\n";
    }
};
