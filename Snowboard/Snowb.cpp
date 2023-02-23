#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <cctype>
#include <math.h>

#define  N  6

using namespace std;

class partecipanti {
private:
    string matricola;
    string cogn;
    int x;
    int y;
    int distanza;

public:
    partecipanti(int ordine) {
        this->cogn = genNome();
        this->matricola = genMatricola(ordine);
        x = 0;
        y = 0;
        this->distanza = calcola_distanza();
    }

    string genNome() {
        string s;
        fstream fin("nomi.txt", ios::in);
        if (!fin)
            cout << "Errore\n";
        else {
            int n_cogn = rand() % 20;
            int i = 0;

            while (i != n_cogn) {
                getline(fin, s);
                i++;
            }
        }
        fin.close();
        return s;
    }

    string genMatricola(int ordine) {
        string matri;
        char c = toupper(cogn[2]);

        if(ordine<10)
            matri = cogn.substr(0, 1) + c + '0' + to_string(ordine);
        else
            matri = cogn.substr(0, 1) + c + to_string(ordine);
        return matri;
    }

    string getMatricola() {
        return matricola;
    }

    string getNome(){
        return cogn;
    }


    int getX(){
        return x;
    }

    int getY(){
        return y;
    }

    void posizioni(){
        x = getX() + rand()%20;
        y = getY() + rand()%20;
    }

    void crea_piano(int x,int y){
        string matrice[100][100];

        for(int i=0; i<10; i++){
            for(int k=0; k<10; k++){
                if(i==y && k==x)
                    matrice[i][k] = "0";
                else
                    matrice[i][k] = "1";
            }
        }

        for(int i=0; i<10; i++){
            for(int k=0; k<10; k++){
                cout<<matrice[i][k];
            }
            cout<<endl;
        }
    }

    int calcola_distanza(){
        int distanza = 0;
        int xprec,yprec;
        for(int i = 0; i<5; i++){
            xprec = getX();
            yprec = getY();
            posizioni();
            //crea_piano(getX(),getY());
            distanza += sqrt(pow((getX()-xprec),2) + pow((getY()-yprec),2));
        }
        return distanza;
    }

    int getDistanza(){
        return distanza;
    }
};

void scriviFile(partecipanti* guest){
    fstream fout("concorrenti.txt", ios::app);
    fout<<guest->getNome()<<", "<<guest->getMatricola()<<", "<<guest->getDistanza()<<endl;
    fout.close();
}

void whoWin(){

}

void printStat(partecipanti* guest[]){


    for(int i=0; i<N; i++){
        cout<<"PARTECIPANTE "<<i+1<<": "<<guest[i]->getMatricola()<<" "<<guest[i]->getNome()<<endl<<endl;
        cout<<"\tUltime Coordinate: ("<<guest[i]->getX()<<", "<<guest[i]->getY()<<") \tDistanza percorsa: "<<guest[i]->getDistanza()<<"km\n\n\n";
    }
}

int main() {
    srand(time(NULL));
    partecipanti* guest[N];

    for(int i=0; i<N; i++){
        guest[i] = new partecipanti(i+1);
        scriviFile(guest[i]);
    }

    printStat(guest);

    return 0;
}

