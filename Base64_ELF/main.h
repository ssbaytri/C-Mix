#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*encode_op(char *input);
char	*decode_op(char *input);

char	*read_file(const char *filename);
void	write_file(const char *filename, const char *data);
