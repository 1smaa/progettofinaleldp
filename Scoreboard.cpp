#include "Scoreboard.h"
#include "Box.h"
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>

#define CASELLE_ECONOMICHE 8
#define CASELLE_STANDARD 10
#define CASELLE_LUSSO 6

//Valori utilizzati per identificare il tipo di casella da generare in base al numero random uscito
#define RANDOM_CASELLA_E 0
#define RANDOM_CASELLA_S 1
#define RANDOM_CASELLA_L 2

//Valori utilizzati nei costruttori di Box per identificare il tipo di casella da creare (Economica, Standard, Lusso)
#define CASELLA_E 2
#define CASELLA_S 3
#define CASELLA_L 4

#define LARGHEZZA_CASELLA_STAMPA 10

//Costruttore di default (unico costruttore presente)
Scoreboard::Scoreboard(){

    //Riservo lo spazio necessario per le 28 caselle
    board.reserve(28); 
    
    //Variabili utili per la creazione random delle caselle laterali
    int totCaselleEconomiche = 0;
    int totCaselleStandard = 0;
    int totCaselleLusso = 0;
    //Inizializzazione generatore casuale di numeri
    std::srand(std::time(NULL)); 

    //Creo le caselle da aggiungere al tabellone
    for(int i=0; i<28; i++){
        if(i = 0){
            Box* b = new Box(i, 0); //Casella di partenza
            //Aggiungo la casella di partenza al vector
            board.push_back(b);
        }
        else if(i == 7 || i == 14 || i == 21){ //Si tratta di una casella angolare in uno di questi casi
            Box* b = new Box(i, 1); //Creo le tre casella angolari 
            //Le aggiungo al vector
            board.push_back(b);
        }
        else{ //Altrimenti si tratta di una casella laterale, le genero casualmente
            int random_number = (rand()%3); //Genero un numero random tra 0,1,2 
            if(random_number == RANDOM_CASELLA_E && totCaselleEconomiche < CASELLE_ECONOMICHE){
                Box* b = new Box(i, CASELLA_E); //Creo la casella economica
                totCaselleEconomiche++; //Incremento il numero di caselle economiche create
                board.push_back(b); //Aggiungo la casella al tabellone
            }
            else if(random_number == RANDOM_CASELLA_S && totCaselleStandard < CASELLE_STANDARD){
                Box* b = new Box(i, CASELLA_S); //Creo la casella Standard
                totCaselleStandard++; //Incremento il numero di caselle standard create
                board.push_back(b); //Aggiungo la casella al tabellone
            }
            else if(random_number == RANDOM_CASELLA_L && totCaselleLusso < CASELLE_LUSSO){
                Box* b = new Box(i, CASELLA_L); //Creo la casella Lusso
                totCaselleLusso++; //Incremento il numero di caselle lusso create
                board.push_back(b); //Aggiungo la casella al tabellone
            }

        }
    }
}

std::string Scoreboard::print_scoreboard(){

    //Creo uno string stream così da poter formattare la stringa di output
    std::stringstream stream_string; 
    std::string string_to_print;

    //stream_string<<std::setfill(' '); //Così che vengano fuori gli spazi nella casella vuota
    //Prima riga di stampa (coordinate numeriche)
    stream_string   <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"0"
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "1"
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "2"
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "3"
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "4"
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "5"
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "6"
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "7"
                    <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "8"<<std::endl;
    

    //Prima riga effettiva del tabellone
    stream_string<<"A";
    for(int i=14; i<=21; i++){
        if(i==14 || i == 21){
            stream_string   <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"||";
        }
        else{
            //Ricavo il tipo di casella, PARTENZA, ECONOMICA, STANDARD, LUSSO
            stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[i]->getBoxType()<<"|";
        }
    }
    stream_string <<std::endl;
    
    //Seconda riga del tabellone
    stream_string <<"B";
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[13]->getBoxType()<<"|";
    for(int i=0; i<6; i++){
         stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<std::setfill(' ');
    }
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[22]->getBoxType()<<"|"<<std::endl;

    
    //Terza riga del tabellone
    stream_string <<"C";
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[12]->getBoxType()<<"|";
    for(int i=0; i<6; i++){
         stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<std::setfill(' ');
    }
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[23]->getBoxType()<<"|"<<std::endl;

    //Quarta riga del tabellone
    stream_string <<"D";
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[11]->getBoxType()<<"|";
    for(int i=0; i<6; i++){
         stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<std::setfill(' ');
    }
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[24]->getBoxType()<<"|"<<std::endl;

    //Quinta riga del tabellone
    stream_string <<"E";
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[10]->getBoxType()<<"|";
    for(int i=0; i<6; i++){
         stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<std::setfill(' ');
    }
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[25]->getBoxType()<<"|"<<std::endl;

    //Sesta riga del tabellone
    stream_string <<"F";
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[9]->getBoxType()<<"|";
    for(int i=0; i<6; i++){
         stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<std::setfill(' ');
    }
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[26]->getBoxType()<<"|"<<std::endl;

    //Settima riga del tabellone
    stream_string<<"G";
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[8]->getBoxType()<<"|";
    for(int i=0; i<6; i++){
         stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<std::setfill(' ');
    }
    stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[27]->getBoxType()<<"|"<<std::endl;

    //Ottava riga del tabellone
    stream_string<<"H";
    for(int i=7; i>=0; i--){
        if(i==7){
            stream_string<<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"||";
        }
        else{
            //Ricavo il tipo di casella, PARTENZA, ECONOMICA, STANDARD, LUSSO
            stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"|"<<board[i]->getBoxType()<<"|";
        }
    }
}

