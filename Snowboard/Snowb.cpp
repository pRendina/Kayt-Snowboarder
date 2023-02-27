/*! \file Snowb.cpp
    \author Pasquale Rendina
    \bug Lla generazione del nome non sempre va a buon fine
*/

#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <cctype>
#include <math.h>

#define  N  6

using namespace std;

/*! \class partecipanti
    \brief Classe per identificare un singolo giocatore e le relative azioni che compie
*/
class partecipanti {
private:
    string matricola; //! \var matricola    \brief Indica il codice matricola identificativo
    string cogn;      //! \var cogn         \brief Cognome partecipante
    int x[30];        //! \var x[]          \brief Posizione del partecipante sull'asse x
    int y[30];        //! \var y[]          \brief Posizione del partecipante sull'asse y
    int distanza;     //! \var distanza     \brief Distanza percorsa dal partecipante

public:
    /*! \fn partecipanti
        \brief Costruttore
        \param[in] ordine Ordine di arrivo
    */
    partecipanti(int ordine) {
        this->cogn = genNome();
        this->matricola = genMatricola(ordine);
        x[0] = 0;
        y[0] = 0;
        this->distanza = calcola_distanza();
    }

    /*! \fn genNome
        \brief Genera casualmente il cognome del partecipante attingendo da un file
        \return cognome generato
    */
    string genNome() {
        string cognome;
        fstream fin("nomi.txt", ios::in);
        if (!fin)
            cout << "Errore\n";
        else {
            int n_cogn = rand() % 33;
            int i = 0;

            while (i != n_cogn) {
                getline(fin, cognome);
                i++;
            }
        }
        fin.close();
        return cognome;
    }

    /*! \fn genMatricola
        \brief Genera il codice matricola identificativo del partecipante
        \param[in] ordine Ordine di arrivo dei partecipanti
        \return matricola
    */
    string genMatricola(int ordine) {
        string matri;
        char c = toupper(cogn[2]);

        if(ordine<10)
            matri = cogn.substr(0, 1) + c + '0' + to_string(ordine);
        else
            matri = cogn.substr(0, 1) + c + to_string(ordine);
        return matri;
    }

    /*! \fn getMatricola
        \brief Ritorna il valore della matricola
        \return matricola
    */
    string getMatricola() {
        return matricola;
    }

    /*! \fn getNome
        \brief Ritorna il valore del cognome
        \return cognome
    */
    string getNome(){
        return cogn;
    }

    /*! \fn getX
        \brief Ritorna il valore della coordinata x del partecipante ad uno specifico momento della gara
        \param[in] i Momento rispetto alla quale ritornare la posizione
        \return x
    */
    int getX(int i){
        return x[i];
    }

    /*! \fn getY
        \brief Ritorna il valore della coordinata y del partecipante ad uno specifico momento della gara
        \param[in] i Momento rispetto alla quale ritornare la posizione
        \return y
    */
    int getY(int i){
        return y[i];
    }

    /*! \fn posizioni
        \brief Genera casualmente le 30 posizioni del partecipante durante la gara
    */
    void posizioni(){
        for(int i=1; i<30; i++){
            x[i] = x[i-1] + rand()%5;
            y[i] = y[i-1] + rand()%5;
        }
    }

    /*! \fn calcola_distanza
        \brief Calcola la distanza percorsa dal partecipante
        \return distanza
    */
    int calcola_distanza(){
        int distanza = 0;
        int xprec,yprec;
        posizioni();
        for(int i = 1; i<30; i++)
            distanza += sqrt(pow((x[i]-x[i-1]),2) + pow((y[i]-y[i-1]),2));

        return distanza;
    }

    /*! \fn getDistanza
        \brief Ritorna la distanza
        \return distanza
    */
    int getDistanza(){
        return distanza;
    }
};

/*!
    \brief Memorizza sul file "concorrenti.txt" matricola, cognome e tutte le coordinate
    \param[in] guest Partecipante passato singolarmente all'interno di un ciclo nel main
*/
void scriviFile(partecipanti* guest){

    fstream fout("concorrenti.txt", ios::app);
    fout<<guest->getNome()<<", "<<guest->getMatricola()<<", ";
    for(int i=0; i<30; i++)
        fout<<guest->getX(i)<<" "<<guest->getY(i)<<", ";
    fout<<endl;
    fout.close();
}

