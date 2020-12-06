#include <unistd.h>
#include "public/Stepper.h"
#include "pixy2/src/host/libpixyusb2/include/libpixyusb2.h"

using namespace std;


int main(int argc, char const *argv[])
{
    Pixy2 pixy;
    int Result = pixy.init();

    if(Result < 0)
    {
        cout << "ERROR: Pixy.init() failed: " << Result << endl;
        return -1;
    }

    pixy.changeProg("color_connected_components");

    Stepper my_stepper(7,11,13,15,1);
    my_stepper.setVelocity(0.5);

    Timer my_time;
    my_time.reset();
    while(my_time.elapsed() < 10)
    {
        pixy.ccc.getBlocks();

        if(pixy.ccc.numBlocks)
        {
            cout << "X: " << pixy.ccc.blocks[0].m_x << "   Y: " << pixy.ccc.blocks[0].m_y << endl;
            cout << "lol" << endl;
        }
        
        // my_stepper.pollStep();
    }

    my_stepper.motorOff();
    return 0;
}
