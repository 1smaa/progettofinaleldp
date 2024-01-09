#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include "Dadi.h"

using uint = unsigned int;
namespace Board{
    class Player;
    class Box{
    public:
        //Costruttori
        Box(int id, int tipo);
        Box(int id, int tipo, int costruzioni);

        //Funzioni per settare le variabili protected
        void setBoxType(int type){this->box_type_ = type; }
        void setIdBox(int id){this->box_id_ = id; }
        void setBoxConstruction(int construction){this->box_construction_ = construction;}
        void setBoxCost(int cost){this->box_cost_ = cost; }
        void setOwner(Player* owner){this->owner_ = owner;}
        void setBoxStayCost();

        //Funzioni per return variabili protected
        int getBoxType(){return this->box_type_;}
        int getIdBox(){return this->box_id_;}
        int getBoxConstruction(){return this-> box_construction_;}
        int getBoxCost(){return this->box_cost_;}
        int getBoxStayCost(){return this->box_stay_cost_;}
        Player* getOwner(){return this->owner_;};

        //Funzioni
        
        //Stampa a schermo informazioni generali della casella
        void print_box_info();

        //Costruisce su una casella senza effettuare controlli (poiché già effettuati nella classe player), ritorna un valore booleano per identificare
        //la buona riuscita
        bool build_on_box();

        //Ritorna le costruzioni presenti sulla casella
        std::string construction();

    private:
        int assegnaCosto(int& tipo_casella_);
        //Definisce il tipo di casella: Economica, Standard, Lusso
        int box_type_;

        //Definisce l'id per identificare la casella nel tabellone
        int box_id_;

        //Definisce il tipo di costruzione presente sulla casella
        int box_construction_;

        //Definisce il costo associato alla casella
        int box_cost_;

        //Costo associato al pernottamento
        int box_stay_cost_;

        //Indica il possessore della casella.
        Player* owner_; 
    };
    class Board;
    class Player{
    private:
        // tipo di giocatore
        bool automate;
        // saldo del giocatore
        int saldo;
        // posizione del giocatore
        uint pos;
        // id del giocatore
        uint id;
        // vector di caselle associate al giocatore
        std::vector<Box*> squares;
        bool isCommand(std::string s);
        //funzione virtuale per gestire le decisioni del giocatore
        bool decide(std::string question);
        bool human_decide(std::string question);
        bool computer_decide(std::string question);
        std::string to_coordinates(int index);
    public:
        // costruttore di default
        explicit Player(bool automate) : automate(automate), id(0), pos(0), saldo(0){};
        // costruttori parametrizzati
        Player(bool automate,uint id): automate(automate),id(id), pos(0), saldo(0){ srand(time(NULL)); };
        Player(bool automate,uint id,int saldo): automate(automate),id(id), pos(0), saldo(saldo){ srand(time(NULL)); };
        Player(bool automate,uint id,int saldo,uint pos): automate(automate),id(id), pos(pos), saldo(saldo){ srand(time(NULL)); };
        // funzione virtuale che gestisce la mossa del giocatore
        std::string move(Board s,Dadi d);
        // restituisce 1 (true) se il giocatore è ancora in gioco, 0 (false) se è stato eliminato
        bool inPlay() const { return this->saldo>=0; };
        // funzioni per settare le variabili del player
        void setPos(uint newPos){ this->pos=newPos; };
        void modifySaldo(int s){ this->saldo+=s; };
        //funzioni per ottenere le variabili dei player
        uint getId() const { return this->id; };
        uint getPos() const { return this->pos; };
        uint getSaldo() const { return this->saldo; };
        // restituisce 1 (true) se la casella è in possesso del giocatore, 0 (false) altrimenti
        bool isMine(Box s);
        std::string logConstruction();
    };
    class Board{
    public:
        //Costruttori
        Board() : players_(std::vector<Player*>{}), board(std::vector<Box*>{}){};
        Board(std::vector<Player*>& players_);

        Box* getBox(int id_box); 

        std::string print_board();
        std::vector<Player*> getPlayers() { return this->players_; }

        void print_player_costruction();
           
    private:
        std::vector<Player*> players_; 
        std::vector<Box*> board;
        void print_testata(std::stringstream& ss);
        std::string string_to_print(Box* box, std::vector<Player*>& player);
        void print_blank_space(std::stringstream& ss);
    };
    // mappa per l'interpretazione dei comandi
    extern std::map<std::string,std::function<void(Board& s)>> COMMANDS;
}


#endif