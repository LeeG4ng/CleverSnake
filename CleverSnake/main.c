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
#include <locale.h>
#include <pthread.h>
#include "Timer.h"
#include "Menu.h"
#include "GameLogic.h"
#include "Ranking.h"
#include "Archiver.h"



void presentMenu(void);
void presentLevel(void);

int main(int argc, const char * argv[]) {
    setlocale(LC_ALL, "en_US.utf-8");
    initscr();
    raw();
    noecho();
    keypad(stdscr, true);
    curs_set(0);
    
    presentMenu();

    getch();
    endwin();
    return 0;
}

#pragma mark - Menu Function
void endGame(Status * end);
void presentMenu() {
    MenuItem selected = drawMenu();
    Status * end = NULL;
    switch (selected) {
        case MenuNewGame:
            presentLevel();
            break;
        case MenuLoadArchive:
            end = startGameWithArchive(loadArchive());
            endGame(end);
            break;
        case MenuRanking:
            drawRanking();
            presentMenu();
            break;
        case MenuExit:
            endwin();
            exit(0);
            break;
    }
}

void presentLevel() {
    LevelItem level = drawLevelSelect();
    Status * end = NULL;
    switch (level) {
        case Low:
            end = startGameWithLevel(LevelLow);
            break;
        case Medium:
            end = startGameWithLevel(LevelMedium);
            break;
        case High:
            end = startGameWithLevel(LevelHigh);
            break;
        case Back:
            break;
    }
    if(end) {
        endGame(end);
    }
    
}

void endGame(Status * end) {
    if(end->alive) {//存档
        archive(end);
    } else {//排行榜
        clear();
        char score[20];
        sprintf(score, "Your length:%d", end->snake->length);
        mvaddstr(5, 30, score);
        mvaddstr(6, 30, "Enter your name:");
        Player new;
        new.length = end->snake->length;
        refresh();
        echo();
        keypad(stdscr, false);
        int ch;
        int i = -1;
        while(++i < 9) {
            ch = getch();
            if(ch == 10)
                break;
            new.name[i] = ch;
        }
        new.name[i+1] = '\0';
        noecho();
        keypad(stdscr, true);
        recordPlayer(new);
    }
    presentMenu();
}
