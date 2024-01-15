Per poter compilare il codice è necessario, all'interno della cartella del progetto, creare una cartella build.
All'interno di questa richiamiamo il comando cmake.. seguito da make.
Per poter avviare effettivamente il gioco abbiamo due possibilità:

./main human -> per una partita con 3 computer (è accettato anche la stringa con la lettera H maiuscola)

./main computer -> per una partita automatica tra 4 computer (è accettata anche la stringa con la lettera C maiuscola)

Una volta terminata la partita, il rispettivo file di log verrà salvato all'interno della cartella build, così da evitare la sovrascrittura di quello già presente all'interno 
della cartella del progetto che, come da istruzioni, va consegnato.

Punti di attenzione:

- Nel file main.cpp ci sono alcune righe commentate, sia per quanto riguarda la partita tra 4 computer sia per quella tra 3 computer e un umano.
Queste righe di codice riguardano la stampa e la scrittura su file dei saldi finali di ogni giocatore. 

- Il distruttore è stato inserito all'interno di tabellone così che, con un opportuno sviluppo, è possibile riutilizzare le stesse caselle e gli stessi giocatori in più partite.

- Le opzioni di ottimizzazione (-O2) sono già attive poiché è stato aggiunto il flag al CMakeLists.txt

- È stata fatta la scelta di non eseguire stampe relative a pernottamenti con costo di 0 fiorini, per mancanza di utilità pratica
