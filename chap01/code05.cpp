#include <stdio.h>

int calculate_sum(int *array);

int main()
{
    int sum;
    int num[10];
    for (int i = 0; i < 10; i++)
        scanf("%d", &num[i]);
    sum = calculate_sum(num);
    printf("%lf\n", sum / 10.0);
    return 0;
}

int calculate_sum(int *array)
{
    int sum = 0;
    for ( int i = 0; i < 10; i++ )
        sum = sum + *(array + i);
    return sum;
}