#include "Customer.h"

    float Customer::CalculatePrice() {
        // adults: £9.50, children: £5.50, senior citizens: £6.50 and students: £7.00.
        float Price{ 0 };
        string types[4] = { "Adult: £9.50", "Student: £7.00", "Child: £5.50", "Senior Citizen: £6.5" };
        for (int i = 0; i < (sizeof(types) / sizeof(types[0])); i++)
        {
            cout << i + 1 << ")" + types[i] << endl;
        }
        float cost{ 0 };
        switch (check.Int("Choose the category:", 4, 1))
        {
        case 1: cost = 9.5; break;
        case 2: cost = 7; break;
        case 3: cost = 5.5; break;
        case 4: cost = 6.5; break;
        }
        Price += cost;
        return Price;
    }
    string Customer::GetDay() {
        int index;
        string days[7] = { "Thursday","Friday","Saturday","Sunday","Monday","Tuesday","Wendsday" };
        //Output the days.
        for (int i = 0; i < 7; i++)
        {
            cout << to_string((i + 1)) + ")" + days[i] << endl;
            //Error-handle the user response
            //Ask User the day
        }
        while (true)
        {
            int response = check.Int("Day:", 7, 1);
            SeeAvailableMovies(days[response - 1]);
            string togo = check.String("Are you ready to choose your movie?\nyes/no:", 4, 0);
            togo = check.ToLower(togo);
            //Make sure that the manager chosed the right movie.
            if (togo == "y" || togo == "yes") { index = response; break; }
            else if (togo == "n" || togo == "no") { task.Options("Continue", "Return to the Menu"); }
            else { cout << "There is no such answer.\nPlease repeat the process.\n"; }
        }

        return days[index - 1];
    }
    string Customer::GetPaymentType() {
        cout << "Choose your payment:\n1)Cash\n2)Card\n";
        int answer = check.Int("Answer: ", 2, 1);
        string type{ "" };
        if (answer == 1) {
            type = "Cash";
        }
        else { type = "Card"; }
        return type;
    }
    void Customer::SeeAvailableMovies(string WeekDay) {
        booking.ReedFullBookingFile();
        vector<vector<string>> bookingfile = booking.GetBookingData();
        vector<vector<string>> movies = movie.GetMovies();
        string screenid{ "" }, movieid{ "" }, starttime{ "" }, endtime{ "" };
        string checkscreenid{ "" }, checkmovieid{ "" }, checkstarttime{ "" }, checkendtime{ "" };
        int row{ 1 };
        cout << WeekDay + ":" << endl;
        while (row < bookingfile.size())
        {
            if (bookingfile[row][0] == WeekDay)
            {
                int column{ 0 };
                screen.GetscreenParametrs(screen, "screen" + screenid + ".csv");
                while (column < 5)
                {
                    switch (column) {
                    case 1:screenid = bookingfile[row][column]; break;
                    case 2:movieid = bookingfile[row][column]; break;
                    case 3:starttime = bookingfile[row][column]; break;
                    case 4:endtime = bookingfile[row][column]; break;
                    }
                    column++;
                }
                if (screenid != checkscreenid && movieid != checkmovieid)
                {
                    cout << endl;
                    movie.GetMovieInformation(stoi(movieid));
                    cout << endl;
                    cout << "\033[1;31m\t|Screen - " + screenid + "| |Starts at: " + starttime + "| |Ends at: " + endtime << "|\033[0m\n";
                    checkscreenid = screenid; checkmovieid = movieid; checkstarttime = starttime; checkendtime = endtime;
                }
                if (starttime != checkstarttime && endtime != checkendtime)
                {
                    cout << "\033[1;31m\t|Screen - " + screenid + "| |Starts at: " + starttime + "| |Ends at: " + endtime << "|\033[0m\n";
                    checkstarttime = starttime; checkendtime = endtime;
                }
            }
            row++;
        }
    }

    void Customer::MakeBooking()
    {
        system("CLS");
        int answer, screenid, StartTimeHour, StartTimeMinute, day, response;
        string Day{""}, StartTime{""}, screenID, screenpath;
        bool errorExists{ true };
        vector<string> AvailableSeats;
        vector<vector<string>> movies, map,bookingdata;
        cout << "+________________________________________________________________+" << endl;
        cout << "|                          Warning!                              |" << endl;
        cout << "|         YOU ARE IN THE PROCESS OF BOOKING SEATS                |" << endl;
        cout << "| - You are now responsible for booking screen and seats         |" << endl;
        cout << "+________________________________________________________________+" << endl;

        while (errorExists == true)
        {
            //Calling function that asks the day.
            Day = GetDay();
            //Ask user the movie details
            screenid = check.Int("Choose the screen: ", 5, 1);
            StartTimeHour = check.Int("Start time hour: ", 23, 10);
            StartTimeMinute = check.Int("Start time minute:", 59, 00);
            //Convert the entered details to string
            if (StartTimeMinute < 10)
            {
                StartTime = to_string(StartTimeHour) + ":" + "0" + to_string(StartTimeMinute);
            }
            else {
                StartTime = to_string(StartTimeHour) + ":" + to_string(StartTimeMinute);
            }
            screenID = to_string(screenid);
            //Preparing data for outputing the screen map
            screenpath = "screen" + screenID + ".csv";
            screen.ReadScreenFile(screen, screenpath);
            cout << "ID = " << screen.GetScreenID() << endl << "Capacity = " << screen.GetMaxSeatingCapacity() << endl << "Facilities = " << screen.GetScreenFacilities() << endl;
            //Assigning a reference of a screen map to the "map"
            map = screen.GetScreenMap();
            //Reading from booking all sessions
            booking.ReedFullBookingFile();
            bookingdata = booking.GetBookingData();
            movies = movie.GetMovies();
            //Reading all the seats that available to the vector;
            AvailableSeats;
            for (int row = 0; row < bookingdata.size(); row++)
            {
                if (bookingdata[row][0] == Day && bookingdata[row][1] == screenID && bookingdata[row][3] == StartTime)
                {
                    movie.SetMovieID(stoi(bookingdata[row][2]));
                    if (bookingdata[row][8] == "Available") {
                        AvailableSeats.push_back(bookingdata[row][5]);
                    }
                    else { AvailableSeats.push_back(""); }
                }
            }
            int freeSeats{ 0 };//Counter of free seats
            if (AvailableSeats.empty() || AvailableSeats.size() == 1)
            {
                system("CLS");
                cout << "No session on the given time..." << endl;
            }
            else {
                int seatIndex = 0;
                //Outputing the screen map
                for (int i = 0; i < screen.GetRows() - 3; i++)
                {
                    for (int j = 0; j <= screen.GetSeats(); j++)
                    {
                        if (j != screen.GetSeats())
                        {
                            if (i >= 1 && j >= 1)
                            {
                                if (map[i][j] == AvailableSeats[seatIndex])
                                {
                                    cout << "\033[1;32m" + map[i][j] + "\033[0m" << " ";
                                    freeSeats++;
                                }
                                else {
                                    cout << "\033[1;31m" + map[i][j] + "\033[0m" << " ";
                                }
                                if (map[i][j] != " ") { seatIndex++; }
                            }
                            else {
                                cout << map[i][j] << " ";
                            }
                        }
                        else { cout << endl; }

                    }
                }//Finishing showing the screen map;
                //Booking Tickets
                cout << "How many Tickets you need?\nThere are " << freeSeats << " avilable tickets." << endl;
                int ticketQuantity = check.Int("Tickets quantity: ", freeSeats, 1);
                float Price;
                string seat{ "" };
                bool match{ false };
                //Asking the seats and rewritng booking file
                while (ticketQuantity != 0)
                {   
                    match = false;
                    seat = check.String("Enter the seat: ", 4, 0);
                    for (int i = 0; i < AvailableSeats.size(); i++)
                    {
                        if (check.ToLower(seat) == check.ToLower(AvailableSeats[i]))
                        {
                            AvailableSeats[i] = "";
                            match = true;
                            break;
                        }
                    }
                    if (match == true) {
                        string type = GetPaymentType(), name, surname;
                        seat = check.ToUpper(seat);
                        Price = CalculatePrice();
                        name = check.String("Enter the name of person:", 10, 1);
                        surname = check.String("Enter the surname of person:", 10, 1);
                        cout << "\033[0;31mPLEASE WAIT! DO NOT CLOSE THE PROGRAM!\nBOOKING IS IN THE PROCESS OF GENTERATION!!!\033[0m" << endl;
                        booking.EditBookingFile(Day, screenID, StartTime, seat, 7, type, bookingdata);
                        booking.EditBookingFile(Day, screenID, StartTime, seat, 8, "Not Available", bookingdata);
                        booking.EditBookingFile(Day, screenID, StartTime, seat, 9, to_string(Price), bookingdata);
                        booking.WriteMyBookingFile(Day, screenID, StartTime, seat, type, to_string(Price), name, surname, movies[movie.GetMovieID()][1]);
                        ticketQuantity--;
                    }
                    else { cout << "Seats you choosed out of your reach.\n"; }
                }
                system("CLS");
                errorExists = false;
            }
        }
    }
    void Customer::CancelMyBooking() {
        system("CLS");
        cout << "Your Bookings:";
        ShowMyBookings();
        short int answer{ 0 };
        vector<vector<string>> bookingdata;
        string Day{ "" }, ScreenID{ "" }, StartTime{ "" }, Seat{ "" };
        string days[7] = { "Thursday","Friday","Saturday","Sunday","Monday","Tuesday","Wendsday" };
        cout << "1)Thursday\n2)Friday\n3)Saturday\n4)Sunday\n5)Monday\n6)Tuesday\n7)Wendsday\n";
        answer = check.Int("Choose the day: ", 7, 1);
        Day = days[answer-1];
        ScreenID = to_string(check.Int("Screen ID: ", 5, 1));
        StartTime = check.String("Start Time: ", 6, 1);
        Seat = check.ToUpper(check.String("Seat: ", 4, 0));
        cout << "\033[0;31mPLEASE WAIT! DO NOT CLOSE THE PROGRAM!\nBOOKING CANCELATION IS IN THE PROCESS OF GENTERATION!!!\033[0m" << endl;
        booking.ReedFullBookingFile();
        bookingdata = booking.GetBookingData();
        if (booking.CancelMyBooking(Day, ScreenID, StartTime, Seat, name, surname) == true)
        {
            booking.EditBookingFile(Day, ScreenID, StartTime, Seat, 7, "Not Selected", bookingdata);
            booking.EditBookingFile(Day, ScreenID, StartTime, Seat, 8, "Available", bookingdata);
            booking.EditBookingFile(Day, ScreenID, StartTime, Seat, 9, "Not price yet", bookingdata);
        }
    }
    void Customer::ShowMyBookings() {
        system("CLS");
        name = check.String("Enter your name:", 10, 1);
        surname = check.String("Enter your surname:", 15, 3);
        booking.ReadFullMyBookingsFile();
        vector<vector<string>> file = booking.GetMyBookingData();
        for (int i = 0; i < file.size();i++) {
            for (int j = 0; j <= 9; j++)
            {
                if (file[i][6] == name && file[i][7] == surname)
                {
                    if (j != 9) { cout << file[i][j] + "|"; }
                    else { cout << endl; }
                }
            }
        }
    }
    void Customer::ShowAvailableMovies() {
        int answer{ 0 };
        string days[7] = { "Thursday","Friday","Saturday","Sunday","Monday","Tuesday","Wendsday" };
        cout << "1)Thursday\n2)Friday\n3)Saturday\n4)Sunday\n5)Monday\n6)Tuesday\n7)Wendsday\n";
        answer = check.Int("Choose the day: ", 7, 1);
        SeeAvailableMovies(days[answer-1]);
    }

