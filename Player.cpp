#include "Player.h"
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

bool Player::isMine(Box s){
    // Scansiona le caselle in possesso fino a trovare quella indicata
    for(int i=0;i<this->squares.size();i++){
        if(s.getIdBox()==(this->squares[i].getIdBox())){
            return true;
        }
    }
    return false;
}

std::map<std::string, std::function<void(Scoreboard s)>> Player::initialize_commands() {
    return std::map<std::string, std::function<void(Scoreboard s)>>{
        {"/help", [](Scoreboard s) {
            std::cout << "Ecco la lista dei comandi: \n";
            std::cout<<"/help: Ottieni la lista dei comandi\n";
            std::cout<<"/tabellone: Stampa il tabellone al turno corrente\n";
            std::cout<<"/costruzioni: Ottieni una lista dei giocatori e delle loro relative costruzioni ( case o alberghi )";
        }},
        {"/tabellone",[](Scoreboard s){
            s.print_scoreboard();
        }},
        {"/costruzioni",[](Scoreboard s){
            
        }}
    };
}

bool Player::isCommand(std::string s){
    return ((s!="")&&(s[0]=='/'));
}

bool Player::human_decide(std::string question){
    std::cout<<question<<" (Y/N)"<<std::endl;
    char response;
    std::cin>>response;
    return response=='Y';
}

bool Player::computer_decide(std::string question){
    srand(time(NULL));
    int r=rand()%101;
    return r<=25;
}

bool Player::decide(std::string question){
    if(this->automate){
        return this->computer_decide(question);
    } else {
        return this->human_decide(question);
    }
}

std::string Player::to_coordinates(int index){
    if(index<22&&index>=14){
        return "A"+std::to_string(index-13);
    }
    if(index<8){
        return "H"+std::to_string(8-index);
    }
    if(index<=13&&index>=8){
        return {(char)('O'-index),'1'};
    }
    if(index>=22){
        return {(char)(index+','),'8'};
    }
    return "";
}

std::string Player::logConstruction(){
    std::string log="";
    for(int i=0;i<this->squares.size();i++){
        if(squares[i].getBoxConstruction()!=0){
            log+=this->to_coordinates(squares[i].getIdBox())+",";
        }
    }
    return log;
}

