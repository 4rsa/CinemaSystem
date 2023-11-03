#include "Cinema.h"
 
 
    void Cinema::StartMenu() {
        Tasks task;
        system("CLS");
        cout << "+____________________________________________________________+" << endl;
        cout << "|                 Welcome to the Cinema System!              |" << endl;
        cout << "|Movie:                                                      |" << endl;
        cout << "|  1)Schedule Week                                           |" << endl;
        cout << "|  2)Add Movie                                               |" << endl;
        cout << "|  3)Edit Movie                                              |" << endl;
        cout << "|Booking:                                                    |" << endl;
        cout << "|  4)Make Booking                                            |" << endl;
        cout << "|  5)See Available Movies                                    |" << endl;
        cout << "|  6)Show my Bookings                                        |" << endl;
        cout << "|  7)Cancel my booking                                       |" << endl;
        cout << "|Please choose the option:                                   |" << endl;
        cout << "+____________________________________________________________+" << endl;
        answer = check.Int("Please enter your answer here: ", 7, 1);
        switch (answer)
        {
        case 1:
            staff.ScheduleWeek();
            while(task.AskToGo("Return to menu?\nAnswer y/n: ") == false) 
            { staff.ScheduleWeek(); }
            break;
        case 2:
            staff.AddMovie();
            while (task.AskToGo("Return to menu?\nAnswer y/n: ") == false)
            { staff.AddMovie(); }
            break;
        case 3:
            staff.EditMovie();
            while(task.AskToGo("Return to menu?\nAnswer y/n: ") == false)
            { staff.EditMovie(); }
            break;
        case 4:
            customer.MakeBooking();
            while (task.AskToGo("Return to menu?\nAnswer y/n: ") == false)
            { customer.MakeBooking(); }
            break;
        case 5:
            customer.ShowAvailableMovies();
            while(task.AskToGo("Return to menu?\nAnswer y/n:: ") == false) {
                customer.ShowAvailableMovies();
            }
            break;
        case 6:
            customer.ShowMyBookings();
            while(task.AskToGo("Return to menu?\nAnswer y/n: ") == false) {
                customer.ShowMyBookings();
            }
            break;
        case 7:
            customer.CancelMyBooking();
            break;
        }

        StartMenu();
    }

