#ifndef PATHFINDER_HEADER
#define PATHFINDER_HEADER

#define BUF_SIZE 128 // for read_line
#define DELIM '\n'   // for read_line

#include "libmx.h"

typedef enum e_error
{
    FILE_DEXIST,
    FILE_EMPTY,
    INVLD_LINE,
} t_error;

typedef struct s_island t_island;
typedef struct s_link t_link;
typedef struct s_main t_main;
typedef struct s_path t_path;

struct s_island
{
    int index;
    char *name;
    t_link *links;  // linked islands list
    t_path **paths; // path to each island
    t_island *next;
};

struct s_link
{
    int weight; // weight between parent and linked island
    t_island *linked_island;
    t_link *next;
};

struct s_main
{
    int fd;                    // for read_line
    char *filename;            // for read_line
    char *lineptr;             // for read_line
    int V;                     // islands count
    t_island *islands;         // all islands
    t_island *start;           // for find_path
    t_island *end;             // for find_path
    int weight;                // for find_path
    t_island *start_remainder; // for find_path
};

struct s_path
{
    t_link *route;
    int dist;         // summary distance of route
    bool is_shortest; // true if dist of path is minimum in list of paths
    t_path *next;
};

//util.c
void mx_printerr_pf(t_error err, const char *s);
int mx_atoi(const char *str);
//main.c
t_main *mx_create_main();
void mx_prepare_for_algorithm(t_main *m);
//islands.c
t_island *mx_create_island(char *name);
void mx_add_island(t_island **islands, t_island *i);
t_island *mx_get_island(t_island **islands, char *name);
//links.c
t_link *mx_create_link(t_island *linked_island);
void mx_add_link(t_link **links, t_link *l);
void mx_push_back_link(t_link **links, t_link *l);
void mx_set_link(t_link **links, t_island *linked_island, int weight);
void mx_pop_back_link(t_link **links);
//paths.c
t_path *mx_create_path(t_link *routes);
void mx_add_path(t_path **paths, t_path *p);
//parse_file.c
void mx_parse_file(t_main *m);
//find_all_paths.c
void mx_find_all_paths(t_main *m);
//print_all_paths.c
void mx_print_all_paths(t_main *m);

#endif
