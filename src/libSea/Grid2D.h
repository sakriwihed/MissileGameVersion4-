#ifndef BLATT6_GRID2D_H
#define BLATT6_GRID2D_H


#include <vector>

#include "Coordinates.h"


namespace Sea {

    template<class T>
    class Grid2D {

    private:
        std::vector<std::vector<T>> grid;

    public:
        Grid2D(unsigned int sizeX, unsigned int sizeY, T const & initElement);

        unsigned int sizeX() const;
        unsigned int sizeY() const;
        unsigned int size() const;

        T const & operator[](Coordinates const & coords) const;
        T & operator[](Coordinates const & coords);

        T const & operator()(unsigned int x, unsigned int y) const;
        T & operator()(unsigned int x, unsigned int y);

        // TODO Aufgabe 2:
        //  Deklariert die Funktion `walk(operation)` als konstante Funktion, die eine Lambda-Funktion `operation` als Parameter übergeben bekommt.
        //  Die Funktion soll nichts zurückliefern.

        template<typename FunkL>
        void walk(FunkL operation) const;

        // TODO Aufgabe 2:
        //  Deklariert die Funktion `filter(condition)` als konstante Funktion, die eine Lambda-Funktion `condition` als Parameter übergeben bekommt.
        //  Die Funktion soll einen `vector` von Elementen des Typs `T` zurückliefern.

        template<typename FunkL>
        std::vector<T> filter (FunkL condition) const;

    };

}


#include "Grid2D.inl"


#endif //BLATT6_GRID2D_H
