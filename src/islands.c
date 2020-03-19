#include "pathfinder.h"

t_island *mx_create_island(char *name) {
    t_island *island = malloc(sizeof(t_island));

    island->links = NULL;
    island->name = name;
    island->next = NULL;
    return island;
}

void mx_add_island(t_island **islands, t_island *i) {
    if (!*islands) {
        *islands = i;
        return;
    }
    i->next = *islands;
    *islands = i;
}

t_island *mx_get_island(t_island **islands, char *name) {
    t_island *iter = *islands;
    t_island *last_island;

    if (!iter) {
        *islands = mx_create_island(name);
        return *islands;
    }
    while (iter) {
        if (mx_strcmp(iter->name, name) == 0) {
            mx_strdel(&name);
            return iter;
        }
        if (iter->next == NULL)
            last_island = iter;
        iter = iter->next;
    }
    last_island->next = mx_create_island(name);
    return last_island->next;
}
