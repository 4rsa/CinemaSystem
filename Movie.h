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
#pragma warning(disable : 4996)

class Movie {
private:
    int MovieID{ 0 };
    int RunningTime{ 0 };
    int rows{ 0 }, columns{ 0 };
    string Title{ "" };
    string Genre{ "" };
    string Description{ "" };
    string MainStar{ "" };
    string FilmDisrtibutor{ "" };
    tm ReleaseDate;
    vector<vector<string>> redMovieFile;
public:
    Movie();

    int GetMovieID();
    string GetTitle();
    string GetGenre();
    string GetDescription();
    string GetMainStar();
    string GetFilmDisrtibutor();
    int GetRunningTime();
    tm GetReleaseDate();
    vector<vector<string>>& GetMovies();
    void GetMovieInformation(int movieID);

    void SetMovieID(int temp);
    void SetTitle(string temp);
    void SetGenre(string temp);
    void SetDescription(string temp);
    void SetMainStar(string temp);
    void SetFilmDisrtibutor(string temp);
    void SetRunningTime(int temp);
    void SetReleaseDate(tm temp);

    void GetMovieParametrs(Movie& movie);
    void ReadMovieFile();
    void AddMovieInfoFile(Movie movie);
    void EditMovieFile(Movie movie, int id, int column, string change);
};