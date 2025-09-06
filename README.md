# Futoshiki Solver

A comprehensive Futoshiki puzzle solver implemented in multiple programming languages: Python, C, and C++.

## What is Futoshiki?

Futoshiki is a logic puzzle where you fill a grid with numbers following these rules:
1. **Sudoku rules**: Each row, column, and 3×3 box contains unique numbers 1-9
2. **Inequality constraints**: Adjacent cells must satisfy `<`, `>`, `^`, and `v` relationships
3. **Complete the grid**: Fill all empty cells while respecting both constraints

## Files

- **`futoshiki.py`** - Original Python implementation with full features
- **`futoshiki.cpp`** - Complete C++ implementation with object-oriented design
- **`futoshiki.c`** - Simplified C implementation for maximum compatibility
- **`debug_futoshiki.py`** - Python debugging version
- **`futoshiki_c`** - Compiled C executable (ready to run)
- **`Makefile`** - Build system for C/C++ versions
- **`README_CPP.md`** - Detailed C/C++ documentation

## Quick Start

### Python Version (Recommended for Development)
```bash
python3 futoshiki.py
```

### C Version (Fastest, Most Compatible)
```bash
# Already compiled and ready to run:
./futoshiki_c

# Or compile from source:
make run
```

### C++ Version (Full Featured)
```bash
# Build and run (requires proper C++ environment):
make run-cpp
```

## Performance Comparison

| Language | Execution Speed | Development | Compatibility |
|----------|----------------|-------------|---------------|
| Python   | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐⭐ |
| C        | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |
| C++      | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐ |

## Example Input Format

```
 > <   < <   > <
v ^ v v ^ v ^ ^ v
 < <   < >   < <
v ^ v ^ v v ^ ^ v
 < <   < <   > >
 < >   > >   < >
v v ^ ^ v ^ ^ v v
 < >   > <   > >
^ v v v ^ v v ^ v
 > <   < >   > >
 < >   > >   > <
v v v v ^ ^ ^ ^ ^
 > <   < <   < <
^ ^ ^ ^ ^ v v v ^
 > >   < >   < <
```

Where:
- `<` `>` indicate horizontal inequalities (left < right, left > right)
- `^` `v` indicate vertical inequalities (up ^ down, up v down)
- Spaces represent positions without constraints

## Algorithm

All implementations use the same core algorithm:

1. **Input Parsing**: Convert constraint symbols into internal representation
2. **Backtracking**: Try values 1-9 for each empty cell
3. **Validation**: Check Sudoku rules + inequality constraints
4. **Solution**: Return completed grid or indicate no solution exists

## Building from Source

```bash
# Build both C and C++ versions
make all

# Build and run C version
make run

# Build and run C++ version  
make run-cpp

# Clean compiled files
make clean
```

## Use Cases

- **Educational**: Learn constraint satisfaction and backtracking algorithms
- **Performance Testing**: Compare execution speeds across languages
- **Puzzle Solving**: Solve complex Futoshiki puzzles quickly
- **Algorithm Development**: Extend with new constraint types or optimizations

## Contributing

Feel free to:
- Add optimizations to the solving algorithms
- Implement versions in other programming languages
- Add new constraint types or puzzle variants
- Improve the input/output formats

## License

Open source - feel free to use and modify for educational and personal purposes.
