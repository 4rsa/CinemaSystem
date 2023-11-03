#include "Check.h"
#include <limits>
string Check::ToUpper(string data) {
    transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return data;
}
string Check::ToLower(string data) {
    transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return data;
}
string Check::String(string request, int max, int min) {
    string var;
    cout << request;
    getline(cin, var, '\n');
    while (!(!var.empty() && var.length() < max && var.length() > min)) {
        cout << "Invalid input. Please enter form 6 to 24 chars: ";
        getline(cin, var, '\n');
    }
    return var;
}
int Check::Int(string request, int max, int min) {
    int value;
    while (true) {
        cout << "\033[32m" + request + "\033[0m";
        while (!(std::cin >> value) || std::cin.peek() != '\n' || value != static_cast<int>(value)) {
            cout << "Invalid input. Please enter an integer value: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        if ((value > max) || (value < min)) {
            cout << "The input is out of the border!" << endl;
        }
        else {
            string pass; getline(cin,pass,'\n');break;
        }
    }
    return value;
}
tm Check::Date() {
    tm t;
    int year{ 0 }, month{ 0 }, day{ 0 };
    year = Int("Year: ", 2023, 1970);
    month = Int("Month: ", 12, 1);
    int maxdays = 31;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) { maxdays = 31; }
    else if (month == 4 || month == 6 || month == 9 || month == 11) { maxdays = 30; }
    else { maxdays = 29; }
    day = Int("Day: ", maxdays, 1);
    t.tm_year = year - 1900; // Years since 1900
    t.tm_mon = month - 1;   // Month (0-11)
    t.tm_mday = day;
    return t;
}
tm Check::Time(string request1, int MaxHour, int MinHour, string request2, int MaxMinute, int MinMinute) {
    tm t;
    int hour, minute;
    hour = Int(request1, MaxHour, MinHour);
    minute = Int(request2, MaxMinute, MinMinute);
    t.tm_hour = hour;
    t.tm_min = minute;
    return t;
}