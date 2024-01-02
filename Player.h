#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <functional>
#include <map>
#include <string>
#include "Box.h"
#include "Scoreboard.h"
#include "Dadi.h"

#define uint unsigned int

class Player{
protected:
    // tipo di giocatore
    bool automate;
    // saldo del giocatore
    int saldo;
    // posizione del giocatore
    uint pos;
    // id del giocatore
    uint id;
    // vector di caselle associate al giocatore
    std::vector<Box> squares;
    // mappa per l'interpretazione dei comandi
    std::map<std::string,std::function<void(Scoreboard::Scoreboard s)>> initialize_commands();
    bool isCommand(std::string s);
    std::map<std::string,std::function<void(Scoreboard::Scoreboard s)>> commands;
    //funzione virtuale per gestire le decisioni del giocatore
    bool decide(std::string question);
    bool human_decide(std::string question);
    bool computer_decide(std::string question);
public:
    // costruttore di default
    Player(bool automate) : automate(automate), id(0), pos(0), saldo(0), commands(this->initialize_commands()){};
    // costruttori parametrizzati
    Player(bool automate,uint id): automate(automate),id(id), pos(0), saldo(0), commands(this->initialize_commands()){};
    Player(bool automate,uint id,int saldo): automate(automate),id(id), pos(0), saldo(saldo), commands(this->initialize_commands()){};
    Player(bool automate,uint id,int saldo,uint pos): automate(automate),id(id), pos(pos), saldo(saldo), commands(this->initialize_commands()){};
    // funzione virtuale che gestisce la mossa del giocatore
    virtual std::string move(Scoreboard::Scoreboard s,Dadi d);
    // restituisce 1 (true) se il giocatore è ancora in gioco, 0 (false) se è stato eliminato
    bool inPlay(){ return this->saldo>=0; };
    // funzioni per settare le variabili del player
    void setPos(uint newPos){ this->pos=newPos; };
    void modifySaldo(int s){ this->saldo+=s; };
    //funzioni per ottenere le variabili dei player
    uint getId(){ return this->id; };
    uint getPos(){ return this->pos; };
    uint getSaldo(){ return this->saldo; };
    // restituisce 1 (true) se la casella è in possesso del giocatore, 0 (false) altrimenti
    bool isMine(Box s);
};

#endif