//
//  Timer.h
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/28.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#ifndef Timer_h
#define Timer_h

#include <stdio.h>

typedef void (^timer_block)(void);

void set_timer(time_t interval_ms, timer_block do_block);
void destroy_timer(void);

#endif /* Timer_h */
