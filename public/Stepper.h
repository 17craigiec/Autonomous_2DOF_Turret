#include <vector>
#include <string>
#include <iostream>
#include <wiringPi.h>

#include "Timer.h"

using namespace std;

const int TICKS_PER_ROTATION = 200;
const double pi = 3.14159;

class Stepper
{
private:
    struct Pins
    {
        int p0 = -1;
        int p1 = -1;
        int p2 = -1;
        int p3 = -1;
    }m_pins;
    
    // These three variables keep track of the steppers status
    vector<vector<bool>> m_cycle = 
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,1,1},
        {1,0,0,1}
    };
    int m_cycle_index = 0;
    double m_velocity = 0;
    Timer m_internal_timer;

    // This direction value is only altered if the positive motor direction is reversed
    int m_dir = 1;

    bool pollInternalTimer(double seconds_per_tick);
    void writePins();

public:

    Stepper(int pin0, int pin1, int pin2, int pin3, int direction);
    ~Stepper();

    void setVelocity(double vel);
    void motorOff();

    // Poll step should be consistently called in a fast moving loop as to calculate when to update the step sequence
    void pollStep();
};