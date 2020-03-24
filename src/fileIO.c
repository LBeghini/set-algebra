//
// Created by Lavinia on 3/23/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "fileIO.h"

char *parse(char *path) {

    char ch;
    FILE *fp;

    fp = fopen(path, "r");

    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
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

Line * split(char * strFile){
    const char s[2] = "\n";
    char *token;

    Line *current;
    Line *head;

    head = (Line*) malloc(sizeof(Line));

    head->next= NULL;
    head->value=NULL;

    current = head;

    token = strtok(strFile, s);

    while(token!= NULL){
        current->value = token;

        token = strtok(NULL, s);

        if(token != NULL){
            current->next = (Line*) malloc(sizeof(Line));
            current = current->next;
            current->next = NULL;
        }
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