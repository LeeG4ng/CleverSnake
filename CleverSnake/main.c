//
//  main.c
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/16.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#include "SnakeModel.h"
#include <ncurses.h>
#include <stdio.h>
#include "Timer.h"
#include "ThreadManager.h"

int main(int argc, const char * argv[]) {
    Snake *snake = initSnake();
    initscr();
    raw();
    noecho();
    keypad(stdscr, true);
    pthread_t myThread = NULL;
    dispatch(myThread, ^{
        while (1) {
            int ch = getch();
            switch (ch) {
                case KEY_UP:
                    snake->direction = SnakeDirectionUp;
                    break;
                case KEY_LEFT:
                    snake->direction = SnakeDirectionLeft;
                    break;
                case KEY_DOWN:
                    snake->direction = SnakeDirectionDown;
                    break;
                case KEY_RIGHT:
                    snake->direction = SnakeDirectionRight;
                    break;
            }
        }
    });
    timer(500, ^(int count) {}, ^(int count) {
        clear();
        moveWithoutFood(snake);
        Node *tempNode = snake->head;
        for(int i = 0; i < snake->length; i++) {
            tempNode = tempNode->next;
            mvaddstr(tempNode->position.y, tempNode->position.x, "*");
        }
        refresh();
    });
    while (1) {
        ;
    }
}


