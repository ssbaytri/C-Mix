#include "hexdump.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For getopt
#include <errno.h>

// --- Argument Parsing ---

bool parse_arguments(int argc, char *argv[], HexdumpConfig *config) {
    // Default configuration: 2-byte hex (-x)
    config->format = FORMAT_DEFAULT_X;
    config->filename = NULL;

    int opt;
    // Handle single-character options
    while ((opt = getopt(argc, argv, "bcCdox")) != -1) {
        switch (opt) {
            case 'b': config->format = FORMAT_BYTE_OCTAL_B; break;
            case 'c': config->format = FORMAT_BYTE_CHAR_C; break;
            case 'C': config->format = FORMAT_CANONICAL_C; break;
            case 'd': config->format = FORMAT_TWO_BYTE_DECIMAL_D; break;
            case 'o': config->format = FORMAT_TWO_BYTE_OCTAL_O; break;
            case 'x': config->format = FORMAT_DEFAULT_X; break;
            case '?': // getopt prints error message for unknown options
                return false;
            default:
                return false;
        }
    }

    // Check for remaining arguments (should be the filename, if any)
    if (optind < argc) {
        if (optind == argc - 1) {
            config->filename = argv[optind];
        } else {
            fprintf(stderr, "Error: Too many arguments.\n");
            return false;
        }
    }

    return true;
}

/**
 * @brief Reads the input stream and dispatches the buffer to the correct printing function.
 */
int hexdump_run(const HexdumpConfig *config) {
    FILE *input_file;

    // Handle standard input vs. file input
    if (config->filename == NULL) {
        input_file = stdin;
    } else {
        input_file = fopen(config->filename, "rb");
        if (input_file == NULL) {
            perror("Error opening file");
            return -1;
        }
    }

    uint8_t buffer[BYTES_PER_LINE];
    size_t bytes_read;
    long offset = 0;

    // Read input in chunks of 16 bytes
    while ((bytes_read = fread(buffer, 1, BYTES_PER_LINE, input_file)) > 0) {
        // Dispatch based on the configured format
        switch (config->format) {
            case FORMAT_CANONICAL_C:
                print_format_c(buffer, offset, bytes_read);
                break;
            case FORMAT_BYTE_OCTAL_B:
            case FORMAT_BYTE_CHAR_C:
                print_format_1byte(buffer, offset, bytes_read, config->format);
                break;
            case FORMAT_DEFAULT_X:
            case FORMAT_TWO_BYTE_DECIMAL_D:
            case FORMAT_TWO_BYTE_OCTAL_O:
                print_format_2byte(buffer, offset, bytes_read, config->format);
                break;
        }
        offset += bytes_read;
    }

    // Check for read errors
    if (ferror(input_file)) {
        if (input_file != stdin) fclose(input_file);
        return -1;
    }
    
    // Print the final offset line
    if (config->format == FORMAT_CANONICAL_C) {
        printf("%08lx\n", offset);
    } else {
        // All other formats use a 7-digit offset based on 2-byte groups
        printf("%07lx\n", offset / 2); 
    }

    // Close the file if it was opened
    if (input_file != stdin && input_file != NULL) {
        fclose(input_file);
    }

    return 0;
}

int main(int argc, char *argv[]) {
    HexdumpConfig config;

    if (!parse_arguments(argc, argv, &config)) {
        fprintf(stderr, "Usage: %s [-b|-c|-C|-d|-o|-x] [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (hexdump_run(&config) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}