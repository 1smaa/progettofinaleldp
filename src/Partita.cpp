#include <iostream>
#include <algorithm>
#include "Partita.h"
/*
*   CIAN IRENE
*/
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
        lanciDado.push_back(std::make_pair(giocatori[i], 0)); // aggiungo un elemento alla fine del vettore
    }
    //casi di pareggio
    std::vector<std::pair<int,int>> unsorted{std::make_pair(0,lanciDado.size())};
    do{
        std::cout<<std::endl;
        std::vector<std::pair<int,int>> newunsort{};
        for(int i=0;i<unsorted.size();i++){
            for(int j=unsorted[i].first;j<unsorted[i].second;j++){
                int t=d.lancia();
                this->s+="- Giocatore "+std::to_string(giocatori[j]->getId())+" ha lanciato "+std::to_string(t)+".\n";
                lanciDado[j].second=t;
            }
            std::sort(lanciDado.begin()+unsorted[i].first,lanciDado.begin()+unsorted[i].second,[](const auto& a,const auto& b){
                return a.second>b.second;
            });
            for(int j=unsorted[i].first;j<unsorted[i].second-1;j++){
                int start=j;
                int end=j;
                while(j+1<unsorted[i].second&&lanciDado[j].second==lanciDado[j+1].second){
                    end++;
                    j++;
                }
                if(end-start){
                    newunsort.push_back(std::pair<int,int>{start,end+1});
                }
            }
        }
        unsorted=newunsort;
    }while(unsorted.size());

    for(int i=0;i<lanciDado.size();i++){
        this->giocatori[i]=lanciDado[i].first;
    }
    //stampo l'ordine di partenza
    std::cout<<this->s<<std::endl;
    //Id giocatore al primo turno
    this->prossimoGiocatore=-1;
    return giocatori[0]->getId();
}

int Partita::prossimoTurno(){
    turno ++;
    prossimoGiocatore=(prossimoGiocatore+1)%4;
    while(!this->giocatori[prossimoGiocatore]->inPlay()){
        prossimoGiocatore=(prossimoGiocatore+1)%4;
    }
    std::string log=this->giocatori[prossimoGiocatore]->move(*this->tabellone,this->d); // move fa giocare tutto il turno al prossimo giocatore
    this->s+=log;
    return turno;
}

bool Partita::terminata() const{
    //termina se rimane solo un giocatore 
    if(this->turno>=200){
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

std::vector<Board::Player*> Partita::vincitore()const{
    //vince l'ultimo che rimane
    std::vector<Board::Player*> vincitori{};
    int saldoMax=0;
    for(int i=0;i<this->giocatori.size();i++){
        if(this->giocatori[i]->inPlay()){
            int saldo=this->giocatori[i]->getSaldo();
            if(saldoMax<saldo){
                saldoMax=saldo;
                vincitori=std::vector<Board::Player*>{this->giocatori[i]};
            } else if(saldoMax==saldo){
                vincitori.push_back(this->giocatori[i]);
            }
        }
    }
    return vincitori;
}
