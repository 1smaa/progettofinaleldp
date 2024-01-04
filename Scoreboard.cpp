#include "Scoreboard.h"
#include "Box.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>


//Numero totale di caselle nel tabellone
#define NUMERO_CASELLE 28

//Numero totale di ogni tipo di casella
#define NUMERO_CASELLE_ECONOMICHE 8
#define NUMERO_CASELLE_STANDARD 10
#define NUMERO_CASELLE_LUSSO 6

//Valori utilizzati per identificare il tipo di casella da generare in base al numero random uscito
#define RANDOM_CASELLA_E 0
#define RANDOM_CASELLA_S 1
#define RANDOM_CASELLA_L 2

//Valori utilizzati nei costruttori di Box per identificare il tipo di casella da creare (Economica, Standard, Lusso)
#define CASELLA_E 2
#define CASELLA_S 3
#define CASELLA_L 4

#define LARGHEZZA_CASELLA_STAMPA 10

void print_testata(std::stringstream& ss){
            ss     <<"0"
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  1  "
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  2  "
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  3  "
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  4  "
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  5  "
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  6  "
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  7  "
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  8  "<<std::endl;
}

std::string string_to_print(Box* box){
    
    std::string to_return;
    switch(box->getBoxType()){
        case 0: 
            to_return+="P";
            break;
        case 1:
            to_return+=" ";
            break;
        case 2:
            to_return+= "E";
            break;
        case 3:
            to_return+= "S";
            break;
        case 4:
            to_return+= "L";
            break;
    }

    switch(box->getBoxConstruction()){
        case 0:
            to_return+=" ";
            break;
        case 1:
            to_return+="*";
            break;
        case 2:
            to_return+="^";
            break;
    }
    //Per avere tutte le scritte centrate
    if(to_return.length()==2) to_return = "| "+to_return+"|"; 
    else{
        to_return = "|"+to_return+"|";
    }
    return to_return;
}

//Costruttore 
Scoreboard::Scoreboard(const std::vector<Player>& players_){
    this->players_ = players_;
    //Riservo lo spazio necessario per le 28 caselle
    this->board.reserve(NUMERO_CASELLE); 
    //Variabili utili per la creazione random delle caselle laterali
    int totCaselleEconomiche=0;
    int totCaselleStandard=0;
    int totCaselleLusso=0;
    int random_number=0;
    //Inizializzazione generatore casuale di numeri
    std::srand(std::time(NULL)); 
    //Creo le caselle da aggiungere al tabellone
    for(int i=0;i<NUMERO_CASELLE;i++){
        if(i==0){
            //Casella di partenza
            Box* b=new Box(i, 0);
            //Aggiungo la casella di partenza al vector
            board.push_back(b);
        }
        else if(i==7||i==14||i==21){ //Si tratta di una casella angolare in uno di questi casi
            //Creo le tre caselle angolari
            Box* b = new Box(i, 1);
            //Le aggiungo al vector
            board.push_back(b);
        }
        //Altrimenti si tratta di una casella laterale, quindi le genero casualmente
        else{
            /*Utilizzo un valore booleano per controllare che la casella venga effettivamente aggiunta al tabellone
                Altrimenti potrebbe succedere che il numero generato randomicamente corrisponda
                ad una casella che ha raggiunto il numero massimo (ad esempio 8 caselle economiche)
                Se dovesse succedere, senza il controllo con il valore booleano, l'iterazione del for si concluderebbe 
                ma nel vector non verrebbe aggiunto alcun valore.
            */

            bool aggiunto = false; 
            while(!aggiunto){ 
                random_number=(rand()%3); //Genero un numero random tra 0,1,2 
                if(random_number==RANDOM_CASELLA_E && totCaselleEconomiche<NUMERO_CASELLE_ECONOMICHE){
                    Box* b = new Box(i, CASELLA_E); //Creo la casella economica
                    totCaselleEconomiche++; //Incremento il numero di caselle economiche create
                    board.push_back(b); //Aggiungo la casella al tabellone
                    aggiunto = true;
                }
                if(random_number==RANDOM_CASELLA_S && totCaselleStandard<NUMERO_CASELLE_STANDARD){
                    Box* b = new Box(i, CASELLA_S); //Creo la casella Standard
                    totCaselleStandard++; //Incremento il numero di caselle standard create
                    board.push_back(b); //Aggiungo la casella al tabellone
                    aggiunto = true;
                }
                if(random_number==RANDOM_CASELLA_L && totCaselleLusso<NUMERO_CASELLE_LUSSO){
                    Box* b = new Box(i, CASELLA_L); //Creo la casella Lusso
                    totCaselleLusso++; //Incremento il numero di caselle lusso create
                    board.push_back(b); //Aggiungo la casella al tabellone
                    aggiunto = true;
                }
            }
        }
    }
}

std::string Scoreboard::print_scoreboard(){
    
    //Creo uno string stream così da poter formattare la stringa di output
    std::stringstream stream_string; 
    try{
        //Prima riga di stampa (coordinate numeriche)
        print_testata(stream_string);

        //Prima riga effettiva del tabellone
        stream_string<<"A";
        for(int i=14; i<=21; i++){
            if(i==14 ||i==21){
                stream_string<<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|   |";
            }
            else{
                //Ricavo il tipo di casella, PARTENZA, ECONOMICA, STANDARD, LUSSO
                stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(i));
            }
        }
        stream_string <<std::endl;
        
        
        //Seconda riga del tabellone
        stream_string <<"B";
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(13));
        for(int i=0; i<6; i++){
            stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"";
        }
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(21))<<std::endl;

        
        //Terza riga del tabellone
        stream_string <<"C";
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(12));
        for(int i=0; i<6; i++){
            stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<std::setfill(' ')<<"";
        }
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(22))<<std::endl;

        //Quarta riga del tabellone
        stream_string <<"D";
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(11));
        for(int i=0; i<6; i++){
            stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<std::setfill(' ')<<"";
        }
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(24))<<std::endl;

        //Quinta riga del tabellone
        stream_string <<"E";
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(10));
        for(int i=0; i<6; i++){
            stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<std::setfill(' ')<<"";
        }
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(25))<<std::endl;

        //Sesta riga del tabellone
        stream_string <<"F";
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(9));
        for(int i=0; i<6; i++){
            stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<std::setfill(' ')<<"";
        }
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(26))<<std::endl;

        //Settima riga del tabellone
        stream_string<<"G";
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(8));
        for(int i=0; i<6; i++){
            stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<std::setfill(' ')<<"";
        }
        stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(27))<<std::endl;

        //Ottava riga del tabellone
        stream_string<<"H";
        for(int i=7; i>=0; i--){
            if(i==7){
                stream_string<<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|   |";
            }
            else{
                //Ricavo il tipo di casella, PARTENZA, ECONOMICA, STANDARD, LUSSO
                stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(board.at(i));
            }
        }
        
        stream_string<<std::endl;
    }catch(std::out_of_range){
        std::cout<<"ERRORE"<<std::endl;
    }
    return stream_string.str();
}

Box* Scoreboard::getBox(int id_box){
    try{
        return board.at(id_box);
    }catch(std::out_of_range){
        throw std::invalid_argument("Valore casella non valido!");
    }

}