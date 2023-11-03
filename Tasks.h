#pragma once
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

#pragma warning(disable : 4996)
class Tasks {
private:
    Check check;
public:
    void ShowTwoDimensionalArray(int InitialRow, int InitialColumn, int rows, int columns, vector<vector<string>>& TwoDArray);
    bool AskToGo(string question);
    void Options(string q1, string q2);
};