/*!
    \brief Mostra a schermo la classifica dei vincitori
    \param[in] guest[] Vettore dei partecipanti
*/
void whoWin(partecipanti* guest[]) {
    cout << "CLASSIFICA\n\n";
     for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (guest[j]->getDistanza() < guest[j + 1]->getDistanza()) {
                partecipanti* temp = guest[j];
                guest[j] = guest[j + 1];
                guest[j + 1] = temp;
            }
        }
    }

    cout << "\t " << 1 << ") " << guest[0]->getMatricola() << " " << guest[0]->getNome() << "     Distanza: " << guest[0]->getDistanza() << "km" << endl <<endl;
    cout << "\t\t " << 2 << ") " << guest[1]->getMatricola() << " " << guest[1]->getNome() << "     Distanza: " << guest[1]->getDistanza() << "km" << endl <<endl;
    cout << "\t\t\t" << 3 << ") " << guest[2]->getMatricola() << " " << guest[2]->getNome() << "      Distanza: " << guest[2]->getDistanza() << "km" << endl <<endl;

    cout<<"RESTO CLASSIFICA\n\n";
    for (int i = 3; i < N; i++)
        cout << i + 1 << ") " << guest[i]->getMatricola() << " " << guest[i]->getNome() << "     Distanza: " << guest[i]->getDistanza() << "km" << endl;

}

/*!
    \brief Stampa a schermo le matricola, cognome, ultime coordinate e distanza percorsa di ogni giocatore
    \param[in] guest[] Vettore dei partecipanti
*/
void printStat(partecipanti* guest[]){
    for(int i=0; i<N; i++){
        cout<<"PARTECIPANTE "<<i+1<<": "<<guest[i]->getMatricola()<<" "<<guest[i]->getNome()<<endl<<endl;
        cout<<"\tUltime Coordinate: ("<<guest[i]->getX(29)<<", "<<guest[i]->getY(29)<<") \tDistanza percorsa: "<<guest[i]->getDistanza()<<"km\n\n\n";
    }
}

/*!
    \brief stampa a schermo le matricola, cognome, tutte le coordinate e distanza percorsa di ogni giocatore
    \param[in] guest[] Vettore dei partecipanti
*/
void moreStat(partecipanti* guest[]){
    system("cls");
    cout<<"STATISTICHE SPECIFICHE\n\n";
    for(int i=0; i<N; i++){
        cout<<"PARTECIPANTE "<<i+1<<": "<<guest[i]->getMatricola()<<" "<<guest[i]->getNome()<<"\n\nCoordinate durante la gara\n";
        for(int k=0; k<30; k++){
            if(k<9)
                cout<<"23:0"<<k+1<<"\t("<<guest[i]->getX(k)<<", "<<guest[i]->getY(k)<<")\n";
            else
                cout<<"23:"<<k+1<<"\t("<<guest[i]->getX(k)<<", "<<guest[i]->getY(k)<<")\n";
        }

        cout<<"\n\tDistanza percorsa: "<<guest[i]->getDistanza()<<"km\n\n\n";
    }
}

/*! \fn clearFile
    \brief Pulisce il file
*/
void clearFile(){
    fstream fout("concorrenti.txt", ios::out);

    fout<<"";

    fout.close();
}

/*! \fn menu
    \brief Stampa su schermo il menu e attraverso la scelta richiama le funzioni appropriate
*/
void menu(){
    int scelta;
    partecipanti* guest[N];

    do{
        cout<<"\n\nSIMULATORE DI UNA COMPETIZIONE DI KITE SNOWBOARDING\n\n"
        <<"1] Avvia simulazione\n"
        <<"2] Mostra specifiche dei concorrenti\n"
        <<"3] Mostra podio\n"
        <<"4] ESCI\n>>";

        cin>>scelta;

        switch(scelta){
            case 1: system("cls");
                    clearFile();
                    for(int i=0; i<N; i++){
                        guest[i] = new partecipanti(i+1);
                        scriviFile(guest[i]);
                    }
                    printStat(guest);
                    break;

            case 2: moreStat(guest);
                    break;

            case 3: whoWin(guest);
                    break;

        }
    }while(scelta!=4);
}

//! \brief Software che simula una gara di kite snowboarding
int main() {
    srand(time(NULL));

    menu();

    return 0;
}

