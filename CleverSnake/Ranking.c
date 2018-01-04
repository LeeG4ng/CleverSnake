//
//  Ranking.c
//  CleverSnake
//
//  Created by Gary Lee on 2018/1/3.
//  Copyright © 2018年 UniqueStudio. All rights reserved.
//

#include "Ranking.h"
#include <stdlib.h>
#include <ncurses.h>

#pragma mark - 私有函数
int count;
static char * path = "/users/leeg4ng/ranking.json";

/*操作：对玩家数组进行排序
 *参数：数组*/
static void sortRanking(Player * array) {
    for(int index = 0; index < count; index++) {
        
    }
}

static Player * getRanking(void) {
    FILE * file = fopen(path, "r");
    char temp[100];
    rewind(file);
    while(fgets(temp, 1000, file) != NULL) {
        count++;
    }
    rewind(file);
    Player * arr = (Player *)malloc(count * sizeof(Player));
    for(int index = 0; index < count; index++) {
        fscanf(file, "%s", arr[index].name);
        fscanf(file, "%d", &(arr[index].length));
    }
    
    return arr;
}


#pragma mark - 接口实现
void recordPlayer(Player player) {
    FILE * file = fopen(path, "a+");
    fprintf(file, "%s %d\n", player.name, player.length);
}

void drawRanking(void) {
    Player * arr = getRanking();
    
    clear();
    for(int index = 0; index < count; index++) {
        mvaddstr(5+index, 20, arr[index].name);
        char temp[50];
        sprintf(temp, ":%d", arr[index].length);
        mvaddstr(5+index, 30, temp);
    }
    refresh();
}
