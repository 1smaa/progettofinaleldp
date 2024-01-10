#include <iostream>
#include <algorithm>
#include "Partita.h"
//COSTRUTTORI
Partita::Partita(std::vector<Board::Player*>& giocatori, Board::Board* tabellone){
    this-> giocatori = giocatori;
    this-> tabellone = tabellone;
    this-> turno = 0;
    this-> s = " ";
    this -> d = Dadi();
    this->prossimoGiocatore=0;
}
Partita::Partita(std::vector<Board::Player*>& giocatori, Board::Board* tabellone, int turno){
    this-> giocatori = giocatori;
    this-> tabellone = tabellone;
    this-> turno = turno;
    this-> s = " ";
    this -> d = Dadi();
    this->prossimoGiocatore=0;
}
//FUNZIONI

int Partita::inizia(){

    //assegno ad ogni giocatore un lancio casuale
    std::vector<std::pair<Board::Player*, int>> lanciDado; //coppie (giocatore, numero dado)
    for (int i =0; i< giocatori.size(); i++){
        int valoreDado =d.lancia();
        lanciDado.push_back(std::make_pair(giocatori[i], valoreDado)); // aggiungo un elemento alla fine del vettore
    }
    
    //ordino i giocatori (decrescente)
    std::sort (lanciDado.begin(), lanciDado.end(),[](const auto& a, const auto& b){
        return a.second> b.second;
    });

    //casi di pareggio
    for(int i =0; i< lanciDado.size()-1; i++){
        while (lanciDado[i].second== lanciDado[i+1].second){
            //ritiriamo il dado
            lanciDado[i].second= d.lancia();
            lanciDado[i+1].second= d.lancia();
        }
    } 

    //riordino 
    std::sort(lanciDado.begin(), lanciDado.end(),[](const auto& a, const auto& b){
        return a.second> b.second;
    });

    //riordino i giocatori (decrescente)
    std::vector<Board::Player*> ordineGiocatori;
    for (const auto& risultato: lanciDado){
        ordineGiocatori.push_back(risultato.first);
    }
    giocatori= ordineGiocatori;

    //stampo l'ordine di partenza
    for(int i=0; i<giocatori.size(); i++){
        std::cout<< "Giocatore "<<giocatori[i]->getId()<<" ha lanciato "<<lanciDado[i].second<<std::endl;
    }
    //Id giocatore al primo turno
    return giocatori[0]->getId();
}

int Partita::prossimoTurno(){
    turno ++;
    prossimoGiocatore=(prossimoGiocatore+1)%4;
    while(!this->giocatori[prossimoGiocatore]->inPlay()){
        prossimoGiocatore=(prossimoGiocatore+1)%4;
    }
    std::string log=this->giocatori[prossimoGiocatore]->move(*this->tabellone,this->d); // move fa giocare tutto il turno al prossimo giocatore
    std::cout<<log<<std::endl;
    this->s+=log;
    return turno;
}

bool Partita::terminata() const{
    //termina se rimane solo un giocatore 
    if(this->turno>=20000){
        return 1;
    }
    int n=0;
    for(int i=0;i<this->giocatori.size();i++){
        if(this->giocatori[i]->inPlay()){
            n++;
        }
    }
    return n==1;
}

std::string Partita::log() const{
    //restituisci il log della partita
    return s;
}

std::vector<Board::Player> Partita::vincitore()const{
    //vince l'ultimo che rimane
    std::vector<Board::Player> vincitori{};
    int saldoMax=0;
    for(int i=0;i<this->giocatori.size();i++){
        if(this->giocatori[i]->inPlay()){
            int saldo=this->giocatori[i]->getSaldo();
            if(saldoMax<saldo){
                saldoMax=saldo;
                vincitori=std::vector<Board::Player>{*this->giocatori[i]};
            } else if(saldoMax==saldo){
                vincitori.push_back(*this->giocatori[i]);
            }
        }
    }
    return vincitori;
}
