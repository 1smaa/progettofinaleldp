#include "Dadi.h"
#include "Partita.h"
#include "Board.h"

#include <vector>
#include <fstream>

#define DEFAULT_SALDO 100

/*
    AMBROSO PIERLORENZO
*/

//Funzione per stampare il messaggio di errore
void print_mex_error(){
    std::cout<<"Errore nell'avvio del gioco!"<<std::endl
				<<"Digitare:"<<std::endl
				<<"[./main computer] -> per una partita tra 4 computer"<<std::endl
				<<"[./main human] -> per giocare una partita contro 3 computer"<<std::endl;
}

int main(int argc,char *argv[] ){

	if(argc==2){ //Controllo che sia stato scritto qualcosa dopo il comando ./main, se viene inserita più di una parola verrà stampato il messaggio di errore
		if(std::string(argv[1]).compare("Human")==0 || std::string(argv[1]).compare("human")==0){ //Controllo se la partita desiderata è con 3 computer e un umano

        //Eseguo il gioco con 3 computer e un umano
			std::vector<Board::Player*> giocatori{};
   			for(int i=0;i<3;i++){
    	    	giocatori.push_back(new Board::Computer(i,DEFAULT_SALDO));
    		}
			
    		giocatori.push_back(new Board::Human(3,DEFAULT_SALDO));
			std::cout<<std::endl<<"IL GIOCATORE UMANO E' IL NUMERO: "<<std::to_string(giocatori[3]->getId()+1)<<std::endl; //COUT per stampare il numero del giocatore umano

			std::ofstream log_partita; //Per scrivere sul file il log della partita
            log_partita.open("Partita_con_umano.txt", std::fstream::trunc); //Apro il file
			if(log_partita.is_open()) log_partita<<"IL GIOCATORE UMANO E' IL NUMERO: "+std::to_string(giocatori[3]->getId()+1); //Scrivo anche nel file quale è il giocatore umano
			
            //Creo il tabellone
    		Board::Board tabellone(giocatori);
            //Genero la partita
    		Partita p(giocatori,&tabellone,true);
            //Faccio iniziare la partita
    		int t=p.inizia();
    		while(!p.terminata()){
        		t=p.prossimoTurno();
    		}
            //Scrivo su file il log della partita
            if(log_partita.is_open()) log_partita<<p.log(); //Scrivo il log della partita sul file
            

			std::cout<<std::endl<<std::endl<<"Il gioco è terminato!"<<std::endl;
			std::vector<Board::Player*> inPlay=tabellone.getPlayers();
			for(int i=0;i<inPlay.size();i++){
				std::string to_print = "Saldo giocatore "+std::to_string(inPlay[i]->getId())+": "+std::to_string(inPlay[i]->getSaldo())+"\n\n"; //Creo una stringa così da accedere ai vector una volta sola
	   	    	std::cout<<to_print; //Stampo a schermo le informazioni
				if(log_partita.is_open()) log_partita<<to_print; //Scrivo su file le informazioni
	    	}
	    	std::vector<Board::Player*> vincitori=p.vincitore();
	    	for(int i=0;i<vincitori.size();i++){
				std::string to_print = "Il giocatore "+std::to_string(vincitori[i]->getId())+" ha vinto"+"\n";    	
				std::cout<<to_print;
				if(log_partita.is_open()) log_partita<<to_print;
	    	}

			log_partita.close();
		}

		else if(std::string(argv[1]).compare("Computer")==0 || std::string(argv[1]).compare("computer")==0){ //Altrimenti controllo se la partita desiderata è tra 4 computer
        
        //Eseguo il gioco tra 4 computer
			std::vector<Board::Player*> giocatori{};
   			for(int i=0;i<4;i++){
    	    	giocatori.push_back(new Board::Computer(i,DEFAULT_SALDO));
    		}
			Board::Board tabellone(giocatori);
    		Partita p(giocatori,&tabellone,false);
    		int t=p.inizia();
    		while(!p.terminata()){
        		t=p.prossimoTurno();
    		}

            //Scrivo su file il log della partita
            std::ofstream log_partita;
            log_partita.open("Partita_tra_computer.txt", std::fstream::trunc); //Apro il file, utilizzo il parametro trunc per eliminare il suo contenuto, nel caso in cui fosse presente.
			if(log_partita.is_open()){ //Controllo che il file sia aperto
            	log_partita<<p.log(); //Scrivo il log della partita sul file
			}
			/*
			std::cout<<std::endl<<std::endl<<"Il gioco è terminato!"<<std::endl;
			std::vector<Board::Player*> inPlay=tabellone.getPlayers();
			for(int i=0;i<inPlay.size();i++){
				std::string to_print = "Saldo giocatore "+std::to_string(inPlay[i]->getId())+": "+std::to_string(inPlay[i]->getSaldo())+"\n\n"; //Creo una stringa così da accedere ai vector una volta sola
	   	    	std::cout<<to_print; //Stampo a schermo le informazioni
				if(log_partita.is_open()) log_partita<<to_print; //Scrivo su file le informazioni
	    	}*/
	    	std::vector<Board::Player*> vincitori=p.vincitore();
	    	for(int i=0;i<vincitori.size();i++){
				std::string to_print = "Il giocatore "+std::to_string(vincitori[i]->getId()+1)+" ha vinto"+"\n";    	
				std::cout<<to_print;
				if(log_partita.is_open()) log_partita<<to_print;
	    	}

			log_partita.close(); //Chiudo lo stream del file
		}

        else{
            print_mex_error();
        }
	}

	else{ //Se non è stato inserito alcun comando dopo ./main stampo un messaggio di errore
		print_mex_error();
	}
	return 0;
}
