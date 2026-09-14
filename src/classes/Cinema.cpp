#include <string>
#include <vector>
using namespace std;

class Screen {
private:
    int screenNumber;
public:
    explicit Screen(int n): screenNumber(n) {}
    int getScreenNumber() const { return screenNumber; }
};

class Cinema {
private:
    string name;
    vector<Screen> screens;

public:
    explicit Cinema(string name): name(name) {}
    void addScreen(int number) { screens.emplace_back(number); }
    const string& getName() const { return name; }
    const vector<Screen>& getScreens() const { return screens; }
};
