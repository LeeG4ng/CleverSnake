//
//  Timer.c
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/28.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#include "Timer.h"
#include <sys/time.h>

int timer(time_t interval, timer_block timing, timer_block completion) {
    int count = 0;
    while (1) {
        struct timeval start, end;
        gettimeofday(&start, NULL);
        time_t now_intetval;
        timing(count);
        do {
            gettimeofday(&end, NULL);
            now_intetval = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000;
        } while (now_intetval < interval);
        count++;
        completion(count);
    }
    return 0;
}
