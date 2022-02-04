#include "movie.h"
#include "movies.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

//Usiamo reference in modo tale da evitare che si effettui una copia 
//dell'intera collection
//Inoltre si usa const in quanto la reference permette la modifica degli
//elementi della collection
void Movies::add_movie(string title, int rating, int num_watched){
    bool find = false;
    for(const Movie &movie : collection){
        if (movie.get_name()==title){find=true;}
    }
    if (!find){
        collection.push_back(Movie(title, rating, num_watched));
    }
    else{
        cout << "Movie already exists" << endl;
    }
}

void Movies::display_movies(){
    for(const Movie &movie : collection){
        cout << "Name: " << movie.get_name() << "  Rating:" << movie.get_rating() << "  Watched " << movie.get_num_watched() << " times\n" << endl;
    }
    cout << "-------------------------------------------------------" << endl;
}

void Movies::increment_watched(string title){
    bool find = false;
    for(auto &movie : collection){
        if(movie.get_name() == title){
            movie.increment_watched();
            find=true;
        }
    }
    if (!find){
        cout << "Movie not found" << endl;
    }
}


/*
MORALE: se devi usare funzioni che non modificano nulla
usa sempre const reference per evitare copie
*/