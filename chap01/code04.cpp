#include <stdio.h>

int main() {
    char c = 'h';
    char *ptrc = &c;

    printf("%p\n", ptrc);
    printf("%p\n", ptrc+1);
    printf("%p\n", ptrc-1);

    int x = 10;
    int *ptrint = &x;

    printf("%p\n", ptrint);
    printf("%p\n", ptrint+1);
    printf("%p\n", ptrint-1);


    long long y = 10;
    long long *ptrlonglong = &y;
    printf("%p\n", ptrlonglong);
    printf("%p\n", ptrlonglong+1);

    double z = 0.5;
    double *ptrdouble = &z;
    printf("%p\n", ptrdouble);
    printf("%p\n", ptrdouble+1);

    return 0;
}
