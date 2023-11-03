#include "Staff.h"

    void Staff::AddMovie() {
        system("CLS");
        string answer;
        movie.GetMovieParametrs(movie);
        cout << "+________________________________________________________________+" << endl;
        cout << "|                          Warning!                              |" << endl;
        cout << "|         YOU ARE IN THE PROCESS OF ADDING NEW MOVIE             |" << endl;
        cout << "| - You are now responsible for adding the new movie!            |" << endl;
        cout << "| - Remember that there is no system to validate the added movie |" << endl;
        cout << "+________________________________________________________________+" << endl;
        //Asking necessary informartion regarding film. 
        movie.SetTitle(check.String("Title:", 25, 5));
        movie.SetGenre(check.String("Genre:", 25, 5));
        movie.SetDescription(check.String("Description:", 25, 5));
        movie.SetMainStar(check.String("Main Star:", 25, 5));
        movie.SetFilmDisrtibutor(check.String("Disrtibutor:", 25, 5));
        movie.SetRunningTime(check.Int("Duration: ", 1000, 5));
        movie.SetReleaseDate(check.Date());
        movie.AddMovieInfoFile(movie);
        cout << movie.GetTitle() + " has been successfully added!" << endl;
    }
    void Staff::EditMovie() {
        system("CLS");
        string StrAnswer{ "" }, change{ "" };
        int IntAnswer{ 0 }, ID{ 0 }, column{ 0 };
        tm DateAnswer;
        vector<vector<string>> movies;
        cout << "+________________________________________________________________+\n";
        cout << "|                          Warning!                              |\n";
        cout << "|         YOU ARE IN THE PROCESS OF EDITING MOVIE                |\n";
        cout << "| - You are now responsible for editing the movie!               |\n";
        cout << "| - Remember that there is no system to validate the added movie |\n";
        cout << "+________________________________________________________________+\n\n";
        movie.GetMovieParametrs(movie);//Spreadibg movie parametrs in Class Movie State
        movies = movie.GetMovies();//Assigning a reference to the movies vector
        //Outputing movies
        task.ShowTwoDimensionalArray(1, 0, movie.GetMovieID() + 1, movies[1].size(), movies);//Outputing Movies
        //Asking The row and Column to Edit.
        ID = check.Int("Enter the Movie ID:", movie.GetMovieID(), 1);
        cout << "1)Title\n" << "2)Genre\n" << "3)Description\n" << "4)Main Star\n" << "5)Film Disrtibutor\n" << "6)Duration\n" << "7)Release Date\n";
        IntAnswer = check.Int("Choose the column: ", 7, 1);
        switch (IntAnswer) {
        case 1:StrAnswer = check.String("Title: ", 25, 1);  break;
        case 2:StrAnswer = check.String("Genre: ", 25, 1);  break;
        case 3:StrAnswer = check.String("Description: ", 25, 1); break;
        case 4:StrAnswer = check.String("Main Star: ", 25, 1);  break;
        case 5:StrAnswer = check.String("Disrtibutor: ", 25, 1); break;
        case 6:IntAnswer = check.Int("Duration: ", 450, 1); StrAnswer = to_string(IntAnswer); IntAnswer = 6; break;
        case 7:DateAnswer = check.Date();
            movie.SetReleaseDate(DateAnswer);
            char date[100];
            struct tm help = movie.GetReleaseDate();
            strftime(date, sizeof(date), "%d/%m/%Y", &help);
            StrAnswer = date;
            break;
        }
        change = StrAnswer;
        movie.EditMovieFile(movie, ID + 1, IntAnswer, change);//Rewritng the File
        cout << "Movie has been successfuly edited!" << endl;

    }
    void Staff::ScheduleWeek() {
        booking.ClearBookingFile();
        booking.ClearMyBookingsFile();
        //Declaring Variables
        int day{ 0 }, ticketID{ 1 }, sessions{ 0 }, answer{ 0 }, counter{ 0 };//ticket ID is a sequentialy increaing value that uniqly identifies each ticket.;
        movie.GetMovieParametrs(movie);//We call this function to get the data about the sizes of movie.file and movies.
        vector<vector<string>> movies = movie.GetMovies(), seats;
        vector<string> bookingfile;
        vector<int> checkmovies = { 0,0,0,0,0 };
        string path;
        string StartTime, EndTime;
        int movieID{ 0 }, screenID{ 1 };
        int StartTimeHour, StartTimeMinute, EndTimeHour, EndTimeMinute, counth{ 10 }, countm{ 15 };
        int maxhour{ 23 }, minhour{ 10 }, maxmin{ 59 }, minmin{ 15 };
        int duration{ 0 };
        int seatrow{ 1 }, seatnum{ 1 };
        int MaxSessions{ 0 };
        const int breakTime = 25;
        while (screenID <= 5)
        {
            duration = 0;
            path = "screen" + to_string(screenID) + ".csv";//We are now creatng the path using screenID.
            screen.ReadScreenFile(screen, path);//Calling the function that reads screen file to get any data about it.
            seats = screen.GetScreenMap();//Reading the screen map to fill the the columns for seats respectievely.
            maxhour = 23; minhour = 10;  maxmin = 59;  minmin = 15;

            bool nextscreen{ false };
            system("CLS");
            cout << "+----------------------------------------------------------------+" << endl;
            cout << "|                          Warning!                              |" << endl;
            cout << "|         YOU ARE IN THE PROCESS OF SHEDULING THE WEEK           |" << endl;
            cout << "| - You are now responsible for scheduling the week              |" << endl;
            cout << "+----------------------------------------------------------------+" << endl;
            cout << "\033[0;31mThe schedule goes straight from 10:15 - 23:30!\033[0m" << endl;
            cout << "You have to schedule screen No - " << to_string(screenID) + "." << endl << "With capacity - " << screen.GetMaxSeatingCapacity() << endl;
            while (true)
            {
                movieID = check.Int("Enter the Movie ID: ", movie.GetMovieID(), 1);
                if (checkmovies[0] != movieID && checkmovies[1] != movieID && checkmovies[2] != movieID && checkmovies[3] != movieID && checkmovies[4] != movieID)
                {
                    cout << "Movie: " << "\033[32m" + movies[movieID + 1][1] + "\033[0m" << endl;
                    cout << "Is it correct movie? y/n" << endl;
                    string answer = check.String("Answer: ", 4, 0);
                    answer = check.ToLower(answer);
                    //Make sure that the manager chosed the right movie.
                    if (answer == "y" || answer == "yes") { checkmovies[screenID - 1] = movieID; break; }
                    else if (answer == "n" || answer == "no") { cout << "Please repeat the process." << endl; }
                    else { cout << "There is no such answer." << endl << "Repeat the process" << endl; }
                }
                else { cout << "You can't set this film." << endl; }
            }
            system("CLS");
            duration = stoi(movies[movieID + 1][6]); // Getting the film duration
            MaxSessions = int(765) / (duration + int(25));//Calculating max number of sessions using equation
            cout << "\033[32m" + movies[movieID + 1][1] + " duration is " + to_string(duration) + " minutes!" + "\033[0m" << endl;
            cout << "Would you like to shedule this day manually, or you want a program automayically fill sessions?\n1)Manually\n2)Automatically\n";
            answer = check.Int("Answer: ", 2, 1);
            if (answer == 1) {
                StartTimeHour = 10; StartTimeMinute = 15;
                EndTimeHour = 0; EndTimeMinute = 0;
                cout << "\033[0;31mMaximum sessions: " << MaxSessions << "\033[0m" << endl;
                sessions = check.Int("Sessions quantity: ", MaxSessions, 0);
                while (nextscreen == false)
                {
                    //Warnnig manager about the time frames with the red color.
                    string zero{ "" };
                    if (minmin < 10)
                    {
                        zero = "0";
                    }
                    cout << "\033[0;31mWarning!\033[0m" << endl << "\033[0;31mTime frames:" + to_string(minhour) + ":" + zero + to_string(minmin) +  " - 23 : 30\033[0m" << endl;
                    //Asking the start and end times of the film and error-handle the inputs.
                    StartTimeHour = check.Int("Start time hour: ", maxhour, minhour);
                    if (StartTimeHour > minhour)
                    {
                        minmin = 0;
                    }
                    StartTimeMinute = check.Int("Start time minute:", maxmin, minmin);
                    counter = (((StartTimeHour * 60) + StartTimeMinute) + duration) / int(60);
                    if (counter > 23)
                    {
                        counter = 24;
                    }
                    else counter = 0;
                    EndTimeHour = check.Int("End time hour: ", maxhour, 0);
                    EndTimeMinute = check.Int("End time minute: ", maxmin, 0);
                    while ((((60 * (counter + EndTimeHour)) + EndTimeMinute) - ((StartTimeHour * 60) + StartTimeMinute) < duration) || ((counter + EndTimeHour) > 29))
                    {
                        cout << "\033[0;31mYour End Time is too small!\033[0m" << endl;
                        cout << "\033[0;31mMinimal End Time: " << to_string(((((StartTimeHour-counter) * 60) + StartTimeMinute) + duration) / int(60)) + ":" + to_string((((StartTimeHour * 60) + StartTimeMinute) + duration) % int(60)) + "\033[0m" << endl;
                        
                        EndTimeHour = check.Int("End time hour: ", maxhour, 0);
                        EndTimeMinute = check.Int("End time minute: ", maxmin, 0);
                    }
                    minmin = EndTimeMinute + breakTime;
                    minhour = EndTimeHour;
                    while (minmin >= 60) {
                        minhour++;
                        minmin = minmin - 60;
                    }

                    if (StartTimeMinute < 10)
                    {
                        StartTime = to_string(StartTimeHour) + ":" + "0" + to_string(StartTimeMinute);
                    }
                    else {
                        StartTime = to_string(StartTimeHour) + ":" + to_string(StartTimeMinute);
                    }
                    if (EndTimeHour > 23 || EndTimeHour < 10) {
                        if (EndTimeHour > 23) { EndTimeHour -= 24; }
                        EndTime = "0" + to_string(EndTimeHour) + ":";
                    }
                    else {
                        EndTime = to_string(EndTimeHour) + ":";
                    }
                    if (EndTimeMinute < 10)
                    {
                        EndTime += "0" + to_string(EndTimeMinute);
                    }
                    else {
                        EndTime += to_string(EndTimeMinute);
                    }

                    seatrow = 1; seatnum = 1;//Since the screen map and booking file are not the same in terms of sizes,we declared a new variable to adjust the assignning the seats.
                    for (int i = 0; i < screen.GetMaxSeatingCapacity(); i++)//This is the double loop that will fill the array for booking file. 
                    {
                        bookingfile.resize(10);
                        if (seatnum == screen.GetSeats()) { seatnum = 1; seatrow++; }
                        for (int j = 0; j < bookingfile.size(); j++)//Counting columns.
                        {
                            switch (j)
                            {
                            case 0:bookingfile[j] = ""; break;
                            case 1:bookingfile[j] = to_string(screenID); break;
                            case 2:bookingfile[j] = to_string(movieID); break;
                            case 3:bookingfile[j] = StartTime; break;
                            case 4:bookingfile[j] = EndTime; break;
                            case 5:
                                if (seats[seatrow][seatnum] == " ") { seatnum++; }
                                bookingfile[j] = seats[seatrow][seatnum];
                                break;
                            case 6:bookingfile[j] = to_string(ticketID); break;
                            case 7:bookingfile[j] = "Not selected"; break;
                            case 8:bookingfile[j] = "Available"; break;
                            case 9:bookingfile[j] = "No Price Yet"; break;
                            }
                        }
                        booking.WriteBookingFile(bookingfile);
                        seatnum++;
                        ticketID++;
                    }
                    sessions--;
                    if (sessions == 0)
                    {
                        nextscreen = true;
                    }
                    else if ((StartTimeHour * 60) + StartTimeMinute + duration > 1379) {
                        nextscreen = true;
                    }
                    else {
                        nextscreen = false;
                    }
                }
            }
            else {
                StartTimeHour = 10; StartTimeMinute = 15;
                counter = 0;
                while (counter < MaxSessions)
                {
                    if (StartTimeMinute < 10)
                    {
                        StartTime = to_string(StartTimeHour) + ":" + "0" + to_string(StartTimeMinute);
                    }
                    else {
                        StartTime = to_string(StartTimeHour) + ":" + to_string(StartTimeMinute);
                    }
                    EndTimeHour = int(StartTimeHour * 60 + StartTimeMinute + duration) / int(60);
                    if (EndTimeHour > 23) {
                        EndTimeHour -= 24;
                        EndTime = "0" + to_string(EndTimeHour) + ":";
                    }
                    else {
                        EndTime = to_string(EndTimeHour) + ":";
                    }
                    EndTimeMinute = int(StartTimeHour * 60 + StartTimeMinute + duration) % int(60);
                    if (EndTimeMinute < 10)
                    {
                        EndTime += "0" + to_string(EndTimeMinute);
                    }
                    else {
                        EndTime += to_string(EndTimeMinute);
                    }
                    StartTimeHour = int(EndTimeHour * 60 + EndTimeMinute + 25) / int(60);
                    StartTimeMinute = int(EndTimeHour * 60 + EndTimeMinute + 25) % int(60);
                    seatrow = 1; seatnum = 1;
                    for (int i = 0; i < screen.GetMaxSeatingCapacity(); i++)//This is the double loop that will fill the array for booking file. 
                    {
                        bookingfile.resize(10);
                        if (seatnum == screen.GetSeats()) { seatnum = 1; seatrow++; }
                        for (int j = 0; j < bookingfile.size(); j++)//Counting columns.
                        {
                            switch (j)
                            {
                            case 0:bookingfile[j] = ""; break;
                            case 1:bookingfile[j] = to_string(screenID); break;
                            case 2:bookingfile[j] = to_string(movieID); break;
                            case 3:bookingfile[j] = StartTime; break;
                            case 4:bookingfile[j] = EndTime; break;
                            case 5:
                                if (seats[seatrow][seatnum] == " ") { seatnum++; }
                                bookingfile[j] = seats[seatrow][seatnum];
                                break;
                            case 6:bookingfile[j] = to_string(ticketID); break;
                            case 7:bookingfile[j] = "Not selected"; break;
                            case 8:bookingfile[j] = "Available"; break;
                            case 9:bookingfile[j] = "No Price Yet"; break;
                            }
                        }
                        booking.WriteBookingFile(bookingfile);
                        seatnum++;
                        ticketID++;
                    }
                    counter++;
                }
            }
            screenID++;
        }
        cout << "\033[0;31mPLEASE WAIT! DO NOT CLOSE THE PROGRAM!\nWEEK SCHEDULE IS IN THE PROCESS OF GENTERATION!!!\033[0m" << endl;
        booking.ReedFullBookingFile();
        vector<vector<string>> file = booking.GetBookingData();
        booking.ClearBookingFile();
        string days[7] = { "Thursday","Friday","Saturday","Sunday","Monday","Tuesday","Wendsday" };
        ticketID = 1;
        for (int day = 0; day <= 6; day++)
        {
            for (int i = 0; i < (file.size()); i++)
            {
                file[i][0] = days[day];
                file[i][6] = to_string(ticketID);
                booking.WriteBookingFile(file[i]);
                ticketID++;
            }
        }
    }
