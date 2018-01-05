//
//  Timer.c
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/28.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#include <stdbool.h>
#include "Timer.h"
#include "ThreadManager.h"
#include <sys/time.h>


void set_timer(time_t interval_ms, bool * stop, timer_block do_block) {
    while (1) {
        struct timeval start, end;
        gettimeofday(&start, NULL);
        time_t now_intetval;
        if(stop) {
            if(*stop)
                return;
        }
        do_block();
        pthread_testcancel();
        do {
            gettimeofday(&end, NULL);
            now_intetval = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
        } while (now_intetval < interval_ms);
    }
}

