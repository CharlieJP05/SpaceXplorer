#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "funcs.c"












main(void) {
    srand((unsigned)time(NULL)); // allows for random to be used
    Map map;
    init_map(&map,18); // init map
    char prbuff[2048] = {0};
    create_map(&map); // create map
    display_map(&map,"None"); // show map
    spawn_asteroid(&map);
    for (int i = 0; i < 1000; i++) {//main loop
        //Time
        Sleep(100);
        //Logic
        spawn_asteroid(&map);
        move_asteroid(&map,prbuff);
        //Draw funcs
        display_map(&map,prbuff);
        // End loop
        memset(prbuff, 0, sizeof(prbuff));
    }
    return 0;
}