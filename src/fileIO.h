//
// Created by Lavinia on 3/23/2020.
//


#ifndef DISCRETE_FILEIO_H
#define DISCRETE_FILEIO_H



typedef struct Line{
    char *value;
    struct  Line *next;
} Line;


char *parse();
Line * split(char * str, char *separator);
void print_lines(Line *head);
void remove_spaces_from_lines(Line *head);
void remove_spaces(char * s);
Line *process_input();
Line* get_numbers(char *s);


#endif //DISCRETE_FILEIO_H
