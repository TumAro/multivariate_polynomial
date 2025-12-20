#!/bin/bash

# Simple test runner for multivariate polynomial library
# Compiles and runs each test file in tests/ directory

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

PASSED=0
FAILED=0
BUILD_DIR="build"

# Create build directory
mkdir -p "$BUILD_DIR"

echo -e "${BLUE}Running tests...${NC}\n"

# Find all test .cpp files
for test_file in tests/*.cpp; do
    test_name=$(basename "$test_file" .cpp)
    executable="$BUILD_DIR/${test_name}"

    echo -e "${BLUE}>>> Testing: ${test_name}${NC}"

    # Compile
    g++ -std=c++17 -I. "$test_file" -o "$executable" 2>&1

    if [ $? -ne 0 ]; then
        echo -e "${RED}✗ COMPILE FAILED: ${test_name}${NC}\n"
        ((FAILED++))
        continue
    fi

    # Run
    output=$("$executable" 2>&1)
    exit_code=$?

    if [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
        echo "$output"
        ((PASSED++))
    else
        echo -e "${RED}✗ FAILED (exit code: $exit_code)${NC}"
        echo "$output"
        ((FAILED++))
    fi

    echo ""
done

# Summary
echo -e "${BLUE}==================${NC}"
echo -e "${GREEN}Passed: $PASSED${NC}"
echo -e "${RED}Failed: $FAILED${NC}"
echo -e "${BLUE}==================${NC}"

if [ $FAILED -gt 0 ]; then
    exit 1
fi
