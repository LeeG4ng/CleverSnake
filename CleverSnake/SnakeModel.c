//
//  SnakeModel.c
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/18.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#include "SnakeModel.h"
#include <stdlib.h>

#pragma mark - 私有函数
/*操作：初始化链表的一个节点
 *参数：该节点存储的坐标x,y
 *结果：该节点的前驱后驱节点均为自身*/
static Node * createNodeWithPosition(short x, short y) {
    Node * pnode = NULL;
    pnode = (Node *)malloc(sizeof(Node));
    pnode->next = pnode->last = pnode;
    pnode->x = x;
    pnode->y = y;
    return pnode;
}

#pragma mark - 接口实现
Snake * initSnake(void) {
    Snake * psnake = (Snake *)malloc(sizeof(Snake));
    psnake->head = createNodeWithPosition(10, 10);
    return psnake;
}
