#include "main.h"

char *encode_op(char *input)
{
	const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int output_len = 4 * ((strlen(input) + 2) / 3);
	char *result = malloc(output_len + 1);
	
	unsigned long i;
	int j = 0;
	for (i = 0; i < strlen(input); i += 3)
	{
		char group[3];
		strncpy(input, group, 3);
		result[j++] = (group[0] >> 2) & 0x3F;
		result[j++] = ((group[0] & 0x03) << 4) | ((group[1] >> 4) & 0x0F); 
		result[j++] = ((group[1] & 0x0F) << 2) | ((group[2] >> 6) & 0x03);
		result[j++] = group[2] & 0x3F;
	}
	return (result);
}