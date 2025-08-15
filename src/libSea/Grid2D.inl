
    class Grid2DInvalidSizeException : public std::exception {
    private:
        const char * what() const noexcept override { return "sizeX and sizeY must both be > 0"; }
    };

    template<class T>
    Sea::Grid2D<T>::Grid2D(unsigned int sizeX, unsigned int sizeY, T const & initElement)
    : grid(sizeY, std::vector<T>(sizeX, initElement))
    {
        if (sizeX == 0 || sizeY == 0) {
            throw Grid2DInvalidSizeException();
        }
    }

    template<class T>
    unsigned int Sea::Grid2D<T>::sizeX() const
    {
        return static_cast<unsigned int>(grid[0].size());
    }

    template<class T>
    unsigned int Sea::Grid2D<T>::sizeY() const
    {
        return static_cast<unsigned int>(grid.size());
    }

    template<class T>
    unsigned int Sea::Grid2D<T>::size() const
    {
        return sizeX() * sizeY();
    }

    template<class T>
    T const & Sea::Grid2D<T>::operator[](Sea::Coordinates const & coords) const
    {
        return grid.at(coords.getY()).at(coords.getX());
    }

    template<class T>
    T & Sea::Grid2D<T>::operator[](Sea::Coordinates const & coords)
    {
        return grid.at(coords.getY()).at(coords.getX());
    }

    template<class T>
    T const & Sea::Grid2D<T>::operator()(unsigned int x, unsigned int y) const
    {
        return grid.at(y).at(x);
    }

    template<class T>
    T & Sea::Grid2D<T>::operator()(unsigned int x, unsigned int y)
    {
        return grid.at(y).at(x);
    }

    // TODO Aufgabe 2:
    //  Implementiert hier die Funktion `walk(..)`.
    //  Sie soll die übergebene (Lambda-)Funktion `operation` einmal für jedes Element im Grid aufrufen.
    //  Es wird also mindestens eine Schleife (loop) benötigt, um über alle Elemente zu iterieren.


    template<class T>
    template<typename FunkL>

    void Sea::Grid2D<T>::walk(FunkL operation) const {
        //Es wird durch jede Zeile im Grid gelaufen
        for (const auto& row : grid) {
            //Innerhalb jeder Zeile wird durch alle Elemente gegangen
            for (const auto& elem : row) {
                //Übergebene Lambda Funktion wird auf das aktuelle Element angewendet
                operation(elem);
            }
        }
    }


    // TODO Aufgabe 2:
    //  Implementiert hier die Funktion `filter(..)`.
    //  Sie soll die übergebene (Lambda-)Funktion `condition` nutzen, um jedes Element zu prüfen.
    //  Alle Elemente, für die die Funktion "true" zurückgibt, sollen gesammelt in einem `vector` zurückgegeben werden.
    //  Es wird also mindestens eine Schleife (loop) benötigt, um über alle Elemente zu iterieren.
    //  Die Elemente in dem Ergebnis-`vector` sollen Kopien sein.

    template<class T>
    template<typename FunkL>

    std::vector<T> Sea::Grid2D<T>::filter (FunkL condition) const {
        //Elemente die Bedingungen erfüllen, werden hier gespeichert
        std::vector<T> result;


        for (const auto& row : grid) {
            for (const auto& elem : row) {
                //Aktuelles Element wird geprüft, ob es die Bedingung erfüllt
                if (condition(elem)) {
                    //Wenn Bedingung erfüllt -> wird Kopie gespeichert im Ergebnis Vektor
                    result.push_back(elem);
                }
            }

        }
        return result;
    }
