#include "Box.h";
#include <iostream>
/*
Il tipo di casella (box_type_) è specificato da questi numeri:
0 = Partenza
1 = Angolare
2 = Economica 6€
3 = Standard 10€
4 = Lusso 20€

Le costruzioni (box_construction_)invece sono specificate da:
0 = Terreno
1 = Casa
2 = Albergo

box_cost_ = costo per acquisto casella 
box_stay_cost_ = costo pernottamento
box_construction_ = tipo di costruzione presente sulla casella
*/

//Implementazione costruttori

Box::Box(int id, int tipo){
    //Inizialmente ogni casella rappresenta un terreno acquistabile
    //Assegnamento prezzo per acquisto
    this-> box_cost_ = assegnaCosto(this->box_type_);
}

Box::Box(int id, int tipo, int costruzioni){
    //Controllo il prezzo da assegnare alla casella, 
    this->box_cost_ = assegnaCosto(this->box_type_);
    //Controllo il prezzo da assegnare al pernottamento, se sono presenti costruzioni
    this->box_stay_cost_ = assegnaPernottamento(this->box_type_, this->box_construction_);
}

void Box::print_box_info(){
    std::string tipo_casella;
    std::string costruzioni_casella;

    //Switch-case per trovare il tipo di casella da stampare nel messaggio
    switch(this->box_type_){
        case 0:
            tipo_casella = "Partenza";
            break;
        case 1:
            tipo_casella = "Angolare";
            break;
        case 2:
            tipo_casella = "Economica";
            break;
        case 3:
            tipo_casella = "Standard";
            break;
        case 4:
            tipo_casella = "Lusso";
            break;
    }

    //Switch-case per trovare il tipo di costruzione presente sulla casella
    switch(this->box_construction_){
        case 0:
            costruzioni_casella = "Terreno";
            break;
        case 1:
            costruzioni_casella = "Casa";
            break;
        case 2:
            costruzioni_casella = "Albergo";
            break;
    }

    std::cout<< "Casella numero: "<< this->box_id_<<'\n'<<"Tipo casella: "<<tipo_casella<<'\n'<<"Costruzioni casella:"<<costruzioni_casella<<'\n'<<"Costo casella: "<<this->box_cost_<<'\n'<<"Costo pernottamento: "<<this->box_stay_cost_<<std::endl;
}

bool Box::build_on_box(){
    //Controllo che sulla casella non sia già presente un albergo, in tal caso non posso costruire
    if(this->box_construction_ == 2) return false;
    
    //Da Terreno passo a Casa
    if(this->box_construction_ == 0){
        this->box_construction_ = 1;
        this-> box_stay_cost_ = assegnaPernottamento(this->box_type_, this->box_construction_);
        return true;
    }

    //Da casa passo ad Albergo
    if(this->box_construction_ == 1){
        this->box_construction_ = 2;
        this->box_stay_cost_ = assegnaPernottamento(this->box_type_, this->box_construction_);
        return true;
    }
}


//Funzioni che restituisce il tipo di costruzione presente sulla casella
std::string Box::construction(){
    switch(this->box_construction_){
        case 0:
            return "Terreno";
            break;
        case 1:
            return "Casa";
            break;
        case 2:
            return "Albergo";
            break;
    }

}

char Box::getBoxType(){
    if(this->box_type_ = 0) return 'P';
    else if(this->box_type_ = 2) return 'E';
    else if(this->box_type_ = 3) return 'S';
    else if(this->box_type_ = 4) return 'L';
}

//Funzioni ausiliare

//Funzione per assegnare il costo ad una casella in base al tipo
int assegnaCosto(int tipo_casella_){
    //Se la casella è un terreno assegno i costi associati all'acquisto della casella
        if(tipo_casella_ = 2) return 6;
        else if(tipo_casella_= 3) return 10;
        else if(tipo_casella_ = 4) return 20;
        else return 0; //La casella è la partenza o è una casella angolare (quindi non acquistabili)
}

//Funzione per assegnare il costo del pernottamento in base al tipo di casella e alla struttura costruita sopra
int assegnaPernottamento(int tipo_casella_, int costruzioni_casella_){
        //Se nella casella è presente una casa (=1) associo i costi del pernottamento
    if(costruzioni_casella_=1) 
        if(tipo_casella_ = 2) return 2;
        else if(tipo_casella_ = 3) return 4;
        else return 7;

    //Altrimenti se è presente un castello (=2) associo i costi del pernottamento
    else{
        if(tipo_casella_= 2) return 4;
        else if(tipo_casella_= 3) return 8;
        else return 14;
    }

    return 0; //nel caso in cui non fossero presenti costruzioni il pernottamento è uguale a 0
}