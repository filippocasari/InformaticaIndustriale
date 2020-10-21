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
const int led_yellow = 1;
const int led_red = 2;

const int timeoutMs = 1000; // 1 second

const int stati[3] = {0, 1, 2};
const int Time[3] = {2, 3, 2};

void waitingTime(unsigned int *countPnt, int *tempo);

int NormalCycle(unsigned int *countPointer, int *statocorrentePnt, int *tempo);

void  errorState();

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

        statocorrente = NormalCycle(&count, &statocorrente, &tempo);
    }
    return 0;
}
int NormalCycle(unsigned int *countPnt, int *statocorrentePnt, int *tempo)
{
    if (*countPnt % 10 == 0) {
        errorState();
    }

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
    
    *tempo = Time[*statocorrentePnt];
    waitingTime(countPnt, tempo);

    return (*statocorrentePnt);
}
void waitingTime(unsigned int *countPnt, int *tempo)
{
    int i;
    for (i = 1; i =< *tempo; i++)
    {
        
        cout << "sono passati... " << i << " sec" << endl;
#ifndef NO_PI
        delay(timeoutMs);
#else
        sleep(timeoutMs / 1000);
#endif
    }
    *counterPnt += i;
}

void  errorState() {
    cout << "error!!\n";
}
