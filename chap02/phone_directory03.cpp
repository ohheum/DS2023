/*
 * support dynamic array reallocation
 * handling invalid command format - missing argument etc.
 * to do so, introduce 'input by line' and 'strtok'
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INIT_CAPACITY 3
#define BUFFER_SIZE 100

char ** names;            /* names */
char ** numbers;          /* phone numbers */
int capacity = INIT_CAPACITY;
int n = 0;                   /* number of people in phone directory */

void add(char * ,char *);
void find(char *);
void status();
void remove(char *);
void load(char *);
void save(char *);
int read_line(char *, int);
void init_directory();
void process_command();

char *delim = " ";

int main() {

    init_directory();
    process_command();

    return 0;
}

void process_command() {
    char command_line[BUFFER_SIZE];
    char *command, *argument1, *argument2;

    while (1) {
        printf("$ ");

        fgets(command_line, BUFFER_SIZE, stdin);
        command_line[strlen(command_line)-1] = '\0';
        if (strlen(command_line) <= 0)
            continue;

        command = strtok(command_line, delim);
        if (command==NULL) continue;

        if (strcmp(command, "read") == 0) {
            argument1 = strtok(NULL, "\0");
            if (argument1 == NULL) {
                printf("File name required.\n");
                continue;
            }
            load(argument1);
        }
        else if (strcmp(command, "add") == 0) {
            argument1 = strtok(NULL, delim);
            argument2 = strtok(NULL, delim);
            if (argument1 == NULL || argument2 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            add(argument1, argument2);
            printf("%s was added successfully.\n", argument1);
        }
        else if (strcmp(command, "find") == 0) {
            argument1 = strtok(NULL, delim);
            if (argument1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            find(argument1);
        }
        else if (strcmp(command, "status")==0)
            status();
        else if (strcmp(command, "delete")==0) {
            argument1 = strtok(NULL, delim);
            if (argument1 == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            remove(argument1);
        }
        else if (strcmp(command, "save")==0) {
            argument1 = strtok(NULL, delim);
            argument2 = strtok(NULL, delim);
            if (argument1 == NULL || strcmp("as", argument1) != 0 || argument2 == NULL) {
                printf("Invalid command format.\n");
                continue;
            }
            save(argument2);
        }
        else if (strcmp(command, "exit")==0)
            break;
    }
}

void init_directory() {
    names = (char **) malloc(INIT_CAPACITY * sizeof(char *));
    numbers = (char **) malloc(INIT_CAPACITY * sizeof(char *));
}

void load(char *fileName) {
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    FILE *fp = fopen(fileName, "r");
    if (fp==NULL) {
        printf("Open failed.\n");
        return;
    }
    while ((fscanf(fp, "%s", buf1)!=EOF)) {
        fscanf(fp, "%s", buf2);
        add(buf1, buf2);
    }
    fclose(fp);
}

void save(char *fileName) {
    int i;
    FILE *fp = fopen(fileName, "w");
    if (fp==NULL) {
        printf("Open failed.\n");
        return;
    }

    for (i=0; i<n; i++) {
        fprintf(fp, "%s %s\n", names[i], numbers[i]);
    }
    fclose(fp);
}

int search(char *name) {
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(name, names[i])==0) {
            return i;
        }
    }
    return -1;
}

void remove(char *name) {

    int i = search(name);  /* returns -1 if not exists */
    if (i == -1) {
        printf("No person named '%s' exists.\n", name);
        return;
    }

    int j = i;
    for (; j<n-1; j++) {
        names[j] = names[j+1];
        numbers[j] = numbers[j+1];
    }
    n--;
    printf("'%s' was deleted successfully. \n", name);
}

void status() {
    int i;
    for (i=0; i<n; i++)
        printf("%s  %s\n", names[i], numbers[i]);
    printf("Total %d persons.\n", n);
}

void find(char *name) {
    char *token;

    int index = search(name);
    if (index == -1)
        printf("No person named '%s' exists.\n", name);
    else
        printf("%s\n", numbers[index]);

}

void reallocate()
{
    int i;
    capacity *= 2;
    char ** tmp1 = (char **)malloc(capacity*sizeof(char *));
    char ** tmp2 = (char **)malloc(capacity*sizeof(char *));
    for (i=0; i<n; i++) {
        tmp1[i] = names[i];
        tmp2[i] = numbers[i];
    }
    free(names);
    free(numbers);
    names = tmp1;
    numbers = tmp2;
}

void add(char * name, char * number) {
    if (n>=capacity)
        reallocate();
    int i=n-1;
    while (i>=0 && strcmp(names[i], name) > 0) {
        names[i+1] = names[i];
        numbers[i+1] = numbers[i];
        i--;
    }
    names[i+1] = strdup(name);
    numbers[i+1] = strdup(number);
    n++;
}

