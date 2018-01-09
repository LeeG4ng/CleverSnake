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
#include <stdbool.h>

#pragma mark - 类型定义
/*坐标*/
struct point {
    int x;
    int y;
};
typedef struct point Point;

Point PointMake(int x, int y);

/*节点*/
struct node {
    Point position;
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
    SnakeDirection tempDirection;
    Node * head;
    int length;
    int poisoned;
};
typedef struct Snake Snake;

#pragma mark - 函数原型
/*操作：初始化蛇模型
 *参数：空
 *结果：返回蛇的指针*/
Snake * initSnake(void);

/*操作：向蛇模型中插入一个节点
 *参数：蛇的指针，插入的位置，节点的坐标
 *结果：*/
void insertNodeAtIndex(Snake * psnake, int index, Point position);

/*操作：删除蛇模型中的指定节点
 *参数：蛇的指针，节点的位置
 *结果：*/
void deleteNodeAtIndex(Snake * psnake, int index);

/*操作：吃到食物移动
 *参数：蛇的指针
 *结果：蛇头向前延伸，蛇尾不动*/
void moveWithFood(Snake * psnake);

/*操作：没有食物正常移动
 *参数：蛇的指针
 *结果：蛇身整体移动*/
void moveWithoutFood(Snake * psnake);

void moveWithWeed(Snake * psnake);

void moveWithBomb(Snake * psnake);

/*操作：获得蛇的位置数组
 *参数：蛇的指针
 *返回：位置数组首地址*/
Point * getPositions(Snake * psnake);

#endif /* SnakeModel_h */
