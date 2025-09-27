#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' 

TOTAL=0
PASSED=0
FAILED=0

echo "Testing bad maps in maps/bad directory..."
echo "========================================"

if [ ! -f "./cub3D" ]; then
    echo -e "${RED}Error: cub3D executable not found. Run 'make' first.${NC}"
    exit 1
fi

if [ ! -d "maps/bad" ]; then
    echo -e "${RED}Error: maps/bad directory not found.${NC}"
    exit 1
fi

for map_file in maps/bad/*.cub; do
    if [ -f "$map_file" ]; then
        TOTAL=$((TOTAL + 1))
        filename=$(basename "$map_file")
        
        echo -n "Testing $filename... "
        
        
        ./cub3D "$map_file" >/dev/null 2>&1
        exit_code=$?
        
        
        if [ $exit_code -ne 0 ]; then
            echo -e "${GREEN}PASS${NC} (exit code: $exit_code)"
            PASSED=$((PASSED + 1))
        else
            echo -e "${RED}FAIL${NC} (should have failed but exit code was 0)"
            FAILED=$((FAILED + 1))
        fi
    fi
done

echo "========================================"
echo "Results:"
echo -e "Total tests: ${YELLOW}$TOTAL${NC}"
echo -e "Passed: ${GREEN}$PASSED${NC}"
echo -e "Failed: ${RED}$FAILED${NC}"

if [ $FAILED -eq 0 ]; then
    echo -e "${GREEN}All tests passed!${NC}"
    exit 0
else
    echo -e "${RED}Some tests failed!${NC}"
    exit 1
fi