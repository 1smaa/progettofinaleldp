#include "Board.h"
#include <iostream>
#include <ctime>

#define VIA 20
#define N_CASELLE 28
#define NO_PLAYER nullptr

#define ECON 2
#define STD 3
#define LUX 4

#define TERRENO_ECON 6
#define TERRENO_STD 10
#define TERRENO_LUX 20

#define CASA_ECON 3
#define CASA_STD 5
#define CASA_LUX 10

#define ALB_ECON 3
#define ALB_STD 5
#define ALB_LUX 10

std::map<std::string,std::function<void(Board::Board& s)>> Board::COMMANDS=std::map<std::string,std::function<void(Board& s)>>{
        {"help", [](Board& s) {
            std::cout <<"Ecco la lista dei comandi: \n";
            std::cout<<"/help: Ottieni la lista dei comandi\n";
            std::cout<<"/tabellone: Stampa il tabellone al turno corrente\n";
            std::cout<<"/costruzioni: Ottieni una lista dei giocatori e delle loro relative costruzioni ( case o alberghi )\n";
            std::cout<<"/saldo: Ottieni il saldo dei giocatori\n";
        }},
        {"show",[](Board& s){
            std::cout<<s.print_board()<<std::endl;
            std::cout<<s.print_player_costruction()<<std::endl;
            std::vector<Player*> giocatori=s.getPlayers();
            for(int i=0;i<giocatori.size();i++){
                std::cout<<"Giocatore "<<giocatori[i]->getId()<<" ha "<<giocatori[i]->getSaldo()<<" fiorini.\n";
            }
        }}
    };

bool Board::Player::isMine(Box s){
    // Scansiona le caselle in possesso fino a trovare quella indicata
    for(int i=0;i<this->squares.size();i++){
        if(s.getIdBox()==(this->squares[i]->getIdBox())){
            return true;
        }
    }
    return false;
}

bool Board::Player::isCommand(std::string s){
    return COMMANDS.count(s)>0;
}

bool Board::Player::human_decide(std::string question,Board b){
    std::cout<<question<<" (Y/N)"<<std::endl;
    std::string response;
    std::cin>>response;
    while(this->isCommand(response)){
        COMMANDS[response](b);
        std::cin>>response;
    }
    return response=="Y";
}

bool Board::Player::computer_decide(){
    int r=rand()%101;
    //std::cout<<r<<std::endl;
    return r<=25;
}

bool Board::Player::decide(std::string question,Board b){
    if(this->automate){
        return this->computer_decide();
    } else {
        return this->human_decide(question,b);
    }
}
std::string Board::Player::logConstruction(){
    std::string log="";
    for(int i=0;i<this->squares.size();i++){
        if(squares[i]->getBoxConstruction()!=0){
            log+=this->squares[i]->getCoordinates()+",";
        }
    }
    return log.substr(0,log.length()-1);
}

