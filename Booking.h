#pragma once
#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <ctime>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include "Check.h"
#include "Tasks.h"
#include "Movie.h"
#include "Screen.h"
#pragma warning(disable : 4996)
using namespace std;

class Booking
{
private:
    vector<vector<string>> bookingRedFile, MybookingsRedFile;
public:
    vector<vector<string>>& GetBookingData();
    vector<vector<string>>& GetMyBookingData();

    void ReedFullBookingFile();
    void WriteBookingFile(vector<string>& bookingData);

    void ClearBookingFile();
    void EditBookingFile(string Day, string ScreenID, string StartTime, string Seat, int column, string Change, vector<vector<string>>& bookingfile);

    void ClearMyBookingsFile();
    bool CancelMyBooking(string Day, string ScreenID, string StartTime, string Seat, string name, string surname);

    void ReadFullMyBookingsFile();
    void WriteMyBookingFile(string Day, string ScreenID, string StartTime, string Seat, string Type, string Price, string name, string surname, string movietitle);
};