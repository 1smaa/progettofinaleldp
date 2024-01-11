#include <vector>
#include <iostream>
#include <fstream>

#include "Dadi.h"
#include "Partita.h"
#include "Board.h"

#define DEFAULT_SALDO 100

int main(){

//creo il tabellone e i giocatori
    std::vector<Board::Player*> giocatori{};
    Board::Board tabellone(giocatori);
        //inserisco nel vettore i giocatori e inizializzo il saldo di ognuno
        for(int i=0; i<4; i++){
        giocatori.push_back(new Board::Player(true, i, DEFAULT_SALDO));
    }
//apro il file di testo
    std::ofstream outputFile ("MONOPOLY.txt"); 
        if (!outputFile.is_open()){ //verifico sia aperto correttamente
            std::cerr << "errore nell'apertura del file" << std::endl;
            return 1;
        }
//creo un oggetto partita
    Partita partita(giocatori, &tabellone);
    int g = partita.inizia(); //inizio la partita
    outputFile << "PARTITA INIZIATA! Il primo giocatore è " << giocatori[0] << std::endl;
    outputFile << partita.log() <<std::endl;
        while (!partita.terminata()){
            std::cout << g << std::endl;
            g= partita.prossimoTurno(); //esegui il turno e passa al giocatore successivo
        }

    std::vector<Board::Player*> inPLay= tabellone.getPlayers();
        for(int i=0; i < inPLay.size(); i++){
        std::cout<< inPLay[i]-> getSaldo()<< std::endl;
    }
//stampo il vincitore
    std::vector<Board::Player> vincitori = partita.vincitore();
        for(int i=0; i < vincitori.size(); i++){
        std::cout << "PARTITA TERMINATA! Il giocatore " << vincitori[i].getId() << " ha vinto" << std::endl;
    }
//chiusura file
    outputFile.close();
    
    return 0;
} 
