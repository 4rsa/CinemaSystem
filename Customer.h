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
#include "Booking.h"
#include "Staff.h"
#pragma warning(disable : 4996)
using namespace std;

class Customer {
private:
    Movie movie;
    Screen screen;
    Booking booking;
    Check check;
    Tasks task;
    string BookingMovieTitle{ "" };
    string name, surname;

    float CalculatePrice();
    string GetDay();
    string GetPaymentType();
    void SeeAvailableMovies(string WeekDay);

public:

    void MakeBooking();
    void CancelMyBooking();
    void ShowMyBookings();
    void ShowAvailableMovies();

};