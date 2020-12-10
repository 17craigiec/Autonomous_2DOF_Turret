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
