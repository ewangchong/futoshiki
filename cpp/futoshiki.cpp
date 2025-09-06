#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

const int VERBOSE_LIMIT = 10;

struct ParsedConstraints {
    std::vector<std::vector<char>> horizontal;
    std::vector<std::vector<char>> vertical;
};

class FutoshikiSolver {
private:
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<char>> horizontal;
    std::vector<std::vector<char>> vertical;
    int step_count;

public:
    FutoshikiSolver() : step_count(0) {
        // Initialize 9x9 grid with zeros
        grid = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
        // Initialize horizontal constraints (9 rows, 6 constraints each)
        horizontal = std::vector<std::vector<char>>(9, std::vector<char>(6, '\0'));
        // Initialize vertical constraints (6 rows, 9 columns each)
        vertical = std::vector<std::vector<char>>(6, std::vector<char>(9, '\0'));
    }

    ParsedConstraints parseInput(const std::vector<std::string>& lines) {
        ParsedConstraints result;
        result.horizontal = std::vector<std::vector<char>>(9, std::vector<char>(6, '\0'));
        // Restored C++ implementation for Futoshiki solver
        result.vertical = std::vector<std::vector<char>>(6, std::vector<char>(9, '\0'));
        
        int h_idx = 0;  // Index for horizontal constraint rows
        int v_idx = 0;  // Index for vertical constraint rows
        
        for (size_t i = 0; i < lines.size(); ++i) {
            const std::string& line = lines[i];
            
            // Get all constraint symbols in this line
            std::vector<char> symbols;
            std::vector<char> horizontal_symbols;
            std::vector<char> vertical_symbols;
            
            for (char c : line) {
                if (c == '<' || c == '>' || c == '^' || c == 'v') {
                    symbols.push_back(c);
                    if (c == '<' || c == '>') {
                        horizontal_symbols.push_back(c);
                    }
                    if (c == '^' || c == 'v') {
                        vertical_symbols.push_back(c);
                    }
                }
            }
            
            if (!horizontal_symbols.empty() && vertical_symbols.empty()) {
                // This is a horizontal constraint line
                if (h_idx < 9) {
                    int col_idx = 0;
                    for (char c : line) {
                        if (c == '<' || c == '>') {
                            if (col_idx < 6) {
                                result.horizontal[h_idx][col_idx] = c;
                                col_idx++;
                            }
                        }
                    }
                    h_idx++;
                }
            } else if (!vertical_symbols.empty() && horizontal_symbols.empty()) {
                // This is a vertical constraint line
                if (v_idx < 6) {
                    int col_idx = 0;
                    for (char c : line) {
                        if (c == '^' || c == 'v') {
                            if (col_idx < 9) {
                                result.vertical[v_idx][col_idx] = c;
                                col_idx++;
                            }
                        }
                    }
                    v_idx++;
                }
            }
        }
        
        return result;
    }

    bool isValid(int row, int col, int val) {
        // Check row constraint
        for (int c = 0; c < 9; ++c) {
            if (grid[row][c] == val) {
                return false;
            }
        }
        
        // Check column constraint
        for (int r = 0; r < 9; ++r) {
            if (grid[r][col] == val) {
                return false;
            }
        }
        
        // Check 3x3 subgrid constraint
        int start_row = (row / 3) * 3;
        int start_col = (col / 3) * 3;
        for (int r = start_row; r < start_row + 3; ++r) {
            for (int c = start_col; c < start_col + 3; ++c) {
                if (grid[r][c] == val) {
                    return false;
                }
            }
        }
        
        // Check inequality constraints
        // Horizontal constraints (between columns)
        std::vector<int> constraint_positions = {0, 1, 3, 4, 6, 7};  // Skip positions 2 and 5 (thick lines)
        
        for (size_t i = 0; i < constraint_positions.size(); ++i) {
            int pos = constraint_positions[i];
            if (col == pos && col + 1 < 9) {
                // Check constraint between col and col+1
                char constraint = horizontal[row][i];
                if (constraint != '\0' && grid[row][col + 1] != 0) {
                    if (constraint == '<' && val >= grid[row][col + 1]) {
                        return false;
                    } else if (constraint == '>' && val <= grid[row][col + 1]) {
                        return false;
                    }
                }
            } else if (col == pos + 1 && col - 1 >= 0) {
                // Check constraint between col-1 and col
                char constraint = horizontal[row][i];
                if (constraint != '\0' && grid[row][col - 1] != 0) {
                    if (constraint == '<' && grid[row][col - 1] >= val) {
                        return false;
                    } else if (constraint == '>' && grid[row][col - 1] <= val) {
                        return false;
                    }
                }
            }
        }
        
        // Vertical constraints (between rows)
        std::vector<int> constraint_rows = {0, 1, 3, 4, 6, 7};  // Skip rows 2 and 5 (thick lines)
        
        for (size_t i = 0; i < constraint_rows.size(); ++i) {
            int pos = constraint_rows[i];
            if (row == pos && row + 1 < 9) {
                // Check constraint between row and row+1
                char constraint = vertical[i][col];
                if (constraint != '\0' && grid[row + 1][col] != 0) {
                    if (constraint == '^' && val >= grid[row + 1][col]) {
                        return false;
                    } else if (constraint == 'v' && val <= grid[row + 1][col]) {
                        return false;
                    }
                }
            } else if (row == pos + 1 && row - 1 >= 0) {
                // Check constraint between row-1 and row
                char constraint = vertical[i][col];
                if (constraint != '\0' && grid[row - 1][col] != 0) {
                    if (constraint == '^' && grid[row - 1][col] >= val) {
                        return false;
                    } else if (constraint == 'v' && grid[row - 1][col] <= val) {
                        return false;
                    }
                }
            }
        }
        
        return true;
    }

