#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person{
   char *name;
   int age;
   int height;
   int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
     struct Person *who  = malloc(sizeof(struct Person));
     assert(who != NULL);

     who->name = strdup(name);
     who->age = age;
     who->height = height;
     who->weight = weight; 

     return who;
}

void Person_destroy(struct Person *who)
{
    static int i = 0;
    assert(who != NULL);
   
    free(who->name);
    who->name = NULL;
    free(who);
    who = NULL;

    printf("destroy successfully!: %d\n",i++);
}

void Person_print(struct Person *who)
{
    printf("Name: %s\n",who->name);
    printf("\tage: %d\n",who->age);
    printf("\theight: %d\n",who->height);
    printf("\tweight: %d\n",who->weight);
}

int main(int argc, char *argv[])
{
    struct Person *joe = Person_create("Joe_ALex", 32, 64, 140);
    struct Person *frank = Person_create("Frank_Blank", 20, 72, 180);

    printf("Jos is at memory location: %p\n",joe);
    Person_print(joe);

    printf("frank is at memory location: %p\n",frank);
    Person_print(frank);

    joe->age +=20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight +=20;
    Person_print(frank);

    Person_destroy(joe);
    Person_destroy(frank);

    return 0;
}
