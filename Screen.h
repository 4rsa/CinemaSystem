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
#pragma warning(disable : 4996)
using namespace std;


class Screen {
private:
    int rows, seats;
    int ScreenID;
    int MaxSeatingCapacity;
    string ScreenFacilities;
    vector<vector<string>>redfile;
    vector<vector<string>>ScreenMap;
public:
    int GetScreenID();
    void SetScreenID(int temp);

    vector<vector<string>>& GetScreenMap();
    void SetScreenMap(vector<vector<string>>& p);

    int GetRows();
    void SetRows(int temp);

    int GetSeats();
    void SetSeats(int temp);

    int GetMaxSeatingCapacity();
    void SetMaxSeatingCapacity(int temp);

    string GetScreenFacilities();
    void SetScreenFacilities(string temp);

    void GetscreenParametrs(Screen& screen, string path);
    void ReadScreenFile(Screen& screen, string path);
};