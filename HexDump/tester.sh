#!/bin/bash

# --- Configuration ---
CUSTOM_PROGRAM="./hexzero"

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# --- Setup Check ---
if [ ! -f "$CUSTOM_PROGRAM" ]; then
    echo -e "${RED}ERROR: Custom program '$CUSTOM_PROGRAM' not found.${NC}"
    echo "Please ensure you have compiled it using 'make'."
    exit 1
fi

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  Advanced Hexdump Testing Suite${NC}"
echo -e "${BLUE}========================================${NC}"
echo

# --- Counters ---
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# --- Test Function ---
run_test() {
    local test_name="$1"
    local test_file="$2"
    local option="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    local custom_out="custom_test_${TOTAL_TESTS}.txt"
    local system_out="system_test_${TOTAL_TESTS}.txt"
    
    # Run both programs
    "$CUSTOM_PROGRAM" "$option" "$test_file" > "$custom_out" 2>&1
    hexdump "$option" "$test_file" > "$system_out" 2>&1
    
    # Compare outputs
    if diff -q "$custom_out" "$system_out" > /dev/null 2>&1; then
        echo -e "${GREEN}[PASS]${NC} $test_name"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}[FAIL]${NC} $test_name"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        echo -e "${YELLOW}Expected vs Actual:${NC}"
        echo "==========================================="
        diff -u "$system_out" "$custom_out" | head -30
        echo "==========================================="
    fi
    
    # Cleanup
    rm -f "$custom_out" "$system_out"
}

# --- Test Cases ---

echo -e "${BLUE}Test Suite 1: Edge Cases${NC}"
echo "-----------------------------------"

# Test 1: Empty file
TEST_FILE="test_empty.bin"
touch "$TEST_FILE"
run_test "Empty file (-x)" "$TEST_FILE" "-x"
run_test "Empty file (-C)" "$TEST_FILE" "-C"
run_test "Empty file (-b)" "$TEST_FILE" "-b"
rm -f "$TEST_FILE"

# Test 2: Single byte
TEST_FILE="test_single.bin"
printf '\x42' > "$TEST_FILE"
run_test "Single byte (-x)" "$TEST_FILE" "-x"
run_test "Single byte (-C)" "$TEST_FILE" "-C"
run_test "Single byte (-b)" "$TEST_FILE" "-b"
run_test "Single byte (-c)" "$TEST_FILE" "-c"
rm -f "$TEST_FILE"

# Test 3: Exactly 16 bytes (one full line)
TEST_FILE="test_16bytes.bin"
printf '\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F' > "$TEST_FILE"
run_test "Exactly 16 bytes (-x)" "$TEST_FILE" "-x"
run_test "Exactly 16 bytes (-C)" "$TEST_FILE" "-C"
run_test "Exactly 16 bytes (-d)" "$TEST_FILE" "-d"
rm -f "$TEST_FILE"

# Test 4: 17 bytes (one full line + 1 byte)
TEST_FILE="test_17bytes.bin"
printf '\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10' > "$TEST_FILE"
run_test "17 bytes (-x)" "$TEST_FILE" "-x"
run_test "17 bytes (-C)" "$TEST_FILE" "-C"
run_test "17 bytes (-o)" "$TEST_FILE" "-o"
rm -f "$TEST_FILE"

echo
echo -e "${BLUE}Test Suite 2: Special Characters${NC}"
echo "-----------------------------------"

# Test 5: All printable ASCII
TEST_FILE="test_printable.bin"
printf 'Hello World! 123' > "$TEST_FILE"
run_test "Printable ASCII (-C)" "$TEST_FILE" "-C"
run_test "Printable ASCII (-c)" "$TEST_FILE" "-c"
rm -f "$TEST_FILE"

# Test 6: All control characters
TEST_FILE="test_control.bin"
printf '\x00\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F' > "$TEST_FILE"
run_test "Control characters (-C)" "$TEST_FILE" "-C"
run_test "Control characters (-c)" "$TEST_FILE" "-c"
run_test "Control characters (-b)" "$TEST_FILE" "-b"
rm -f "$TEST_FILE"

# Test 7: Mixed printable and non-printable
TEST_FILE="test_mixed.bin"
printf 'ABC\x00\x01\x02DEF\x0A\x0D\x09GHI' > "$TEST_FILE"
run_test "Mixed characters (-C)" "$TEST_FILE" "-C"
run_test "Mixed characters (-c)" "$TEST_FILE" "-c"
rm -f "$TEST_FILE"

# Test 8: All escape sequences
TEST_FILE="test_escapes.bin"
printf '\x00\x07\x08\x09\x0A\x0B\x0C\x0D' > "$TEST_FILE"
run_test "Escape sequences (-c)" "$TEST_FILE" "-c"
rm -f "$TEST_FILE"

echo
echo -e "${BLUE}Test Suite 3: Boundary Conditions${NC}"
echo "-----------------------------------"

# Test 9: 15 bytes (one short line)
TEST_FILE="test_15bytes.bin"
printf '\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F' > "$TEST_FILE"
run_test "15 bytes (-x)" "$TEST_FILE" "-x"
run_test "15 bytes (-C)" "$TEST_FILE" "-C"
rm -f "$TEST_FILE"

