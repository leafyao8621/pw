#ifndef _UTIL_H_
#define _UTIL_H_

#include <time.h>
size_t cnt;
struct User {
    char name[9];
    time_t created;
    char pw[50];
} users[20];

double data[100];

void initialize(void);
int create(char* name, char* pw);
int authenticate(char* name, char* pw, size_t ind);
void display(size_t ind);
void modify(size_t ind, double val);
void finalize(void);
#endif
