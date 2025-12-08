#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

#define BYTES_PER_LINE 16 // The number of bytes to display per line (0x10)

/**
 * @brief Prints a single line of the canonical hexdump output: 
 * Offset, Hex values (with 8-byte split), and ASCII representation.
 * @param buffer The buffer containing the bytes to print (up to 16 bytes).
 * @param offset The starting file offset for the data in the buffer.
 * @param count The actual number of bytes in the buffer (0 < count <= 16).
 */
void print_canonical_line(const uint8_t *buffer, long offset, size_t count) {
    // 1. Print the file offset (8 hex digits, 0-padded)
    printf("%08lx  ", offset);

    // 2. Print the hexadecimal representation
    for (size_t i = 0; i < BYTES_PER_LINE; ++i) {
        if (i < count) {
            // Print the byte in hex
            printf("%02x", buffer[i]);
        } else {
            // Print spaces for missing bytes (padding on the last line)
            printf("  ");
        }
        
        // Add a space after every byte
        printf(" ");

        // Add the extra space separator after the 8th byte (i=7) for the split
        if (i == 7) {
            printf(" ");
        }
    }

    // 3. Print the ASCII representation (the |...| part)
    printf(" |"); // Start ASCII section
    for (size_t i = 0; i < count; ++i) {
        // Use '.' for non-printable characters (like control characters or null bytes)
        // otherwise, use the character itself.
        char c = (char)buffer[i];
        printf("%c", isprint((unsigned char)c) ? c : '.');
    }
    printf("|\n"); // End ASCII section and line
}

/**
 * @brief Main logic to read from a file descriptor and print the canonical hexdump.
 * @param input_file The FILE pointer (e.g., stdin or a file opened with fopen).
 * @return 0 on success, 1 on failure.
 */
int hexdump_stream(FILE *input_file) {
    uint8_t buffer[BYTES_PER_LINE];
    size_t bytes_read;
    long offset = 0;

    // Read input in chunks of 16 bytes until EOF
    while ((bytes_read = fread(buffer, 1, BYTES_PER_LINE, input_file)) > 0) {
        print_canonical_line(buffer, offset, bytes_read);
        offset += bytes_read;
    }

    // Check for read errors (excluding EOF)
    if (ferror(input_file)) {
        perror("Error reading input");
        return 1;
    }
    
    // 4. Print the final offset line to indicate the total file size
    printf("%08lx\n", offset);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input_file = stdin; // Default to reading from standard input (for piping)

    if (argc == 2) {
        // If a filename is provided, open that file
        input_file = fopen(argv[1], "rb");
        if (input_file == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }
    }

    int result = hexdump_stream(input_file);

    // Close the file if it was opened (not stdin)
    if (input_file != stdin && input_file != NULL) {
        fclose(input_file);
    }

    return (result == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}