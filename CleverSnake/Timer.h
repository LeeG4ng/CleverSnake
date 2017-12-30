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

typedef void (^timer_block)(int count);

int timer(time_t interval_ms, _Nullable timer_block timing, _Nullable timer_block completion);

#endif /* Timer_h */
