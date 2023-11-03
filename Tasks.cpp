#include "Tasks.h"
#include "Cinema.h"
 

    void Tasks::ShowTwoDimensionalArray(int InitialRow, int InitialColumn, int rows, int columns, vector<vector<string>>& TwoDArray)
    {
        for (int i = InitialRow; i <= rows; i++)
        {
            for (int j = InitialColumn; j <= columns; j++)
            {
                if (j != columns) { cout << TwoDArray[i][j] + "|"; }
                else { cout << endl; }
            }
        }
    }
    bool Tasks::AskToGo(string question) {
        bool togo{ true };
        string answer{ "" };
        answer = check.String("\033[0;32m"+question+"\033[0m", 4, 0);
        answer = check.ToLower(answer);
        if (answer == "y" || answer == "yes") { togo = true; }
        else if (answer == "n" || answer == "no") { togo = false; }
        else { cout << "\033[0;31mUSE ONLY y/n or yes/no or Y/N or YES/NO!\033[0m" << endl; AskToGo(question);}
        return togo;
    }
    void Tasks::Options(string q1, string q2){
        Cinema cinema;
        Check check;
        short int answer{ 0 };
        cout << "1)" + q1 + "\n2)" + q2 + "\n";
        answer = check.Int("Answer: ", 2, 1);
        if (answer == 2)
        {
            cinema.StartMenu();
        }
    }
