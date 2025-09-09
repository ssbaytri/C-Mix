#include "main.h"

int main(int argc, char *argv[])
{
	int encode = 0;
	int decode = 0;
	char *input_file = NULL;
	char *output_file = NULL;
    char *direct_input = NULL;

	for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) {
            encode = 1;
        } else if (strcmp(argv[i], "-d") == 0) {
            decode = 1;
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            input_file = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            output_file = argv[++i];
        } else {
            continue;
        }
    }

    for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
        if ((input_file && strcmp(argv[i], input_file) == 0) ||
            (output_file && strcmp(argv[i], output_file) == 0)) {
            continue;
        }
        direct_input = argv[i];
        break;
    }
}

	if ((encode && decode) || (!encode && !decode))
	{
		fprintf(stderr, "Error: Specify either -e (encode) or -d (decode), not both.\n");
        goto usage;
	}

    if (encode && direct_input)
    {
        char *encoded_str = encode_op(direct_input);
        printf("%s\n", encoded_str);
    }

    if (decode && direct_input)
    {
        char *decode_str = decode_op(direct_input);
        printf("%s\n", decode_str);
    }

	return (0);

	usage:
	fprintf(stderr,
        "Usage: base64tool -e|-d [-i input_file] [-o output_file]\n"
        "  -e : encode\n"
        "  -d : decode\n"
        "  -i : specify input file (default: stdin)\n"
        "  -o : specify output file (default: stdout)\n");

	return (1);
}