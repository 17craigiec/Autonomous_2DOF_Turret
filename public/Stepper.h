#include <vector>
#include <string>
#include <iostream>
#include <wiringPi.h>

#include "Timer.h"

using namespace std;

const int TICKS_PER_ROTATION = 800;
const double pi = 3.14159;

class Stepper
{
private:
    int m_dir_pin = -1;
    int m_pulse_pin = -1;
    double m_velocity = 0;
    Timer m_internal_timer;

    // This direction value is only altered if the positive motor direction is reversed
    int m_dir_offset = 1;

    bool pollInternalTimer(double seconds_per_tick);

public:

    Stepper(int direction_pin, int pulse_pin);
    ~Stepper();

    void inverseDirectionOffset();
    void setVelocity(double vel);

    // Poll step should be consistently called in a fast moving loop as to calculate when to update the step sequence
    void pollStep();
};