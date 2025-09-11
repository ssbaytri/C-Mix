#include "main.h"

int get_index(char c)
{
	const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int i = 0;
	while (base64_table[i])
	{
		if (c == base64_table[i])
			return (i);
		i++;
	}
	return (-1);
}

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
		memset(group, 0, 3);
		strncpy(group, input + i, 3);
		int bytes_read = strlen(input + i);

		if (bytes_read > 3)
			bytes_read = 3;

		result[j++] = base64_table[(group[0] >> 2) & 0x3F];
		result[j++] = base64_table[((group[0] & 0x03) << 4) | ((group[1] >> 4) & 0x0F)];
		
		if (bytes_read == 1)
		{
			result[j++] = '=';
			result[j++] = '=';
		}
		else
		{
			result[j++] = base64_table[((group[1] & 0x0F) << 2) | ((group[2] >> 6) & 0x03)];
			if (bytes_read == 2)
				result[j++] = '=';
			else
				result[j++] = base64_table[group[2] & 0x3F];
		}
	}
	result[output_len] = '\0';
	return (result);
}

char *decode_op(char *input)
{
    // First, strip newlines and invalid chars
    int clean_len = 0;
    char *clean_input = malloc(strlen(input) + 1);
    for (int k = 0; input[k]; k++)
    {
        if ((input[k] >= 'A' && input[k] <= 'Z') ||
            (input[k] >= 'a' && input[k] <= 'z') ||
            (input[k] >= '0' && input[k] <= '9') ||
            input[k] == '+' || input[k] == '/' || input[k] == '=')
        {
            clean_input[clean_len++] = input[k];
        }
    }
    clean_input[clean_len] = '\0';

    int len = clean_len;
    int padding = 0;
    if (len >= 2 && clean_input[len - 1] == '=' && clean_input[len - 2] == '=')
        padding = 2;
    else if (len >= 1 && clean_input[len - 1] == '=')
        padding = 1;

    int decoded_len = (len / 4) * 3 - padding;
    char *result = malloc(decoded_len + 1);

    int i = 0;
    int j = 0;
    while (i < len)
    {
        int a = get_index(clean_input[i++]);
        int b = get_index(clean_input[i++]);
        int c = clean_input[i] == '=' ? 0 : get_index(clean_input[i++]);
        int d = clean_input[i] == '=' ? 0 : get_index(clean_input[i++]);

        int combined = (a << 18) | (b << 12) | (c << 6) | d;

        char byte1 = (combined >> 16) & 0xFF;
        char byte2 = (combined >> 8) & 0xFF;
        char byte3 = combined & 0xFF;

        result[j++] = byte1;
        if (clean_input[i - 2] != '=') result[j++] = byte2;
        if (clean_input[i - 1] != '=') result[j++] = byte3;
    }
    result[j] = '\0';

    free(clean_input);
    return result;
}

