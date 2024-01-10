#include "Dadi.h"
#include "Partita.h"
#include "Board.h"


#include <vector>

#define DEFAULT_SALDO 100

int main(void){
    std::vector<Board::Player*> giocatori{};
    for(int i=0;i<4;i++){
        giocatori.push_back(new Board::Player(true,i,DEFAULT_SALDO));
    }
    //giocatori.push_back(new Board::Player(false,3,DEFAULT_SALDO));
    Board::Board tabellone(giocatori);
    Partita p(giocatori,&tabellone);
    int t=p.inizia();
    while(!p.terminata()){
        std::cout<<t<<std::endl;
        t=p.prossimoTurno();
    }
    std::vector<Board::Player*> inPLay=tabellone.getPlayers();
    for(int i=0;i<inPLay.size();i++){
        std::cout<<inPLay[i]->getSaldo()<<std::endl;
    }
    std::vector<Board::Player> vincitori=p.vincitore();
    for(int i=0;i<vincitori.size();i++){
        std::cout<<"Il giocatore "<<vincitori[i].getId()<<" ha vinto"<<std::endl;
    }
}