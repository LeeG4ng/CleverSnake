//
//  Menu.h
//  CleverSnake
//
//  Created by Gary Lee on 2018/1/2.
//  Copyright © 2018年 UniqueStudio. All rights reserved.
//

#ifndef Menu_h
#define Menu_h

#include <stdio.h>

typedef enum {
    MenuNewGame,
    MenuLoadArchive,
    MenuRanking,
    MenuExit
} MenuItem;

MenuItem drawMenu(void);

typedef enum {
    Low,
    Medium,
    High,
    Back
} LevelItem;

LevelItem drawLevelSelect(void);

#endif /* Menu_h */
