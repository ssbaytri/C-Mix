# Base64 Encoder/Decoder

A lightweight, command-line base64 encoding and decoding tool written in C. This tool provides functionality similar to the standard `base64` utility with support for files, stdin/stdout, and flexible input/output options.

## Features

- **Encode** text and binary data to base64
- **Decode** base64 data back to original format
- Read from **files** or **stdin**
- Write to **files** or **stdout**
- Automatic **newline handling** during decoding
- **Error handling** for invalid base64 input
- Compatible command-line interface

## Building

To compile the base64 tool, use:

```bash
gcc -o base64 main.c file_ops.c ops.c
```

Or if you have a Makefile:

```bash
make
```

## Usage

```
base64 [OPTION]... [FILE]
```

### Options

- `-d, --decode`     Decode data (default is encode)
- `-i, --input`      Specify input file (use '-' for stdin)
- `-o, --output`     Specify output file (use '-' for stdout)  
- `-h, --help`       Display help message

### Input/Output

- **No file specified**: Reads from stdin
- **FILE**: Read from the specified file
- **'-'**: Explicitly use stdin/stdout

## Examples

### Basic Encoding

```bash
# Encode a string (via stdin)
echo "Hello world" | ./base64
# Output: SGVsbG8gd29ybGQK

# Encode a file
./base64 test.txt
# Output: SGVsbG8gd29ybGQK

# Encode with explicit input file
./base64 -i test.txt
```

### Basic Decoding

```bash
# Decode from stdin
echo "SGVsbG8gd29ybGQK" | ./base64 -d
# Output: Hello world

# Decode a file containing base64
./base64 -d encoded.txt

# Decode with explicit options
./base64 --decode --input encoded.txt
```

### File Operations

```bash
# Encode file and save to another file
./base64 -i input.txt -o output.b64

# Decode file and save result
./base64 -d -i encoded.b64 -o decoded.txt

# Using positional arguments
./base64 input.txt > output.b64
./base64 -d encoded.b64 > original.txt
```

### Stdin/Stdout Examples

```bash
# Pipe operations
cat file.txt | ./base64 | ./base64 -d

# Explicit stdin usage
./base64 -i - -o encoded.txt < input.txt

# Explicit stdout usage
./base64 -i input.txt -o -
```

## Implementation Details

### File Structure

- **main.c**: Command-line argument parsing and program flow
- **file_ops.c**: File I/O operations and utility functions
- **ops.c**: Base64 encoding and decoding algorithms
- **main.h**: Header with function declarations and includes

### Key Features

#### Robust Input Handling
- Dynamically allocated buffers for large files
- Automatic memory management
- Support for binary data

#### Standards Compliant
- Uses standard base64 alphabet: `A-Z`, `a-z`, `0-9`, `+`, `/`
- Proper padding with `=` characters
- Handles newlines and whitespace in encoded input

#### Error Handling
- Invalid base64 character detection
- File access error reporting
- Memory allocation failure handling

## Testing

The repository includes test files for verification:

```bash
# Test basic encoding
./base64 test.txt
# Expected: SGVsbG8gd29ybGQK

# Test decoding
echo "SGVsbG8gd29ybGQK" | ./base64 -d
# Expected: Hello world

# Test with newlines in base64 (should be ignored)
./base64 -d test_with_newlines.txt
# Should decode properly despite line breaks
```

## Memory Management

- All dynamically allocated memory is properly freed
- Input buffers are automatically sized based on content
- No memory leaks in normal operation paths

## Compatibility

- **POSIX compliant** C code
- Compatible with **GCC** and **Clang**
- Tested on **Linux** and **Unix-like** systems
- Should compile on **macOS** and **Windows** (with appropriate compiler)

## Error Codes

- `0`: Success
- `1`: Error (invalid arguments, file access issues, invalid base64, etc.)

## Contributing

When contributing to this project:

1. Ensure code follows the existing style
2. Add appropriate error handling
3. Test with various input sizes and types
4. Update documentation as needed

## License

"This project is open source, feel free to use it as you like!"

---

*This base64 tool provides a reliable, efficient implementation for encoding and decoding base64 data with flexible input/output options suitable for both interactive use and shell scripting.*
