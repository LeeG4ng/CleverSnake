//
//  ThreadManager.c
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/28.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#include "ThreadManager.h"

static void * thread_func(void * tas) {
    task_block b = (task_block)tas;
    b();
    return (void *)0;
}

void dispatch(pthread_t thread, task_block task) {
    pthread_create(&thread, NULL, thread_func, (void *)task);
}
