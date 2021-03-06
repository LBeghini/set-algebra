//
// Created by Lavinia on 3/23/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileIO.h"
#define PRIMARY_PATH "..\\set.txt"
#define SECONDARY_PATH "set.txt"

char *parse() {

    char ch;
    FILE *fp;

    fp = fopen(PRIMARY_PATH, "r");

    if (fp == NULL) {
        fp = fopen(SECONDARY_PATH, "r");
        if (fp == NULL){
            perror("Error while opening the file.\n");
            exit(EXIT_FAILURE);
        }
    }

    int numberOfChar = 0;

    while (fscanf(fp, "%c", &ch) != EOF){
        numberOfChar++;
    }

    char *file;
    file = (char*) malloc(numberOfChar * sizeof(char));
    file[numberOfChar] = '\0';

    int count = 0;

    fseek(fp, 0, SEEK_SET);

    while (fscanf(fp, "%c", &ch) != EOF){
        file[count] = ch;
        count++;
    }

    fclose(fp);

    return file;
}

Line * split(char * str, char * separator){
    char *token;

    Line *current;
    Line *head;

    head = (Line*) malloc(sizeof(Line));

    head->next= NULL;
    head->value=NULL;

    current = head;

    token = strtok(str, separator);

    while(token!= NULL){
        current->value = token;

        token = strtok(NULL, separator);

        if(token != NULL){
            current->next = (Line*) malloc(sizeof(Line));
            current = current->next;
            current->next = NULL;
        }
    }

    if(head->next == NULL && head->value == NULL){
        return NULL;
    }

    return head;

}

void print_lines(Line *head){
    if(head == NULL){
        return;
    }
    printf("%s",head->value);
    print_lines(head->next);
}

void remove_spaces_from_lines(Line *head){
    if(head){
        remove_spaces(head->value);
        remove_spaces_from_lines(head->next);
    }

    return;
}

void remove_spaces(char * s){
    char *copy = s;
    char *temp = s;

    while(*copy){
        if(*copy != ' '){
            *temp++ = *copy;
        }
        copy++;
    }

    *temp = 0;
}

Line* get_numbers(char *s){
    char *aux = (char*) malloc(sizeof(char) * (int)(strlen(s)+1));
    strcpy(aux, s);

    char *copy = aux;
    char *tmp = aux;

    while (*copy){
        if((*copy >= '0' && *copy <= '9')||(*copy == ',')||(*copy == '-')){
            *tmp++ = *copy;
        }
        copy++;
    }
    *tmp = 0;

    return split(aux, ",");
}

Line *process_input(){
    char * file = parse();
    Line *head = split(file, "\n");
    remove_spaces_from_lines(head);
    return head;
}
