#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <iostream>
#include <vector>
#include <sstream>


class Scoreboard{
    public:
        //Costruttori
        Scoreboard(const std::vector<Player>& players_);

        Box* getBox(int id_box); 

        std::string print_scoreboard();

        void print_player_costruction();
            
    protected:

        //Si potrebbero utilizzare gli array visto che si conoscono le dimensioni effettive (e non venogno modificate)
        //Ma per semplicità di gestione della memoria utlizziamo gli std::vector
        std::vector<Player> players_; 
        std::vector<Box*> board;

    //Funzioni private utili alla stampa del tabellone
    private:
        void print_testata(std::stringstream& ss);
        std::string string_to_print(Box* box, std::vector<Player>& player);
        void print_blank_space(std::stringstream& ss);
};
    
    //Overloading operatore << per permettere la stampa del tabellone con le informazioni corrette  
   // std::ostream& operator<<(std::ostream& out, const Scoreboard& scoreboard);


#endif