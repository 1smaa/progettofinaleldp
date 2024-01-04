#ifndef FUNCTION_BOX_H
#define FUNCTION_BOX_H
#include "Player.h"

    class Box{

        public:
            
            //Costruttori    
            Box(int id, int tipo) : box_id_(id), box_type_(tipo), box_construction_(0), box_stay_cost_(0),owner_{nullptr}{}
            Box(int id, int tipo, int costruzioni) : box_id_(id), box_type_(tipo), box_construction_(costruzioni), owner_{nullptr}{}

            //Costruttori di copia e spostamento
            //Box(const Box&) = delete;


            //Funzioni per settare le variabili protected
            void setBoxType(int type){this->box_type_ = type; }
            void setIdBox(int id){this->box_id_ = id; }
            void setBoxConstruction(int construction){this->box_construction_ = construction;}
            void setBoxCost(int cost){this->box_cost_ = cost; }
            void setOwner(Player* owner){this->owner_ = owner;}

            //Funzioni per return variabili protected

            int getBoxType(){return this->box_type_;}
            int getIdBox(){return this->box_id_;}
            int getBoxConstruction(){return this-> box_construction_;}
            int getBoxCost(){return this->box_cost_;}
            Player* getOwner(){return this->owner_;};

        //Bozza di funzioni
            void print_box_info(); //Stampa le informazioni della casella

            bool build_on_box(); //Costruisce su una casella e ritorna un valore booleano

            int pernottamento(){return this->box_stay_cost_;}   //Ritorna il costo del pernottamento

            std::string construction(); //Ritorna le costruzioni presenti sulla casella

        protected:
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



#endif/*FUNCTION_BOX_H*/