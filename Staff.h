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
#include <iomanip>
#include "Check.h"
#include "Tasks.h"
#include "Movie.h"
#include "Screen.h"
#include "Booking.h"
#pragma warning(disable : 4996)
using namespace std;

class Staff {
    Movie movie;
    Screen screen;
    Booking booking;
    Check check;
    Tasks task;

public:
    void AddMovie();
    void EditMovie();
    void ScheduleWeek();
};