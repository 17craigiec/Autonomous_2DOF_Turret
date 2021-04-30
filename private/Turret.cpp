#include "../public/Turret.h"

Turret::Turret()
{
}

Turret::~Turret()
{
}

void Turret::setVelocities(double yaw_vel, double pitch_vel)
{
    m_yaw.setVelocity(yaw_vel);
    m_pitch.setVelocity(pitch_vel);
}

void Turret::advanceMotors()
{
    m_yaw.pollStep();
    m_pitch.pollStep();
}

void Turret::centerOnBlob(int cent_x, int cent_y)
{
    int RESOLUTION_WIDTH = 320;

    if(cent_x != -1 && cent_y != -1)
    {
        if(cent_x < RESOLUTION_WIDTH/2)
        {
            setVelocities(-0.5, 0);
            cout << "Dir: -1" << endl;
        }
        else
        {
            setVelocities(0.5, 0);
            cout << "Dir: 1" << endl;
        }
        advanceMotors();
    }
}
