#include <unistd.h>
#include "public/Turret.h"

using namespace std;


int main(int argc, char const *argv[])
{

    Turret turret;

    Pixy2 pixy;
    int Result = pixy.init();

    if(Result < 0)
    {
        cout << "ERROR: Pixy.init() failed: " << Result << endl;
        cout << "Check that the camera is plugged in..." << endl;
        return -1;
    }

    pixy.changeProg("color_connected_components");

    Timer my_time;
    my_time.reset();
    while(my_time.elapsed() < 10)
    {
        pixy.ccc.getBlocks();

        if(pixy.ccc.numBlocks)
        {
            cout << "X: " << pixy.ccc.blocks[0].m_x << "   Y: " << pixy.ccc.blocks[0].m_y << endl;
        }

    }

    return 0;
}
