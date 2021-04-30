#include <mutex>
#include <thread>
#include <unistd.h>
#include "public/Turret.h"

using namespace std;

#define RUNTIME 60

// These globals are shared memory between threads
mutex mu;
int gb_centroid_x = -1;
int gb_centroid_y = -1;

int getGbCentX()
{
    mu.lock();
    int tmp = gb_centroid_x;
    mu.unlock();
    return tmp;
}

int getGbCentY()
{
    mu.lock();
    int tmp = gb_centroid_y;
    mu.unlock();
    return tmp;
}

void computerVisionLoop()
{
    // Intitial Setup
    Pixy2 pixy;
    int Result = pixy.init();

    if(Result < 0)
    {
        cout << "ERROR: Pixy.init() failed. " << Result << endl;
        cout << "NOTE: Check that the camera is plugged in." << endl;
        cout << "NOTE: Assure you ran the command with sudo." << endl;
        return;
    }

    pixy.changeProg("color_connected_components");


    // Constant Loop
    Timer my_time;
    my_time.reset();
    while(my_time.elapsed() < RUNTIME)
    {
        pixy.ccc.getBlocks();

        int new_centroid_x = -1;
        int new_centroid_y = -1;
        int max_block_area = -1;

        // Print all the blocks detected
        if(pixy.ccc.numBlocks)
        {
            new_centroid_x = pixy.ccc.blocks[0].m_x;
            new_centroid_y = pixy.ccc.blocks[0].m_y;

            // for(int i = 0; i < pixy.ccc.numBlocks; i++)
            // {
            //     // Updated the max block area
            //     if(max_block_area < pixy.ccc.blocks[i].m_height * pixy.ccc.blocks[i].m_width){
            //         max_block_area = pixy.ccc.blocks[i].m_height * pixy.ccc.blocks[i].m_width;
            //         new_centroid_x = pixy.ccc.blocks[i].m_x;
            //         new_centroid_y = pixy.ccc.blocks[i].m_y;
            //     }
            //     cout << "   || X: " << pixy.ccc.blocks[i].m_x << "   Y: " << pixy.ccc.blocks[i].m_y;
            // }
            // cout << endl;
        }

        // Check if the centroid has changed
        bool centroid_changed = ( (new_centroid_x != getGbCentX()) && (new_centroid_y != getGbCentY()) );

        if(centroid_changed)
        {
            // This section is used for mutual exlusion of the shared resource.
            // This is the only location that updated the centroid values
            mu.lock();
            std::cout << "The centroid has changed:  " << new_centroid_x << ", " << new_centroid_y << std::endl;
            gb_centroid_x = new_centroid_x;
            gb_centroid_y = new_centroid_y;
            mu.unlock();
        }
    }
}


int main(int argc, char const *argv[])
{
    // ==================================================================
    // COMPUTER VISION THREAD TESTING

    thread cv_thread(&computerVisionLoop);

    // ==================================================================
    // CAMERA TESTING

    // Pixy2 pixy;
    // int Result = pixy.init();

    // if(Result < 0)
    // {
    //     cout << "ERROR: Pixy.init() failed: " << Result << endl;
    //     cout << "Check that the camera is plugged in..." << endl;
    //     return -1;
    // }

    // pixy.changeProg("color_connected_components");

    // Timer my_time;
    // my_time.reset();
    // while(my_time.elapsed() < 10)
    // {
    //     pixy.ccc.getBlocks();

    //     if(pixy.ccc.numBlocks)
    //     {
    //         cout << "X: " << pixy.ccc.blocks[0].m_x << "   Y: " << pixy.ccc.blocks[0].m_y << endl;
    //     }

    // }

    // ==================================================================
    // TURRET TESTING

    // Turret turret;

    // Timer my_time;
    // my_time.reset();

    // turret.setVelocities(60, 0);
    // while(my_time.elapsed() < 5)
    // {
    //     turret.advanceMotors();
        
    // }

    // turret.setVelocities(-0.5, 0);
    // while(my_time.elapsed() < 10)
    // {
    //     turret.advanceMotors();
        
    // }
    
    // ==================================================================
    // FOLLOWING TESTING

    Turret turret;

    Timer my_time;
    my_time.reset();

    while(my_time.elapsed() < RUNTIME)
    {
        turret.centerOnBlob( getGbCentX(), getGbCentY() );
    }

    cv_thread.join();

    return 0;
}
