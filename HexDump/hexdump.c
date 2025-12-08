#include "hexdump.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// --- Argument Parsing ---

bool parse_arguments(int argc, char *argv[], HexdumpConfig *config) {
    config->format = FORMAT_DEFAULT_X;
    config->filename = NULL;

    int opt;
    while ((opt = getopt(argc, argv, "bcCdox")) != -1) {
        switch (opt) {
            case 'b': config->format = FORMAT_BYTE_OCTAL_B; break;
            case 'c': config->format = FORMAT_BYTE_CHAR_C; break;
            case 'C': config->format = FORMAT_CANONICAL_C; break;
            case 'd': config->format = FORMAT_TWO_BYTE_DECIMAL_D; break;
            case 'o': config->format = FORMAT_TWO_BYTE_OCTAL_O; break;
            case 'x': config->format = FORMAT_DEFAULT_X; break;
            case '?':
                return false;
            default:
                return false;
        }
    }

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
 * @brief Compares two buffers to check if they're identical
 */
static bool buffers_equal(const uint8_t *buf1, const uint8_t *buf2, size_t size) {
    return memcmp(buf1, buf2, size) == 0;
}

/**
 * @brief Reads the input stream and dispatches the buffer to the correct printing function.
 */
int hexdump_run(const HexdumpConfig *config) {
    FILE *input_file;

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
    uint8_t prev_buffer[BYTES_PER_LINE];
    size_t bytes_read;
    size_t prev_bytes_read = 0;
    long offset = 0;
    bool duplicate_suppressed = false;
    bool first_line = true;
    bool any_data_read = false;

    while ((bytes_read = fread(buffer, 1, BYTES_PER_LINE, input_file)) > 0) {
        any_data_read = true;
        // Check if this line is identical to the previous line
        bool is_duplicate = !first_line && 
                           bytes_read == prev_bytes_read && 
                           bytes_read == BYTES_PER_LINE &&
                           buffers_equal(buffer, prev_buffer, BYTES_PER_LINE);

        if (is_duplicate) {
            // Suppress duplicate lines, print * only once
            if (!duplicate_suppressed) {
                printf("*\n");
                duplicate_suppressed = true;
            }
            // Don't print the line, but still need to track offset
        } else {
            // Print the line normally
            duplicate_suppressed = false;
            
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
            
            // Save current buffer for next comparison (only when not a duplicate)
            memcpy(prev_buffer, buffer, BYTES_PER_LINE);
            prev_bytes_read = bytes_read;
        }

        first_line = false;
        offset += bytes_read;
    }

    if (ferror(input_file)) {
        if (input_file != stdin) fclose(input_file);
        return -1;
    }
    
    // Print the final offset line only if we read any data
    if (any_data_read) {
        if (config->format == FORMAT_CANONICAL_C) {
            printf("%08lx\n", offset);
        } else {
            printf("%07lx\n", offset);
        }
    }

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