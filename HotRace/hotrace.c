#include "hotrace.h"
#include <sys/time.h>
unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_SIZE;
}

t_hash_table *create_hash_table() {
    t_hash_table *ht = malloc(sizeof(t_hash_table));
    if (!ht) return NULL;
    
    ht->size = HASH_SIZE;
    ht->entries = calloc(HASH_SIZE, sizeof(t_entry *));
    if (!ht->entries) {
        free(ht);
        return NULL;
    }
    return ht;
}

void insert(t_hash_table *ht, const char *key, const char *value) {
    unsigned long index = hash_function(key);
    t_entry *entry = malloc(sizeof(t_entry));
    if (!entry) return;
    
    entry->key = strdup(key);
    entry->value = strdup(value);
    entry->next = ht->entries[index];
    ht->entries[index] = entry;
}

const char *search(t_hash_table *ht, const char *key) {
    unsigned long index = hash_function(key);
    t_entry *entry = ht->entries[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0)
            return entry->value;
        entry = entry->next;
    }
    return NULL;
}

void free_hash_table(t_hash_table *ht) {
    for (size_t i = 0; i < ht->size; i++) {
        t_entry *entry = ht->entries[i];
        while (entry) {
            t_entry *next = entry->next;
            free(entry->key);
            free(entry->value);
            free(entry);
            entry = next;
        }
    }
    free(ht->entries);
    free(ht);
}

int read_line(char *buffer, int size) {
    int i = 0;
    char c;
    
    while (i < size - 1 && read(0, &c, 1) > 0 && c != '\n')
        buffer[i++] = c;
    buffer[i] = '\0';
    return i;
}

void print_hash_table(t_hash_table *ht) {
    if (!ht) return;
    
    for (size_t i = 0; i < ht->size; i++) {
        t_entry *entry = ht->entries[i];
        if (entry) {
            printf("Bucket %zu:\n", i);
            while (entry) {
                printf("  %s => %s\n", entry->key, entry->value);
                entry = entry->next;
            }
        }
    }
}

void	ll()
{
	system("leaks -q hotrace");
}

int main(void) {
	struct timeval start, end;
	double elapsed_time_sec;
	long elapsed_time_usec;
	gettimeofday(&start, NULL);
	atexit(ll);
    t_hash_table *ht = create_hash_table();
    if (!ht) return 1;

    char key[BUFFER_SIZE];
    char value[BUFFER_SIZE];
    
    // Read key-value pairs
    while (1) {
        if (read_line(key, sizeof(key)) == 0) break;
        if (read_line(value, sizeof(value)) == 0) break;
        insert(ht, key, value);
    }

    // Process search queries
    while (read_line(key, sizeof(key)) > 0) {
        const char *result = search(ht, key);
        if (result)
            write(1, result, strlen(result));
        else {
            write(1, key, strlen(key));
            write(1, " Not found.\n", 12);
        }
        write(1, "\n", 1);
    }
	print_hash_table(ht);
    free_hash_table(ht);
	gettimeofday(&end, NULL);
	elapsed_time_sec = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
	elapsed_time_usec = end.tv_usec - start.tv_usec;
	if (elapsed_time_usec < 0) {
		elapsed_time_sec--;
		elapsed_time_usec += 1000000;
	}
	printf("Execution time: %.6f seconds and %ld microseconds\n", elapsed_time_sec, elapsed_time_usec);
    return 0;
}