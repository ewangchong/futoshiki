VERBOSE_LIMIT = 10

def parse_input(lines):
    """Parse the 15-line input format into horizontal and vertical constraints."""
    horizontal = [[None] * 6 for _ in range(9)]  # 9 rows, 6 possible horizontal constraints each
    vertical = [[None] * 9 for _ in range(6)]    # 6 constraint rows, 9 columns each
    
    h_idx = 0  # Index for horizontal constraint rows
    v_idx = 0  # Index for vertical constraint rows
    
    for i, line in enumerate(lines):
        # Get all constraint symbols in this line
        symbols = [c for c in line if c in '<>^v']
        horizontal_symbols = [c for c in symbols if c in '<>']
        vertical_symbols = [c for c in symbols if c in '^v']
        
        if horizontal_symbols and not vertical_symbols:
            # This is a horizontal constraint line
            if h_idx < 9:
                col_idx = 0
                for c in line:
                    if c in '<>':
                        if col_idx < 6:
                            horizontal[h_idx][col_idx] = c
                            col_idx += 1
                h_idx += 1
        elif vertical_symbols and not horizontal_symbols:
            # This is a vertical constraint line
            if v_idx < 6:
                col_idx = 0
                for c in line:
                    if c in '^v':
                        if col_idx < 9:
                            vertical[v_idx][col_idx] = c
                            col_idx += 1
                v_idx += 1
    
    return horizontal, vertical


def is_valid(grid, row, col, val, horizontal, vertical):
    """Check if placing val at (row, col) is valid."""
    # Check row constraint
    for c in range(9):
        if grid[row][c] == val:
            return False
    
    # Check column constraint
    for r in range(9):
        if grid[r][col] == val:
            return False
    
    # Check 3x3 subgrid constraint
    start_row, start_col = (row // 3) * 3, (col // 3) * 3
    for r in range(start_row, start_row + 3):
        for c in range(start_col, start_col + 3):
            if grid[r][c] == val:
                return False
    
    # Check inequality constraints
    # Horizontal constraints (between columns)
    constraint_positions = [0, 1, 3, 4, 6, 7]  # Skip positions 2 and 5 (thick lines)
    
    for i, pos in enumerate(constraint_positions):
        if col == pos and col + 1 < 9:
            # Check constraint between col and col+1
            constraint = horizontal[row][i]
            if constraint and grid[row][col + 1] != 0:
                if constraint == '<' and val >= grid[row][col + 1]:
                    return False
                elif constraint == '>' and val <= grid[row][col + 1]:
                    return False
        elif col == pos + 1 and col - 1 >= 0:
            # Check constraint between col-1 and col
            constraint = horizontal[row][i]
            if constraint and grid[row][col - 1] != 0:
                if constraint == '<' and grid[row][col - 1] >= val:
                    return False
                elif constraint == '>' and grid[row][col - 1] <= val:
                    return False
    
    # Vertical constraints (between rows)
    constraint_rows = [0, 1, 3, 4, 6, 7]  # Skip rows 2 and 5 (thick lines)
    
    for i, pos in enumerate(constraint_rows):
        if row == pos and row + 1 < 9:
            # Check constraint between row and row+1
            constraint = vertical[i][col]
            if constraint and grid[row + 1][col] != 0:
                if constraint == '^' and val >= grid[row + 1][col]:
                    return False
                elif constraint == 'v' and val <= grid[row + 1][col]:
                    return False
        elif row == pos + 1 and row - 1 >= 0:
            # Check constraint between row-1 and row
            constraint = vertical[i][col]
            if constraint and grid[row - 1][col] != 0:
                if constraint == '^' and grid[row - 1][col] >= val:
                    return False
                elif constraint == 'v' and grid[row - 1][col] <= val:
                    return False
    
    return True


def solve(grid, horizontal, vertical, verbose=False):
    """Solve the enhanced Sudoku using backtracking."""
    step_count = 0
    
    def find_empty():
        for r in range(9):
            for c in range(9):
                if grid[r][c] == 0:
                    return r, c
        return None, None
    
    def solve_recursive():
        nonlocal step_count
        step_count += 1
        
        if verbose and step_count <= VERBOSE_LIMIT:
            print(f"Step {step_count}: Looking for empty position...")
        
        row, col = find_empty()
        if row is None:
            return True  # All positions filled
        
        for val in range(1, 10):
            if is_valid(grid, row, col, val, horizontal, vertical):
                grid[row][col] = val
                
                if verbose and step_count <= VERBOSE_LIMIT:
                    print(f"  Placed {val} at ({row}, {col})")
                
                if solve_recursive():
                    return True
                
                grid[row][col] = 0  # Backtrack
        
        return False
    
    return solve_recursive()


def print_solution(grid):
    """Print the solution in the required format."""
    for row in grid:
        print(' '.join(map(str, row)))


def solve_enhanced_sudoku(input_text, verbose=False):
    """Main function to solve enhanced Sudoku from input text."""
    lines = input_text.strip().split('\n')
    horizontal, vertical = parse_input(lines)

    print(horizontal)
    print(vertical)

    # Initialize empty grid
    grid = [[0] * 9 for _ in range(9)]
    
    if solve(grid, horizontal, vertical, verbose):
        return grid
    else:
        return None


def solve_from_stdin():
    """Solve enhanced Sudoku reading from standard input."""
    import sys
    lines = [line.rstrip('\n') for line in sys.stdin]
    solution = solve_enhanced_sudoku('\n'.join(lines))
    print_solution(solution)


def show_demo():
    """Simple demo showing how the solver works"""
    test_input = """ > <   < <   > <
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
 > >   < >   < <"""
    
    print("Enhanced Sudoku Solver Demo")
    print("=" * 40)
    print("Solving puzzle with constraints...")
    
    solution = solve_enhanced_sudoku(test_input, verbose=True)
    
    if solution:
        print("\nFinal Solution:")
        print_solution(solution)
    else:
        print("No solution found!")


def main():
    test_input = """ > <   < <   > <
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
 > >   < >   < <"""

    print("Enhanced Sudoku Solver")
    print("=" * 30)
    
    solution = solve_enhanced_sudoku(test_input)
    
    if solution:
        print("Solution:")
        print_solution(solution)
        print("\nTo see solving steps: show_demo()")
    else:
        print("No solution found!")

    show_demo()


if __name__ == "__main__":
    main()
