/**
 * This is the utilities File for the program
 */

#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"

/**
 * This function is printing the prompt of the shell with special colors
 *  including the path of the current working directory
 */
void print_prompt() {
    char cwd[PATH_MAX]; // PATH_MAX taken from limits.h
    if (in_server){

    }
    else{

    }
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        fprintf(stdout, "\033[1;35m");
        if (in_server) {
            fprintf(stdout, "user@server");
        } else
            fprintf(stdout, "user@myshell");
        fprintf(stdout, "\033[1;36m");
        fprintf(stdout, ":~%s$ ", cwd);
        fprintf(stdout, "\033[0;37m");
    } else {
        perror("cwd ERROR");
        exit(1);
    }
}

// function to compare to strings with specific length
int str_cmp(char *str1, size_t len1, char *str2, size_t len2) {
    if (len1 != len2)
        return FALSE;

    for (size_t i = 0; i < len1; ++i) {
        if (str1[i] != str2[i])
            return FALSE;
    }
    return TRUE;
}

/**
 *
 * @param paths is a string represent file path
 * @return the first space char found in path
 */
size_t find_space(char *paths) {
    for (size_t i = 0; i < strlen(paths); ++i) {
        if (paths[i] == ' ')
            return i;
    }

    return -1;
}

/**
 *
 * @param str
 * @param to_count
 * @return return the occurrences number of the to_count char in str
 */
int count_chars(char *str, char to_count) {
    int count = 0;
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == to_count)
            ++count;
    }
    return count;
}

/**
 *This function take a string and split it to separate string according to the parse_by char
 * @param str the origin string
 * @param splited - the returned separated strings
 * @param parse_by
 */
void parse_str(char *str, char **splited, char *parse_by) {
    int index = 0;
    char *temp;
    temp = strtok(str, parse_by);

    while (temp != NULL) {
        splited[index++] = temp;
        temp = strtok(NULL, parse_by);
    }
}
