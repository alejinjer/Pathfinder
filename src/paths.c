#include "pathfinder.h"

t_path *mx_create_path(t_link *route) {
    t_path *path = mx_memalloc(sizeof(t_path));
    t_link *iter = route;
    t_link *ptr;

    path->route = mx_create_link(route->linked_island);
    path->route->weight = route->weight;
    path->next = NULL;
    ptr = path->route;
    while (iter->next) {
        ptr->next = mx_create_link(iter->next->linked_island);
        ptr->next->weight = iter->next->weight;
        ptr = ptr->next;
        iter = iter->next;
    }
    return path;
}

void mx_add_path(t_path **paths, t_path *p) {
    if (!*paths) {
        *paths = p;
        return;
    }
    p->next = *paths;
    *paths = p;
}
