#include <stdio.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor
{
    BLUE_EYES,
    GREEN_EYES,
    BROWN_EYES,
    BLACK_EYES,
    OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"};

typedef struct Person
{
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int read_file_scanf(const char *filename, int string_size, char Save[])
{
    FILE *file = fopen(filename, "r");
    check(file, "failed to open file: %s", filename);

    int i = 0;
    char c;

    // while (i < string_size - 1 && (c = scanf("%c", &c)) != EOF)
    while (i < string_size - 1 && (c = fgetc(file)) != EOF)
    {
        Save[i] = c;
        i++;
    }
    Save[i] = '\0';

    fclose(file);
    return 0;

error:
    return -1;
}

int main(int argc, char *argv[])
{
    Person you = {.age = 0};
    int i = 0;
    char *in = NULL;

    printf("What's your First Name? ");
    in = fgets(you.first_name, MAX_DATA - 1, stdin);
    // fscanf(stdin, "%50s", you.first_name); Don't use it ,something strange
    // check(in != NULL, "Failed to read first name.");
    // gets(you.first_name);//Don't use, dangerous!
    printf("What's your Last Name? ");
    in = fgets(you.last_name, MAX_DATA - 1, stdin);
    check(in != NULL, "Failed to read last name.");

    printf("How old are you? ");
    int rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0, "You have to enter a number.");

    printf("What color are your eyes:\n");
    for (i = 0; i <= OTHER_EYES; i++)
    {
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "You have to enter a number.");

    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "Enter a floating point number.");

    printf("----- RESULTS -----\n");

    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    printf("----- test -----\n");
    char Save[100];
    if (read_file_scanf("example.txt", 100, Save) == 0)
    {
        printf("%s\n", Save);
    }
    else
    {
        printf("no!");
    }
    return 0;
error:

    return -1;
}
