#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person Person_create(char *name, int age, int height, int weight)
{
    struct Person New;
    New.name = strdup(name); // 复制 name 到新分配的内存中
    New.age = age;
    New.height = height;
    New.weight = weight;

    return New;
}

void Person_print(struct Person who)
{
    printf("Name: %s\n", who.name);
    printf("\tage: %d\n", who.age);
    printf("\theight: %d\n", who.height);
    printf("\tweight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
    struct Person joe = Person_create("Joe_Alex", 32, 64, 140);
    struct Person frank = Person_create("Frank_Blank", 20, 72, 180);

    printf("Joe is at memory location: %p\n", &joe);
    Person_print(joe);

    printf("Frank is at memory location: %p\n", &frank);
    Person_print(frank);

    joe.age += 20;
    joe.height -= 2;
    joe.weight += 40;
    Person_print(joe);

    frank.age += 20;
    frank.weight += 20;
    Person_print(frank);

    // 释放 name 字段的内存
    free(joe.name);
    free(frank.name);

    return 0;
}
