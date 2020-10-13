#include <iostream>
#include <wiringPi.h>

using namespace std;

int current_state = 0;
int states[3][2] = {{0,2},{1,0},{2,1}};
int timers[3] = {2000,1000,2000}
int led_green = 2;
int led_yellow = 1;
int led_red = 0;

void wait(int time)
{
    delay(time);
}

void go()
{	
    while(True)
    {
        digitalWrite(current_state,0);
        current_state = states[current_state][1];
        cout << "current state: " << current_state <<endl;
        digitalWrite(current_state,1);
        wait(timers[current_state]);
        cout << "time passed: " << timers[current_state] << "ms" <<endl;
    }
	
}

int main()
{
    wiringPiSetup();
	pinMode(0, OUTPUT);
    pinMode(1, OUTPUT);
    pinMode(2, OUTPUT);

    go();
    
   return 0;
}