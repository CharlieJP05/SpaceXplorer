//
// Created by charl on 04/05/2025.
//

#ifndef FUNCS_H
#define FUNCS_H
#include "structs.h"

void init_map(Map *map,int worldSize);

void create_map(Map *map);

void display_map(Map *map,char prbuff[]);

void spawn_asteroid(Map *map);

void update(Map *map,char prbuff[],char action);

int check_collision(Map *map, int i, int j);

void hide_cursor();

void move_cursor_top_left();

#endif //FUNCS_H
