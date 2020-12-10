#include "../public/Stepper.h"
#include "../pixy2/src/host/libpixyusb2/include/libpixyusb2.h"


class Turret
{
private:
    // Motor objects
    Stepper m_yaw = Stepper(1, 2, 3, 4);
    Stepper m_pitch = Stepper(5, 6, 7, 8);
    
public:
    Turret();
    ~Turret();

    void setVelocities(double yaw_vel, double pitch_vel);
    void advanceMotors();
};