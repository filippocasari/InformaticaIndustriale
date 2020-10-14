#include <iostream>


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#ifndef NO_PI
#include <wiringPi.h>
#endif

using namespace std;

int current_state = 0;
int states[3][2] = {{0,2},{1,0},{2,1}};
int timers[3] = {2000,1000,2000};
#define LED1 2 //ledgreen
#define LED2 1 //ledyellow
#define LED3 0 //led_red


void wait(int time)
{
#ifndef NO_PI
    delay(time);
#else
    Sleep(time);
#endif

}

void go()
{	
    while(true)
    {
        #ifndef NO_PI
        digitalWrite(current_state,0);
        #endif
        current_state = states[current_state][1];
        cout << "current state: " << current_state <<endl;
        #ifndef NO_PI
        digitalWrite(current_state,1);
        wait(timers[current_state]);
        #endif
        cout << "time passed: " << timers[current_state] << "ms" <<endl;
    }
	
}

int main()
{
    #ifndef NO_PI
        wiringPiSetup();
        pinMode(LED3, OUTPUT);
        pinMode(LED2, OUTPUT);
        pinMode(LED1, OUTPUT);
    #endif
    go();
    
   return 0;
}