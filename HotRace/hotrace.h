#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define HASH_SIZE 1000003

typedef struct s_entry {
    char *key;
    char *value;
    struct s_entry *next;
} t_entry;

typedef struct {
    t_entry **entries;
    size_t size;
} t_hash_table;