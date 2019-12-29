#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

int main(void) {
    initialize();
    create("admin", "admin");
    _Bool cont = 1;
    for (; cont;) {
        puts("l to login; c to create; q to quit");
        fflush(stdout);
        int in = getchar();
        for (; in == 10; in = getchar());
        int code;
        char name[100], *pw, *pw1, *pw2;
        switch (in) {
        case 'l':
            printf("%s: ", "user name");
            fflush(stdout);
            scanf("%s", name);
            pw = getpass("password: ");
            if (authenticate(name, pw)) {
                printf("%s\n", "login failed!");
                break;
            }
            printf("Welcome %s!\n", name);
            break;
        case 'c':
            printf("%s: ", "user name");
            fflush(stdout);
            scanf("%s", name);
            pw1 = getpass("new password: ");
            pw2 = getpass("new password: ");
            if (strcmp(pw1, pw2)) {
                puts("Invalid!");
                break;
            }
            if (code = create(name, pw1)) {
                printf("Invalid! code: %d\n", code);
                break;
            }
            printf("User %s has been created!\n", name);
            break;
        case 'q':
            cont = 0;
            break;
        // default:
        //     puts("Invalid!");
        }
    }
    finalize();
}
