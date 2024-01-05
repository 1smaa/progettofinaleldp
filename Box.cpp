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

//Definisco i prezzi qui così che, se si volessero cambiare per modificare le meccaniche di gioco, è possibile farlo velocemente modificando solo i valori
// riportati qui sotto, senza mettere mani al codice.


//Define dei tipi casella
#define CASELLA_PARTENZA 0
#define CASELLA_ANGOLARE 1
#define CASELLA_ECONOMICA 2
#define CASELLA_STANDARD 3
#define CASELLA_LUSSO 4

//Define costruzioni
#define COSTRUZIONE_TERRENO 0
#define COSTRUZIONE_CASA 1
#define COSTRUZIONE_ALBERGO 2

//Define prezzi acquisto e pernottamento su caselle
#define ACQUISTO_ECONOMICA 6
#define ACQUISTO_STANDARD 10
#define ACQUISTO_LUSSO 20

#define PERNOTTAMENTO_CASA_ECONOMICA 2
#define PERNOTTAMENTO_CASA_STANDARD 4
#define PERNOTTAMENTO_CASA_LUSSO 7

#define PERNOTTAMENTO_ALBERGO_ECONOMICA 4
#define PERNOTTAMENTO_ALBERGO_STANDARD 8
#define PERNOTTAMENTO_ALBERGO_LUSSO 14

//Funzioni ausiliare

//Funzione per assegnare il costo ad una casella in base al tipo
int assegnaCosto(int& tipo_casella_){
    //Se la casella è un terreno assegno i costi associati all'acquisto della casella
        if(tipo_casella_ = CASELLA_ECONOMICA) return ACQUISTO_ECONOMICA;
        else if(tipo_casella_= CASELLA_STANDARD) return ACQUISTO_STANDARD;
        else if(tipo_casella_ = CASELLA_LUSSO) return ACQUISTO_LUSSO;
        else return 0; //La casella è la partenza o è una casella angolare (quindi non acquistabili)
}

//Funzione per assegnare il costo del pernottamento in base al tipo di casella e alla struttura costruita sopra
void Box::setBoxStayCost(){
        //Se nella casella è presente una casa (=1) associo i costi del pernottamento
    if(this->box_construction_= COSTRUZIONE_CASA) 
        if(this->box_type_= CASELLA_ECONOMICA) this->box_stay_cost_= PERNOTTAMENTO_CASA_ECONOMICA;
        else if(this->box_type_ = CASELLA_STANDARD) this->box_stay_cost_ =PERNOTTAMENTO_CASA_STANDARD;
        else this->box_stay_cost_= PERNOTTAMENTO_CASA_LUSSO;

    //Altrimenti se è presente un castello (=2) associo i costi del pernottamento
    else{
        if(this->box_type_= CASELLA_ECONOMICA) this->box_stay_cost_= PERNOTTAMENTO_ALBERGO_ECONOMICA;
        else if(this->box_type_= CASELLA_STANDARD) this->box_stay_cost_= PERNOTTAMENTO_ALBERGO_ECONOMICA;
        else this->box_stay_cost_ = PERNOTTAMENTO_ALBERGO_LUSSO;
    }

    this->box_stay_cost_ = 0; //nel caso in cui non fossero presenti costruzioni il pernottamento è uguale a 0
}


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
    this->setBoxStayCost();
}

void Box::print_box_info(){
    std::string tipo_casella;
    std::string costruzioni_casella;

    //Switch-case per trovare il tipo di casella da stampare nel messaggio
    switch(this->box_type_){
        case CASELLA_PARTENZA:
            tipo_casella = "Partenza";
            break;
        case CASELLA_ANGOLARE:
            tipo_casella = "Angolare";
            break;
        case CASELLA_ECONOMICA:
            tipo_casella = "Economica";
            break;
        case CASELLA_STANDARD:
            tipo_casella = "Standard";
            break;
        case CASELLA_LUSSO:
            tipo_casella = "Lusso";
            break;
    }

    //Switch-case per trovare il tipo di costruzione presente sulla casella
    switch(this->box_construction_){
        case COSTRUZIONE_TERRENO:
            costruzioni_casella = "Terreno";
            break;
        case COSTRUZIONE_CASA:
            costruzioni_casella = "Casa";
            break;
        case COSTRUZIONE_ALBERGO:
            costruzioni_casella = "Albergo";
            break;
    }

    std::cout<< "Casella numero: "<< this->box_id_<<'\n'<<"Tipo casella: "<<tipo_casella<<'\n'<<"Costruzioni casella:"<<costruzioni_casella<<'\n'<<"Costo casella: "<<this->box_cost_<<'\n'<<"Costo pernottamento: "<<this->box_stay_cost_<<std::endl;
}

bool Box::build_on_box(){
    //Controllo che sulla casella non sia già presente un albergo, in tal caso non posso costruire
    //controllo che non sia una casella laterale o la partenza
    if(this->box_construction_ == 2||this->box_id_==0 ||this->box_id_ ==7||this->box_id_ ==14||this->box_id_ ==21) return false;
    
    //Da Terreno passo a Casa
    if(this->box_construction_ == COSTRUZIONE_TERRENO){
        this->box_construction_ = COSTRUZIONE_CASA;
        this->setBoxStayCost();
        return true;
    }

    //Da casa passo ad Albergo
    if(this->box_construction_ == COSTRUZIONE_CASA){
        this->box_construction_ = COSTRUZIONE_ALBERGO;
        this->setBoxStayCost();;
        return true;
    }
    return false; //Nel caso in cui non venisse costruito viene ritornato false di default
}


//Funzioni che restituisce il tipo di costruzione presente sulla casella
std::string Box::construction(){
    switch(this->box_construction_){
        case COSTRUZIONE_TERRENO:
            return "Terreno";
            break;
        case COSTRUZIONE_CASA:
            return "Casa";
            break;
        case COSTRUZIONE_ALBERGO:
            return "Albergo";
            break;
    }
    return "";

}


