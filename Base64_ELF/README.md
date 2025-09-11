# Base64 Encoder/Decoder Tool

A Linux-compatible base64 encoder and decoder utility written in C, designed to replicate the functionality of the standard `base64` command.

## Features

- ✅ **Base64 encoding and decoding**
- ✅ **Multiple input methods**: stdin, files, or command-line arguments
- ✅ **Multiple output methods**: stdout or files
- ✅ **Whitespace tolerance**: Automatically handles newlines and spaces in base64 input
- ✅ **Linux compatibility**: Matches the behavior of the standard `base64` command
- ✅ **Error handling**: Comprehensive error checking and reporting
- ✅ **Memory safe**: Proper memory management with no leaks

## Building

```bash
gcc -o base64 main.c file_operations.c base64_logic.c -I.
```

## Usage

```
base64 [OPTION]... [FILE]
```

### Options

| Option | Long Option | Description |
|--------|-------------|-------------|
| `-d` | `--decode` | Decode base64 input instead of encoding |
| `-i FILE` | `--input FILE` | Read input from specified file (use `-` for stdin) |
| `-o FILE` | `--output FILE` | Write output to specified file (use `-` for stdout) |
| `-h` | `--help` | Display help message and exit |

### Basic Examples

#### Encoding

```bash
# Encode text from stdin
echo "Hello World" | ./base64
# Output: SGVsbG8gV29ybGQK

# Encode from file
./base64 myfile.txt

# Encode to file
echo "Hello World" | ./base64 -o encoded.txt
```

#### Decoding

```bash
# Decode from stdin
echo "SGVsbG8gV29ybGQK" | ./base64 -d
# Output: Hello World

# Decode from file
./base64 -d encoded.txt

# Decode file to another file
./base64 -d -i encoded.txt -o decoded.txt
```

### Advanced Examples

```bash
# Read from file, encode, save to another file
./base64 -i input.txt -o encoded.b64

# Read from stdin, decode, save to file
cat encoded.b64 | ./base64 -d -o output.txt

# Explicit stdin/stdout usage
./base64 -i - -o - < input.txt > output.b64

# Chain operations
echo "test" | ./base64 | ./base64 -d
```

## Input/Output Priority

The tool follows this priority order for determining input source:

1. **`-i` option**: If specified, reads from the given file
2. **Positional argument**: If no `-i` option, uses the filename argument
3. **stdin**: If neither `-i` nor filename specified, reads from stdin

```bash
./base64 -i input.txt output.txt    # Reads from input.txt (ignores output.txt)
./base64 myfile.txt                 # Reads from myfile.txt
./base64                            # Reads from stdin
```

## File Structure

```
base64/
├── main.h              # Header file with function declarations
├── main.c              # Main program with argument parsing
├── file_operations.c   # File I/O operations
├── base64_logic.c      # Base64 encoding/decoding algorithms
├── Makefile           # Build configuration
└── README.md          # This file
```

## Implementation Details

### Base64 Algorithm

The tool implements the standard Base64 encoding as defined in RFC 4648:

- **Character set**: `A-Z`, `a-z`, `0-9`, `+`, `/`
- **Padding**: Uses `=` characters for padding
- **Line breaks**: Adds newlines after encoding (like standard `base64`)
- **Whitespace handling**: Ignores whitespace, newlines, and non-base64 characters when decoding

### Memory Management

- Dynamic memory allocation for input/output buffers
- Automatic cleanup on exit
- Error handling prevents memory leaks
- stdin reading uses chunked buffering for large inputs

### Error Handling

The tool provides clear error messages for:
- Invalid command-line arguments
- File access errors (permissions, not found)
- Invalid base64 input during decoding
- Memory allocation failures

## Compatibility

This tool aims to be fully compatible with the GNU coreutils `base64` command:

```bash
# These should produce identical results:
echo "test" | base64
echo "test" | ./base64

# These should also be identical:
echo "dGVzdAo=" | base64 -d
echo "dGVzdAo=" | ./base64 -d
```

## Error Codes

| Code | Meaning |
|------|---------|
| 0 | Success |
| 1 | Invalid arguments, file errors, or decode errors |

## Examples Output

```bash
$ echo "Hello, World!" | ./base64
SGVsbG8sIFdvcmxkIQo=

$ echo "SGVsbG8sIFdvcmxkIQo=" | ./base64 -d
Hello, World!

$ ./base64 -i /etc/hostname -o hostname.b64
$ ./base64 -d hostname.b64
kali
```

## Development

### Adding Features

To extend functionality:

1. **New options**: Add parsing in `main.c`
2. **New algorithms**: Extend `base64_logic.c`
3. **New I/O methods**: Modify `file_operations.c`

### Testing

Test against the standard `base64` command:

```bash
# Build the project first
make

# Test encoding
echo "test data" | base64 > expected.txt
echo "test data" | ./base64 > actual.txt
diff expected.txt actual.txt

# Test decoding
echo "dGVzdCBkYXRhCg==" | base64 -d > expected.txt
echo "dGVzdCBkYXRhCg==" | ./base64 -d > actual.txt
diff expected.txt actual.txt

# Clean up test files
make clean
```

## License

This project is open source. Feel free to use, modify, and distribute.

## Contributing

Contributions are welcome! Please ensure:

- Code follows the existing style
- New features include appropriate error handling
- Changes maintain compatibility with standard `base64`
- Memory management is properly handled
