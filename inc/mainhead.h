#ifndef MAINHEAD_H
#define MAINHEAD_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void mx_printerr(const char *s);
int mx_strlen(const char *s);
bool mx_atoi(const char *str, int *val);
bool mx_isdigit(char c);
bool mx_isspace(char c);
void mx_printint(int n);
void mx_printchar(char c);
void mx_printstr(const char *s);

#endif
