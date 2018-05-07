#include <stdio.h>

typedef enum {
    GREEN,
    RED,
    YELLOW
} state_t;

typedef enum {
    GO,
    STOP,
    TIMEOUT
} event_t;

static event_t ce = STOP;
static event_changed = 0;

void ISR() {
    //ce = *;    
}

state_t state_machine() {
    static state_t cs = RED;
    switch(cs) {
        case GREEN:
            if(ce == STOP) {
                cs = YELLOW;
            }
            break;
        case RED:
            if(ce == GO) {
                cs = GREEN;
            }
            break;
        case YELLOW:
            if(ce == TIMEOUT) {
                cs = RED;
            }
            break;
        default:
    }
    return cs;
}

void action(state_t cs) {
    // Turn all led off
    switch(cs) {
    case GREEN:
        // Turn on GREEN led
        break;
    case RED:
        // Turn on RED led
        break;
    case YELLOW:
        // Turn on YELLOW led
        break;
    default:
    }
}

int main() {
    while(1) {
        if(event_changed)
            action(state_machine());
    }
    return 0;
}
