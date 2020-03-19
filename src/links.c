#include "pathfinder.h"

t_link *mx_create_link(t_island *linked_island) {
    t_link *link = malloc(sizeof(t_link));

    link->linked_island = linked_island;
    link->next = NULL;
    return link;
}

void mx_add_link(t_link **links, t_link *l) {
    if (!*links) {
        *links = l;
        return;
    }
    l->next = *links;
    *links = l;
}

void mx_push_back_link(t_link **links, t_link *l) {
    t_link *iter = *links;

    if (!*links) {
        *links = l;
        return;
    }
    while (iter->next)
        iter = iter->next;
    iter->next = l;
}

void mx_pop_back_link(t_link **links) {
    t_link *l = *links;

    if (*links != NULL) {
        if (l->next == NULL) {
            l->linked_island = NULL;
            free(l);
        } else {
            while (l->next->next)
                l = l->next;
            l->next->linked_island = NULL;
            free(l->next);
            l->next = NULL;
        }
    }
}

void mx_set_link(t_link **links, t_island *linked_island, int weight) {
    t_link *iter = *links;
    t_link *last_link;

    if (!iter) {
        *links = mx_create_link(linked_island);
        (*links)->weight = weight;
        return;
    }
    while (iter) {
        if (linked_island == iter->linked_island)
            return;
        if (iter->next == NULL)
            last_link = iter;
        iter = iter->next;
    }

    last_link->next = mx_create_link(linked_island);
    last_link->next->weight = weight;
}
