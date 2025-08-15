#include "PlayerSea.h"

#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::max;

#include "Output.h"
using GameObjects::OutputGridCell;


namespace GameObjects {

    unsigned int numShipPositionsUnhit(OutputGrid const & grid)
    {
        // TODO Aufgabe 3:
        //  Nutzt `grid.filter(..)`, um die Spielfeld-Positionen herauszufiltern, an denen ein Schiff liegt aber keine Rakete getroffen hat.
        //  Gebt danach die Anzahl der Elemente in dem gefilterten `vector` als Ergebnis zurück.

        return  grid.filter([](OutputGridCell const & cell) {
            return cell.ship && cell.missiles == 0;
        }).size();
    }

    unsigned int numWaterPositionsHit(OutputGrid const & grid)
    {
        // TODO Aufgabe 3:
        //  Nutzt `grid.filter(..)`, um die Spielfeld-Positionen zu herauszufiltern, an denen mindestens eine Rakete ins Wasser getroffen hat.
        //  Gebt davon wieder die Anzahl zurück.
        return grid.filter([](OutputGridCell const & cell)
        {
            return !cell.ship && cell.missiles > 0;
        }).size();
    }

    unsigned int numMaxMissilesPerPosition(OutputGrid const & grid)
    {
        unsigned int maxMissiles = 0;
        // TODO Aufgabe 3:
        //  Nutzt `grid.walk(..)` und die *Capture Clause* einer Lambda-Funktion, um die Spielfeld-Position mit den meisten Raketen zu ermitteln.
        //  Zurückgegeben werden soll die Anzahl der Elemente auf der Position.
        //  Also, wie viele Raketen haben maximal ein und das selbe Feld getroffen?

        grid.walk([&maxMissiles](OutputGridCell const & cell)
            {
            if (cell.missiles > maxMissiles )
                {
                maxMissiles = cell.missiles;
            }
        });
        return maxMissiles;
    }

    // TODO Aufgabe 4:
    //  Implementiert eine neue Funktion `numMultipleHits(..)`.
    //  Ermittelt darin, wie vielen Spielfeld-Positionen mit einem Schiff, von mehr als einer Rakete getroffen wurden.
    //  Ermittelt außerdem, von wie vielen Raketen diese Felder insgesamt getroffen wurden.
    //  Als Ergebnis der Funktion sollen beide Werte als `std::pair` zurückgegeben werden.

    std::pair<unsigned int, unsigned int>numMultipleHits(OutputGrid const & grid)
    {
        unsigned int numMultipleHitMissiles = 0;
        unsigned int numMultipleHitPositions = 0;

        //Geht über alle Felder des Spielfeldes
        grid.walk([&](OutputGridCell const & cell)
        {
            //Prüft, ob ein Schiff auf dem Feld liegt und ob es von mehr als einer Rakete getroffen wurde
            if (cell.ship && cell.missiles > 1)
            {
                //Zählt, wie viele Positionen Mehrfachtreffer haben
                numMultipleHitPositions++;
                // Zählt die Anzahl aller Raketen auf diesen Positionen
                numMultipleHitMissiles += cell.missiles;
            }
        });
            return std::pair{numMultipleHitPositions, numMultipleHitMissiles};
    }

    void PlayerSea::printStats() const
    {
        // TODO Aufgabe 4:
        //  verwendet die neue Funktion `numMultipleHits(..)`, um `numMultipleHitMissiles` und `numMultipleHitPositions` mit den korrekten Werten zu belegen.
        auto multipleHits = numMultipleHits(gridOwnSea);
        unsigned int numMultipleHitMissiles = multipleHits.first;
        unsigned int numMultipleHitPositions = multipleHits.second;


        cout << numShipPositionsUnhit(gridOwnSea) << " Position(en) der eigenen Schiffe sind ungetroffen" << endl;
        cout << numMultipleHitMissiles << " Mehrfach-Treffer auf " << numMultipleHitPositions << " Schiffsposition(en) des Gegners" << endl;
        cout << "Maximal " << numMaxMissilesPerPosition(gridOtherSea) << " Treffer auf der selben Position" << endl;
        cout << numWaterPositionsHit(gridOtherSea) << " Wasserposition(en) getroffen" << endl;
    }

}