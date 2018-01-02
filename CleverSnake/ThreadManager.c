//
//  ThreadManager.c
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/28.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#include "ThreadManager.h"

static void * thread_func(void * tas) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_testcancel();
    task_block b = (task_block)tas;
    b();
    return (void *)0;
}

void dispatch(pthread_t thread, task_block task) {
    pthread_create(&thread, NULL, thread_func, (void *)task);
}
