#include <iostream>
#include <ctime>

#define pass (void)0

class Timer
{
public:
    Timer() { clock_gettime(CLOCK_REALTIME, &beg_); }

    double elapsed() {
        clock_gettime(CLOCK_REALTIME, &end_);
        return end_.tv_sec - beg_.tv_sec +
            (end_.tv_nsec - beg_.tv_nsec) / 1000000000.;
    }

    void reset() { clock_gettime(CLOCK_REALTIME, &beg_); }

private:
    timespec beg_, end_;
};

// void sleep_tm(double ns){
//     Timer my_timer;
//     my_timer.reset();

//     while (my_timer.elapsed() < ns)
//     {
//         pass;
//     }
// };