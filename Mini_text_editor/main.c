#include <stdio.h>
#include <string.h>

int edit_line(char *buffer, int curr_line)
{
	for (int i = 0; i < curr_line; i++)
	{
		buffer = strchr(buffer, '\n');
		if (!buffer)
			return (printf("Invalid Line\n"), 0);
		buffer = buffer + 1;
	}
	char *line_end = strchr(buffer, '\n');
	char saved[1024] = {0};
	strcpy(saved, line_end);
	scanf("%s", buffer);
	strcat(buffer, saved);
	return (1);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (printf("./editor: [filename]\n"), 1);
	FILE* file = fopen(argv[1], "r");
	char buffer[1024] = {0};
	fread(buffer, 1024, 1, file);
	fclose(file);

	int current_line = 0;
	printf("Contents: \n%s\n", buffer);
	scanf("%d", &current_line);
	if (!edit_line(buffer, current_line))
		return (1);
	file = fopen(argv[1], "w");
	fwrite(buffer, strlen(buffer), 1, file);
	fclose(file);

	return (0);
}