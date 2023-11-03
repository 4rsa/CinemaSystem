
#include "Check.h"
#include "Tasks.h"
#include "Movie.h"

     Movie:: Movie() {
         redMovieFile.resize(1000, vector<string>(8));
     }

     int Movie::GetMovieID() { return MovieID; }
     string Movie::GetTitle() { return Title; }
     string Movie::GetGenre() { return Genre; }
     string Movie::GetDescription() { return Description; }
     string Movie::GetMainStar() { return MainStar; }
     string Movie::GetFilmDisrtibutor() { return FilmDisrtibutor; }
     int Movie::GetRunningTime() { return RunningTime; }
     tm Movie::GetReleaseDate() { return ReleaseDate; }
     vector<vector<string>>& Movie::GetMovies() { ReadMovieFile(); return redMovieFile; }
     void Movie::GetMovieInformation(int movieID) {
         SetMovieID(movieID);
         vector<vector<string>> movies = GetMovies();
         cout << "\033[38;5;208m\tMovie ID: " << GetMovieID() << "\n\tMovie Titile: " + movies[GetMovieID() + 1][1] + "\n\tGenre: " + movies[GetMovieID() + 1][2] + "\n\tDescription: " + movies[GetMovieID() + 1][3] + "\n\tMain Star: " + movies[GetMovieID() + 1][4] + "\n\tFilm Distributor: " + movies[GetMovieID() + 1][5] + "\n\tDuration: " + movies[GetMovieID() + 1][6] + "\n\tRelease Date: " + movies[GetMovieID() + 1][7] + "\033[0m";
     }

     void Movie::SetMovieID(int temp) { MovieID = temp; }
     void Movie::SetTitle(string temp) { Title = temp; }
     void Movie::SetGenre(string temp) { Genre = temp; }
     void Movie::SetDescription(string temp) { Description = temp; }
     void Movie::SetMainStar(string temp) { MainStar = temp; }
     void Movie::SetFilmDisrtibutor(string temp) { FilmDisrtibutor = temp; }
     void Movie::SetRunningTime(int temp) { RunningTime = temp; }
     void Movie::SetReleaseDate(tm temp) { ReleaseDate = temp; }

     void Movie::GetMovieParametrs(Movie& movie) {
         ifstream file("movie.csv");
         if (file.is_open()) {
             string line{ "" };
             if (getline(file, line)) {
                 istringstream iss(line);
                 string cell{ "" };
                 int i = 0; int ID = 0;
                 while (getline(iss, cell, '|')) {
                     i++;
                     if (i == 2)ID = stoi(cell);

                 }
                 movie.SetMovieID(ID);
             }
         }
         file.close();
     }
     void Movie::ReadMovieFile() {
         redMovieFile.resize(1000, vector<string>(8));
         ifstream file("movie.csv");
         if (!file) { cout << "Error!"; }
         string line;
         int i = 0, j = 0;
         while (file.good())
         {
             getline(file, line);
             j = 0;
             istringstream iss(line);
             string cell;
             while (getline(iss, cell, '|')) {
                 redMovieFile[i][j] = cell;
                 j++;
             }
             i++;
         }
         rows = i - 1;
         file.close();
     }
     void Movie::AddMovieInfoFile(Movie movie) {
         ReadMovieFile();
         fstream file("movie.csv", ofstream::out);
         redMovieFile[0][1] = to_string(movie.GetMovieID() + 1);
         redMovieFile[rows][0] = to_string(movie.GetMovieID() + 1);
         redMovieFile[rows][1] = movie.GetTitle();
         redMovieFile[rows][2] = movie.GetGenre();
         redMovieFile[rows][3] = movie.GetDescription();
         redMovieFile[rows][4] = movie.GetMainStar();
         redMovieFile[rows][5] = movie.GetFilmDisrtibutor();
         redMovieFile[rows][6] = to_string(movie.GetRunningTime());
         //Converting date to string
         char date[100];
         struct tm help = movie.GetReleaseDate();
         strftime(date, sizeof(date), "%d:%m:%Y", &help);
         redMovieFile[rows][7] = date;
         //Rewriting the movie file
         string temp{ "" };
         if (file.is_open())
         {
             string temp{ "" };
             for (int j = 0; j <= rows; j++)
             {
                 temp = "";
                 for (int i = 0; i < 8; i++)
                 {
                     if (i != 7) { temp += redMovieFile[j][i] + '|'; }
                     else { temp += redMovieFile[j][i]; }
                 }
                 file << temp << endl;
             }
             file.close();
         }
         else {
             cout << "ERROR IN ADD MOVIE!";
         }
     }
     void Movie::EditMovieFile(Movie movie, int id, int column, string change) {
         ReadMovieFile();
         string temp;
         fstream file("movie.csv", ofstream::out);
         if (file.is_open())
         {
             redMovieFile[id][column] = change;
             for (int j = 0; j <= rows - 1; j++)
             {
                 temp = "";
                 for (int i = 0; i < 8; i++)
                 {
                     if (i != 7) { temp += redMovieFile[j][i] + '|'; }
                     else { temp += redMovieFile[j][i]; }
                 }
                 file << temp << endl;
             }
             file.close();
         }
         else { cout << "ERROR IN EDIT MOVIE!"; }

     }
