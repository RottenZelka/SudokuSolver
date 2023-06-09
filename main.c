#include <stdio.h>
#include <string.h>


int valid(int puzzle[][9], int row, int column, int guess) {
  int corner_x = row / 3 * 3;
  int corner_y = column / 3 * 3;

  for (int x = 0; x < 9; ++x) 
  {
    if (puzzle[row][x] == guess)
      return 0;
    if (puzzle[x][column] == guess) 
      return 0;
    if (puzzle[corner_x + (x % 3)][corner_y + (x / 3)] == guess)
      return 0;
  }
  return 1;
}

int find_empty_cell(int puzzle[][9], int *row, int *column) {
  for (int x = 0; x < 9; x++) {
    for (int y = 0; y < 9; y++) {
      if (!puzzle[x][y]) {
        *row = x;
        *column = y;

        return 1;
      }
    }
  }
  return 0;
}

int solve(int puzzle[][9]) {
  int row;
  int column;

  if(!find_empty_cell(puzzle, &row, &column)) return 1;

  for (int guess = 1; guess < 10; guess++) {
    if (valid(puzzle, row, column, guess)) {
      puzzle[row][column] = guess;

      if(solve(puzzle)) return 1;
      puzzle[row][column] = 0;
    }
  }
  return 0;
}

int is_valid(int sudoku[9][9], int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (sudoku[row][i] == num || sudoku[i][col] == num) {
            return 0;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[startRow + i][startCol + j] == num) {
                return 0;
            }
        }
    }

    return 1;
}

int solve_sudoku(int sudoku[9][9]) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (sudoku[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(sudoku, row, col, num)) {
                        sudoku[row][col] = num;
                        if (solveSudoku(sudoku)) {
                            return 1;
                        }
                        sudoku[row][col] = 0; 
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}


void save_sudoku(const char* filename, int sudoku[SIZE][SIZE]) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        exit(1);
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] != 0) {
                fprintf(file, "%d ", sudoku[i][j]);
            } else {
                fprintf(file, "u");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void grid_maker(char* input_file_name, char* output_file_name)
{
  FILE* file = fopen(input_file_name, "r");
  if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
  }
  char* ext = strrchr(input_file_name, '.');
  int grid[9][9]; 
  if(strcmp(ext, ".ss") == 0)
  {
    //only with X in the candidate spaces
    for(int i = 0; i < 9; i++)
    {
      for(int j = 0; j < 9; j++)
      {
        char c;
        if(c == '\n') c = fgetc(file);
        if((c = fgetc(file)) != 'X')
          grid[i][j] = c - '0';
        else
          grid[i][j] = 0;
      }
    }
    solve(grid);
    save_sudoku(output_file_name, grid);
  }
  else if(strcmp(ext, ".sdx") == 0)
  {
    char line[30];
    for (int i = 0; i < 9; i++) {
        if (fgets(line, sizeof(line), file) != NULL) {
            int j = 0;
            for (char* token = strtok(line, " "); token != NULL; token = strtok(NULL, " ")) {
                if (token[0] == 'u') {
                    grid[i][j] = atoi(token + 1);
                } else {
                    grid[i][j] = atoi(token);
                }
                j++;
            }
        }
    }
    solve_suoku(grid);
    save_sudoku(output_file_name, grid);
  }
  else if(strcmp(ext, ".sdm") == 0)
  {
    while(fgetc(file) != EOF)
    {
      for(int i = 0; i < 9; i++)
      {
        for(int j = 0; j < 9; j++)
        {
          char c = fgetc(file);
          if(c == '\n') c = fgetc(file);
          grid[i][j] = c - '0';
        }
      }
      solve(grid);
      save_sudoku(output_file_name, grid);
    }
  }
  else{
    return;
  }
}


int main(void) {
  char *input, *output;
  printf("Input File Name: ");
  scanf("%s", input);
  printf("Output File Name: ");
  scanf("%s", output);

  grid_maker(input, output);
  return 0;
}
