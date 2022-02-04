#include "movie.h"
#include <string>
#include <iostream>

using namespace std;

void Movie::increment_watched(){
    num_watched++;
}

//const necessario per usare const reference
string Movie::get_name() const{
    return title;

}

int Movie::get_rating() const{
    return rating;
}

int Movie::get_num_watched() const{
    return num_watched;
}

Movie::Movie(string name, int rate, int watching)
    :title{name}, rating{rate}, num_watched{watching}
{
}