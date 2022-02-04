/*Challenge:
Class movie (attributi nome, rating, volte che il film è stato visto )
Class movies collezione di movie

Crea movies
aggiungi movie con attributi
metodo di moviesper incrementare ocntatore di un film
metodo per mostrare tutti movie

Addizionalmente:
se movie già esiste torna errore
se incremento contatore per film che non esiste torna errore

Usa gli header
*/
#include "movies.h"
#include "movie.h"
#include <string>

int main(){
    Movies movies;
    movies.add_movie("The Matrix", 10, 3);
    movies.add_movie("Resident Evil", 0, 1);
    movies.add_movie("Inception",7,2);
    movies.display_movies();
    movies.increment_watched("Inception");
    movies.increment_watched("Inception");
    movies.display_movies();
    movies.increment_watched("Django");
    movies.add_movie("Inception",7,2);
    return 0;
}