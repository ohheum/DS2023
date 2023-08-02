#include <stdio.h>
#include <stdlib.h>

int main() {
    int size = 5;
    int *data = (int *)malloc(size*sizeof(int));
    int n = 0, k;
    while(1) {
        scanf("%d", &k);
        if (k==-1) break;
        if (n == size) {
            size *= 2;
            int *tmp = (int *)malloc(size*sizeof(int));
            for (int i=0; i<n; i++)
                tmp[i] = data[i];
            data = tmp;
        }
        data[n++] = k;
    }

    return 0;
}
