/*! \file Snowb.cpp
    \author Pasquale Rendina
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
    \brief classe per identificare un singolo giocatore e le relative azioni che compie
*/
class partecipanti {
private:
    string matricola; //! \var matricola    \brief indica il codice matricola identificativo
    string cogn;      //! \var cogn         \brief cognome partecipante
    int x[30];        //! \var x[]          \brief posizione del partecipante sull'asse x
    int y[30];        //! \var y[]          \brief posizione del partecipante sull'asse y
    int distanza;     //! \var distanza     \brief distanza percorsa dal partecipante

public:
    /*! \fn partecipanti
        \brief costruttore
        \param ordine di arrivo
    */
    partecipanti(int ordine) {
        this->cogn = genNome();
        this->matricola = genMatricola(ordine);
        x[0] = 0;
        y[0] = 0;
        this->distanza = calcola_distanza();
    }

    /*! \fn genNome
        \brief genera casualmente il cognome del partecipante attingendo da un file
        \return nome
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
        \brief genera il codice matricola identificativo del partecipante
        \return matri
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
        \brief ritorna il valore della matricola
        \return matricola
    */
    string getMatricola() {
        return matricola;
    }

    /*! \fn getNome
        \brief ritorna il valore del cognome
        \return cogn
    */
    string getNome(){
        return cogn;
    }

    /*! \fn getX
        \brief ritorna il valore della coordinata x del partecipante ad uno specifico momento della gara
        \param momento rispetto alla quale ritornare la posizione
        \return x
    */
    int getX(int i){
        return x[i];
    }

    /*! \fn getY
        \brief ritorna il valore della coordinata y del partecipante ad uno specifico momento della gara
        \param momento rispetto alla quale ritornare la posizione
        \return y
    */
    int getY(int i){
        return y[i];
    }

    /*! \fn posizioni
        \brief genera casualmente le 30 posizioni del partecipante durante la gara
    */
    void posizioni(){
        for(int i=1; i<30; i++){
            x[i] = x[i-1] + rand()%5;
            y[i] = y[i-1] + rand()%5;
        }

    }

    /*! \fn calcola_distanza
        \brief calcola la distanza percorsa dal partecipante
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

    /*! \fn getY
        \brief ritorna la distanza
        \return distanza
    */
    int getDistanza(){
        return distanza;
    }
};

/*! \fn scriviFile
    \brief memorizza sul file "concorrenti.txt" matricola, cognome e tutte le coordinate
    \param il vettore dei partecipanti
*/
void scriviFile(partecipanti* guest){
    fstream fout("concorrenti.txt", ios::app);
    fout<<guest->getNome()<<", "<<guest->getMatricola()<<", ";
    for(int i=0; i<30; i++)
        fout<<guest->getX(i)<<" "<<guest->getY(i)<<", ";
    fout<<endl;
    fout.close();
}

/*! \fn whoWin
    \brief mostra a schermo la classifica dei vincitori
    \param il vettore dei partecipanti
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

/*! \fn printStat
    \brief stampa a schermo le matricola, cognome, ultime coordinate e distanza percorsa di ogni giocatore
    \param il vettore dei partecipanti
*/
void printStat(partecipanti* guest[]){
    for(int i=0; i<N; i++){
        cout<<"PARTECIPANTE "<<i+1<<": "<<guest[i]->getMatricola()<<" "<<guest[i]->getNome()<<endl<<endl;
        cout<<"\tUltime Coordinate: ("<<guest[i]->getX(29)<<", "<<guest[i]->getY(29)<<") \tDistanza percorsa: "<<guest[i]->getDistanza()<<"km\n\n\n";
    }
}

/*! \fn moreStat
    \brief stampa a schermo le matricola, cognome, tutte le coordinate e distanza percorsa di ogni giocatore
    \param il vettore dei partecipanti
*/
void moreStat(partecipanti* guest[]){
    system("cls");
    cout<<"STATISTICHE SPECIFICHE\n\n";
    for(int i=0; i<N; i++){
        cout<<"PARTECIPANTE "<<i+1<<": "<<guest[i]->getMatricola()<<" "<<guest[i]->getNome()<<endl<<endl;
        for(int k=0; k<30; k++){
            if(k%2 != 0 || k == 0)
                cout<<"\t";

            cout<<"("<<guest[i]->getX(k)<<", "<<guest[i]->getY(k)<<")";
            if(k%2 == 0)
                cout<<endl;
        }

        cout<<"\n\tDistanza percorsa: "<<guest[i]->getDistanza()<<"km\n\n\n";
    }

}

/*! \fn clearFile
    \brief pulisce il file
*/
void clearFile(){
    fstream fout("concorrenti.txt", ios::out);

    fout<<"";

    fout.close();
}

/*! \fn menu
    \brief stampa su schermo il menu e attraverso la scelta richiama le funzioni appropriate
*/
void menu(){
    int scelta;
    partecipanti* guest[N];

    do{
        cout<<"\n\nSIMULATORE DI UNA COMPETIZIONE DI KAYT SNOWBOARDING\n\n"
        <<"1] Avvia simulazione\n"
        <<"2] Mostra specifiche dei concorrenti\n"
        <<"3] Mostra podio\n"
        <<"3] ESCI\n>>";

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

int main() {
    srand(time(NULL));

    menu();

    return 0;
}

