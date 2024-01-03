#ifndef PARTITA_H
#define PARTITA_H

#include "Dado.h"
#include "Player.h"
#include "Scoreboard.h"
#include <vector>
#include <string>

class Partita{
private:
    std::vector<Player> giocatori;
    Scoreboard tabellone;
    int turno;
    int prossimoGiocatore;
    std::string s;
    Dado d;

public: 
    //costruttori
    Partita(const std::vector<Player>& giocatori, const Scoreboard& tabellone);
    Partita(const std::vector<Player>& giocatori, const Scoreboard& tabellone, int turno);
    //costruttore di copia
    Partita (const Partita& ) 
    //costruttore di spostamento
    Partita (Partita&& ) 

    //funzioni
    int inizia();
    int prossimoTurno();
    bool terminata() const;
    std::string log() const;
    std::vector<Player>vincitore() const;

};
#endif
