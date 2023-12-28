#ifndef FUNCTION_BOX_H
#define FUNCTION_BOX_H

namespace Box{

    class Box{

        protected:
            //Definisce il tipo di casella: Economica, Standard, Lusso
            int box_type_;

            //Definisce l'id per identificare la casella nel tabellone
            int id_box_;

            //Definisce il tipo di costruzione presente sulla casella
            int box_construction_;

            //Definisce il costo associato alla casella
            int box_cost_;

        public:
            //Costruttore di default
            Box() : box_type_(0), id_box_(0), box_construction_(0), box_cost_(0){}; //DA VALUTARE??

            //Costruttori con parametri    
            Box(int id) : id_box_(id) {};
            Box(int id, int tipo) : id_box_(id), box_type_(tipo){};
            Box(int id, int tipo, int costruzioni) : id_box_(id), box_type_(tipo), box_construction_(costruzioni){};

            //Costruttori di copia e spostamento
            //Box(const Box&) = delete;


            //Funzioni per settare le variabili protected
            void setBoxType(int type){this->box_type_ = type; };
            void setIdBox(int id){this->id_box_ = id; };
            void setBoxConstruction(int construction){this->box_construction_ = construction;};
            void setBoxCost(int cost){this->box_cost_ = cost; };

            //Funzioni per return variabili protected

            int getBoxType(){return this->box_type_;};
            int getIdBox(){return this->id_box_;};
            int getBoxConstruction(){return this-> box_construction_;};
            int getBoxCost(){return this->box_cost_;};

        //Bozza di funzioni
            void print_box_info(); //Stampa le informazioni della casella

            bool build_on_box(); //Costruisce su una casella e ritorna un valore booleano

            int pernottamento();   //Ritorna il costo del pernottamento

            int costruzioni(); //Ritorna le costruzioni presenti sulla casella

    };
}


#endif/*FUNCTION_BOX_H*/