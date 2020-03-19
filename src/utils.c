#include "pathfinder.h"

void mx_printerr_pf(t_error err, const char *s) {
    switch (err) {
        case FILE_DEXIST:
            mx_printerr("error: file ");
            mx_printerr(s);
            mx_printerr(" does not exist");
            break;
        case FILE_EMPTY:
            mx_printerr("error: file ");
            mx_printerr(s);
            mx_printerr(" is empty");
            break;
        case INVLD_LINE:
            mx_printerr("error: line ");
            mx_printerr(s);
            mx_printerr(" isn\'t valid");
            break;
    }
    mx_printerr("\n");
    exit(1);
}

int mx_atoi(const char *str) {
    int i = -1;
    int result = 0;

    while (str[++i]) {
        if (mx_isdigit(str[i]))
            result = result * 10 + str[i] - '0';
        if (!mx_isdigit(str[i]))
            return result;
    }
    return result;
}
