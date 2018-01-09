//
//  Archiver.c
//  CleverSnake
//
//  Created by Gary Lee on 2018/1/8.
//  Copyright © 2018年 UniqueStudio. All rights reserved.
//

#include "Archiver.h"
#include <stdlib.h>

static char * path = "/users/leeg4ng/archives.json";

void archive(Status * end) {
    FILE * file = fopen(path, "wb");
    Archive new;
    
    Snake * snake = end->snake;
    new.length = end->snake->length;
    new.dir = end->snake->direction;
    new.level = end->level;
    new.poisoned = end->snake->poisoned;
    
    for(int row = 0; row < 24-TEXT_HEIGHT; row++) {
        for(int col = 0; col < 80; col++) {
            if(end->map[row][col] >= 0 && end->map[row][col] < 5) {
                new.map[row][col] = end->map[row][col];
            } else {
                new.map[row][col] = 0;
            }
        }
    }
    Node * temp = snake->head;
    for(int i = 0; i < new.length; i++) {
        new.snake[i] = temp->position;
        temp = temp->next;
    }
    
    fwrite(&new, sizeof(Archive), 1, file);
    fclose(file);
}

Status * loadArchive(void) {
    FILE * file = fopen(path, "rb+");
    Archive old;
    fread(&old, sizeof(Archive), 1, file);
    
    Status * initial = (Status *)malloc(sizeof(Status));
    Snake * snake = initSnake();
    initial->alive = true;
    initial->level = old.level;
    initial->snake = snake;
    snake->direction = old.dir;
    snake->tempDirection = old.dir;
    snake->poisoned = old.poisoned;
    
    MapElement ** map = (MapElement **)malloc(sizeof(MapElement *) * (24-TEXT_HEIGHT));
    for(int row = 0; row < 24 - TEXT_HEIGHT; row++) {
        map[row] = (MapElement *)malloc(sizeof(MapElement) * 80);
    }
    initial->map = map;
    
    snake->head->position = old.snake[0];
    for(int i = 1; i < old.length; i++) {
        insertNodeAtIndex(snake, i, old.snake[i]);
    }
    
    for(int row = 0; row < 24-TEXT_HEIGHT; row++) {
        for(int col = 0; col < 80; col++) {
            initial->map[row][col] = old.map[row][col];
        }
    }
    fclose(file);
    return initial;
}
