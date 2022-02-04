#ifndef _MOVIE_H_
#define _MOVIE_H_
#include<string>

using namespace std;

class Movie{
    private:
        string title;
        int rating;
        int num_watched;
    public:
        void increment_watched();
        string get_name() const;
        int get_rating() const;
        int get_num_watched() const;
        Movie(string title, int rating, int num_watched);
};
#endif // !_MOVIE_H_