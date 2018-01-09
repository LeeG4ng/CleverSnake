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
#include <stdbool.h>
#include "SnakeModel.h"

#define TEXT_HEIGHT 5

#pragma mark - Map Elements
typedef enum {
    Blank = 0,//空地
    Food,//食物：长度增加 LevelLow
    Weed,//毒草：长度减少 LevelMedium
    Bomb,//炸弹：长度减半 LevelHigh
    Wall,//墙@：凉凉
    Self//蛇身
} MapElement;

#pragma mark - Game Logic
/*游戏难度*/
typedef enum {
    LevelLow,//四周无界,长度5
    LevelMedium,//上下无界，左右有界，长度10
    LevelHigh//四周有界，长度15
} GameLevel;

/*游戏状态*/
struct status {
    Snake * snake;
    GameLevel level;
    MapElement ** map;//以二维数组表示的地图
    bool alive;
};
typedef struct status Status;

/*操作：开始新游戏
 *参数：游戏难度*/
Status * startGameWithLevel(GameLevel);

Status * startGameWithArchive(Status *);


#endif /* GameLogic_h */
