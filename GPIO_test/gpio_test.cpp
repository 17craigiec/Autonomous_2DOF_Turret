#include <wiringPi.h>

int main(int argc, char const *argv[])
{
    int TEST_PIN = 0;

    wiringPiSetup();			    // Setup the library
    pinMode(TEST_PIN, OUTPUT);		// Configure GPIO0 as an output

    for (int i = 0; i < 10; i++)
    {
        digitalWrite(TEST_PIN, 1);
        delay(2500);
        digitalWrite(TEST_PIN, 0);
        delay(2500);
    }
    
    return 0;
}
