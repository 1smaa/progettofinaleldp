#include "Player.h"
#include <iostream>

bool Player::Player::isMine(Box s){
    // Scansiona le caselle in possesso fino a trovare quella indicata
    for(int i=0;i<this->squares.size();i++){
        if(s.getIdBox()==(this->squares[i].getIdBox())){
            return true;
        }
    }
    return false;
}

std::map<std::string, std::function<void(Scoreboard::Scoreboard s)>> Player::Human::initialize_commands() {
    return std::map<std::string, std::function<void(Scoreboard::Scoreboard s)>>{
        {"/help", [](Scoreboard::Scoreboard s) {
            std::cout << "Ecco la lista dei comandi: \n";
            std::cout<<"/help: Ottieni la lista dei comandi\n";
            std::cout<<"/tabellone: Stampa il tabellone al turno corrente\n";
            std::cout<<"/costruzioni: Ottieni una lista dei giocatori e delle loro relative costruzioni ( case o alberghi )";
        }},
        {"/tabellone",[](Scoreboard::Scoreboard s){
            //s.stampa();
        }},
        {"/costruzioni",[](Scoreboard::Scoreboard s){

        }}
    };
}

bool Player::Human::isCommand(std::string s){
    return ((s!="")&&(s[0]=='/'));
}

uint Player::Human::move(Scoreboard::Scoreboard s){
    std::string input;
    std::cin>>input;
    while(this->isCommand(input)){
        if(this->commands.count(input)){
            this->commands[input](s);
        } else {
            break;
        }
    }
    uint t=2;// lancia il dado
    this->pos+=t;
    return this->pos;
}
