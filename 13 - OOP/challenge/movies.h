#ifndef _MOVIES_H_
#define _MOVIES_H_
#include "movie.h"
#include <string>
#include <vector>

using namespace std;

class Movies {
    private:
        vector<Movie> collection;

    public:
        void add_movie(string title, int rating, int num_watched);
        void display_movies();
        void increment_watched(string title);

};
#endif // !_MOVIES_H_