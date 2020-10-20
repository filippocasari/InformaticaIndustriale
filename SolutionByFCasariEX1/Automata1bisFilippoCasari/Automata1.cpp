#include <iostream>
#include <string>

using namespace std;

#include <sstream>


char matricetot[][3]={   {'0', 'a','2'},
                         {'0', 'b', '1'}, 
                         {'0','c','3'},
                         {'1','b','1'},
                         {'1','c','3'},
                        {'2','a','0'}   };


void printMatrix(int dimensione);

int findfun( int statocorrente, char lettera, int dimensione, bool *flag);

int main() {


    char matricestati[4] = {'0', '1', '2', '3'};
    char matricelettere[3] = {'a', 'b', 'c'};
    int size1 = sizeof(matricestati);
    int size2 = sizeof(matricelettere);
    int dimensione = (size1 * size2);
    int statocorrente = 0;
 
    char lettera;

    printMatrix( dimensione);

    do {
        bool flag = false;
        cout << "inserisci lettera (q per uscire dal programma): ";
        cin >> lettera;
        if (lettera == 'q') {
            cout << "uscita dal programma!" << endl;
            break;
        }
        statocorrente = findfun(statocorrente, lettera, dimensione, &flag);

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

int findfun(int statocorrente, char lettera, int dimensione, bool *flag) {

    for (int i = 0; i < dimensione; i++) {
        stringstream str;
        str << matricetot[i][0];
        int x;
        str >> x;
        if (statocorrente == x and lettera == matricetot[i][1] ) {
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

void printMatrix(int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matricetot[i][j] << " ";
        }
        cout << endl;
    }
}

