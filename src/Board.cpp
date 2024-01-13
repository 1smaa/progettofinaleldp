#include "Board.h"

/*
*   AMBROSO PIERLORENZO
*/

//Numero totale di caselle nel tabellone
#define NUMERO_CASELLE 28

//Numero totale di ogni tipo di casella
#define NUMERO_CASELLE_ECONOMICHE 8
#define NUMERO_CASELLE_STANDARD 10
#define NUMERO_CASELLE_LUSSO 6

//Valori utilizzati per identificare il tipo di casella da generare in base al numero random uscito
#define RANDOM_CASELLA_E 0
#define RANDOM_CASELLA_S 1
#define RANDOM_CASELLA_L 2

//Valori utilizzati nei costruttori di Box per identificare il tipo di casella da creare (Economica, Standard, Lusso)
#define CASELLA_E 2
#define CASELLA_S 3
#define CASELLA_L 4

#define LARGHEZZA_CASELLA_STAMPA 10

//Funzioni private utili per la stampa del tabellone

//Funzione privata utile al fine della stampa della prima riga del tabellone, ovvero la riga contenente i numeri da 1 a 8
//Ricevo uno stringstream per riferimento così da poter aggiungere i valori alla stringa che poi andrà ritornata
void Board::Board::print_testata(std::stringstream& ss){
            ss<<"0"
            <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  1  " //Tramite std::setw imposto la larghezza della "cella", così da avere tutte le larghezze uguali
            <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  2  "
            <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  3  "
            <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  4  "
            <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  5  "
            <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  6  "
            <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  7  "
            <<std::setw(LARGHEZZA_CASELLA_STAMPA)<< "  8  "<<std::endl;
};

//Funzione privata utilizzata per ottenere la casella con le informazioni (giocatore sopra, case o alberghi costruiti, ...)
std::string Board::Board::string_to_print(Box* box, std::vector<Player*>& player){
    
    std::string to_return; //Creo una stringa temporanea che mi è utile per poter memorizzare alcuni valori
    
    switch(box->getBoxType()){ //Ricavo il tipo di casella tramite l'apposita funzione per poi, tramite uno switch-case, aggiungere alla stringa temporanea il corretto carattere
        case 0: //La casella è la partenza
            to_return+="P";
            break;
        case 1: //La casella è angolare
            to_return+=" ";
            break;
        case 2: //La casella è di tipo economico
            to_return+= "E";
            break;
        case 3: //La casella è di tipo Standard
            to_return+= "S";
            break;
        case 4: //La casella è di tipo Lusso
            to_return+= "L";
            break;
    }

    //Cerco se un giocatore è sopra la casella che sto stampando tramite un ciclo for
    try{
        for(int i=0; i<player.size(); i++){
            //Se il giocatore è nella posizione = all'id della casella, lo aggiungo alla casella da stampare
            if(player.at(i)->getPos() == box->getIdBox()){
                to_return+=std::to_string(player.at(i)->getId());
            }
        }
    }catch(std::out_of_range){
        std::cout<<"Posizione Player - Out of Range";
    }

    //Tramite questo switch case ricavo quale costruzione è presente sopra la casella
    switch(box->getBoxConstruction()){
        case 0: //Nessuna costruzione (è ancora terreno)
            to_return+=" ";
            break;
        case 1: //é presente una casa
            to_return+="*";
            break;
        case 2: //é presente un albero
            to_return+="^";
            break;
    }

    //Per avere tutte caselle di uguale lunghezza nel caso in cui fosse presente solo un carattere tra i due delimitatori | |, aggiungo uno spazio vuoto
    if(to_return.length()==2) {
        to_return = "| "+to_return+"|";
    }
    else{
        to_return = "|"+to_return+"|";
    }
    return to_return;
};

//Funzione ausiliaria privata per ottenere gli spazi centrali del tabellone, ricevo un riferimento a uno stringstream 
void Board::Board::print_blank_space(std::stringstream& ss){
    for(int i=0; i<6; i++){
        ss <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<"";
     }
};


//FUNZIONI PUBBLICHE

