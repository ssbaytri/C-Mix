#include "main.h"

char *read_file(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (!fp)
		return (NULL);
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	rewind(fp);

	char *buffer = malloc(size + 1);
	if (!buffer)
		return (NULL);
	fread(buffer, size, 1, fp);
	buffer[size] = '\0';
	fclose(fp);
	return (buffer);
}

void write_file(const char *filename, const char *data)
{
	FILE *fp = fopen(filename, "w");
	if (!fp)
		return;
	fputs(data, fp);
	fclose(fp);
}

char *read_stdin(void)
{
    char *buffer = NULL;
    size_t buffer_size = 0;
    size_t total_size = 0;
    char chunk[4096];
    size_t bytes_read;

    while ((bytes_read = fread(chunk, 1, sizeof(chunk), stdin)) > 0) {
        if (total_size + bytes_read >= buffer_size) {
            buffer_size = (buffer_size == 0) ? 4096 : buffer_size * 2;
            while (buffer_size <= total_size + bytes_read) {
                buffer_size *= 2;
            }
            buffer = realloc(buffer, buffer_size + 1);
            if (!buffer) {
                fprintf(stderr, "Error: Memory allocation failed\n");
                return NULL;
            }
        }
        memcpy(buffer + total_size, chunk, bytes_read);
        total_size += bytes_read;
    }

    if (buffer) {
        buffer[total_size] = '\0';
    }
    return buffer;
}

void print_usage(void)
{
    fprintf(stderr, "Usage: base64 [OPTION]... [FILE]\n");
    fprintf(stderr, "Base64 encode or decode FILE, or standard input, to standard output.\n\n");
    fprintf(stderr, "  -d, --decode     decode data\n");
    fprintf(stderr, "  -i, --input      input file (use '-' for stdin)\n");
    fprintf(stderr, "  -o, --output     output file (use '-' for stdout)\n");
    fprintf(stderr, "  -h, --help       display this help and exit\n\n");
    fprintf(stderr, "With no FILE, or when FILE is -, read standard input.\n");
}

