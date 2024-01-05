#ifndef FUNCTION_BOX_H
#define FUNCTION_BOX_H
#include "Player.h"

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