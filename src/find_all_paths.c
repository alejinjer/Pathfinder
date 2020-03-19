#include "pathfinder.h"

static bool is_visited(t_link *visited, t_island *i) {
    t_link *iter = visited;

    if (!iter)
        return false;
    while (iter) {
        if (iter->linked_island->name == i->name)
            return true;
        iter = iter->next;
    }
    return false;
}

static void set_distances(t_path *path) {
    t_path *iter = path;
    t_link *rt;
    int distance;

    while (iter) {
        if (!iter->dist) {
            rt = iter->route;
            distance = 0;
            while (rt) {
                distance += rt->weight;
                rt = rt->next;
            }
            iter->dist = distance;
            distance = 0;
        }
        iter = iter->next;
    }
}

static void check_is_shortest(t_path *path) {
    t_path *iter = path;
    int min_dist = path->dist;

    while (iter) {
        if (iter->dist < min_dist)
            min_dist = iter->dist;
        iter->is_shortest = false;
        iter = iter->next;
    }
    iter = path;
    while (iter) {
        if (iter->dist == min_dist)
            iter->is_shortest = true;
        iter = iter->next;
    }
}

static void find_path(t_main *m, t_link *visited, int weight, t_path **paths) {
    t_link *iter = m->start->links;
    t_link *visited_island = NULL;

    if (is_visited(visited, m->start))
        return;
    visited_island = mx_create_link(m->start);
    visited_island->weight = weight;
    mx_push_back_link(&visited, visited_island);
    if (m->start == m->end)
        mx_add_path(&paths[m->end->index], mx_create_path(visited));
    else
        while (iter) {
            m->start = iter->linked_island;
            find_path(m, visited, iter->weight, paths);
            iter = iter->next;
        }
    mx_pop_back_link(&visited);
}

void mx_find_all_paths(t_main *m) {
    m->start = m->islands;
    t_link *visited = NULL;

    while (m->start) {
        m->end = m->start->next;
        m->start_remainder = m->start;
        while (m->end) {
            if (m->start != m->end) {
                find_path(m, visited, 0, m->start->paths);
                m->start = m->start_remainder;
                set_distances(m->start->paths[m->end->index]);
                check_is_shortest(m->start->paths[m->end->index]);
            }
            m->end = m->end->next;
        }
        m->start = m->start->next;
    }
}
