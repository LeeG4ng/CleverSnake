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
#include <stdlib.h>
#include <stdbool.h>
#include "Timer.h"
#include "ThreadManager.h"
#include "Menu.h"
#include "Ranking.h"

bool willCancleTimer = false;

void presentMenu(void);
void presentLevel(void);

int main(int argc, const char * argv[]) {
    Snake *snake = initSnake();
    initscr();
    raw();
    noecho();
    keypad(stdscr, true);
    curs_set(0);
    
    presentMenu();
    
    pthread_t th = NULL;
//    dispatch(th, ^{
//        int i = 0;
//        while (1) {
//            mvaddstr(i++, i++, "c");
//            refresh();
//        }
//    });
//    getch();
//    pthread_cancel(th);
//    pthread_join(th, NULL);
//    dispatch(th, ^{
//        set_timer(500, ^{
//            clear();
//            moveWithoutFood(snake);
//            Node *tempNode = snake->head;
//            for(int i = 0; i < snake->length; i++) {
//                tempNode = tempNode->next;
//                mvaddstr(tempNode->position.y, tempNode->position.x, "*");
//            }
//
//            refresh();
//        });
//    });
//    set_timer(500, ^{
//        clear();
//        moveWithoutFood(snake);
//        Node *tempNode = snake->head;
//        for(int i = 0; i < snake->length; i++) {
//            tempNode = tempNode->next;
//            mvaddstr(tempNode->position.y, tempNode->position.x, "*");
//        }
//
//        refresh();
//    });
    getch();
    willCancleTimer = true;
    /*
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
            destroy_timer(timer);
            timer = NULL;
            set_timer(timer, 500, ^{
                clear();
                moveWithoutFood(snake);
                Node *tempNode = snake->head;
                for(int i = 0; i < snake->length; i++) {
                    tempNode = tempNode->next;
                    mvaddstr(tempNode->position.y, tempNode->position.x, "*");
                }
                refresh();
            });
        }
    });*/
//    pthread_join(th, NULL);
    getch();
    endwin();
    return 0;
}

#pragma mark - Menu Function
void presentMenu() {
    MenuItem selected = drawMenu();
    switch (selected) {
        case MenuNewGame:
            presentLevel();
            break;
        case MenuLoadArchive:
            break;
        case MenuRanking:
            drawRanking();
            break;
        case MenuExit:
            exit(0);
            break;
    }
}

void presentLevel() {
    LevelItem level = drawLevelSelect();
    switch (level) {
        case LevelLow:
            break;
        case LevelMedium:
            break;
        case LevelHigh:
            break;
        case LevelBack:
            presentMenu();
            break;
    }
}


