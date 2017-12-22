//
//  main.c
//  CleverSnake
//
//  Created by Gary Lee on 2017/12/16.
//  Copyright © 2017年 UniqueStudio. All rights reserved.
//

#include <stdio.h>
#include "SnakeModel.h"

int main(int argc, const char * argv[]) {
    Snake * snake = initSnake();
    printf("%d",  snake->head->x);
    return 0;
}

