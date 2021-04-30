#include "../public/Stepper.h"
#include "../pixy2/src/host/libpixyusb2/include/libpixyusb2.h"


class Turret
{
private:
    // Motor objects
    Stepper m_yaw = Stepper(0, 7);
    Stepper m_pitch = Stepper(2, 3);
    
public:
    Turret();
    ~Turret();

    void setVelocities(double yaw_vel, double pitch_vel);
    void advanceMotors();
    void centerOnBlob(int cent_x, int cent_y);
};