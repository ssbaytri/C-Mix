#include "hotrace.h"
#include <sys/time.h>

unsigned long hash_function(const char *str) {
    unsigned long hash = 5381;
    int c;
    
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_SIZE;
}

int read_line(char *buffer, int size) {
    int i = 0;
    char c;
    
    while (i < size - 1 && read(0, &c, 1) > 0 && c != '\n')
        buffer[i++] = c;
    buffer[i] = '\0';
    return i;
}

void insert(char *key, char *value, char *table[])
{
    unsigned long index;

    index = hash_function(key);
    table[index] = strdup(value);
}

char *search(char *key, char *table[])
{
    unsigned long index;

    index = hash_function(key);
    return (table[index]);
}

void print_table(char *values[])
{
    for (size_t i = 0; i < HASH_SIZE; i++)
    {
        if (values[i])
            printf("the value %s at index %zu\n", values[i], i);
    }
}

int main()
{
    struct timeval start, end;
	double elapsed_time_sec;
	long elapsed_time_usec;
    gettimeofday(&start, NULL);
    char **values;
    char key[BUFFER_SIZE];
    char value[BUFFER_SIZE];
    values = calloc(HASH_SIZE, sizeof(char *));
    if (!values)
        return 1;
    while (1)
    {
        if (read_line(key, sizeof(key)) == 0)
            break;
        if (read_line(value, sizeof(value)) == 0)
            break;
        insert(key, value, values);
    }
    // print_table(values);

    while (read_line(key, sizeof(key)) > 0) {
        const char *result = search(key, values);
        if (result)
        {
            write(1, result, strlen(result));
            write(1, "\n", 1);
        }
        else {
            write(1, key, strlen(key));
            write(1, " Not found.\n", 12);
        }
        // write(1, "\n", 1);
    }

    gettimeofday(&end, NULL);
	elapsed_time_sec = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
	elapsed_time_usec = end.tv_usec - start.tv_usec;
	if (elapsed_time_usec < 0) {
		elapsed_time_sec--;
		elapsed_time_usec += 1000000;
	}
	printf("Execution time: %.6f seconds and %ld microseconds\n", elapsed_time_sec, elapsed_time_usec);
    return (0);
}
