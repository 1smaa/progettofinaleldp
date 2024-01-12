#include <iostream>
#include <ctime>
#include "Dadi.h"

/*
*   CIAN IRENE
*/


Dadi::Dadi() {
//inizializzazione generatore di numeri casuali
    std::srand(std::time(NULL));
}
int Dadi::lancia() const {
    int dado1= (rand()%6) +1; //lancio del primo dado
    int dado2 = (rand()%6) +1; //lancio del secondo dado
    return dado1 + dado2;
}
