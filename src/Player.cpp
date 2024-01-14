#include "Board.h"
/*
*   LORENZON ISMAELE
*/

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

#define CASA 0
#define ALBERGO 1

std::map<std::string,std::function<void(Board::Board& s)>> Board::COMMANDS=std::map<std::string,std::function<void(Board& s)>>{
    //comando help per avere informazioni sui comandi del gioco
    {"help", [](Board& s) {
        std::cout <<"Ecco la lista dei comandi: \nshow: Ottieni le informazioni riguardanti la partita\n";
    }},
    //comanndo show per mostrare le informazioni sul tabellone
    {"show",[](Board& s){
        std::cout<<s.print_board()<<std::endl;
        std::cout<<s.print_player_costruction()<<std::endl;
        std::vector<Player*> giocatori=s.getPlayers();
        for(int i=0;i<giocatori.size();i++){
            std::cout<<"Giocatore "<<giocatori[i]->getId()+1<<" ha "<<giocatori[i]->getSaldo()<<" fiorini\n";
        }
    }}
};

//mappa dei costi dei vari terreni
std::map<int,std::vector<int>> Board::Player::initialize_costs() const{
    return std::map<int,std::vector<int>>{
        {ECON , std::vector<int>{TERRENO_ECON,CASA_ECON,ALB_ECON}},
        {STD , std::vector<int>{TERRENO_STD,CASA_STD,ALB_STD}},
        {LUX, std::vector<int>{TERRENO_LUX,CASA_LUX,ALB_LUX}}
    };
};

//funzione per processare la possibilità di acquisto di una casella
std::string Board::Player::processBuy(Board& board,Box* box){
    std::string q="Acquistare il terreno "+box->getCoordinates()+"? ";
    //ottieni il tipo del terreno
    int t=box->getBoxType();
    //se il tipo di questa casella non è acquistabile restituisci un log vuoto
    if(!this->costs.count(t)){return "";}
    std::string log="";
    //se hai un saldo disponibile e la logica di decisione restituisce 1
    if(this->saldo>=this->costs[t][0]&&this->decide(q,board)){
        //modifica il proprietario della casella
        box->setOwner(this);
        //aggiorna il saldo
        this->saldo-=this->costs[t][0];
        //aggiorna il log
        log+="- Giocatore "+std::to_string(this->id+1)+" ha acquistato il terreno "+box->getCoordinates()+"\n";
        //aggiungi alla propria casella
        this->squares.push_back(box);
    }
    return log;
}

//funzione per processare il pernottamento in un terreno
std::string Board::Player::processStay(Board& board,Box* box){
    std::string log="";
    if(box->getBoxStayCost()>0){
        //aggiorn il log
        log+="- Giocatore "+std::to_string(this->id+1)+" ha pagato "+std::to_string(box->getBoxStayCost())+" fiorini a giocatore "+std::to_string(box->getOwner()->getId()+1)+" per pernottamento nella casella "+box->getCoordinates()+"\n";
        //aggiorna il saldo del possessore della casella
        box->getOwner()->modifySaldo(std::min(this->saldo,box->getBoxStayCost()));
        //aggiorna il saldo di questio giocatore
        this->saldo-=box->getBoxStayCost();
    }
    //se il saldo è <0 il giocatore è eliminato e le caselle vengono rimesse a disposizione
    if(this->saldo<0){
        log+="- Giocatore "+std::to_string(this->id+1)+" è  stato eliminato";
        for(int i=0;i<this->squares.size();i++){
            this->squares[i]->setOwner(nullptr);
            this->squares[i]->setBoxConstruction(0);
        }
    }
    return log;
}

//funzione per processare la possibilità di mettere costruzioni
std::string Board::Player::processBuild(Board& board, Box* box){
    std::string log="";
    std::string qAskCasa="Acquistare una casa? ";
    std::string qAskAlbergo="Acquistare un albergo? ";
    //ottieni il tipo della casella
    int t=box->getBoxType();
    //separa i casi: acquisto di una casa e acquisto di un albergo
    switch(box->getBoxConstruction()){
        case CASA:
            //logica decisionale per l'acquisto di una casa
            if(this->saldo>=this->costs[t][1]&&this->decide(qAskCasa,board)){
                box->build_on_box();
                this->saldo-=this->costs[t][1];
                log+="- Giocatore "+std::to_string(this->id+1)+" ha costruito una casa sul terreno "+box->getCoordinates()+"\n";
            }
            break;
        case ALBERGO:
            //logica decisionale per l'acquisto di un albergo
            if(this->saldo>=this->costs[t][2]&&this->decide(qAskAlbergo,board)){
                box->build_on_box();
                this->saldo-=this->costs[t][2];
                log+="- Giocatore "+std::to_string(this->id+1)+" ha migliorato una casa in albergo sul terreno "+box->getCoordinates()+"\n";
            }
            break;
        default:
            break;
    }
    return log;
}

bool Board::Player::isMine(Box& s) const {
    // Scansiona le caselle in possesso fino a trovare quella indicata
    for(int i=0;i<this->squares.size();i++){
        if(s.getIdBox()==(this->squares[i]->getIdBox())){
            return true;
        }
    }
    return false;
}

bool Board::Player::isCommand(std::string s){
    return COMMANDS.count(s);
}

bool Board::Human::decide(std::string& question,Board& b){
    // logica di decisione per player umani
    std::string response;
    do{
        std::cout<<question<<" (S/N)"<<std::endl;
        std::cin>>response;
        if(this->isCommand(response)){
            COMMANDS[response](b);
        }
    }while(this->isCommand(response)||(response!="S"&&response!="N"));
    return response=="S";
}

bool Board::Computer::decide(std::string& question,Board& b){
    //logica di decisione per computer
    bool  d=!(rand()%4);
    return d;
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

void Board::Player::log(std::string& log,std::string s){
    std::cout<<s;
    log+=s;
}

std::string Board::Player::move(Board& s,Dadi& d){
    std::string log="";
    int t=d.lancia();
    this->log(log,"- Giocatore "+std::to_string(this->id+1)+" ha tirato i dadi ottendendo un valore di "+std::to_string(t)+"\n");
    this->pos+=t;
    if(this->pos>=N_CASELLE){
        this->pos-=N_CASELLE;
        this->saldo+=VIA;
        this->log(log,"- Giocatore "+std::to_string(this->id+1)+" è passato dal via e ha ritirato 20 fiorini\n");
    }
    Box* arrivalBox=s.getBox(this->pos);
    this->log(log,"- Giocatore "+std::to_string(this->id+1)+" è arrivato alla casella "+arrivalBox->getCoordinates()+"\n");
    if(arrivalBox->getOwner()!=NO_PLAYER&&arrivalBox->getOwner()->getId()==this->id){
        this->log(log,this->processBuild(s,arrivalBox));
    } else if(arrivalBox->getOwner()==NO_PLAYER){
        this->log(log,this->processBuy(s,arrivalBox));
    } else {
        this->log(log,this->processStay(s,arrivalBox));
    }
    this->log(log,"- Giocatore "+std::to_string(this->id+1)+" ha finito il turno\n");
    return log;
}
