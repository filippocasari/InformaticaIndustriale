#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>

#endif

#include <iostream>

#ifndef NO_PI
#include <wiringPi.h>
#endif

using namespace std;

const int led_green = 0;

const int led_red = 2;

const int led_yellow = 1;
const int timeoutMs = 1000; // 1 second

const int stati[3] = {0, 1, 2};
const int Time[3] = {2, 3, 2};
void waitingTime(unsigned int *countPointer, int *tempo);

int semaforo(unsigned int *countPointer, int *statocorrentePnt, int *tempo);

///
/// Utils
///
void init()
{
#ifndef NO_PI
    wiringPiSetup();
    pinMode(led_red, OUTPUT);
    pinMode(led_green, OUTPUT);
    pinMode(led_yellow, OUTPUT);
    
#endif
}



int main()
{
    init();

    unsigned int count = 0;
    int statocorrente = stati[0];
    int tempo = Time[0];
    while (true)
    {

        cout << "stato corrente= " << statocorrente << endl;

        statocorrente = semaforo(&count, &statocorrente, &tempo);
    }
    return 0;
}
int semaforo(unsigned int *countPointer, int *statocorrentePnt, int *tempo)
{

    switch (*statocorrentePnt)
    {

    case (0):

        *statocorrentePnt = stati[1];
        cout<<*statocorrentePnt;

    case (1):
        *statocorrentePnt = stati[2];

    case (2):

        *statocorrentePnt = stati[0];

    }
    *countPointer = 0;
    *tempo = Time[*statocorrentePnt];
    waitingTime(countPointer, tempo);

    
    return (*statocorrentePnt);
}
void waitingTime(unsigned int *countPointer, int *tempo)
{
    for (int i = 0; i < *tempo; i++)
    {
        *countPointer += 1;
        cout << "sono passati... " << *countPointer << " sec" << endl;
#ifndef NO_PI
        delay(timeoutMs);
#else
        sleep(timeoutMs / 1000);
#endif
    }
}
