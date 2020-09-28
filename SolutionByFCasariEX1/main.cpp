#include <iostream>
#include <string>

using namespace std;

#include <sstream>


void creaMatrice(const char *matricestati, const char *matricelettere, char matricetot[][3],
                 int dimensione, int size2);

void printMatrix(char matricetot[][3], int dimensione);

int findfun(char matricetot[][3], int statocorrente, char lettera, int dimensione, bool *flag);

int main() {


    char matricestati[4] = {'0', '1', '2', '3'};
    char matricelettere[3] = {'a', 'b', 'c'};
    int size1 = sizeof(matricestati);
    int size2 = sizeof(matricelettere);
    int dimensione = (size1 * size2);
    int statocorrente = 0;
    char matricetot[dimensione][3];

    creaMatrice(matricestati, matricelettere, matricetot, dimensione, size2);
    char lettera;
    printMatrix(matricetot, dimensione);
    do {
        bool flag = false;
        cout << "inserisci lettera (q per uscire dal programma): ";
        cin >> lettera;
        if (lettera == 'q') {
            cout << "uscita dal programma!" << endl;
            break;
        }
        statocorrente = findfun(matricetot, statocorrente, lettera, dimensione, &flag);

        cout << "stato corrente=" << statocorrente << endl;
        if (flag) {
            cout << "trovato" << endl;
            if (lettera == 'c') {
                break;
            }
        } else {
            cout << "Errore, nessuna corrispondenza (statocorrente, input), riprova o esci" << endl;

        }


    } while (true);

}


void creaMatrice(const char *matricestati, const char *matricelettere, char matricetot[][3], int dimensione,
                 int size2) {


    int indicestato = -1;
    int indicelettera = -1;
    for (int i = 0; i < dimensione; i++) {


        if (i % size2 == 0) {
            indicestato++;
        }
        matricetot[i][0] = matricestati[indicestato];

        indicelettera++;
        if ((indicelettera) % (size2) == 0) {
            indicelettera = 0;
        }
        matricetot[i][1] = matricelettere[indicelettera];
        matricetot[i][2] = 'N';

    }
    matricetot[0][2] = '2';
    matricetot[1][2] = '1';
    matricetot[2][2] = '3';


    matricetot[4][2] = '1';
    matricetot[5][2] = '3';
    matricetot[6][2] = '0';


}

int findfun(char matricetot[][3], int statocorrente, char lettera, int dimensione, bool *flag) {

    for (int i = 0; i < dimensione; i++) {
        stringstream str;
        str << matricetot[i][0];
        int x;
        str >> x;
        if (statocorrente == x and lettera == matricetot[i][1] and matricetot[i][2] != 'N') {
            statocorrente = (int(matricetot[i][2]));
            statocorrente = statocorrente - 48;
            *flag = true;
            if (statocorrente == 3) {
                cout << "FINE PROGRAMMA" << endl;
            }
            break;

        }
    }
    return statocorrente;


}

void printMatrix(char matricetot[][3], int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matricetot[i][j] << " ";
        }
        cout << endl;
    }
}

