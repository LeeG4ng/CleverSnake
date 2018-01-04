//
//  ThreadManager.c
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/28.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#include "ThreadManager.h"

static void * thread_func(void * task) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_testcancel();
    task_block block = (task_block)task;
    block();
    return (void *)0;
}

void dispatch(pthread_t thread, task_block task) {
    pthread_create(&thread, NULL, thread_func, (void *)task);
}
