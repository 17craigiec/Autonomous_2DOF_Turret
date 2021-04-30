#include "../public/Stepper.h"

using namespace std;

// INPUTS ( pin #'s: 1-40 )
Stepper::Stepper(int direction_pin, int pulse_pin)
{
    wiringPiSetup();
    pinMode(direction_pin, OUTPUT);
    pinMode(pulse_pin, OUTPUT);

    // Associate pins
    m_dir_pin = direction_pin;
    m_pulse_pin = pulse_pin;

    // Set direction orientation on construction
    m_dir_offset = 1;

    m_internal_timer.reset();
}

Stepper::~Stepper()
{
}

void Stepper::setVelocity(double vel)
{   
    m_velocity = vel * m_dir_offset;

    if(m_velocity != 0)
    {
        // cout << "velocity set... seconds per tick: " << 1/(abs(m_velocity)*(1/(2*pi))*TICKS_PER_ROTATION) << endl;
    }
}

void Stepper::inverseDirectionOffset()
{
    m_dir_offset = -1 * m_dir_offset;
}

void Stepper::pollStep()
{
    if(m_velocity != 0)
    {
        // vel in rad/s
        // to calculate time delay per tick, we must calculate ticks/s
        //                          1/( (rad/s) * (rot/rad) * (ticks/rot) )
        double seconds_per_tick = 1/(abs(m_velocity)*(1/(2*pi))*TICKS_PER_ROTATION);

        if(pollInternalTimer(seconds_per_tick))
        {
            // Set the dir pin appropriately
            if (m_velocity < 0)
            {
                digitalWrite(m_dir_pin, 0);
                // cout << "Pulse -1" << endl;
            }
            else
            {
                digitalWrite(m_dir_pin, 1);
                // cout << "Pulse 1" << endl;
            }

            // Pulse the stepper
            digitalWrite(m_pulse_pin, 1);
            delay(0.001);
            digitalWrite(m_pulse_pin, 0);
        }
    }
}

bool Stepper::pollInternalTimer(double seconds_per_tick)
{
    bool time_exceeded = false;

    if(m_internal_timer.elapsed() > seconds_per_tick)
    {
        m_internal_timer.reset();
        time_exceeded = true;
    }

    return time_exceeded;
}