#include <stdio.h>

void Fun1(int *cur_age, char *cur_name[], int count);
void Fun2(int *cur_age, char *cur_name[], int count);
void Fun3(int *cur_age, char *cur_name[], int count);
void Fun4(int *ages, char *names[], int count);

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    Fun1(ages, names, count);
    printf("---\n");

    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    Fun2(ages, names, count);
    printf("---\n");

    // third way, pointers are just arrays
    Fun3(ages, names, count);
    printf("---\n");

    // fourth way with pointers in a stupid complex way
    Fun4(ages, names, count);
    printf("---\n");

    //because the pointer was shifted in Fun4, we need to repoint the pointer back to the beginning
    cur_name = names;
    cur_age = ages;

    for(i = 0; i < count; i++)
    {
	printf("%s's address:%p\n",cur_name[i],*cur_name);
	printf("%d's address:%p\n",cur_age[i], cur_age);
    }
    return 0;
}

 
void Fun1(int *cur_age, char **cur_name, int count)
{
    int i = 0;
    for(i = 0; i < count; i++)
    {
        printf("%s has %d years alive.\n",
                *(cur_name + i), *(cur_age + i));
    }
}

void Fun2(int *cur_age, char **cur_name, int count)
{
    int i = 0;
    for(i = 0; i < count; i++)
    {
        printf("%s is %d years old.\n",
                cur_name[i], cur_age[i]);
    }
}

void Fun3(int *cur_age, char **cur_name, int count)
{
    int i = 0;
    for(i = 0; i < count; i++)
    {
        printf("%s is %d years old again.\n",
                *(cur_name + i), *(cur_age + i));
    }
}

void Fun4(int *ages, char **names, int count)
{
    int *cur_age = ages;
    char **cur_name = names;
    for(cur_name = names, cur_age = ages;
        (cur_age - ages) < count;
         cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n",
               *cur_name, *cur_age);
    }
}

