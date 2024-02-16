#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int read_file_content(const char *filename, char *content, size_t size) {
    FILE *file = fopen(filename, "r");
    check(file, "Failed to open the file: %s", filename);

    size_t i = 0;
    int c;
    while (i < size - 1 && (c = getc(file)) != EOF) {
        content[i] = (char)c;
        i++;
    }
    content[i] = '\0';

    fclose(file);
    return 0;

error:
    if (file) fclose(file);
    return -1;
}

int main(int argc, char *argv[])
{
    Person you = {.age = 0};
    int i = 0;
    char in[MAX_DATA];

    printf("What's your First Name? ");
    fgets(in, MAX_DATA-1, stdin);
    in[strcspn(in, "\n")] = 0;  // 移除换行符
    strncpy(you.first_name, in, MAX_DATA-1);

    printf("What's your Last Name? ");
    fgets(in, MAX_DATA-1, stdin);
    in[strcspn(in, "\n")] = 0;  // 移除换行符
    strncpy(you.last_name, in, MAX_DATA-1);

    printf("How old are you? ");
    scanf("%d", &you.age);

    printf("What color are your eyes:\n");
    for(i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    scanf("%d", &eyes);
    you.eyes = eyes - 1;

    printf("How much do you make an hour? ");
    scanf("%f", &you.income);

    printf("----- RESULTS -----\n");

    printf("First Name: %s\n", you.first_name);
    printf("Last Name: %s\n", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    char content[MAX_DATA];
    if (read_file_content("example.txt", content, MAX_DATA) == 0) {
        printf("File content: %s\n", content);
    } else {
        printf("Failed to read file content.\n");
    }

    return 0;
}
