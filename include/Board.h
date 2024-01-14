#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <functional>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "Dadi.h"
#include "BoardExceptions.h"

/*
*   LORENZON ISMAELE
*/

using uint = unsigned int;

namespace Board{
    class Player;
    class Box{
    public:
        //Costruttori
        Box(int id, int tipo);
        Box(int id, int tipo, int costruzioni);

        //Funzioni per settare le variabili private
        void setBoxType(int type){
            if(type<0||type>4) throw BoxError("Casella non valida.");
            this->box_type_ = type;
        }
        void setBoxConstruction(int construction){ 
            if(construction<0||construction>2) throw BoxError("Costruzione non valida.");
            this->box_construction_ = construction;
        }
        void setBoxCost(int cost){this->box_cost_ = cost; }
        void setOwner(Player* owner){this->owner_ = owner;}
        void setBoxStayCost();

        //Funzioni per return variabili protected
        int getBoxType() const { return this->box_type_; }
        int getIdBox() const { return this->box_id_; }
        int getBoxConstruction() const { return this-> box_construction_; }
        int getBoxCost() const { return this->box_cost_; }
        int getBoxStayCost() const { return this->box_stay_cost_; }
        Player* getOwner() const { return this->owner_; }
        std::string getCoordinates() const { return this->coordinates; };

        //Funzioni
        
        //Stampa a schermo informazioni generali della casella
        void print_box_info() const;

        //Costruisce su una casella senza effettuare controlli (poiché già effettuati nella classe player), ritorna un valore booleano per identificare
        //la buona riuscita
        bool build_on_box();

        //Ritorna le costruzioni presenti sulla casella
        std::string construction() const ;


    private:
        int assegnaCosto(int tipo_casella_);
        std::string to_coordinates() const;
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

        std::string coordinates;
    };
    class Board;
    class Player{
    protected:
        // saldo del giocatore
        int saldo;
        // posizione del giocatore
        uint pos;
        // id del giocatore
        uint id;
        // vector di caselle associate al giocatore
        std::vector<Box*> squares;
        std::map<int,std::vector<int>> costs;
        bool isCommand(std::string s);
        std::map<int,std::vector<int>> initialize_costs() const;
        std::string processBuy(Board& board,Box* box);
        std::string processBuild(Board& board,Box* box);
        std::string processStay(Board& board,Box* box);
        //funzione virtuale per gestire le decisioni del giocatore
        virtual bool decide(std::string& question,Board& b) = 0;
        void log(std::string& log,std::string s);
    public:
        // costruttori parametrizzati
        explicit Player(uint id): id(id), pos(0), saldo(0), costs(initialize_costs()) { srand(time(NULL)); };
        Player(uint id,int saldo): id(id), pos(0), saldo(saldo), costs(initialize_costs()) { srand(time(NULL)); };
        Player(uint id,int saldo,uint pos): id(id), pos(pos), saldo(saldo), costs(initialize_costs()) { 
            srand(time(NULL));
            if(this->pos<0||this->pos>27){
                throw PositionError(this->pos); 
            }
        };
        // cancellazione costruttori di copia per ovviare a problemi di slicing
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
        // funzione virtuale che gestisce la mossa del giocatore
        std::string move(Board& s,Dadi& d);
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
        bool isMine(Box& s) const;
        std::string logConstruction();
        virtual ~Player(){};
    };
    class Computer : public Player{
    private:
        bool decide(std::string& question,Board& b) override;
    public:
        explicit Computer(uint id) : Player(id){};
        Computer(uint id,int saldo) : Player(id,saldo){};
        Computer(uint id,int saldo,uint pos): Player(id,saldo,pos){};
    };
    class Human : public Player{
    private:
        bool decide(std::string& question,Board& b) override;
    public:
        explicit Human(uint id) : Player(id){};
        Human(uint id,int saldo) : Player(id,saldo){};
        Human(uint id,int saldo,uint pos): Player(id,saldo,pos){};
    };
    class Board{
    public:
        //Costruttore di default
        Board() : players_(std::vector<Player*>{}), board(std::vector<Box*>{}){};
        //Costruttore parametrizzato
        explicit Board(std::vector<Player*>& players_);
        //Ottieni la casella ad un determinato indice
        Box* getBox(int id_box) const; 
        //Stampa il tabellone
        std::string print_board();
        //Ottieni i giocatori
        std::vector<Player*> getPlayers() const { return this->players_; }
        //Stampa le costruzioni dei giocatori
        std::string print_player_costruction() const;
           
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