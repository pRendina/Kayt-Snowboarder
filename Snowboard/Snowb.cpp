#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <cctype>
#include <math.h>
using namespace std;

class partecipanti {
private:
    string matricola;
    string cogn;
    int x;
    int y;

public:
    partecipanti(int ordine) {
        this->cogn = genNome();
        this->matricola = genMatricola(ordine);
        x = 0;
        y = 0;
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

};


int main() {
    srand(time(NULL));
    partecipanti* guest = new partecipanti(1);
    cout << guest->getMatricola()<<endl;

    return 0;
}
