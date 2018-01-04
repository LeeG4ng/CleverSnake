//
//  GameLogic.h
//  CleverSnake
//
//  Created by Gary Lee on 2018/1/4.
//  Copyright © 2018年 UniqueStudio. All rights reserved.
//

#ifndef GameLogic_h
#define GameLogic_h

#include <stdio.h>
#include "SnakeModel.h"

/*游戏难度*/
typedef enum {
    LevelLow,//四周无界
    LevelMedium,//上下无界，左右有界
    LevelHigh//四周有界
} GameLevel;

/*游戏状态*/
struct status {
    Snake * snake;
    GameLevel level;
};
typedef struct status Status;

/*操作：开始新游戏
 *参数：游戏难度*/
void startGameWithLevel(GameLevel);

void startGameWithArchive();

#endif /* GameLogic_h */
