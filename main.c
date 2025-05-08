#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
//#include "funcs.h"
#include "funcs.c"
//#include "structs.h"
#include "structs.c"
#include "files.c"
//#include "files.h"


int main(void) {
    int print = 0;
    int cont = 1;
    char prbuff[2048] = {0};
    srand((unsigned)time(NULL)); // allows for random to be used
    hide_cursor(); // hide cursor
    while (cont) {
        Map map;
        while (1) {
            system("cls");
            printf("1. Start game\n");
            printf("2. View Highscores\n");
            printf("3. Exit\n");
            printf("Enter: ");
            int input = getch();
            if (input == '1') {
                char diffs[100][10][10] = {0};
                int select_diff = parse("difficulty.txt",diffs);
                system("cls");
                for (int i = 0; i < select_diff; i++) {
                    printf("%d. %s\n", i + 1, diffs[i][0]);
                }
                printf("Enter: ");
                while (1) {
                    if (_kbhit()) {
                        input = getch();
                        input = input - 48;
                        if (input >= 1 && input <= select_diff) {
                            break;
                        } else {
                            printf("Invalid input. Please try again.\n");
                            printf("Enter: ");
                        }
                    }
                }
                init_map(&map, 18,
                atoi(diffs[input-1][1]),
                atoi(diffs[input-1][2]),
                atoi(diffs[input-1][3]),
                atoi(diffs[input-1][4]),
                atoi(diffs[input-1][5]));
                printf("\n");
                printf("World size: %d\n", map.worldSize);
                printf("fuelPerScrap: %d\n", map.fuelPerScrap);
                printf("startFuel: %d\n", map.startFuel);
                printf("startHealth: %d\n", map.startHealth);
                printf("scrapCount: %d\n", map.scrapCount);
                printf("asteroidCount: %d\n", map.asteroidCount);
                printf("Difficulty: %s\n", diffs[input-1][0]);
                strcpy(map.difficulty,diffs[input-1][0]);
                printf("Starting game...\n");
                break;
            } else if (input == '2') {
                char lines[100][10][10] = {0};
                int lines_amount = parse("highscore.txt",lines);
                system("cls");
                for (int i = 0; i < lines_amount; i++) {
                    printf("%d. %s - %s - %s\n", i + 1, lines[i][0],lines[i][1],lines[i][2]);
                }
                printf("\nEnter any to continue: ");
                while (1) {
                    if (_kbhit()) {
                        input = getch();
                        break;
                    }
                }
            } else if (input == '3') {
                cont = 0;
                exit(0);
                break;
            }
        }

        //##############
        //MAIN GAME LOOP
        //##############
        create_map(&map); // create map
        display_map(&map,"None",1); // show map
        spawn_asteroid(&map);
        while (get_health(&map) > 0 && get_fuel(&map) > 0) {//main loop
            //Input
            char input = 0;
            while (_kbhit()) {
                _getch(); // Consume any lingering input
            }

            while (1) {
                if (_kbhit()) {
                    input = _getch(); // get input without Enter
                    break;
                } else {
                    Sleep(10);
                    if (time(NULL) % 2 == 0) {
                        display_map(&map,prbuff,0);
                    } else {
                        display_map(&map,prbuff,1);
                    }
                    memset(prbuff, 0, sizeof(prbuff));

                }
            }

            // Logic
            spawn_asteroid(&map);
            move(&map, prbuff, input);
            check_collision(&map);

            // Draw funcs
            display_map(&map, prbuff,1);

            // Clear buffer
            memset(prbuff, 0, sizeof(prbuff));
            Sleep(10);

        }
        //################
        //END OF GAME CODE
        //################
        system("cls");
        printf("Game Over\n");
        printf("Your score: %d\n", get_scrap(&map));
        printf("Enter name to save: ");
        char name[10] = "";
        scanf("%s",name);
        printf("Saving...\n");
        add("highscore.txt",name,map.difficulty,get_scrap(&map));
        
    }
    //##############
    //QUITTING CODE
    //##############
    return 0;
}