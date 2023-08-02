#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORDS 1000
#define MAX_LEN 20

char *words[MAX_WORDS];
int n = 0;

void trim(char str[]);

int main()
{
    FILE *fp = fopen("input.txt", "r");
    char buf[MAX_LEN];
    while(fscanf(fp, "%s", buf) != EOF) {
        trim(buf);
        if (strlen(buf) < 2) continue;
        int i=0;
        for (; i<n; i++) {
            if (strcmp(buf, words[i]) == 0)
                break;
        }
        if (i == n)     // not found
            words[n++] = strdup(buf);
    }
    fclose(fp);

    for (int i=0; i<n; i++)
        printf("%s\n", words[i]);
    return 0;
}

void trim(char str[]) {
    int i=strlen(str)-1;
    for (; i>=0 && !isalnum(str[i]); i--)
        str[i] = '\0';
    for (; i>=0; i--)
        str[i] = tolower(str[i]);
}

