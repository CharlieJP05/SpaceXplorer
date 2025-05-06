
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "funcs.h"
#include "structs.h"

void clear_space(Map *map, int i, int j) {
  map->world[i][j].contains = 0b000000;
}
void init_map(Map *map,int worldSize) {
    const char gear[] = "\xE2\x9A\x99";

    worldSize = 18; // overwrite value
    map->worldSize = worldSize;
    map->player.lives = 5;
    map->player.scrap = 0;
    for (int i = 0; i < map->worldSize; i++) {
        for (int j = 0; j < map->worldSize; j++) {
            clear_space(map,i,j);
            map->world[i][j].symbol = ' ';
        }
    }
}
void update_map(Map *map) {
  for (int i = 0; i < map->worldSize; i++) {
    for (int j = 0; j < map->worldSize; j++) {
        if (has_asteroid(map,i,j) && has_player(map,i,j)){
            int damage = has_asteroid_dir(map,i,j,0)+has_asteroid_dir(map,i,j,1)+has_asteroid_dir(map,i,j,2)+has_asteroid_dir(map,i,j,3);
            remove_asteroid_all(map,i,j);
            set_health(map,get_health(map)-damage);
            if (get_health(map) <= 0) {
              remove_player(map,i,j);
              //TODO end game
            }

        }
        if (has_scrap(map,i,j) && has_player(map,i,j)){
            increase_scrap(map);
            remove_scrap(map,i,j);
        }
    }
  }
}

void update_symbols(Map *map) {
  for (int i = 0; i < map->worldSize; i++) {
    for (int j = 0; j < map->worldSize; j++) {
      if ((map->world[i][j].contains & (map->world[i][j].contains - 1)) != 0){// if contains more than one thing
        map->world[i][j].symbol = '?'; //TEMPORARY TODO
        }
      if (has_asteroid(map,i,j)){
        if (has_asteroid_dir(map,i,j,0)){
          map->world[i][j].symbol = ASTEROID_SYM_UP;
        } else if (has_asteroid_dir(map,i,j,1)){
          map->world[i][j].symbol = ASTEROID_SYM_DOWN;
        } else if (has_asteroid_dir(map,i,j,2)){
          map->world[i][j].symbol = ASTEROID_SYM_LEFT;
        } else if (has_asteroid_dir(map,i,j,3)){
          map->world[i][j].symbol = ASTEROID_SYM_RIGHT;
        } else {
          map->world[i][j].symbol = '?';
        }
      } else if (has_scrap(map,i,j)){
        map->world[i][j].symbol = SCRAP_SYM;
      } else if (has_player(map,i,j)){
        map->world[i][j].symbol = PLAYER_SYM;
      } else {
        map->world[i][j].symbol = ' ';
      }
    }
  }
}

void move(Map *map,char prbuff[],char action) {
    Map tempMap;
    memcpy(&tempMap,map,sizeof(Map));
    int x = map->worldSize;
    int y = map->worldSize;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
          if (has_player(&tempMap,i,j)) {
            if (action == 'w') {
              add_player(map,i-1,j);
              remove_player(map,i,j);
            } else if (action == 'a') {
              add_player(map,i,j-1);
              remove_player(map,i,j);
            } else if (action == 's') {
              add_player(map,i+1,j);
              remove_player(map,i,j);
            } else if (action == 'd') {
              add_player(map,i,j+1);
              remove_player(map,i,j);
            }
          }
          if (has_asteroid(&tempMap,i,j)) {
            if (has_asteroid_dir(&tempMap,i,j,0)) {
              add_asteroid(map,i-1,j,0);
              remove_asteroid(map,i,j,0);
            }
            if (has_asteroid_dir(&tempMap,i,j,1)) {
              add_asteroid(map,i,j-1,1);
              remove_asteroid(map,i,j,1);
            }
            if (has_asteroid_dir(&tempMap,i,j,2)) {
               add_asteroid(map,i+1,j,2);
               remove_asteroid(map,i,j,2);
            }
            if (has_asteroid_dir(&tempMap,i,j,3)) {
               add_asteroid(map,i,j+1,3);
               remove_asteroid(map,i,j,3);
            }
          }
        }
    }
}

//asteroids
void add_asteroid(Map *map, int i, int j,int direction) {
    map->world[i][j].contains |= (1 << direction);
}
void add_scrap(Map *map, int i, int j) {
    map->world[i][j].contains |= (1 << 4);
}
void add_player(Map *map, int i, int j) {
    map->world[i][j].contains |= (1 << 5);
}
void remove_asteroid(Map *map, int i, int j,int direction) {
    map->world[i][j].contains &= ~(1 << direction);
}
void remove_asteroid_all(Map *map, int i, int j) {
  map->world[i][j].contains &= ~(0b001111);
}
void remove_scrap(Map *map, int i, int j) {
    map->world[i][j].contains &= ~(1 << 4);
}
void remove_player(Map *map, int i, int j) {
    map->world[i][j].contains &= ~(1 << 5);
}
int has_asteroid_dir(Map *map, int i, int j,int direction) {
    return (map->world[i][j].contains & (1 << direction)) != 0;
}
int has_asteroid(Map *map, int i, int j) {
  return (map->world[i][j].contains & 0b001111);
}
int has_scrap(Map *map, int i, int j) {
    return (map->world[i][j].contains & (1 << 4)) != 0;
}
int has_player(Map *map, int i, int j) {
    return (map->world[i][j].contains & (1 << 5)) != 0;
}
//symbols
char get_symbol(Map *map, int i, int j) {}
//player
void increase_health(Map *map) {
  map->player.lives++;
}
void decrease_health(Map *map) {
  map->player.lives--;
}
void set_health(Map *map, int health) {
  map->player.lives = health;
}
int get_health(Map *map) {
    return map->player.lives;
}
void increase_scrap(Map *map) {
  map->player.scrap++;
}
void decrease_scrap(Map *map) {
  map->player.scrap--;
}
void set_scrap(Map *map, int scrap) {
  map->player.scrap = scrap;
}
int get_scrap(Map *map) {
  return map->player.scrap;
}