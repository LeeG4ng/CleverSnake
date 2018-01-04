//
//  ThreadManager.h
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/28.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#ifndef ThreadManager_h
#define ThreadManager_h

#include <pthread.h>
#include <stdio.h>

typedef void (^task_block)(void);

void dispatch(pthread_t, task_block);

#endif /* ThreadManager_h */
