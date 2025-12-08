#include "hexdump.h"
#include <stdio.h>
#include <ctype.h>

// --- Utility Function for Little-Endian Display ---

/**
 * @brief Swaps the byte order of a 16-bit integer (converts from file order to little-endian display order).
 * If the input is 0xABCD, the output is 0xCDAB.
 * @param val The 16-bit value to swap.
 * @return The byte-swapped value.
 */
static uint16_t swap_uint16(uint16_t val) {
    return (val << 8) | (val >> 8);
}

// --- Canonical Format (-C) ---

/**
 * @brief Prints the ASCII representation for FORMAT_CANONICAL_C.
 */
static void print_ascii_section(const uint8_t *buffer, size_t count) {
    printf(" |");
    for (size_t i = 0; i < count; ++i) {
        char c = (char)buffer[i];
        printf("%c", isprint((unsigned char)c) ? c : '.');
    }
    printf("|\n");
}

/**
 * @brief Prints the data in the FORMAT_CANONICAL_C (-C) format.
 * Offset, 16 hex bytes (8-byte split), and ASCII.
 */
void print_format_c(const uint8_t *buffer, long offset, size_t count) {
    printf("%08lx  ", offset);

    // Print hex bytes with split and padding
    for (size_t i = 0; i < BYTES_PER_LINE; ++i) {
        if (i < count) {
            printf("%02x", buffer[i]);
        } else {
            printf("  "); // Padding for missing bytes
        }
        
        printf(" "); // Space after every byte

        if (i == 7) {
            printf(" "); // Extra space for the 8-byte split
        }
    }

    // Print ASCII part
    print_ascii_section(buffer, count);
}

// --- One-Byte Formats (-b and -c) ---

/**
 * @brief Prints data in formats using 1-byte units (e.g., -b, -c).
 * @param format The format enum (b or c).
 */
void print_format_1byte(const uint8_t *buffer, long offset, size_t count, HexdumpFormat format) {
    // Offset is 7 digits, based on the byte offset
    printf("%07lx", offset); 

    // Print 16 units (bytes)
    for (size_t i = 0; i < BYTES_PER_LINE; ++i) {
        if (i < count) {
            switch (format) {
                case FORMAT_BYTE_OCTAL_B:
                    // One-byte octal (-b)
                    printf(" %03o", buffer[i]);
                    break;
                case FORMAT_BYTE_CHAR_C:
                    // One-byte character (-c): use C escape sequences for non-printables
                    if (isprint((unsigned char)buffer[i])) {
                        printf(" %3c", buffer[i]);
                    } else {
                        switch (buffer[i]) {
                            case '\0': printf(" \\0"); break;
                            case '\a': printf("  \\a"); break;
                            case '\b': printf("  \\b"); break;
                            case '\t': printf("  \\t"); break;
                            case '\n': printf("  \\n"); break;
                            case '\v': printf("  \\v"); break;
                            case '\f': printf("  \\f"); break;
                            case '\r': printf("  \\r"); break;
                            default:   printf(" %03o", buffer[i]); break;
                        }
                    }
                    break;
                default:
                    break;
            }
        } else {
            // Padding for missing bytes
            printf("    ");
        }
    }
    printf("\n");
}


// --- Two-Byte Formats (-x, -d, -o) with Little-Endian Display ---

/**
 * @brief Prints data in formats using 2-byte units (e.g., -x, -d, -o).
 * IMPORTANT: These use little-endian byte swapping for display.
 * @param format The format enum (x, d, or o).
 */
void print_format_2byte(const uint8_t *buffer, long offset, size_t count, HexdumpFormat format) {
    // Offset is 7 hex digits, based on byte offset
    printf("%07lx", offset);

    // Units is the number of 2-byte groups (max 8)
    for (size_t i = 0; i < 8; ++i) {
        size_t index = 2 * i;

        if (index < count) {
            uint16_t unit;
            
            if (index + 1 < count) {
                // Full 2-byte unit available (read B1 B2)
                uint8_t b1 = buffer[index];
                uint8_t b2 = buffer[index + 1];
                // Combine in file order (big-endian)
                unit = (b1 << 8) | b2;
            } else {
                // Partial unit (only one byte remaining) (read B1, pad with 00)
                unit = buffer[index] << 8;
            }
            
            // SWAP bytes for little-endian display (0x B2 B1)
            uint16_t swapped_unit = swap_uint16(unit);

            // Print the swapped unit based on the requested format
            switch (format) {
                case FORMAT_DEFAULT_X:
                    printf("    %04x", swapped_unit); // Hexadecimal (-x)
                    break;
                case FORMAT_TWO_BYTE_DECIMAL_D:
                    printf("   %05u", swapped_unit); // Decimal (-d)
                    break;
                case FORMAT_TWO_BYTE_OCTAL_O:
                    printf("  %06o", swapped_unit); // Octal (-o)
                    break;
                default:
                    break;
            }
        } else {
            // Padding for missing units
            if (format == FORMAT_DEFAULT_X) {
                printf("        ");
            } else if (format == FORMAT_TWO_BYTE_DECIMAL_D) {
                printf("        ");
            } else if (format == FORMAT_TWO_BYTE_OCTAL_O) {
                printf("        ");
            }
        }
    }
    printf("\n");
}