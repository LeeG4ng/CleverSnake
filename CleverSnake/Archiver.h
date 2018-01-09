//
//  Archiver.h
//  CleverSnake
//
//  Created by Gary Lee on 2018/1/8.
//  Copyright © 2018年 UniqueStudio. All rights reserved.
//

#ifndef Archiver_h
#define Archiver_h

#include <stdio.h>
#include "GameLogic.h"
#include "SnakeModel.h"

typedef struct {
    Point snake[500];
    int length;
    int poisoned;
    SnakeDirection dir;
    GameLevel level;
    MapElement map[24][80];
} Archive;

void archive(Status *);
Status * loadArchive(void);
#endif /* Archiver_h */
