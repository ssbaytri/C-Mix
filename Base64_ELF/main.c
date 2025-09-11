#include "main.h"

int main(int argc, char *argv[])
{
    int decode_mode = 0;
    char *input_file = NULL;
    char *output_file = NULL;
    char *positional_file = NULL;
    
    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--decode") == 0) {
            decode_mode = 1;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage();
            return 0;
        } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--input") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: Option %s requires an argument\n", argv[i]);
                print_usage();
                return 1;
            }
            input_file = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: Option %s requires an argument\n", argv[i]);
                print_usage();
                return 1;
            }
            output_file = argv[++i];
        } else if (argv[i][0] != '-') {
            // This is a positional argument (filename)
            if (positional_file == NULL) {
                positional_file = argv[i];
            } else {
                fprintf(stderr, "Error: Multiple input files specified\n");
                print_usage();
                return 1;
            }
        } else {
            fprintf(stderr, "Error: Unknown option %s\n", argv[i]);
            print_usage();
            return 1;
        }
    }

    // Determine input source
    char *input_data = NULL;
    int free_input_data = 1;
    
    if (input_file != NULL) {
        // -i option was specified
        if (strcmp(input_file, "-") == 0) {
            input_data = read_stdin();
        } else {
            input_data = read_file(input_file);
            if (!input_data) {
                fprintf(stderr, "Error: Cannot read file '%s': %s\n", input_file, strerror(errno));
                return 1;
            }
        }
    } else if (positional_file != NULL) {
        // Positional filename argument
        if (strcmp(positional_file, "-") == 0) {
            input_data = read_stdin();
        } else {
            input_data = read_file(positional_file);
            if (!input_data) {
                fprintf(stderr, "Error: Cannot read file '%s': %s\n", positional_file, strerror(errno));
                return 1;
            }
        }
    } else {
        // No input specified, read from stdin
        input_data = read_stdin();
    }

    if (!input_data) {
        fprintf(stderr, "Error: Failed to read input data\n");
        return 1;
    }

    // Process the data
    char *result = NULL;
    if (decode_mode) {
        result = decode_op(input_data);
        if (!result) {
            fprintf(stderr, "Error: Invalid base64 input\n");
            free(input_data);
            return 1;
        }
    } else {
        result = encode_op(input_data);
        if (!result) {
            fprintf(stderr, "Error: Encoding failed\n");
            free(input_data);
            return 1;
        }
    }

    // Output the result
    if (output_file != NULL) {
        if (strcmp(output_file, "-") == 0) {
            printf("%s", result);
            if (!decode_mode) {
                printf("\n"); // Add newline for encoding (like real base64)
            }
        } else {
            FILE *fp = fopen(output_file, "w");
            if (!fp) {
                fprintf(stderr, "Error: Cannot write to file '%s': %s\n", output_file, strerror(errno));
                free(input_data);
                free(result);
                return 1;
            }
            fputs(result, fp);
            if (!decode_mode) {
                fputc('\n', fp); // Add newline for encoding
            }
            fclose(fp);
        }
    } else {
        // Output to stdout
        printf("%s", result);
        if (!decode_mode) {
            printf("\n"); // Add newline for encoding (like real base64)
        }
    }

    // Cleanup
    if (free_input_data) {
        free(input_data);
    }
    free(result);
    
    return 0;
}
