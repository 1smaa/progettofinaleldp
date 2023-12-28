#ifndef FUNCTION_BOX_H
#define FUNCTION_BOX_H

namespace Box{
    class Box{
        public:
        //Costruttori
            Box(int id);


        //Bozza di funzioni
            void print_box_info(); //Stampa le informazioni della casella

            bool build_on_box(); //Costruisce su una casella e ritorna un valore booleano

            int pernottamento();   //Ritorna il costo del pernottamento

            int costruzioni(); //Ritorna le costruzioni presenti sulla casella


        private:
    };
}


#endif/*FUNCTION_CASELLA_H*/