std::string Player::move(Scoreboard s,Dadi d){
    if(!this->automate){ 
        std::string input;
        std::cin>>input;
        while(this->isCommand(input)){
            if(this->commands.count(input)){
                this->commands[input](s);
            } else {
                break;
            }
        }
    }
    std::string log="";
    int t=d.lancia();
    log+="- Il Giocatore "+std::to_string(this->id)+" ha tirato i dadi ottendendo "+std::to_string(t)+"\n";
    this->pos+=t;
    bool startP=false;
    if(this->pos>=N_CASELLE){
        startP=true;
        this->pos-=N_CASELLE;
        this->saldo+=VIA;
    }
    Box* arrivalBox=s.getBox(this->pos);
    log+="- Il Giocatore "+std::to_string(this->id)+" è arrivato alla casella "+std::to_string(arrivalBox->getIdBox())+"\n";
    if(arrivalBox->getOwner()->getId()==this->id){
        switch(arrivalBox->getBoxType()){
            case ECON:
                switch(arrivalBox->getBoxConstruction()){
                    case 0:
                        if(this->saldo>=CASA_ECON&&this->decide("Acquistare una casa? ")){
                            arrivalBox->setBoxConstruction(1);
                            this->saldo-=CASA_ECON;
                            log+="- Il Giocatore "+std::to_string(this->id)+" ha acquistato una casa sulla casella "+std::to_string(arrivalBox->getIdBox())+"\n";
                        }
                        break;
                    case 1:
                        if(this->saldo>=ALB_ECON&&this->decide("Acquistare un albergo? ")){
                            arrivalBox->setBoxConstruction(2);
                            this->saldo-=ALB_ECON;
                            log+="- Il Giocatore "+std::to_string(this->id)+" ha migliorato una casa in albergo sulla casella "+std::to_string(arrivalBox->getIdBox())+"\n";
                        }
                        break;
                    default:
                        break;
                }
            case STD:
                switch(arrivalBox->getBoxConstruction()){
                    case 0:
                        if(this->saldo>=CASA_STD&&this->decide("Acquistare una casa? ")){
                            arrivalBox->setBoxConstruction(1);
                            this->saldo-=CASA_STD;
                            log+="- Il Giocatore "+std::to_string(this->id)+" ha acquistato una casa sulla casella "+std::to_string(arrivalBox->getIdBox())+"\n";
                        }
                        break;
                    case 1:
                        if(this->saldo>=ALB_STD&&this->decide("Acquistare un albergo? ")){
                            arrivalBox->setBoxConstruction(2);
                            this->saldo-=ALB_STD;
                            log+="- Il Giocatore "+std::to_string(this->id)+" ha migliorato una casa in albergo sulla casella "+std::to_string(arrivalBox->getIdBox())+"\n";
                        }
                        break;
                    default:
                        break;
                }
            case LUX:
                switch(arrivalBox->getBoxConstruction()){
                    case 0:
                        if(this->saldo>=CASA_LUX&&this->decide("Acquistare una casa? ")){
                            arrivalBox->setBoxConstruction(1);
                            this->saldo-=CASA_LUX;
                            log+="- Il Giocatore "+std::to_string(this->id)+" ha acquistato una casa sulla casella "+std::to_string(arrivalBox->getIdBox())+"\n";
                        }
                        break;
                    case 1:
                        if(this->saldo>=ALB_LUX&&this->decide("Acquistare un albergo? ")){
                            arrivalBox->setBoxConstruction(2);
                            this->saldo-=ALB_LUX;
                            log+="- Il Giocatore "+std::to_string(this->id)+" ha migliorato una casa in albergo sulla casella "+std::to_string(arrivalBox->getIdBox())+"\n";
                        }
                        break;
                    default:
                        break;
                }
            default: break;
        }
    } else if(arrivalBox->getOwner()==NO_PLAYER){
        switch(arrivalBox->getBoxType()){
            case ECON:
                if(this->saldo>=TERRENO_ECON&&this->decide("Comprare una casella economica? ")){
                    arrivalBox->setOwner(this);
                    this->saldo-=TERRENO_ECON;
                    log+="- Il Giocatore "+std::to_string(this->id)+" ha acquistato il terreno "+std::to_string(arrivalBox->getIdBox())+"\n";
                    this->squares.push_back(*arrivalBox);
                }
                break;
            case STD:
                if(this->saldo>=TERRENO_STD&&this->decide("Comprare una casella standard? ")){
                    arrivalBox->setOwner(this);
                    this->saldo-=TERRENO_STD;
                    log+="- Il Giocatore "+std::to_string(this->id)+" ha acquistato il terreno "+std::to_string(arrivalBox->getIdBox())+"\n";
                    this->squares.push_back(*arrivalBox);
                }
                break;
            case LUX:
                if(this->saldo>=TERRENO_LUX&&this->decide("Comprare una casella lusso? ")){
                    arrivalBox->setOwner(this);
                    this->saldo-=TERRENO_LUX;
                    log+="- Il Giocatore "+std::to_string(this->id)+" ha acquistato il terreno "+std::to_string(arrivalBox->getIdBox())+"\n";
                    this->squares.push_back(*arrivalBox);
                }
                break;
        }
    } else {
        log+="- Il Giocatore "+std::to_string(this->id)+" ha pagato al giocatore "+std::to_string(arrivalBox->getOwner()->getId())+" "+std::to_string(arrivalBox->pernottamento())+" per pernottamento nella casella "+std::to_string(arrivalBox->getIdBox())+"\n";
        arrivalBox->getOwner()->modifySaldo(std::min(this->saldo,arrivalBox->pernottamento()));
        this->saldo-=arrivalBox->pernottamento();
        if(this->saldo<0){
            log+="- Il Giocatore "+std::to_string(this->id)+" è  stato eliminato.";
        }
    }
    return log;
}
