//
//  SnakeModel.h
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/18.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#ifndef SnakeModel_h
#define SnakeModel_h

#include <stdio.h>

#pragma mark - 类型定义
/*节点*/
struct node {
    short x;
    short y;
    struct node * next;
    struct node * last;
};
typedef struct node Node;

/*运动方向*/
typedef enum {
    SnakeDirectionUp,
    SnakeDirectionLeft,
    SnakeDirectionDown,
    SnakeDirectionRight
} SnakeDirection;

/*蛇模型*/
struct Snake {
    SnakeDirection direction;
    Node * head;
};
typedef struct Snake Snake;

#pragma mark - 函数原型
/*操作：初始化链表
 *参数：空
 *结果：返回链表的指针*/
Snake * initSnake(void);



#endif /* SnakeModel_h */
