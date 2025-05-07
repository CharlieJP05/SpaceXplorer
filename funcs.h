//
// Created by charl on 04/05/2025.
//

#ifndef FUNCS_H
#define FUNCS_H
#include "structs.h"


void create_map(Map *map);

void display_map(Map *map,char prbuff[],int print);

void spawn_asteroid(Map *map);

void hide_cursor();

void move_cursor_top_left();

#endif //FUNCS_H
