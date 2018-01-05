//
//  GameLogic.c
//  CleverSnake
//
//  Created by Gary Lee on 2018/1/4.
//  Copyright © 2018年 UniqueStudio. All rights reserved.
//

#include <stdbool.h>
#include <ncurses.h>
#include <stdlib.h>
#include "GameLogic.h"
#include "Timer.h"
#include "ThreadManager.h"

#pragma mark - 私有函数
#define TEXT_HEIGHT 10

/*操作：测试下一步的地图元素
 *参数：游戏状态
 *使用条件：调用蛇移动函数之前*/
static MapElement testElement(Status * status) {
    Point head = status->snake->head->position;
    SnakeDirection direction = status->snake->direction;
    Point nextPoint;
    switch (direction) {
        case SnakeDirectionUp:
            nextPoint = PointMake(head.x, head.y-1);
            break;
        case SnakeDirectionLeft:
            nextPoint = PointMake(head.x-1, head.y);
            break;
        case SnakeDirectionDown:
            nextPoint = PointMake(head.x, head.y+1);
            break;
        case SnakeDirectionRight:
            nextPoint = PointMake(head.x+1, head.y);
            break;
    }
    bool res = false;
    Point * points = getPositions(status->snake);
    for(int i = 1; i < status->snake->length; i++) {
        res = res || ((head.x == points[i].x) && (head.y == points[i].y));
    }
    if(res) {
        return Self;
    }
    MapElement element = status->map[nextPoint.y][nextPoint.x];
    status->map[nextPoint.y][nextPoint.x] = Blank;
    return element;
}


/*操作：测试地图上的点是否为空
 *参数：游戏状态，点*/
static bool testMap(Status * status, Point test) {
    bool res1 = true, res2 = true;
    res1 = res1 && (status->map[test.y][test.x] == Blank);
    Point * points = getPositions(status->snake);
    for(int i = 0; i < status->snake->length; i++) {
        res2 = res2 && ((test.x != points[i].x) && (test.y != points[i].y));
    }
    return res1 && res2;
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
    Status * initial = (Status *)status;
    Snake * snake = initial->snake;
    __block bool stop = false;
    set_timer(getTimerInterval(initial->level), &stop, ^{
        clear();
        switch (testElement(initial)) {
            case Blank:
                moveWithoutFood(snake);
                break;
            case Food:
                moveWithFood(snake);
                break;
            case Weed:
                
                break;
            case Bomb:
                
                break;
            case Wall:
                initial->alive = false;
                stop = true;
                break;
            case Self:
                initial->alive = false;
                stop = true;
                break;
        }
        Node *tempNode = snake->head;
        for(int i = 0; i < snake->length; i++) {
            tempNode = tempNode->next;
            mvaddstr(tempNode->position.y, tempNode->position.x, "#");
        }
        for(int row = 0; row < LINES - TEXT_HEIGHT; row++) {
            for(int col = 0; col < COLS; col++) {
                switch (initial->map[row][col]) {
                    case Blank:
                        break;
                    case Food:
                        mvaddstr(row, col, "x");
                        break;
                    case Weed:
                        mvaddstr(row, col, " ");
                        break;
                    case Bomb:
                        mvaddstr(row, col, " ");
                        break;
                    case Wall:
                        mvaddstr(row, col, "@");
                        break;
                    case Self:
                        break;
                }
            }
        }
        refresh();
    });
    mvaddstr(LINES-5, 30, "You died, press Q to save ranking");
    refresh();
    return (void *)0;
}

static Point randPoint(Status * current) {
    Point rpoint;
    srand((unsigned int)time(NULL));
    int x = rand()%(COLS-1);
    int y = rand()%(LINES-TEXT_HEIGHT-1);
    rpoint = PointMake(x, y);
    while (!testMap(current, rpoint)){
        srand((unsigned int)time(NULL));
        int x = rand()%(COLS-1);
        int y = rand()%(LINES-TEXT_HEIGHT-1);
        rpoint = PointMake(x, y);
    }
    return rpoint;
}

static void * makeFood(void * status) {
    Status * current = (Status *)status;
    set_timer(2000, NULL, ^{
        Point food = randPoint(current);
        current->map[food.y][food.x] = Food;
    });
    return (void *)0;
}

static void * makeWeed(void * status) {
    Status * current = (Status *)status;
    
    return (void *)0;
}

static void * makeBomb(void * status) {
    Status * current = (Status *)status;
    
    return (void *)0;
}

static void makeWall(void * status) {
    Status * current = (Status *)status;
    if(current->level == LevelMedium || current->level == LevelHigh) {//设置左右边界
        for(int i = 0; i < LINES-TEXT_HEIGHT; i++) {
            current->map[i][0] = current->map[i][COLS-1] = Wall;
        }
    }
    if(current->level == LevelHigh) {//设置上下边界
        for(int i = 0; i < COLS; i++) {
            current->map[0][i] = current->map[LINES-1-TEXT_HEIGHT][i] = Wall;
        }
    }
}

static void gameEnd(Status * end) {
    
}

/*操作：制作地图元素，由多线程调用
 *参数：游戏状态*/
pthread_t draw_thread, map_thread;
static void * makeMapElement(void * status) {
    Status * current = (Status *)status;
    pthread_t food = NULL, weed = NULL, bomb = NULL;
    int origin = -1;
    while (1) {
        if(origin != current->level) {
            origin = current->level;
            pthread_cancel(food);
            pthread_cancel(weed);
            pthread_cancel(bomb);
            food = weed = bomb = NULL;
            makeWall(status);
            switch (origin) {
                case LevelLow:
                    pthread_create(&food, NULL, makeFood, status);
                    break;
                case LevelMedium:
                    pthread_create(&food, NULL, makeFood, status);
                    pthread_create(&weed, NULL, makeWeed, status);
                    break;
                case LevelHigh:
                    pthread_create(&food, NULL, makeFood, status);
                    pthread_create(&weed, NULL, makeWeed, status);
                    pthread_create(&bomb, NULL, makeBomb, status);
                    break;
            }
        }
    }
    return (void *)0;
}

/*操作：封装游戏主题功能，供不同的游戏开始状态复用
 *参数：游戏状态*/
static Status * startGame(Status * initial) {
    initial->alive = true;
    Snake * snake = initial->snake;
    draw_thread = NULL;
    pthread_create(&draw_thread, NULL, resetDrawingTimer, (void *)initial);
    map_thread = NULL;
    pthread_create(&map_thread, NULL, makeMapElement, (void *)initial);
    while (1) {
        int ch = getch();
        if(ch == 'q') {
            pthread_cancel(draw_thread);
            pthread_join(draw_thread, NULL);
            return initial;
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
        
//        pthread_cancel(draw_thread);
//        pthread_join(draw_thread, NULL);
//        pthread_create(&draw_thread, NULL, resetDrawingTimer, (void *)&initial);
    }
}



#pragma mark - 接口实现
Status * startGameWithLevel(GameLevel level) {
    Snake * snake = initSnake();
    Status * initial = (Status *)malloc(sizeof(Status));
    initial->snake = snake;
    initial->level = level;
    MapElement ** map = (MapElement **)malloc(sizeof(MapElement *) * (LINES-TEXT_HEIGHT));
    for(int row = 0; row < LINES - TEXT_HEIGHT; row++) {
        map[row] = (MapElement *)malloc(sizeof(MapElement) * COLS);
    }
    initial->map = map;
    return startGame(initial);
}
