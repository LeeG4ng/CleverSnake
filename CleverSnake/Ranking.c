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

/*操作：对玩家数组按降序排序
 *参数：数组*/
static void sortRanking(Player * array) {
    for(int index = 1; index < count; index++) {
        Player toMove = array[index];
        for(int test = 0; test < index; test++) {
            if(toMove.length > array[test].length) {
                for(int j = index; j > test; j--) {
                    //后移
                    array[j] = array[j-1];
                }
                array[test] = toMove;
                break;
            }
        }
    }
}

/*操作：从硬盘读取排行榜，并调用方法排序
 *返回：排序好的玩家数组*/
static Player * getRanking(void) {
    FILE * file = fopen(path, "r");
    char temp[100];
    rewind(file);
    count = 0;
    while(fgets(temp, 1000, file) != NULL) {
        count++;
    }
    rewind(file);
    Player * arr = (Player *)malloc(count * sizeof(Player));
    for(int index = 0; index < count; index++) {
        fscanf(file, "%s", arr[index].name);
        fscanf(file, "%d", &(arr[index].length));
    }
    sortRanking(arr);
    fclose(file);
    return arr;
}

#pragma mark - 接口实现
void recordPlayer(Player player) {
    FILE * file = fopen(path, "a+");
    fprintf(file, "%s %d\n", player.name, player.length);
    fclose(file);
}

void drawRanking(void) {
    Player * arr = getRanking();
    
    clear();
    attron(A_BOLD);
    mvaddstr(2, COLS/2-4, "Ranking");
    attroff(A_BOLD);
    mvaddstr(3, COLS/2-11, "Press Q To Return Menu");
    
    for(int index = 0; index < count; index++) {
        mvaddstr(5+index, 35, arr[index].name);
        char temp[50];
        sprintf(temp, ":%d", arr[index].length);
        mvaddstr(5+index, 40, temp);
    }
    refresh();
    
    while (1) {
        int ch = getch();
        if(ch == 'q')
            break;
    }
}
