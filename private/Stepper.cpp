#include "../public/Stepper.h"

using namespace std;

// INPUTS ( pin #'s: 1-40 )
Stepper::Stepper(int pin0, int pin1, int pin2, int pin3)
{
    wiringPiSetup();
    pinMode(pin0, OUTPUT);
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    pinMode(pin3, OUTPUT);

    // Associate pins with the private struct
    m_pins.p0 = pin0;
    m_pins.p1 = pin1;
    m_pins.p2 = pin2;
    m_pins.p3 = pin3;

    // Set direction orientation on construction
    m_dir = 1;

    m_internal_timer.reset();
}

Stepper::~Stepper()
{
}

void Stepper::setVelocity(double vel)
{
    m_velocity = vel;
}

void Stepper::inverseDirection()
{
    m_dir = -1*m_dir;
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
            if(m_velocity > 0)
            {
                m_cycle_index++;
            }
            else
            {
                m_cycle_index--;
            }
            
            m_cycle_index = m_cycle_index%m_cycle.size();
            writePins();
            cout << "Step: " << m_cycle_index << "   Target Time: " << seconds_per_tick << endl;
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

void Stepper::writePins()
{
    for(int i = 0; i < 4; i++)
    {
        bool write_status = m_cycle[m_cycle_index][i];

        switch(i)
        {
        case 0:
            digitalWrite(m_pins.p0, write_status);
            break;

        case 1:
            digitalWrite(m_pins.p1, write_status);
            break;

        case 2:
            digitalWrite(m_pins.p2, write_status);
            break;

        case 3:
            digitalWrite(m_pins.p3, write_status);
            break;
        
        default:
            cout << "ERROR: Indexed past writable pins" << endl;
            break;
        }

        cout << write_status;
    }

    cout << endl;
}

void Stepper::motorOff()
{
    setVelocity(0);

    bool write_status = false;
    digitalWrite(m_pins.p0, write_status);
    digitalWrite(m_pins.p1, write_status);
    digitalWrite(m_pins.p2, write_status);
    digitalWrite(m_pins.p3, write_status);
}