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
#include "Customer.h"
#pragma warning(disable : 4996)
using namespace std;

class Cinema {
private:
    int answer;
    Check check;
    Staff staff;
    Customer customer;
public:
    void StartMenu();

};
