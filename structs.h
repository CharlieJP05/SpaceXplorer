//
// Created by charl on 06/05/2025.
//

#ifndef STRUCTS_H
#define STRUCTS_H
#define ASTEROID_SYM_UP '^'
#define ASTEROID_SYM_DOWN 'v'
#define ASTEROID_SYM_LEFT '<'
#define ASTEROID_SYM_RIGHT '>'
#define SCRAP_SYM 'X'
#define PLAYER_SYM 219
#define CLEAR ' '


typedef struct {
    int lives;
    int fuel;
    int scrap;
}Player;
typedef struct {
    //int contains; //0=null 1=asteroid 2=scrap 3=player 4=asteroidscrap 5= playerasteroid 6=playerscrap
    unsigned char contains; // 0b000000 <->  0 1 2 3 up down left right       4 scrap 5 unused      0b543210
    char symbol;
}Space;
typedef struct {
    int worldSize;
    Space world[18][18];
    Player player;
    int fuelPerScrap; //1-any reccomend 5 or above, depends on scrap scarcity
    int startFuel; //1-any, reccomend 5 or above
    int startHealth; //1-any
    int scrapCount; //0-100
    int asteroidCount; //0-100
    char difficulty[10];
}Map;

//update
void clear_space(Map *map, int i, int j);
void init_map(Map *map,int worldSize,int fuelPerScrap,int startFuel,int startHealth,int scrapCount,int asteroidCount);
void update_map(Map *map);
void update_symbols(Map *map,char prbuff[],int print);
char show_overlap(Map *map, int i, int j,char prbuff[],int count);
void move(Map *map,char prbuff[],char action);
//spaces
void add_asteroid(Map *map, int i, int j,int direction);
void add_scrap(Map *map, int i, int j);
void add_player(Map *map, int i, int j);
void remove_asteroid(Map *map, int i, int j,int direction);
void remove_asteroid_all(Map *map, int i, int j);
void remove_scrap(Map *map, int i, int j);
void remove_player(Map *map, int i, int j);
int has_asteroid_dir(Map *map, int i, int j,int direction);
int has_asteroid(Map *map, int i, int j);
int has_scrap(Map *map, int i, int j);
int has_player(Map *map, int i, int j);
//symbols
char get_symbol(Map *map, int i, int j);
//player
void increase_health(Map *map);
void decrease_health(Map *map);
void set_health(Map *map, int health);
int get_health(Map *map);
void increase_fuel(Map *map);
void decrease_fuel(Map *map);
void set_scrap(Map *map, int scrap);
int get_fuel(Map *map);
int get_scrap(Map *map);
#endif //STRUCTS_H
