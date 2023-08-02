#include <stdio.h>

int main() {
    // slide page 5
    printf("%d %d\n", sizeof(int), sizeof(int *));
    printf("%d %d\n", sizeof(char), sizeof(char *));
    printf("%d %d\n", sizeof(double), sizeof(double *));

    // slide page 6
    int c = 12;
    int *p;
    p = &c;

    printf("%d\n", p);
    printf("%p\n", p);
    printf("%p\n", (void *)p);
    printf("%d\n", *p);

    *p = 20;
    printf("%p\n", p);
    printf("%d\n", *p);

    return 0;
}