//Costruttore 
Board::Board::Board(std::vector<Player*>& players_){
    //Associo il vector di giocatori che mi viene passato per riferimento
    this->players_ = players_;
    //Variabili utili per la creazione random delle caselle laterali
    int totCaselleEconomiche=0;
    int totCaselleStandard=0;
    int totCaselleLusso=0;
    int random_number;
    //Inizializzazione generatore casuale di numeri
    std::srand(std::time(NULL)); 
    //Creo le caselle da aggiungere al tabellone
    for(int i=0;i<NUMERO_CASELLE;i++){
        if(i==0){
            //Casella di partenza;
            //Aggiungo la casella di partenza al vector
            this->board.push_back(new Box(i, 0));
        }
        else if(i==7||i==14||i==21){ //Si tratta di una casella angolare in uno di questi casi
            //Le aggiungo al vector
            this->board.push_back(new Box(i, 1));
        }

        //Altrimenti si tratta di una casella laterale, quindi le genero casualmente
        else{
            /*
                Utilizzo un ciclo while tramite un valore booleano per controllare che la casella venga effettivamente aggiunta al tabellone
                Altrimenti potrebbe accadere che il numero generato randomicamente corrisponda
                ad una casella che ha raggiunto il numero massimo (ad esempio 8 caselle economiche su 8)
                Se dovesse succedere, senza il controllo con il valore booleano, l'iterazione del for si concluderebbe e l'indice i verrebbe incrementato
                senza però aver aggiunto alcun valore nel vector.
            */
            bool aggiunto = false; //Booleano di controllo
            while (!aggiunto) {
                random_number = (rand() % 3); // Generazione numero casuale tra 0, 1, 2
                if (random_number == RANDOM_CASELLA_E && totCaselleEconomiche < NUMERO_CASELLE_ECONOMICHE) {
                    totCaselleEconomiche++; //Incremento il numero di caselle economiche presenti all'interno del tabellone (del vector)
                    this->board.push_back(new Box(i, CASELLA_E)); //Aggiungo la casella al vector
                    aggiunto = true; //Aggiorno il booleano di controllo
                } else if (random_number == RANDOM_CASELLA_S && totCaselleStandard < NUMERO_CASELLE_STANDARD) {
                    totCaselleStandard++; //Incremento il numero di caselle Standard presenti nel tabellone
                    this->board.push_back(new Box(i, CASELLA_S)); //Aggiungo la casella al vector
                    aggiunto = true; //Aggiorno il booleano di controllo
                } else if (random_number == RANDOM_CASELLA_L && totCaselleLusso < NUMERO_CASELLE_LUSSO) {
                    totCaselleLusso++; //Incremento il numero di caselle Lusso all'interno del tabellone
                    this->board.push_back(new Box(i, CASELLA_L)); //Aggiungo la casella al vector
                    aggiunto = true; //Aggiorno la variabile di controllo
                }
            }
        }
    }
}


//Funzione pubblica per la stampa del tabellone
std::string Board::Board::print_board() {
    
    //Creo uno string stream così da poter formattare la stringa di output
    std::stringstream stream_string; 
    //Tramite un blocco try - catch controllo che gli indici utilizzati per il richiamo di parametri all'interno del vector siano corretti
    try{
        //Prima riga di stampa (coordinate numeriche)
        print_testata(stream_string);

        //Prima riga effettiva del tabellone
        stream_string<<"A"; //Aggiungo la lettera per le coordinate
        for(int i=14; i<=21; i++){ //Tramite un ciclo for stampo tutte le 8 caselle del tabellone
           stream_string<<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(this->board.at(i), this->players_);
        }
        stream_string<<std::endl;
        
        /*
            Per la stampa delle righe che vanno dalla 2 alla 7 richiamo le funzioni private create sopra tramite un ciclo for con due indici.
            In particolare per la stampa delle uniche due caselle presenti sulla riga richiamo la funzione string_to_print con l'indice della casella da stampare.
            Per stampare gli spazi bianchi presenti tra le due caselle richiamo la funzione print_blank_space che non è altro che un ciclo for.
        */
       int to_convert_in_char_ = 66;
       for(int i=13, j=22; i>=7 && j<=27; i--, j++){
            char line_letter = static_cast<char>(to_convert_in_char_);
            stream_string<<line_letter; //Aggiungo la lettera per le coordinate
            stream_string<<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(this->board.at(i), this->players_); //Stampo la casella a sinistra del tabellone
            print_blank_space(stream_string); //Stampo gli spazi all'interno del tabellone
            stream_string<<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(this->board.at(j), this->players_)<<std::endl; //Stampo la casella a destra del tabellone
            to_convert_in_char_++; //Incremento il carattere da stampare
       }

        //Ottava riga del tabellone
        stream_string<<"H";
        for(int i=7; i>=0; i--){
            stream_string <<std::setw(LARGHEZZA_CASELLA_STAMPA)<<string_to_print(this->board.at(i),this->players_);
        }
        
        stream_string<<std::endl;

    }catch(std::out_of_range){ //catch per evitare che si vada fuori dall'array con gli indici
        std::cout<<"Scoreboard - Out of Range";
    }
    return stream_string.str();
}

//Funzione pubblica per ricavare le informazioni della casella
Board::Box* Board::Board::getBox(int id_box) const{
    try{ //Tramite il blocco try-catch controllo che l'id che mi è stato passato sia valido
        return this->board.at(id_box);
    }catch(std::out_of_range){
        throw std::invalid_argument("Indice casella non valido!");
    }
}

//Funzione pubblica per stampare le coordinate delle costruzioni dei singoli giocatori
std::string Board::Board::print_player_costruction() const{
    //Ricavo le costruzioni di ogni giocatore dalla apposita funzione presente nella classe Player
    std::string log="";
    for(int i=0; i<this->players_.size();i++){
       log+="Giocatore "+std::to_string(i)+" "+players_.at(i)->logConstruction()+"\n";
    }
    return log;
}