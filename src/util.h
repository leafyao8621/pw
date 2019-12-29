#ifndef _UTIL_H_
#define _UTIL_H_

#include <time.h>

void reset(void);
void initialize(void);
int create(char* name, char* pw);
int authenticate(char* name, char* pw);
void display(void);
void modify(char* pw);
void edit(double val);
void finalize(void);
#endif
