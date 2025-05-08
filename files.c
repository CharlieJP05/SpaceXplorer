//
// Created by charl on 08/05/2025.
//

#include "files.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add(char *str,char name[10],char diff[10],int score) {
    FILE *file = fopen(str, "a");
    fprintf(file, "%s,%s,%d\n", name, diff, score);
    fclose(file);
}

void make(char *str) {
    FILE *file = fopen(str, "w");
    if (str == "difficulty.txt") {
        fprintf(file, "Easy,5,5,5,20,5\n");
        fprintf(file, "Medium,5,3,3,10,10\n");
        fprintf(file, "Hard,3,2,2,10,20\n");
        fclose(file);
    } else if (str == "highscore.txt"){
        //fprintf(file, "Charlie,Easy,100\n");
        fclose(file);
    } else {
        printf("Unkown file name...Quitting...\n");
        fclose(file);
        exit(1);
    }
}
int parse(char *str,char diffs[100][10][10]) {
    FILE *file = fopen(str, "r");
    if (file == NULL) {
        make(str);
        file = fopen(str, "r");
    }
    char line[100];                  // a single line
    int select_diff = 0;             // lines in the file

    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\r\n")] = '\0'; // remove newline or carriage return from end
        int select_type = 0;
        char diff[10] = "";                //buffer for each value
        for (int i = 0; i <= strlen(line); i++) { //characters in line
            if (line[i] == ',' || line[i] == '\0') { // if comma or end of line is reached
                if (select_diff < 10 && select_type < 10) {
                    strcpy(diffs[select_diff][select_type], diff); // parsed value
                }
                memset(diff, 0, sizeof(diff)); // reset the buffer for the next value
                select_type++;                // move to the next column
            } else {
                size_t len = strlen(diff);    // append character
                if (len < sizeof(diff) - 1) {
                    diff[len] = line[i];
                    diff[len + 1] = '\0';
                }
            }
        }
        select_diff++; // move to the next row
        if (select_diff >= 10) { // dont go out of bounds
            break;
        }
    }
    fclose(file);
    return select_diff;

}