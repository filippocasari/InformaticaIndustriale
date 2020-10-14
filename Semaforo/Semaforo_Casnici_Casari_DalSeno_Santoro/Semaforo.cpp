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

int current_state = 0, numOfCycles = 0;
int states[4][2] = {{0,2},{1,0},{2,1},{3,1}};
const string states_out[4][2] = {{"Led Red OFF", "Led Red ON"},
				                {"Led Yellow OFF","Led Yellow ON"},
				                {"Led Green OFF","Led Green ON"},
				                {" ","All Led OFF"}};
                    

void mfn(int current_state, int in){
	cout << states_out[current_state][in] << endl;
}

int timers[4] = {200,100,200,300};

#define LED1 2 //ledgreen
#define LED2 1 //ledyellow
#define LED3 0 //led_red

void wait(int time)
{
#ifndef NO_PI
    delay(time);
#else
    usleep(time*1000);
#endif

}

void allLedOff(){
    #ifndef NO_PI
    for (int i = 0; i < 3; i++){
        digitalWrite(i,0);
    }
    #endif
}

void trafficLighError(){
    states[1][1] = 3;
    numOfCycles = 0;
    current_state = 1; 
    
    #ifndef NO_PI
    digitalWrite(current_state,1);
    wait(timers[3]);
    #else
    mfn(current_state, 1);
    usleep(timers[3]*1000);
    #endif

    while(true) {   
        numOfCycles++;
        if (numOfCycles > 20) { //Go back when we turn on Yellow for 10 times
            states[1][1] = 0;
            return;
        } 
        current_state = states[current_state][1];
        #ifndef NO_PI
        if(current_state == 3){
            allLedOff();
        } else {
            digitalWrite(current_state,1);
        }
        wait(timers[3]);
        #else
        mfn(current_state, 1);
        usleep(timers[3]*1000);
        #endif
    
        cout << "current state: " << current_state <<endl;
        cout << "time passed: " << timers[3] << "ms" <<endl;
    }

    
}


void go()
{	
    #ifndef NO_PI
    digitalWrite(current_state,1);
    wait(timers[current_state]);
    #else
    mfn(current_state, 1);
    usleep(timers[current_state]*1000);
    #endif
    while(true)
    {   
        numOfCycles++;
        if (numOfCycles > 30){ //Error when we turn on RED for 10 times
            trafficLighError();
            numOfCycles = 0;
            current_state = 1;
        }  
       
        #ifndef NO_PI
        digitalWrite(current_state,0);
        #else
        mfn(current_state, 0);
        usleep(timers[current_state]*1000);
        #endif
        current_state = states[current_state][1];
        cout << "current state: " << current_state <<endl; 
        #ifndef NO_PI
        digitalWrite(current_state,1);
        wait(timers[current_state]);
        #else
        mfn(current_state, 1);
        usleep(timers[current_state]*1000);
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
