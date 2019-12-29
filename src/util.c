#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#define RAND ((double)rand() / RAND_MAX)

static double pmf[676], cdf[676];

static char *table[26] = {
    "字",
    "善",
    "敵",
    "三",
    "声",
    "舞",
    "球",
    "宿",
    "印",
    "女",
    "千",
    "絵",
    "録",
    "独",
    "隼",
    "父",
    "楓",
    "男",
    "山",
    "的",
    "同",
    "勝",
    "酒",
    "検",
    "米",
    "希"
};

static size_t cnt, ind;

static struct User {
    char name[9];
    time_t created;
    char pw[50];
} users[20];

static double data[100];

void reset(void) {
    FILE* fout = fopen("cre/cre", "wb");
    char out = 0;
    fwrite(&out, 1, 1, fout);
    fclose(fout);
}

void initialize(void) {
    FILE* fin = fopen("cre/cre", "rb");
    fread(&cnt, 1, 1, fin);
    if (cnt) {
        fread(users, sizeof(struct User), cnt, fin);
    }
    fclose(fin);
    double *ii, *jj;
    ii = pmf; jj = cdf;
    for (size_t i = 0; i < 26; ++i) {
        for (size_t j = 0; j < 26; ++j, ++ii, ++jj) {
            *ii = i == j ? 0.2 : 0.8 / 25;
            *jj = (j ? jj[-1] : 0) + *ii;
        }
    }
}

static int encode(char* in, char* out, time_t key) {
    srand(key);
    char *j = out;
    for (char *i = in; *i; ++i) {
        char temp = (*i) & 0xcf;
        if (!(temp >= 'A' && temp <= 'Z')) return 1;
        double a = RAND;
        double *l = cdf + 26 * (temp - 'A');
        size_t k = 0;
        for (k = 0; k < 26 && *l < a; ++k, ++l);
        for (char *l = table[k]; *l; *(j++) = *(l++));
    }
    *j = 0;
    return 0;
}

int create(char* name, char* pw) {
    if (cnt == 20) return 1;
    if (strlen(name) > 7) return 2;
    if (strlen(pw) > 15) return 3;
    struct User* ii = users;
    for (size_t i = 0; i < cnt; ++i, ++ii) {
        if (!strcmp(ii->name, name)) {
            return 4;
        }
    }
    strcpy(ii->name, name);
    ii->created = time(0);
    if (encode(pw, ii->pw, ii->created)) return 5;
    cnt++;
    return 0;
}

int authenticate(char* name, char* pw) {
    size_t i = 0;
    struct User* ii = users;
    for (; i < cnt && strcmp(ii->name, name); ++i, ++ii);
    if (i == cnt) return 1;
    char buf[50];
    if (encode(pw, buf, ii->created)) return 2;
    if (strcmp(buf, ii->pw)) {
        return 3;
    }
    return 0;
}

void finalize(void) {
    FILE* fout = fopen("cre/cre", "wb");
    fwrite(&cnt, 1, 1, fout);
    if (cnt) {
        fwrite(users, sizeof(struct User), cnt, fout);
    }
    fclose(fout);
}
