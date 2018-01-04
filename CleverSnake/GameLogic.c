//
//  GameLogic.c
//  CleverSnake
//
//  Created by Gary Lee on 2018/1/4.
//  Copyright © 2018年 UniqueStudio. All rights reserved.
//

#include <stdbool.h>
#include <ncurses.h>
#include "GameLogic.h"
#include "Timer.h"
#include "ThreadManager.h"

#pragma mark - 私有函数
/*操作：测试下一步是否有食物
 *参数：蛇指针
 *使用条件：调用蛇移动函数之前*/
static bool testFood(Snake * snake) {
    
}

/*操作：测试蛇是否存活
 *参数：游戏状态
 *使用条件：调用蛇移动函数之后*/
static bool testAlive(Status status) {
    
}

/*操作：获得计时器的计时周期
 *参数：游戏难度
 *返回：计时周期*/
static time_t getTimerInterval(GameLevel level) {
    switch (level) {
        case LevelLow:
            return 400;
        case LevelMedium:
            return 300;
        case LevelHigh:
            return 200;
    }
}

/*操作：重置计时器，由多线程调用
 *参数：游戏状态*/
static void * resetDrawingTimer(void* status) {
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    Status initial = *(Status *)status;
    Snake * snake = initial.snake;
    set_timer(getTimerInterval(initial.level), ^{
        clear();
        moveWithFood(snake);
        Node *tempNode = snake->head;
        for(int i = 0; i < snake->length; i++) {
            tempNode = tempNode->next;
            mvaddstr(tempNode->position.y, tempNode->position.x, "*");
        }
        if(initial.level == LevelMedium || initial.level == LevelHigh) {//绘制左右边界
            for(int i = 0; i < LINES; i++) {
                mvaddstr(i, 0, "@");
                mvaddstr(i, COLS-1, "@");
            }
        }
        if(initial.level == LevelHigh) {//绘制上下边界
            for(int i = 0; i < COLS; i++) {
                mvaddstr(0, i, "@");
                mvaddstr(LINES-11, i, "@");
            }
        }
        refresh();
    });
    return (void *)0;
}

/*操作：封装游戏主题功能，供不同的游戏开始状态复用
 *参数：游戏状态*/
static void startGame(Status initial) {
    Snake * snake = initial.snake;
//    resetDrawingTimer(initial);
    pthread_t thread = NULL;
    pthread_create(&thread, NULL, resetDrawingTimer, (void *)&initial);
    while (1) {
        int ch = getch();
        if(ch == 'q') {
            pthread_cancel(thread);
            pthread_join(thread, NULL);
            return;
        }
        if(ch == KEY_UP && snake->direction != SnakeDirectionDown) {
            snake->direction = SnakeDirectionUp;
        }
        if(ch == KEY_LEFT && snake->direction != SnakeDirectionRight) {
            snake->direction = SnakeDirectionLeft;
        }
        if(ch == KEY_DOWN && snake->direction != SnakeDirectionUp) {
            snake->direction = SnakeDirectionDown;
        }
        if(ch == KEY_RIGHT && snake->direction != SnakeDirectionLeft) {
            snake->direction = SnakeDirectionRight;
        }
        
//        pthread_cancel(thread);
//        pthread_join(thread, NULL);
//        pthread_create(&thread, NULL, resetDrawingTimer, (void *)&initial);
    }
}

#pragma mark - 接口实现
void startGameWithLevel(GameLevel level) {
    Snake * snake = initSnake();
    Status initial;
    initial.snake = snake;
    initial.level = level;
    startGame(initial);
}
