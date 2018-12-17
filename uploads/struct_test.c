#include<stdio.h>

typedef struct {
    int count;
    char *name;
    void (*display)(int, char *);
} student;

void display(int, char *);

int main(void)
{
    student s = {1, "junli"}; 
    s.display = &display;
    s.display(s.count, s.name);

    printf("display address: %p\n", &display);
    return 0;
}

void display(int c, char *n)
{
    printf("Sudent#: %d, name: %s\n", c, n);
}
