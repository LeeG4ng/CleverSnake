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
#include "Timer.h"
#include "ThreadManager.h"
#include "Menu.h"
#include "GameLogic.h"
#include "Ranking.h"



void presentMenu(void);
void presentLevel(void);

int main(int argc, const char * argv[]) {
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
    switch (level) {
        case Low:
            startGameWithLevel(LevelLow);
            break;
        case Medium:
            startGameWithLevel(LevelMedium);
            break;
        case High:
            startGameWithLevel(LevelHigh);
            break;
        case Back:
            break;
    }
    presentMenu();
}


