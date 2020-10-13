

///
/// NOTE On Desktop systems, compile with -D NO_PI flag
//

#ifdef _WIN32
#include <Windows.h>
#else

#include <unistd.h>
#include <pthread.h>
#include <crypt.h>
#include <fcntl.h>
#endif

#include <iostream>

#ifndef NO_PI

#include <wiringPi.h>

#endif

using namespace std;

///
/// Configuration
///
const int led_Blue = 0;
const int timeoutMs = 1000; // 1 second

const int stati[]={0,1,2};
const int time1=2, time2=5, time3=4;



void semaforo(unsigned int *countPointer, int *statocorrente, int *tempo);

///
/// Utils
///
void init() {
#ifndef NO_PI
    wiringPiSetup();
    pinMode(led_Blue, OUTPUT);
#endif
}

void setLed(int ledNumber, bool value) {
#ifndef NO_PI
    digitalWrite(ledNumber, value);
#else
    cout << "Setting led " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
#endif
}

int main() {
    init();

    // Ok, inited. Now do your work...


    unsigned int count = 0;
    int statocorrente=0;
    int tempo=time1;
    while (true) {
        // We can now add our custom logics here
        /////
        cout << "stato corrente= " << statocorrente << endl;

        // If this led blinks, then the loop is working


        semaforo(&count, &statocorrente, &tempo);

        // Increment timer counter
        delay(timeoutMs * tempo);
    }
    return 0;





}
void semaforo(unsigned int *countPointer, int *statocorrentePnt, int *tempo) {
    *countPointer += 1;
    cout<<*countPointer<<endl;
    if (*countPointer >= time1 && *statocorrentePnt == 0) {
        *statocorrentePnt = stati[2];
        *tempo=time2;
        *countPointer = 0;
    } else if (*countPointer >= time2 && *statocorrentePnt == 2) {
        *statocorrentePnt = stati[1];
        *tempo=time3;
        *countPointer = 0;
    } else if (*countPointer >= time3 && *statocorrentePnt == 1) {
        *countPointer = 0;
        *tempo=time1;
        *statocorrentePnt = stati[0];
    }
}