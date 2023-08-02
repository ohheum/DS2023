/*
 * Name consists of more than one word
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 100
#define BUFFER_LENGTH 100

typedef struct {
    char *name;
    char *number;
    char *email;
    char *group;
} Person;

Person directory[CAPACITY];
int n = 0;                   /* number of people in phone directory */

void handle_add(char *);
void find(char *);
void status();
void remove(char *);
void load(char *);
void save(char *);
int read_line(FILE *, char *, int);
void add(char *, char *, char *, char *);
void release_person(Person p);


int main() {

    char command_line[BUFFER_LENGTH];
    char *command, *argument;

    while (1) {
        printf("$ ");
        if (read_line(stdin, command_line, BUFFER_LENGTH)<=0)
            continue;

        command = strtok(command_line, " ");

        if (strcmp(command, "read") == 0) {
            argument = strtok(NULL, " ");
            if (argument == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            load(argument);
        }
        else if (strcmp(command, "add") == 0) {
            argument = strtok(NULL, " ");
            if (argument == NULL) {
                printf("Name required.\n");
                continue;
            }
            handle_add(argument);
        }
        else if (strcmp(command, "find") == 0) {
            argument = strtok(NULL, " ");
            if (argument == NULL) {
                printf("Name required.\n");
                continue;
            }
            find(argument);
        }
        else if (strcmp(command, "status")==0) {
            status();
        }
        else if (strcmp(command, "delete")==0) {
            argument = strtok(NULL, " ");
            if (argument == NULL) {
                printf("Name required.\n");
                continue;
            }
            remove(argument);
        }
        else if (strcmp(command, "save")==0) {
            argument = strtok(NULL, " ");
            if (strcmp(argument, "as") != 0) {
                printf("Invalid arguments.\n");
                continue;
            }
            argument = strtok(NULL, " ");
            if (argument == NULL) {
                printf("Invalid arguments.\n");
                continue;
            }
            save(argument);
        }
        else if (strcmp(command, "exit")==0)
            break;
    }
    return 0;
}

int read_line( FILE * fp, char str[], int len ) {
    if (fgets(str, len, fp) == NULL)
        return 0;
    str[strlen(str)-1] = '\0';
    return strlen(str);
}


void load(char *fileName) {
    char buffer[BUFFER_LENGTH];
    char * name, *number, *email, *group;

    FILE *fp = fopen(fileName, "r");
    if (fp==NULL) {
        printf("Open failed.\n");
        return;
    }

    while (1) {
        if (read_line(fp, buffer, BUFFER_LENGTH)<=0)
            break;
        name = strtok(buffer, "#");
        number = strtok(NULL, "#");
        email = strtok(NULL, "#");
        group = strtok(NULL, "#");
        add(strdup(name), strdup(number), strdup(email), strdup(group));
    }
    fclose(fp);
}

void save(char *fileName) {
    FILE *fp = fopen(fileName, "w");
    if (fp==NULL) {
        printf("Open failed.\n");
        return;
    }

    for (int i=0; i<n; i++) {
        fprintf(fp, "%s#", directory[i].name);
        fprintf(fp, "%s#", (strlen(directory[i].number)==0 ? " " : directory[i].number));
        fprintf(fp, "%s#", (strlen(directory[i].email)==0 ? " " : directory[i].email));
        fprintf(fp, "%s#\n", (strlen(directory[i].group)==0 ? " " : directory[i].group));
    }
    fclose(fp);
}

int search(char *name) {
    for (int i=0; i<n; i++) {
        if (strcmp(name, directory[i].name)==0) {
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
    release_person(directory[i]);
    int j = i;
    for (; j<n-1; j++) {
        directory[j] = directory[j+1];
    }
    n--;
    printf("'%s' was deleted successfully. \n", name);
}

void release_person(Person p) {
    if (p.name != NULL) free(p.name);
    if (p.number != NULL) free(p.number);
    if (p.email != NULL) free(p.email);
    if (p.group != NULL) free(p.group);
}

void print_person(Person p)
{
    printf("%s:\n", p.name);
    printf("   Phone: %s\n", p.number);
    printf("   Email: %s\n", p.email);
    printf("   Group: %s\n", p.group);
}

void status() {
    for (int i=0; i<n; i++)
        print_person(directory[i]);
    printf("Total %d persons.\n", n);
}

void find(char *name) {
    int index = search(name);
    if (index==-1)
        printf("No person named '%s' exists.\n", name);
    else
        print_person(directory[index]);
}

void handle_add(char * name)  {
    char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
    char empty[] = " ";

    printf("  Phone: ");
    read_line(stdin, number, BUFFER_LENGTH);
    printf("  Email: ");
    read_line(stdin, email, BUFFER_LENGTH);
    printf("  Group: ");
    read_line(stdin, group, BUFFER_LENGTH);

    add(strdup(name), strdup(number),  strdup(email),  strdup(group));
}

void add(char *name, char *number, char *email, char *group) {
    int i=n-1;
    while (i>=0 && strcmp(directory[i].name, name) > 0) {
        directory[i+1] = directory[i];
        i--;
    }

    directory[i+1].name = name;
    directory[i+1].number = number;
    directory[i+1].email = email;
    directory[i+1].group = group;
    n++;
}


//int compose_name(char str[], int limit) {
//    char * ptr;
//    int length = 0;
//    ptr = strtok(NULL, " ");
//    if (ptr == NULL)
//        return 0;
//    strcpy(str, ptr);
//    length += strlen(ptr);
//    while ((ptr = strtok(NULL, " ")) != NULL) {
//        if (length + strlen(ptr) + 1 < limit) {
//            str[length++] = ' ';
//            str[length] = '\0';
//            strcat(str, ptr);
//            length += strlen(ptr);
//        }
//    }
//    return length;
//}

//int compose_name2(char str[], int limit) {
//    char * ptr;
//    int length = 0;
//    str[0] = '\0';
//
//    while ((ptr = strtok(NULL, " ")) != NULL) {
//        if (length + strlen(ptr) + 1 < limit) {
//            strcat(str, ptr);
//            length += strlen(ptr);
//            str[length++] = ' ';
//            str[length] = '\0';
//        }
//    }
//    if (length > 0) {
//        str[length-1] = '\0';
//        length--;
//    }
//    printf(":%s:\n", str);
//    return length;
//}






//int merge_argument(char argument[], int limit) {
//    char * ptr;
//    int length = 0;
//    int cnt = 0;
//    ptr = strtok(NULL, delim);
//    if (ptr != NULL) {
//        strcpy(argument, ptr);
//        length = strlen(argument);
//        cnt++;
//    }
//    else {
//        argument[0] = '\0';
//        return 0;
//    }
//    while ((ptr = strtok(NULL, delim)) != NULL) {
//        argument[length++] = ' ';
//        argument[length] = '\0';
//        strcat(argument, ptr);
//        length += strlen(argument);
//        cnt++;
//    }
//    return cnt;
//}
//
//int merge_tokens(int s, int t, char *tokens[], int limit, char merged[])
//{
//    int length = 0;
//    strcpy(merged, tokens[s]);
//    length = strlen(merged);
//    for (int i=s+1; i<t && length + strlen(tokens[i]) < limit - 1; i++) {
//        merged[length++] = ' ';
//        merged[length] = '\0';
//        strcat(merged, tokens[i]);
//        length += strlen(tokens[i]);
//    }
//    return length;
//}
//

//int split_string(int max_tokens, char *tokens[], char *str_to_split, const char *delim)
//{
//    char * ptr = strtok(str_to_split, delim);
//    int i = 0;
//    while(i < max_tokens && ptr != NULL)
//    {
//        tokens[i++] = ptr;
//        ptr = strtok(NULL, delim);
//    }
//    return i;
//}


/* trimming leading and trailing blanks */
/* replace multiple blanks by a single blank */
//int read_line(FILE * fp, char str[], int n) {
//    int ch, prev = '\0', i = 0;
//    while ((ch=fgetc(fp)) == ' ');
//    while (ch != '\n' && ch != EOF) {
//        if (i < n && !(prev == ' ' && ch == ' ')) {
//            str[i++] = ch;
//            prev = ch;
//        }
//        ch = fgetc(fp);
//    }
//    if (i > 0 && str[i - 1] == ' ') {
//        str[i - 1] = '\0';
//        return i - 1;
//    }
//    str[i] = '\0';
//    return i;
//}

//int read_line(FILE * fp, char str[], int n)
//{
//    int ch, i = 0;
//    while ((ch = fgetc(fp)) != '\n' && ch != EOF)
//        if (i < n)
//            str[i++] = ch;
//    str[i] = '\0';
//    return i;
//}




