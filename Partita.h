#ifndef PARTITA_H
#define PARTITA_H

#include "Dadi.h"
#include "Player.h"
#include "Scoreboard.h"
#include <vector>
#include <string>

class Partita{
private:
    std::vector<Player> giocatori;
    Scoreboard::Scoreboard tabellone;
    int turno;
    std::string s;
    Dadi d;

public: 
    //costruttori
    Partita(const std::vector<Player::Player>& giocatori, const Scoreboard::Scoreboard& tabellone);
    Partita(const std::vector<Player::Player>& giocatori, const Scoreboard::Scoreboard& tabellone, int turno);
    //costruttore di copia
    Partita(const Partita&);
    //costruttore di spostamento
    Partita(Partita&&);

    //funzioni
    int inizia();
    int prossimoTurno();
    bool terminata() const;
    std::string log() const;
    std::vector<Player::Player>vincitore() const;

};
#endif
