#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void part1(bool **grid, unsigned int size);
void part2(bool **grid, unsigned int size);

void print_grid(bool **grid, unsigned int size)
{
    for (size_t y = 0; y < size; y++)
    {
        for (size_t x = 0; x < size; x++)
        {
            printf("%c", grid[y][x] ? '@' : '.');
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
    const char *file_path = argv[1];
    FILE *file = fopen(file_path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open file '%s'\n", file_path);
        return 1;
    }

    unsigned int size = 0;
    {
        int c; // note: int, not char, required to handle EOF
        while ((c = fgetc(file)) != EOF)
        {
            if (c == '\n')
                break;
            size++;
        }
    }
    fseek(file, 0, SEEK_SET);

    printf("Grid size: %u\n", size);
    const unsigned int grid_dims = size + 2;
    bool **grid = malloc(grid_dims * sizeof(bool *));
    for (size_t y = 0; y < grid_dims; y++)
    {
        grid[y] = malloc(grid_dims * sizeof(bool));
        for (size_t x = 0; x < grid_dims; x++)
            grid[y][x] = false;
    }
    {
        size_t row = 0;
        size_t col = 0;
        int c;
        while ((c = fgetc(file)) != EOF)
        {
            if (c == '\n')
            {
                row++;
                col = 0;
                continue;
            }
            grid[row + 1][col + 1] = (c == '@') ? true : false;
            col++;
        }
    }
    fclose(file);

    // print_grid(grid, grid_dims);
    part1(grid, size);
    part2(grid, size);

    for (int i = 0; i < grid_dims; i++)
    {
        free(grid[i]);
    }
    free(grid);
    return 0;
}

void part1(bool **grid, unsigned int size)
{
    printf("Part 1 executed with grid size %u\n", size);
    int count = 0;
    for (size_t y = 1; y <= size; y++)
    {
        for (size_t x = 1; x <= size; x++)
        {
            if (!grid[y][x])
            {
                continue;
            }
            unsigned char neighbors = 0;
            for (short o_x = 0; o_x < 3; o_x++)
                for (short o_y = 0; o_y < 3; o_y++)
                {
                    if (o_x == 1 && o_y == 1)
                        continue;
                    if (grid[y + o_y - 1][x + o_x - 1])
                        neighbors++;
                }

            if (neighbors < 4)
                count++;
        }
    }
    printf("Part 1 result: %d\n", count);
}

void part2(bool **grid, unsigned int size)
{
    printf("Part 2 executed with grid size %u\n", size);
    int count = 0;
    bool movedThisRound = true;
    // Implement a processing queue if this ends up being too slow -@9:40
    // Damn i guess it's just that quick, I was kinda looking forward to having to optimize -@9:50

    while (movedThisRound)
    {
        movedThisRound = false;
        for (size_t y = 1; y <= size; y++)
        {
            for (size_t x = 1; x <= size; x++)
            {
                if (!grid[y][x])
                {
                    continue;
                }
                unsigned char neighbors = 0;
                for (short o_x = 0; o_x < 3; o_x++)
                    for (short o_y = 0; o_y < 3; o_y++)
                    {
                        if (o_x == 1 && o_y == 1)
                            continue;
                        if (grid[y + o_y - 1][x + o_x - 1])
                            neighbors++;
                    }

                if (neighbors >= 4)
                    continue;
                count++;
                movedThisRound = true;
                grid[y][x] = false;
            }
        }
    }
    printf("Part 2 result: %d\n", count);
}