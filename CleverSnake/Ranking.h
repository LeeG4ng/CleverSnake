//
//  Ranking.h
//  CleverSnake
//
//  Created by Gary Lee on 2018/1/3.
//  Copyright © 2018年 UniqueStudio. All rights reserved.
//

#ifndef Ranking_h
#define Ranking_h

#include <stdio.h>

/*玩家*/
struct player {
    char name[10];
    int length;
};
typedef struct player Player;

/*操作：记录玩家信息
 *参数：玩家*/
void recordPlayer(Player);

/*操作：绘制排行榜
 *返回：空*/
void drawRanking(void);

#endif /* Ranking_h */
