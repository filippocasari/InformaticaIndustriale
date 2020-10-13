
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>

#ifdef NO_PI

#include <wiringPi.h>

#endif

using namespace std;


const int led_Blue = 0;
const int timeoutMs = 1000; // 1 second

const int stati[] = { 0,1,2 };
const int time1 = 2, time2 = 5, time3 = 4;
void waitingTime(unsigned int* countPointer, int* tempo);


void semaforo(unsigned int* countPointer, int* statocorrente, int* tempo);

///
/// Utils
///
void init() {
#ifdef NO_PI
    wiringPiSetup();
    pinMode(led_Blue, OUTPUT);
#endif
}

void setLed(int ledNumber, bool value) {
#ifdef NO_PI
    digitalWrite(ledNumber, value);
#else
    cout << "Setting led " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
#endif
}

int main() {
    init();

    unsigned int count = 0;
    int statocorrente = 0;
    int tempo = time1;
    while (true) {

        cout << "stato corrente= " << statocorrente << endl;

        semaforo(&count, &statocorrente, &tempo);

    }
    return 0;

}
void semaforo(unsigned int* countPointer, int* statocorrentePnt, int* tempo) {


    if (*statocorrentePnt == 0) {
        *statocorrentePnt = stati[2];
        *tempo = time2;
        waitingTime(countPointer, tempo);
        *countPointer = 0;
    }
    else if (*statocorrentePnt == 2) {
        *statocorrentePnt = stati[1];
        *tempo = time3;
        waitingTime(countPointer, tempo);
        *countPointer = 0;
    }
    else if (*statocorrentePnt == 1) {

        *tempo = time1;
        waitingTime(countPointer, tempo);
        *statocorrentePnt = stati[0];
        *countPointer = 0;
    }
}
void waitingTime(unsigned int* countPointer, int* tempo) {
    for (int i = 0; i < *tempo; i++) {
        *countPointer += 1;
        cout << "sono passati... " << *countPointer << " sec" << endl;
#ifdef NO_PI
        delay(timeoutMs);
#else
        Sleep(timeoutMs);
#endif
    }

}
