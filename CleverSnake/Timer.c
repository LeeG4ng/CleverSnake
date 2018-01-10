//
//  Timer.c
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/28.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include "Timer.h"


void set_timer(time_t interval_ms, bool * stop, timer_block do_block) {
    while (1) {
        if(stop) {
            if(*stop)
                return;
        }
        do_block();
        usleep((unsigned)interval_ms * 1000);
    }
}

