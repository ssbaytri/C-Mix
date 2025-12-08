#!/bin/bash

# --- Configuration ---
TEST_FILE="test_data.bin"
CUSTOM_PROGRAM="./hexzero"

# --- Test Data Creation ---
# Creates a test file containing:
# 0x01, 0x02, 0x03, 0x04, ... 0x1F, 0x20
# (32 bytes of simple sequential data, which ensures partial lines are tested too)
printf '\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\x20' > "$TEST_FILE"

# --- Setup Check ---
if [ ! -f "$CUSTOM_PROGRAM" ]; then
    echo "ERROR: Custom program '$CUSTOM_PROGRAM' not found."
    echo "Please ensure you have compiled it using 'make'."
    exit 1
fi

echo "--- Starting Hexdump Verification Test ---"
echo "Test file created with 32 bytes of sequential data."
echo

# --- Test Cases ---
OPTIONS="-b -c -C -d -o -x"
TOTAL_TESTS=0
FAILED_TESTS=0

for OPT in $OPTIONS; do
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Define output files
    CUSTOM_OUT="custom_${OPT}.txt"
    SYSTEM_OUT="system_${OPT}.txt"

    echo "Testing option: $OPT..."
    
    # 1. Run custom program
    "$CUSTOM_PROGRAM" "$OPT" "$TEST_FILE" > "$CUSTOM_OUT"
    
    # 2. Run standard hexdump
    # Note: On some systems, the default hexdump is slightly different.
    # We use 'hd' (which is often a symlink to hexdump -C) or /usr/bin/hexdump.
    # We rely on the core 'hexdump' command being available.
    hexdump "$OPT" "$TEST_FILE" > "$SYSTEM_OUT"

    # 3. Compare outputs
    if diff -q "$CUSTOM_OUT" "$SYSTEM_OUT" > /dev/null; then
        echo "  [PASS] Output matches standard hexdump."
    else
        FAILED_TESTS=$((FAILED_TESTS + 1))
        echo "  [FAIL] Output MISMATCHES standard hexdump. See details below:"
        echo "==================================================="
        # Show the differences for easier debugging
        diff -u "$SYSTEM_OUT" "$CUSTOM_OUT"
        echo "==================================================="
    fi

    # Clean up output files
    rm -f "$CUSTOM_OUT" "$SYSTEM_OUT"

done

# --- Cleanup ---
rm -f "$TEST_FILE"

# --- Summary ---
echo
echo "--- Test Summary ---"
if [ $FAILED_TESTS -eq 0 ]; then
    echo "SUCCESS: All $TOTAL_TESTS tests passed!"
else
    echo "FAILURE: $FAILED_TESTS out of $TOTAL_TESTS tests failed."
fi

exit $FAILED_TESTS