#ifndef HEXDUMP_H
#define HEXDUMP_H

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Available output formats supported by the hexdump utility.
 */
typedef enum {
    FORMAT_DEFAULT_X, // Default: Two-byte hexadecimal (-x)
    FORMAT_CANONICAL_C, // Canonical: 16 bytes hex + ASCII (-C)
    FORMAT_BYTE_OCTAL_B, // One-byte octal (-b)
    FORMAT_BYTE_CHAR_C,  // One-byte character (-c)
    FORMAT_TWO_BYTE_DECIMAL_D, // Two-byte decimal (-d)
    FORMAT_TWO_BYTE_OCTAL_O  // Two-byte octal (-o)
} HexdumpFormat;

/**
 * @brief Structure to hold the configuration settings for the hexdump run.
 */
typedef struct {
    HexdumpFormat format;
    const char *filename;
} HexdumpConfig;

/**
 * @brief The maximum number of bytes to display per line.
 */
#define BYTES_PER_LINE 16

/* --- Argument and Execution Prototypes (Defined in hexdump_main.c) --- */

bool parse_arguments(int argc, char *argv[], HexdumpConfig *config);
int hexdump_run(const HexdumpConfig *config);

/* --- Format Printing Prototypes (Defined in hexdump_formats.c) --- */

void print_format_c(const uint8_t *buffer, long offset, size_t count);
void print_format_1byte(const uint8_t *buffer, long offset, size_t count, HexdumpFormat format);
void print_format_2byte(const uint8_t *buffer, long offset, size_t count, HexdumpFormat format);

#endif // HEXDUMP_H
