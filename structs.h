typedef struct {
    int direction; // default value
    char symbol;
}Asteroid;
typedef struct {
    int lives;
    int scrap;
    char symbol;
}Player;
typedef struct {
    char symbol;
}Scrap;
typedef struct {
    int contains; //0=null 1=asteroid 2=scrap 3=player
    Player player;
    Asteroid asteroid;
    Scrap scrap;
    char symbol;
}Space;
typedef struct {
    int worldSize;
    Space world[18][18];
}Map;