    std::pair<int, int> findEmpty() {
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (grid[r][c] == 0) {
                    return std::make_pair(r, c);
                }
            }
        }
        return std::make_pair(-1, -1);
    }

    bool solveRecursive(bool verbose = false) {
        step_count++;
        
        if (verbose && step_count <= VERBOSE_LIMIT) {
            std::cout << "Step " << step_count << ": Looking for empty position..." << std::endl;
        }
        
        std::pair<int, int> empty_pos = findEmpty();
        int row = empty_pos.first;
        int col = empty_pos.second;
        
        if (row == -1) {
            return true;  // All positions filled
        }
        
        for (int val = 1; val <= 9; ++val) {
            if (isValid(row, col, val)) {
                grid[row][col] = val;
                
                if (verbose && step_count <= VERBOSE_LIMIT) {
                    std::cout << "  Placed " << val << " at (" << row << ", " << col << ")" << std::endl;
                }
                
                if (solveRecursive(verbose)) {
                    return true;
                }
                
                grid[row][col] = 0;  // Backtrack
            }
        }
        
        return false;
    }

    bool solve(const std::vector<std::vector<char>>& h_constraints, 
               const std::vector<std::vector<char>>& v_constraints, 
               bool verbose = false) {
        horizontal = h_constraints;
        vertical = v_constraints;
        step_count = 0;
        return solveRecursive(verbose);
    }

    void printSolution() {
        for (const auto& row : grid) {
            for (size_t i = 0; i < row.size(); ++i) {
                std::cout << row[i];
                if (i < row.size() - 1) std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::vector<int>> getGrid() const {
        return grid;
    }

    void printConstraints() {
        std::cout << "Horizontal constraints:" << std::endl;
        for (const auto& row : horizontal) {
            for (char c : row) {
                std::cout << (c == '\0' ? ' ' : c) << " ";
            }
            std::cout << std::endl;
        }
        
        std::cout << "Vertical constraints:" << std::endl;
        for (const auto& row : vertical) {
            for (char c : row) {
                std::cout << (c == '\0' ? ' ' : c) << " ";
            }
            std::cout << std::endl;
        }
    }
};

std::vector<std::string> splitLines(const std::string& input) {
    std::vector<std::string> lines;
    std::stringstream ss(input);
    std::string line;
    
    while (std::getline(ss, line)) {
        lines.push_back(line);
    }
    
    return lines;
}

std::vector<std::vector<int>> solveEnhancedSudoku(const std::string& input_text, bool verbose = false) {
    FutoshikiSolver solver;
    std::vector<std::string> lines = splitLines(input_text);
    
    ParsedConstraints constraints = solver.parseInput(lines);
    
    if (verbose) {
        solver.printConstraints();
    }
    
    if (solver.solve(constraints.horizontal, constraints.vertical, verbose)) {
        return solver.getGrid();
    } else {
        return std::vector<std::vector<int>>();
    }
}

void showDemo() {
    std::string test_input = " > <   < <   > <\n"
                           "v ^ v v ^ v ^ ^ v\n"
                           " < <   < >   < <\n"
                           "v ^ v ^ v v ^ ^ v\n"
                           " < <   < <   > >\n"
                           " < >   > >   < >\n"
                           "v v ^ ^ v ^ ^ v v\n"
                           " < >   > <   > >\n"
                           "^ v v v ^ v v ^ v\n"
                           " > <   < >   > >\n"
                           " < >   > >   > <\n"
                           "v v v v ^ ^ ^ ^ ^\n"
                           " > <   < <   < <\n"
                           "^ ^ ^ ^ ^ v v v ^\n"
                           " > >   < >   < <";
    
    std::cout << "Enhanced Sudoku Solver Demo" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Solving puzzle with constraints..." << std::endl;
    
    FutoshikiSolver solver;
    std::vector<std::string> lines = splitLines(test_input);
    ParsedConstraints constraints = solver.parseInput(lines);
    
    if (solver.solve(constraints.horizontal, constraints.vertical, true)) {
        std::cout << "\nFinal Solution:" << std::endl;
        solver.printSolution();
    } else {
        std::cout << "No solution found!" << std::endl;
    }
}

int main() {
    std::string test_input = " > <   < <   > <\n"
                           "v ^ v v ^ v ^ ^ v\n"
                           " < <   < >   < <\n"
                           "v ^ v ^ v v ^ ^ v\n"
                           " < <   < <   > >\n"
                           " < >   > >   < >\n"
                           "v v ^ ^ v ^ ^ v v\n"
                           " < >   > <   > >\n"
                           "^ v v v ^ v v ^ v\n"
                           " > <   < >   > >\n"
                           " < >   > >   > <\n"
                           "v v v v ^ ^ ^ ^ ^\n"
                           " > <   < <   < <\n"
                           "^ ^ ^ ^ ^ v v v ^\n"
                           " > >   < >   < <";

    std::cout << "Enhanced Sudoku Solver" << std::endl;
    std::cout << "==============================" << std::endl;
    
    std::vector<std::vector<int>> solution = solveEnhancedSudoku(test_input);
    
    if (!solution.empty()) {
        std::cout << "Solution:" << std::endl;
        for (const auto& row : solution) {
            for (size_t i = 0; i < row.size(); ++i) {
                std::cout << row[i];
                if (i < row.size() - 1) std::cout << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "\nRunning demo with verbose output..." << std::endl;
        std::cout << std::endl;
    } else {
        std::cout << "No solution found!" << std::endl;
    }

    showDemo();

    return 0;
}
