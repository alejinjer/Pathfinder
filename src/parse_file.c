#include "pathfinder.h"

static void check_first_line(t_main *m) {
    if (m->lineptr == NULL)
        mx_printerr_pf(FILE_EMPTY, m->filename);
    else if (mx_isnumber(m->lineptr)) {
        m->V = mx_atoi(m->lineptr);
        mx_strdel(&m->lineptr);
    } else
        mx_terminate("error: line 1 isn\'t valid");
}

static bool check_line(char *line) {
    int i = -1;
    int island1 = 0;
    int island2 = 0;

    if (mx_strcmp(line, "") == 0)
        return false;
    while (mx_isalpha(line[++i]))
        island1++;
    if (line[i] != '-')
        return false;
    while (mx_isalpha(line[++i]))
        island2++;
    if (!island1 || !island2)
        return false;
    if (line[i++] != ',')
        return false;
    if (!(line[i]) || !mx_isnumber(line + i))
        return false;
    return true;
}

static void parse_line(t_main *m) {
    char **ptr;
    char *ptr1;
    t_island *island1;
    t_island *island2;
    int weight;

    ptr = mx_strsplit(m->lineptr, '-');
    island1 = mx_get_island(&m->islands, mx_strdup(ptr[0]));
    ptr1 = mx_strdup(ptr[1]);
    mx_del_strarr(&ptr);
    ptr = mx_strsplit(ptr1, ',');
    mx_strdel(&ptr1);
    island2 = mx_get_island(&m->islands, mx_strdup(ptr[0]));
    weight = mx_atoi(ptr[1]);
    mx_del_strarr(&ptr);
    mx_set_link(&island1->links, island2, weight);
    mx_set_link(&island2->links, island1, weight);
}

static void check_isl_count(t_main *m) {
    t_island *iter = m->islands;
    int count = 0;

    while (iter) {
        count++;
        iter = iter->next;
    }
    if (m->V != count)
        mx_terminate("error: invalid number of islands");
}

void mx_parse_file(t_main *m) {
    int line = 2;

    mx_read_line(&m->lineptr, BUF_SIZE, DELIM, m->fd);
    check_first_line(m);
    while (mx_read_line(&m->lineptr, BUF_SIZE, DELIM, m->fd) >= 0) {
        if (check_line(m->lineptr))
            parse_line(m);
        else
            mx_printerr_pf(INVLD_LINE, mx_itoa(line));
        mx_strdel(&m->lineptr);
        line++;
    }
    check_isl_count(m);
}
