#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void initialize(void) {
    FILE* fin = fopen("cre/cre", "rb");
    fread(&cnt, 1, 1, fin);
    if (cnt) {
        fread(users, sizeof(struct User), cnt, fin);
    }
    fclose(fin);
}

static int encode(char* in, char* out, time_t key) {
    srand(key);

}
int create(char* name, char* pw) {
    if (cnt == 20) return 1;
    if (strlen(name) > 7) return 2;
    if (strlen(pw) > 15) return 3;
    struct User* ii = users;
    for (size_t i = 0; i < cnt; ++i) {
        if (!strcmp(ii->name, name)) {
            return 4;
        }
    }
    strcpy(ii->name, name);
    ii->created = time(0);
    if (encode(ii->pw, pw, ii->created)) return 5
    cnt++;
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
