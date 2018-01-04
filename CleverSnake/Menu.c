//
//  Menu.c
//  CleverSnake
//
//  Created by Gary Lee on 2018/1/2.
//  Copyright © 2018年 UniqueStudio. All rights reserved.
//

#include "Menu.h"
#include <ncurses.h>

MenuItem selected;
void selectNewGame(void);
void selectLoadArchive(void);
void selectRanking(void);
void selectExit(void);
void changeSelection(void);

LevelItem level;
void selectLevelLow(void);
void selectLevelMedium(void);
void selectLevelHigh(void);
void selectBack(void);
void changeLevel(void);

MenuItem drawMenu(void) {
    selected = MenuNewGame;
    selectNewGame();
    while(1) {
        int ch = getch();
        if(ch == KEY_UP) {
            selected = (selected-1) % 4;
            changeSelection();
        }
        if(ch == KEY_DOWN) {
            selected = (selected+1) % 4;
            changeSelection();
        }
        if(ch == 10) {
            return selected;
        }
    }
}

LevelItem drawLevelSelect(void) {
    level = Low;
    selectLevelLow();
    while(1) {
        int ch = getch();
        if(ch == KEY_UP) {
            level = (level-1) % 4;
            changeLevel();
        }
        if(ch == KEY_DOWN) {
            level = (level+1) % 4;
            changeLevel();
        }
        if(ch == 10) {
            return level;
        }
    }
}

#pragma mark - Reprint Menu
void changeSelection() {
    if(selected == MenuNewGame)
        selectNewGame();
    if(selected == MenuLoadArchive)
        selectLoadArchive();
    if(selected == MenuRanking)
        selectRanking();
    if(selected == MenuExit)
        selectExit();
}

void selectNewGame() {
    clear();
    attron(A_BOLD);
    mvaddstr(5, COLS/2-6, "Clever Snake");
    attroff(A_BOLD);
    
    attron(A_REVERSE | A_BOLD);
    mvaddstr(10, COLS/2-4, "New Game");
    attroff(A_REVERSE | A_BOLD);
    mvaddstr(11, COLS/2-6, "Load Archive");
    mvaddstr(12, COLS/2-4, "Ranking");
    mvaddstr(14, COLS/2-2, "Exit");
    //...
    refresh();
}

void selectLoadArchive() {
    clear();
    attron(A_BOLD);
    mvaddstr(5, COLS/2-6, "Clever Snake");
    attroff(A_BOLD);
    
    mvaddstr(10, COLS/2-4, "New Game");
    attron(A_REVERSE | A_BOLD);
    mvaddstr(11, COLS/2-6, "Load Archive");
    attroff(A_REVERSE | A_BOLD);
    mvaddstr(12, COLS/2-4, "Ranking");
    mvaddstr(14, COLS/2-2, "Exit");
    //...
    refresh();
}

void selectRanking() {
    clear();
    attron(A_BOLD);
    mvaddstr(5, COLS/2-6, "Clever Snake");
    attroff(A_BOLD);
    
    mvaddstr(10, COLS/2-4, "New Game");
    mvaddstr(11, COLS/2-6, "Load Archive");
    attron(A_REVERSE | A_BOLD);
    mvaddstr(12, COLS/2-4, "Ranking");
    attroff(A_REVERSE | A_BOLD);
    mvaddstr(14, COLS/2-2, "Exit");
    //...
    refresh();
}

void selectExit() {
    clear();
    attron(A_BOLD);
    mvaddstr(5, COLS/2-6, "Clever Snake");
    attroff(A_BOLD);
    
    mvaddstr(10, COLS/2-4, "New Game");
    mvaddstr(11, COLS/2-6, "Load Archive");
    mvaddstr(12, COLS/2-4, "Ranking");
    attron(A_REVERSE | A_BOLD);
    mvaddstr(14, COLS/2-2, "Exit");
    attroff(A_REVERSE | A_BOLD);
    //...
    refresh();
}

#pragma mark - Reprint Level
void changeLevel(void) {
    switch (level) {
        case Low:
            selectLevelLow();
            break;
        case Medium:
            selectLevelMedium();
            break;
        case High:
            selectLevelHigh();
            break;
        case Back:
            selectBack();
            break;
    }
}

void selectLevelLow() {
    clear();
    attron(A_BOLD);
    mvaddstr(5, COLS/2-6, "Select Level");
    attroff(A_BOLD);
    
    attron(A_REVERSE | A_BOLD);
    mvaddstr(10, COLS/2-2, "Low");
    attroff(A_REVERSE | A_BOLD);
    mvaddstr(11, COLS/2-3, "Medium");
    mvaddstr(12, COLS/2-2, "High");
    mvaddstr(14, COLS/2-2, "Back");
    //...
    refresh();
}

void selectLevelMedium(void) {
    clear();
    attron(A_BOLD);
    mvaddstr(5, COLS/2-6, "Select Level");
    attroff(A_BOLD);
    
    mvaddstr(10, COLS/2-2, "Low");
    attron(A_REVERSE | A_BOLD);
    mvaddstr(11, COLS/2-3, "Medium");
    attroff(A_REVERSE | A_BOLD);
    mvaddstr(12, COLS/2-2, "High");
    mvaddstr(14, COLS/2-2, "Back");
    //...
    refresh();
}

void selectLevelHigh(void) {
    clear();
    attron(A_BOLD);
    mvaddstr(5, COLS/2-6, "Select Level");
    attroff(A_BOLD);
    
    mvaddstr(10, COLS/2-2, "Low");
    mvaddstr(11, COLS/2-3, "Medium");
    attron(A_REVERSE | A_BOLD);
    mvaddstr(12, COLS/2-2, "High");
    attroff(A_REVERSE | A_BOLD);
    mvaddstr(14, COLS/2-2, "Back");
    //...
    refresh();
}

void selectBack(void) {
    clear();
    attron(A_BOLD);
    mvaddstr(5, COLS/2-6, "Select Level");
    attroff(A_BOLD);
    
    mvaddstr(10, COLS/2-2, "Low");
    mvaddstr(11, COLS/2-3, "Medium");
    mvaddstr(12, COLS/2-2, "High");
    attron(A_REVERSE | A_BOLD);
    mvaddstr(14, COLS/2-2, "Back");
    attroff(A_REVERSE | A_BOLD);
    //...
    refresh();
}
