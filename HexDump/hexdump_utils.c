#include "hexdump.h"
#include <stdio.h>
#include <ctype.h>

// --- Utility Function for Little-Endian Display ---

static uint16_t swap_uint16(uint16_t val) {
    return (val << 8) | (val >> 8);
}

// --- Canonical Format (-C) ---

static void print_ascii_section(const uint8_t *buffer, size_t count) {
    printf(" |");
    for (size_t i = 0; i < count; ++i) {
        char c = (char)buffer[i];
        printf("%c", isprint((unsigned char)c) ? c : '.');
    }
    printf("|\n");
}

void print_format_c(const uint8_t *buffer, long offset, size_t count) {
    printf("%08lx  ", offset);

    for (size_t i = 0; i < BYTES_PER_LINE; ++i) {
        if (i < count) {
            printf("%02x", buffer[i]);
        } else {
            printf("  ");
        }
        
        printf(" ");

        if (i == 7) {
            printf(" ");
        }
    }

    print_ascii_section(buffer, count);
}

// --- One-Byte Formats (-b and -c) ---

void print_format_1byte(const uint8_t *buffer, long offset, size_t count, HexdumpFormat format) {
    printf("%07lx", offset); 

    for (size_t i = 0; i < BYTES_PER_LINE; ++i) {
        if (i < count) {
            switch (format) {
                case FORMAT_BYTE_OCTAL_B:
                    printf(" %03o", buffer[i]);
                    break;
                case FORMAT_BYTE_CHAR_C:
                    // Handle special escape sequences first
                    if (buffer[i] == '\0') {
                        printf("  \\0");
                    } else if (buffer[i] == '\a') {
                        printf("  \\a");
                    } else if (buffer[i] == '\b') {
                        printf("  \\b");
                    } else if (buffer[i] == '\t') {
                        printf("  \\t");
                    } else if (buffer[i] == '\n') {
                        printf("  \\n");
                    } else if (buffer[i] == '\v') {
                        printf("  \\v");
                    } else if (buffer[i] == '\f') {
                        printf("  \\f");
                    } else if (buffer[i] == '\r') {
                        printf("  \\r");
                    } else if ((buffer[i] >= 32 && buffer[i] < 127) || buffer[i] >= 160) {
                        // Printable: ASCII 32-126 or extended ASCII 160-255
                        printf(" %3c", buffer[i]);
                    } else {
                        // Non-printable: use octal
                        printf(" %03o", buffer[i]);
                    }
                    break;
                default:
                    break;
            }
        } else {
            printf("    ");
        }
    }
    printf("\n");
}

// --- Two-Byte Formats (-x, -d, -o) with Little-Endian Display ---

void print_format_2byte(const uint8_t *buffer, long offset, size_t count, HexdumpFormat format) {
    printf("%07lx", offset);

    for (size_t i = 0; i < 8; ++i) {
        size_t index = 2 * i;

        if (index < count) {
            uint16_t unit;
            
            if (index + 1 < count) {
                uint8_t b1 = buffer[index];
                uint8_t b2 = buffer[index + 1];
                unit = (b1 << 8) | b2;
            } else {
                unit = buffer[index] << 8;
            }
            
            uint16_t swapped_unit = swap_uint16(unit);

            switch (format) {
                case FORMAT_DEFAULT_X:
                    printf("    %04x", swapped_unit);
                    break;
                case FORMAT_TWO_BYTE_DECIMAL_D:
                    printf("   %05u", swapped_unit);
                    break;
                case FORMAT_TWO_BYTE_OCTAL_O:
                    printf("  %06o", swapped_unit);
                    break;
                default:
                    break;
            }
        } else {
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