std::string Board::Player::move(Board s,Dadi d){
    std::string log="";
    int t=d.lancia();
    log+="- Giocatore "+std::to_string(this->id)+" ha tirato i dadi ottendendo un valore di "+std::to_string(t)+"\n";
    this->pos+=t;
    bool startP=false;
    if(this->pos>=N_CASELLE){
        startP=true;
        this->pos-=N_CASELLE;
        this->saldo+=VIA;
        log+="- Giocatore "+std::to_string(this->id)+" è passato dal via e ha ritirato 20 fiorini\n";
    }
    Box* arrivalBox=s.getBox(this->pos);
    log+="- Giocatore "+std::to_string(this->id)+" è arrivato alla casella "+arrivalBox->getCoordinates()+"\n";
    if(arrivalBox->getOwner()!=NO_PLAYER&&arrivalBox->getOwner()->getId()==this->id){
        switch(arrivalBox->getBoxType()){
            case ECON:
                switch(arrivalBox->getBoxConstruction()){
                    case 0:
                        if(this->saldo>=CASA_ECON&&this->decide("Acquistare una casa? ",s)){
                            arrivalBox->build_on_box();
                            this->saldo-=CASA_ECON;
                            log+="- Giocatore "+std::to_string(this->id)+" ha costruito una casa sul terreno "+arrivalBox->getCoordinates()+"\n";
                        }
                        break;
                    case 1:
                        if(this->saldo>=ALB_ECON&&this->decide("Acquistare un albergo? ",s)){
                            arrivalBox->build_on_box();
                            this->saldo-=ALB_ECON;
                            log+="- Giocatore "+std::to_string(this->id)+" ha migliorato una casa in albergo sul terreno "+arrivalBox->getCoordinates()+"\n";
                        }
                        break;
                    default:
                        break;
                }
                break;
            case STD:
                switch(arrivalBox->getBoxConstruction()){
                    case 0:
                        if(this->saldo>=CASA_STD&&this->decide("Acquistare una casa? ",s)){
                            arrivalBox->build_on_box();
                            this->saldo-=CASA_STD;
                            log+="- Giocatore "+std::to_string(this->id)+" ha costruito una casa sul terreno "+arrivalBox->getCoordinates()+"\n";
                        }
                        break;
                    case 1:
                        if(this->saldo>=ALB_STD&&this->decide("Acquistare un albergo? ",s)){
                            arrivalBox->build_on_box();
                            this->saldo-=ALB_STD;
                            log+="- Giocatore "+std::to_string(this->id)+" ha migliorato una casa in albergo sul terreno "+arrivalBox->getCoordinates()+"\n";
                        }
                        break;
                    default:
                        break;
                }
                break;
            case LUX:
                switch(arrivalBox->getBoxConstruction()){
                    case 0:
                        if(this->saldo>=CASA_LUX&&this->decide("Acquistare una casa? ",s)){
                            arrivalBox->build_on_box();
                            this->saldo-=CASA_LUX;
                            log+="- Giocatore "+std::to_string(this->id)+" ha costruito una casa sul terreno "+arrivalBox->getCoordinates()+"\n";
                        }
                        break;
                    case 1:
                        if(this->saldo>=ALB_LUX&&this->decide("Acquistare un albergo? ",s)){
                            arrivalBox->build_on_box();
                            this->saldo-=ALB_LUX;
                            log+="- Giocatore "+std::to_string(this->id)+" ha migliorato una casa in albergo sul terreno "+arrivalBox->getCoordinates()+"\n";
                        }
                        break;
                    default:
                        break;
                }
                break;
            default: break;
        }
    } else if(arrivalBox->getOwner()==NO_PLAYER){
        switch(arrivalBox->getBoxType()){
            case ECON:
                if(this->saldo>=TERRENO_ECON&&this->decide("Comprare una casella economica? ",s)){
                    arrivalBox->setOwner(this);
                    this->saldo-=TERRENO_ECON;
                    log+="- Giocatore "+std::to_string(this->id)+" ha acquistato il terreno "+arrivalBox->getCoordinates()+"\n";
                    this->squares.push_back(arrivalBox);
                }
                break;
            case STD:
                if(this->saldo>=TERRENO_STD&&this->decide("Comprare una casella standard? ",s)){
                    arrivalBox->setOwner(this);
                    this->saldo-=TERRENO_STD;
                    log+="- Giocatore "+std::to_string(this->id)+" ha acquistato il terreno "+arrivalBox->getCoordinates()+"\n";
                    this->squares.push_back(arrivalBox);
                }
                break;
            case LUX:
                if(this->saldo>=TERRENO_LUX&&this->decide("Comprare una casella lusso? ",s)){
                    arrivalBox->setOwner(this);
                    this->saldo-=TERRENO_LUX;
                    log+="- Giocatore "+std::to_string(this->id)+" ha acquistato il terreno "+arrivalBox->getCoordinates()+"\n";
                    this->squares.push_back(arrivalBox);
                }
                break;
            default:
                break;
        }
    } else {
        log+="- Giocatore "+std::to_string(this->id)+" ha pagato "+std::to_string(arrivalBox->getBoxStayCost())+" fiorini a giocatore "+std::to_string(arrivalBox->getOwner()->getId())+" per pernottamento nella casella "+arrivalBox->getCoordinates()+"\n";
        arrivalBox->getOwner()->modifySaldo(std::min(this->saldo,arrivalBox->getBoxStayCost()));
        this->saldo-=arrivalBox->getBoxStayCost();
        if(this->saldo<0){
            log+="- Giocatore "+std::to_string(this->id)+" è  stato eliminato.";
            for(int i=0;i<this->squares.size();i++){
                this->squares[i]->setOwner(nullptr);
                this->squares[i]->setBoxConstruction(0);
            }
        }
    }
    log+="- Giocatore "+std::to_string(this->id)+" ha finito il turno.\n";
    return log;
}
