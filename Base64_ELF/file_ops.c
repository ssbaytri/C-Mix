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
