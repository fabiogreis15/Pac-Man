#include <unistd.h>
#include "timer.h"

void timer_sleep_ms(int ms) {
    usleep(ms * 1000);
}
