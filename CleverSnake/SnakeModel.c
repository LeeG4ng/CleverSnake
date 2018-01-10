//
//  SnakeModel.c
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/18.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#include "SnakeModel.h"
#include <curses.h>
#include <stdlib.h>
#include "GameLogic.h"

#pragma mark - 私有函数
/*操作：初始化链表的一个节点
 *参数：该节点存储的坐标
 *结果：该节点的前驱后驱节点均为自身*/
static Node * nodeMake(Point position) {
    Node * pnode = NULL;
    pnode = (Node *)malloc(sizeof(Node));
    pnode->next = pnode->last = pnode;
    pnode->position = position;
    return pnode;
}

/*操作：从头节点遍历得到该序号的节点
 *参数：蛇的指针，节点序号
 *结果：返回该节点*/
static Node * getNodeAtIndex(Snake * psnake, int index) {
    Node * tempNode = psnake->head;
    for(int i = 0; i < index; i++) {
        tempNode = tempNode->next;
    }
    return tempNode;
}

#pragma mark - 接口实现
Point PointMake(int x, int y) {
    Point point = {x, y};
    return point;
}

Snake * initSnake(void) {
    Snake * psnake = (Snake *)malloc(sizeof(Snake));
    psnake->head = nodeMake(PointMake(10, 10));
    psnake->direction = SnakeDirectionRight;
    psnake->tempDirection = SnakeDirectionRight;
    psnake->length = 1;
    psnake->poisoned = 0;
    return psnake;
}

void insertNodeAtIndex(Snake * psnake, int index, Point position) {
    Node * tempNode = nodeMake(position);//待插入的节点
    Node * nextNode = getNodeAtIndex(psnake, index);
    Node * lastNode = nextNode->last;
    tempNode->next = nextNode;
    tempNode->last = lastNode;
    lastNode->next = tempNode;
    nextNode->last = tempNode;
    psnake->length += 1;
    if(index == 0) {
        psnake->head = tempNode;
    }
}

void deleteNodeAtIndex(Snake * psnake, int index) {
    Node * targetNode = getNodeAtIndex(psnake, index);//待删除的节点
    Node * nextNode = targetNode->next;
    Node * lastNode = targetNode->last;
    nextNode->last = lastNode;
    lastNode->next = nextNode;
    free(targetNode);
    psnake->length -= 1;
}

void moveWithFood(Snake * psnake) {
    Point headPosition = psnake->head->position;
    Point nextPoint;
    switch (psnake->direction) {
        case SnakeDirectionUp:
            nextPoint = PointMake(headPosition.x, headPosition.y-1);
            break;
        case SnakeDirectionLeft:
            nextPoint = PointMake(headPosition.x-1, headPosition.y);
            break;
        case SnakeDirectionDown:
            nextPoint = PointMake(headPosition.x, headPosition.y+1);
            break;
        case SnakeDirectionRight:
            nextPoint = PointMake(headPosition.x+1, headPosition.y);
            break;
    }
    nextPoint.x = (nextPoint.x + COLS) % COLS;
    nextPoint.y = (nextPoint.y + LINES-TEXT_HEIGHT) % (LINES-TEXT_HEIGHT);
    insertNodeAtIndex(psnake, 0, nextPoint);
    if(psnake->poisoned)
        psnake->poisoned--;
}

void moveWithoutFood(Snake * psnake) {
    moveWithFood(psnake);
    deleteNodeAtIndex(psnake, psnake->length-1);
}

void moveWithWeed(Snake * psnake) {
    moveWithoutFood(psnake);
    deleteNodeAtIndex(psnake, psnake->length-1);
    psnake->poisoned += 50;
}

void moveWithBomb(Snake * psnake) {
    moveWithoutFood(psnake);
    int count = (psnake->length+1)/2;
    for(int i = 0; i < count; i++) {
        deleteNodeAtIndex(psnake, psnake->length-1);
    }
}

Point * getPositions(Snake * psnake) {
    Node * tempNode = psnake->head;
    Point * arr = (Point *)malloc(sizeof(Point) * psnake->length);
    for(int i = 0; i < psnake->length; i++) {
        arr[i] = tempNode->position;
        tempNode = tempNode->next;
    }
    return arr;
}
