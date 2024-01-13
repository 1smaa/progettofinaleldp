#ifndef PARTITA_H
#define PARTITA_H

#include "Dadi.h"
#include "Board.h"
#include <vector>
#include <string>
#include <ostream>
#include <algorithm>

/*
*   CIAN IRENE
*/

class Partita{
private:
    std::vector<Board::Player*> giocatori;
    Board::Board* tabellone;
    int turno;
    int prossimoGiocatore;
    std::string s;
    Dadi d;

public: 
    //costruttori
    Partita(std::vector<Board::Player*>& giocatori, Board::Board* tabellone);
    Partita(std::vector<Board::Player*>& giocatori, Board::Board* tabellone, int turno); 

    //funzioni
    int inizia();
    int prossimoTurno();
    bool terminata() const;
    std::string log() const;
    std::vector<Board::Player*>vincitore() const;

};
#endif
