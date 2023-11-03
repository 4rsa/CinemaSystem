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
#pragma warning(disable : 4996)
using namespace std;

class Check {
public:
    string ToUpper(string data);
    string ToLower(string data);
    string String(string request, int max, int min);
    int Int(string request, int max, int min);
    tm Date();
    tm Time(string request1, int MaxHour, int MinHour, string request2, int MaxMinute, int MinMinute);
};