//
//  Timer.h
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/28.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#ifndef Timer_h
#define Timer_h
#include <sys/time.h>
#include <time.h>
#include <stdio.h>

typedef void (^timer_block)(void);

void set_timer(time_t interval_ms, bool * stop, timer_block do_block);

#endif /* Timer_h */
