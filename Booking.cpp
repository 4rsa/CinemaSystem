#include "Booking.h"

    vector<vector<string>>& Booking::GetBookingData() { return bookingRedFile; }
    vector<vector<string>>& Booking::GetMyBookingData() { return MybookingsRedFile; }

    void Booking::ReedFullBookingFile() {
        bookingRedFile.clear();
        ifstream file("booking.csv");
        string line;

        while (getline(file, line)) {
            vector<string> row;
            stringstream lineStream(line);
            string cell;

            while (getline(lineStream, cell, ',')) {
                row.push_back(cell);
            }

            bookingRedFile.push_back(row);
        }
    }
    void Booking::WriteBookingFile(vector<string>& bookingData) {
        ofstream file("booking.csv", std::ios_base::app);
        if (file.is_open())
        {
            string temp{ "" };
            for (int j = 0; j < bookingData.size(); j++)
            {
                temp += bookingData[j] + ",";
            }
            file << temp << endl;
            file.close();
        }
        else {
            cout << "Error occured during booking file execution." << endl;
        }
    }

    void Booking::ClearBookingFile() {
        ofstream file("booking.csv", ofstream::out | ofstream::trunc);
        file.close();
    }
    void Booking::EditBookingFile(string Day, string ScreenID, string StartTime, string Seat, int column, string Change, vector<vector<string>>& bookingfile) 
    {
        if (!(bookingfile.empty()))
        {
            for (int row = 0; row < bookingfile.size(); row++)
            {
                if (bookingfile[row][0] == Day && bookingfile[row][1] == ScreenID && bookingfile[row][3] == StartTime && bookingfile[row][5] == Seat)
                {
                    bookingfile[row][column] = Change;
                }
            }
            ClearBookingFile();
            for (int row = 0; row < bookingfile.size(); row++)
            {
                WriteBookingFile(bookingfile[row]);
            }
        }
        else {
            cout << "Error in Editing Booking File!!!" << endl;
        }
    }

    void Booking::ReadFullMyBookingsFile() {
        MybookingsRedFile.clear();
        ifstream file("MyBooking.csv");
        string line;
        while (getline(file, line)) {
            vector<string> row;
            stringstream lineStream(line);
            string cell;

            while (getline(lineStream, cell, ',')) {
                row.push_back(cell);
            }

            MybookingsRedFile.push_back(row);
        }
    }
    void Booking::WriteMyBookingFile(string Day, string ScreenID, string StartTime, string Seat, string Type, string Price, string name, string surname, string movietitle) {
        string row = Day + "," + ScreenID + "," + StartTime + "," + Seat + "," + Type + "," + Price + "," + name + "," + surname + "," + movietitle;
        ofstream file("MyBooking.csv", std::ios_base::app);
        if (file.is_open())
        {
            file << row << endl;
        }
        else {
            cout << "Error occured during booking file execution." << endl;
        }
    }

    void Booking::ClearMyBookingsFile() {
        ofstream file("MyBooking.csv", ofstream::out | ofstream::trunc);
        file.close();
    }
    bool Booking::CancelMyBooking(string Day, string ScreenID, string StartTime, string Seat, string name, string surname) {
        bool change{ false };
        ReadFullMyBookingsFile();
        vector<vector<string>> MyBookings = GetMyBookingData();
        ClearMyBookingsFile();
        for (int i = 0; i < MyBookings.size(); i++)
        {
            if (!(MyBookings[i][0] == Day && MyBookings[i][1] == ScreenID && MyBookings[i][2] == StartTime && MyBookings[i][3] == Seat && MyBookings[i][6] == name && MyBookings[i][7] == surname))
            {
                WriteMyBookingFile(MyBookings[i][0], MyBookings[i][1], MyBookings[i][2], MyBookings[i][3], MyBookings[i][4], MyBookings[i][5], MyBookings[i][6], MyBookings[i][7], MyBookings[i][8]);
            }   
            else {
                change = true;
            }
        }
        return change;
    }