# Test 10: 31 bytes (almost two lines)
TEST_FILE="test_31bytes.bin"
printf '\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F' > "$TEST_FILE"
run_test "31 bytes (-x)" "$TEST_FILE" "-x"
run_test "31 bytes (-d)" "$TEST_FILE" "-d"
rm -f "$TEST_FILE"

# Test 11: 32 bytes (exactly two lines)
TEST_FILE="test_32bytes.bin"
printf '\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x20' > "$TEST_FILE"
run_test "32 bytes (-x)" "$TEST_FILE" "-x"
run_test "32 bytes (-o)" "$TEST_FILE" "-o"
rm -f "$TEST_FILE"

# Test 12: 33 bytes (two lines + 1)
TEST_FILE="test_33bytes.bin"
printf '\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x20\x21' > "$TEST_FILE"
run_test "33 bytes (-x)" "$TEST_FILE" "-x"
run_test "33 bytes (-C)" "$TEST_FILE" "-C"
rm -f "$TEST_FILE"

echo
echo -e "${BLUE}Test Suite 4: Large Data${NC}"
echo "-----------------------------------"

# Test 13: 256 bytes (all byte values)
TEST_FILE="test_256bytes.bin"
for i in {0..255}; do
    printf "\\x$(printf '%02x' $i)"
done > "$TEST_FILE"
run_test "256 bytes all values (-x)" "$TEST_FILE" "-x"
run_test "256 bytes all values (-C)" "$TEST_FILE" "-C"
run_test "256 bytes all values (-b)" "$TEST_FILE" "-b"
rm -f "$TEST_FILE"

# Test 14: 1000 bytes of repeated pattern
TEST_FILE="test_1000bytes.bin"
for i in {1..1000}; do
    printf '\x55'
done > "$TEST_FILE"
run_test "1000 bytes pattern (-x)" "$TEST_FILE" "-x"
run_test "1000 bytes pattern (-d)" "$TEST_FILE" "-d"
rm -f "$TEST_FILE"

echo
echo -e "${BLUE}Test Suite 5: All Format Options${NC}"
echo "-----------------------------------"

# Test 15: Same data, all formats
TEST_FILE="test_all_formats.bin"
printf '\x01\x23\x45\x67\x89\xAB\xCD\xEF\xFE\xDC\xBA\x98\x76\x54\x32\x10' > "$TEST_FILE"
run_test "All formats test (-x)" "$TEST_FILE" "-x"
run_test "All formats test (-C)" "$TEST_FILE" "-C"
run_test "All formats test (-b)" "$TEST_FILE" "-b"
run_test "All formats test (-c)" "$TEST_FILE" "-c"
run_test "All formats test (-d)" "$TEST_FILE" "-d"
run_test "All formats test (-o)" "$TEST_FILE" "-o"
rm -f "$TEST_FILE"

echo
echo -e "${BLUE}Test Suite 6: Binary Data Patterns${NC}"
echo "-----------------------------------"

# Test 16: All zeros
TEST_FILE="test_zeros.bin"
printf '\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00' > "$TEST_FILE"
run_test "All zeros (-x)" "$TEST_FILE" "-x"
run_test "All zeros (-d)" "$TEST_FILE" "-d"
rm -f "$TEST_FILE"

# Test 17: All ones (0xFF)
TEST_FILE="test_ones.bin"
printf '\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF' > "$TEST_FILE"
run_test "All 0xFF (-x)" "$TEST_FILE" "-x"
run_test "All 0xFF (-o)" "$TEST_FILE" "-o"
rm -f "$TEST_FILE"

# Test 18: Alternating pattern
TEST_FILE="test_alternating.bin"
printf '\xAA\x55\xAA\x55\xAA\x55\xAA\x55\xAA\x55\xAA\x55\xAA\x55\xAA\x55' > "$TEST_FILE"
run_test "Alternating 0xAA/0x55 (-x)" "$TEST_FILE" "-x"
run_test "Alternating 0xAA/0x55 (-C)" "$TEST_FILE" "-C"
rm -f "$TEST_FILE"

# Test 19: Incrementing bytes
TEST_FILE="test_incrementing.bin"
for i in {0..63}; do
    printf "\\x$(printf '%02x' $i)"
done > "$TEST_FILE"
run_test "Incrementing 0-63 (-x)" "$TEST_FILE" "-x"
run_test "Incrementing 0-63 (-C)" "$TEST_FILE" "-C"
rm -f "$TEST_FILE"

# Test 20: High-bit set characters
TEST_FILE="test_highbit.bin"
printf '\x80\x81\x82\x83\x84\x85\x86\x87\x88\x89\x8A\x8B\x8C\x8D\x8E\x8F' > "$TEST_FILE"
run_test "High-bit characters (-C)" "$TEST_FILE" "-C"
run_test "High-bit characters (-b)" "$TEST_FILE" "-b"
rm -f "$TEST_FILE"

# --- Final Summary ---
echo
echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  Test Summary${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "Total Tests:  ${TOTAL_TESTS}"
echo -e "${GREEN}Passed:       ${PASSED_TESTS}${NC}"
echo -e "${RED}Failed:       ${FAILED_TESTS}${NC}"
echo

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}🎉 SUCCESS! All tests passed!${NC}"
    exit 0
else
    PASS_RATE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
    echo -e "${YELLOW}Pass rate: ${PASS_RATE}%${NC}"
    echo -e "${RED}Some tests failed. Review the output above for details.${NC}"
    exit 1
fi