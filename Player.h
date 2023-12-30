#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <functional>
#include <map>
#include <string>
#include "Box.h"
#include "Scoreboard.h"

#define uint unsigned int

namespace Player{
    /*
    *   Classe virtuale madre
    */
    class Player{
    protected:
        // saldo del giocatore
        int saldo;
        // posizione del giocatore
        uint pos;
        // id del giocatore
        uint id;
        // vector di caselle associate al giocatore
        std::vector<Box> squares;
        //funzione virtuale per gestire le decisioni del giocatore
        virtual bool decide() = 0;
    public:
        // costruttore di default
        Player() : id(0), pos(0), saldo(0){};
        // costruttori parametrizzati
        Player(uint id): id(id), pos(0), saldo(0){};
        Player(uint id,int saldo): id(id), pos(0), saldo(saldo){};
        Player(uint id,int saldo,uint pos): id(id), pos(pos), saldo(saldo){};
        // cancellazione costruttori di copia e overload operatore di copia
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
        // funzione virtuale che gestisce la mossa del giocatore
        virtual uint move(Scoreboard::Scoreboard s) = 0;
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
        // distruttore virtuale
        virtual ~Player(){};
        
    };
    class Human : public Player{
    private:
        // mappa per l'interpretazione dei comandi
        std::map<std::string,std::function<void(Scoreboard::Scoreboard s)>> commands;
        // logica di decisione per azioni interattive ( via terminal )
        bool decide() override;
        // initializza la mappa dei comandi
        std::map<std::string,std::function<void(Scoreboard::Scoreboard s)>> initialize_commands();
        // restituisce 1 (true) se la stringa è un comando, 0 (false) altrimenti
        bool isCommand(std::string s);
    public:
        // costruttore di default
        Human() : Player(), commands(this->initialize_commands()){};
        // costruttori parametrizzati
        Human(uint id): Player(id), commands(this->initialize_commands()){};
        Human(uint id,int saldo): Player(id,saldo), commands(this->initialize_commands()){};
        Human(uint id,int saldo,uint pos): Player(id,saldo,pos), commands(this->initialize_commands()){};
        // genera la prossima mossa
        uint move(Scoreboard::Scoreboard s) override;
    };
    class Computer : public Player{
    private:
        // logica di decisione per azioni automatiche
        bool decide() override;
    public:
        // genera la prossima mossa
        uint move(Scoreboard::Scoreboard s) override;
    };
}

#endif