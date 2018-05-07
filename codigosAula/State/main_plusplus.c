#include <stdio.h>

typedef enum {
    GREEN,
    RED,
    YELLOW
} state_t;

typedef enum {
    STOP,
    GO,
    TIMEOUT
} event_t;

/*RED (STOP->RED) (GO->GREEN) (TIMEOUT->RED)
GREEN (STOP->YELLOW) (GO->GREEN) (TIMEOUT->GREEN)
YELLOW (STOP->YELLOW) (GO->YELLOW) (TIMEOUT->RED)
*/

typedef struct {
    state_t events[3];
    void (*action)(void);
} mstate_t;

static event_t ce = STOP;
static event_changed = 0;

void ISR() {
    //ce = *;    
}

void red() {}

void green() {}

void yellow() {}

int main() {
    static state_t cs = RED;
    mstate_t machine[] = {
        { .events={YELLOW, GREEN, GREEN}, .action=green},
        //         STOP GO     TIMEOUT
        { .events={RED, GREEN, RED}, .action=red},
        { .events={YELLOW, YELLOW, RED}, .action=yellow}
    };
    
    while(1) {
        if(event_changed) {      
            cs = machine[cs].events[ce];
            machine[cs].action();
        }
    }
    return 0;
}
