#include "Check.h"
#include "Tasks.h"
#include "Movie.h"
#include "Screen.h"

int Screen::GetScreenID() { return ScreenID; }
void Screen::SetScreenID(int temp) { ScreenID = temp; }

vector<vector<string>>& Screen::GetScreenMap() { return ScreenMap; }
void Screen::SetScreenMap(vector<vector<string>>& p) {
    ScreenMap.resize(GetRows() - 3, vector<string>(GetSeats()));
    for (int i = 0; i < rows - 3; i++)
    {
        for (int j = 0; j < seats; j++)
        {
            ScreenMap[i][j] = p[i][j];
        }
        string bol;
    }
}
int Screen::GetRows() { return rows; }
void Screen::SetRows(int temp) { rows = temp; }

int Screen::GetSeats() { return seats; }
void Screen::SetSeats(int temp) { seats = temp; }

int Screen::GetMaxSeatingCapacity() { return MaxSeatingCapacity; }
void Screen::SetMaxSeatingCapacity(int temp) { MaxSeatingCapacity = temp; }

string Screen::GetScreenFacilities() { return ScreenFacilities; }
void Screen::SetScreenFacilities(string temp) { ScreenFacilities = temp; }

void Screen::GetscreenParametrs(Screen& screen, string path) {
    ifstream file(path);
    //reading rows and columns of the screen files.
    if (file.is_open()) {
        string line{ "" };
        if (getline(file, line)) {
            istringstream iss(line);
            string cell;
            int i = 0;
            while (getline(iss, cell, ',')) {
                i++;
                if (i == 2)screen.SetRows(stoi(cell));
                else if (i == 3)screen.SetSeats(stoi(cell));
            }
        }
    }
    file.close();
}
void Screen::ReadScreenFile(Screen& screen, string path) {
    GetscreenParametrs(screen, path);
    //Open screen file second time to copy it to the vector redfile.
    ifstream file(path);
    redfile.resize(screen.GetRows(), vector<string>(screen.GetSeats()));
    if (file.is_open())
    {
        int i = 0, j = 0;
        while (file.good())
        {
            string line{ "" };
            getline(file, line);
            j = 0;
            istringstream iss(line);
            string cell;
            while (getline(iss, cell, ',')) {
                redfile[i][j] = cell;
                j++;
            }
            i++;
        }
        screen.SetScreenID(stoi(redfile[screen.GetRows() - 1][0]));//Sending screen ID to the Screen class
        screen.SetMaxSeatingCapacity(stoi(redfile[screen.GetRows() - 1][1]));//Sending screen max seating capacity to the Screen class
        screen.SetScreenFacilities(redfile[screen.GetRows() - 1][2]);//Sending screen screen facilities to the Screen class
        vector<vector<string>>ScreenMap(screen.GetRows() - 2, vector<string>(screen.GetSeats()));
        for (int i = 0; i < screen.GetRows() - 3; i++)//Reading screen map to the new smaller vector.
        {
            for (int j = 0; j < screen.GetSeats(); j++) { ScreenMap[i][j] = redfile[i + 1][j]; }
        }
        screen.SetScreenMap(ScreenMap);
    }
    file.close();
}