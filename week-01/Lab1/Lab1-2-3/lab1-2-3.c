// general purpose standard C lib
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h>


// user-defined header files
#include "chain.h"

// macros
#define MAX_LINE_LEN 1024
#define TRUE 1

#define CREATE_MATRIX 1
#define ADD_ROW 2
#define ADD_COLUMN 3
#define INCREMENT 4
#define SCALAR_MULTIPLY 5
#define SCALAR_DiVIDE 6
#define SCALAR_POWER 7
#define DELETE_MATRIX 8

// function prototypes
void print_chain(chain * chn); 
void run(chain * chn);
matrix *get_input_initial_mat(int rows);
matrix *copy_matrix(matrix *mat);
int *parse_line_to_ints(const char *line, int *count);
int *mat_elements(int expected_count);


int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}

// parse the input
// void run(chain *chn) 
// {
// 	int rows;
//     scanf("%d", &rows);
//     getchar();
//     matrix *mat = get_input_initial_mat(rows);
//     insert_node_before(chn, 0, mat);

//     while (TRUE)
//     {
//         int opcode;
//         scanf("%d", &opcode);
//         while (getchar() != '\n');
//         if (opcode == 0)
//         {
//             return;
//         }
//         matrix *copy = NULL;
//         switch (opcode)
//         {
//         case CREATE_MATRIX:
//             int new_rows, new_cols;
//             scanf("%d %d", &new_rows, &new_cols);
//             matrix *new_mat = create_matrix(new_rows, new_cols);
//             insert_node_before(chn, 0, new_mat);
//             mat = new_mat;
//             break;
        
//         case ADD_ROW:
//             int *row = mat_elements(mat->num_cols);
//             copy = copy_matrix(mat);
//             add_row(copy, row);
//             insert_node_before(chn, 0, copy);
//             mat = copy;
//             free(row);
//             break;
        
//         case ADD_COLUMN:
//             int *col = mat_elements(mat->num_rows);
//             copy = copy_matrix(mat);
//             add_col(copy, col);
//             insert_node_before(chn, 0, copy);
//             mat = copy;
//             free(col);
//             break;
        
//         case INCREMENT:
//             int incre_num;
//             scanf("%d", &incre_num);
//             while (getchar() != '\n');
//             copy = copy_matrix(mat);
//             increment(copy, incre_num);
//             insert_node_before(chn, 0, copy);
//             mat = copy;
//             break;
        
//         case SCALAR_MULTIPLY:
//             int mul_num;
//             scanf("%d", &mul_num);
//             while (getchar() != '\n');
//             copy = copy_matrix(mat);
//             scalar_multiply(copy, mul_num);
//             insert_node_before(chn, 0, copy);
//             mat = copy;
//             break;
        
//         case SCALAR_DiVIDE:
//             int div_num;
//             scanf("%d", &div_num);
//             while (getchar() != '\n');
//             copy = copy_matrix(mat);
//             scalar_divide(copy, div_num);
//             insert_node_before(chn, 0, copy);
//             mat = copy;
//             break;
        
//         case SCALAR_POWER:
//             int pow_num;
//             scanf("%d", &pow_num);
//             while (getchar() != '\n');
//             copy = copy_matrix(mat);
//             scalar_power(copy, pow_num);
//             insert_node_before(chn, 0, copy);
//             mat = copy;
//             break;
            
//         case DELETE_MATRIX:
//             delete_matrix(mat);
//             mat = NULL;
//             break;
        
//         default:
//             return;
//         }

//     }

// }

void run(chain *chn) 
{
    int rows;
    scanf("%d", &rows);
    getchar(); // consume newline after number

    matrix *mat = get_input_initial_mat(rows);
    insert_node_before(chn, 0, mat);

    char line[MAX_LINE_LEN];

    while (TRUE)
    {
        if (!fgets(line, sizeof(line), stdin)) {
            return; // EOF or error
        }

        int count;
        int *nums = parse_line_to_ints(line, &count);

        if (count == 0) {
            free(nums);
            continue; // empty line, skip
        }

        int opcode = nums[0];
        if (opcode == 0) {
            free(nums);
            return; // end input
        }

        matrix *copy = NULL;

        switch (opcode)
        {
            case CREATE_MATRIX:
                if (count < 3) 
                {
                    fprintf(stderr, "Expected: 1 rows cols\n");
                    free(nums);
                    exit(1);
                }
                {
                    int rows = nums[1];
                    int cols = nums[2];
                    matrix *new_mat = create_matrix(rows, cols);
                    insert_node_before(chn, 0, new_mat);
                    mat = new_mat;
                }
                break;

            case ADD_ROW:
                if (count - 1 != mat->num_cols) 
                {
                    fprintf(stderr, "Expected %d elements for new row, got %d\n", mat->num_cols, count - 1);
                    free(nums);
                    exit(1);
                }
                copy = copy_matrix(mat);
                add_row(copy, &nums[1]);
                insert_node_before(chn, 0, copy);
                mat = copy;
                break;

            case ADD_COLUMN:
                if (count - 1 != mat->num_rows) 
                {
                    fprintf(stderr, "Expected %d elements for new column, got %d\n", mat->num_rows, count - 1);
                    free(nums);
                    exit(1);
                }
                copy = copy_matrix(mat);
                add_col(copy, &nums[1]);
                insert_node_before(chn, 0, copy);
                mat = copy;
                break;

            case INCREMENT:
                if (count < 2) 
                {
                    fprintf(stderr, "Expected: 4 num\n");
                    free(nums);
                    exit(1);
                }
                copy = copy_matrix(mat);
                increment(copy, nums[1]);
                insert_node_before(chn, 0, copy);
                mat = copy;
                break;

            case SCALAR_MULTIPLY:
                if (count < 2) 
                {
                    fprintf(stderr, "Expected: 5 num\n");
                    free(nums);
                    exit(1);
                }
                copy = copy_matrix(mat);
                scalar_multiply(copy, nums[1]);
                insert_node_before(chn, 0, copy);
                mat = copy;
                break;

            case SCALAR_DiVIDE:
                if (count < 2) 
                {
                    fprintf(stderr, "Expected: 6 num\n");
                    free(nums);
                    exit(1);
                }
                copy = copy_matrix(mat);
                scalar_divide(copy, nums[1]);
                insert_node_before(chn, 0, copy);
                mat = copy;
                break;

            case SCALAR_POWER:
                if (count < 2) 
                {
                    fprintf(stderr, "Expected: 7 num\n");
                    free(nums);
                    exit(1);
                }
                copy = copy_matrix(mat);
                scalar_power(copy, nums[1]);
                insert_node_before(chn, 0, copy);
                mat = copy;
                break;

            case DELETE_MATRIX:
                delete_matrix(mat);
                break;

            default:
                fprintf(stderr, "Unknown opcode %d\n", opcode);
                free(nums);
                exit(1);
        }

        free(nums);
    }
}



//Print the chain
void print_chain(chain * chn)
{
    if (!chn->head) return;

    node *temp = chn->head;
    do
    {
        print_matrix(temp->mat);
        printf("\n");
        temp = temp->next;
    } while (temp != chn->head);
    
    delete_list(chn);
}


matrix *get_input_initial_mat(int rows) 
{
    matrix *mat = malloc(sizeof(matrix));
    if (!mat) { perror("malloc"); exit(1); }

    int **data = malloc(rows * sizeof(int *));
    if (!data) { perror("malloc"); exit(1); }

    int num_cols = -1;

    char line[MAX_LINE_LEN];
    for (int i = 0; i < rows; i++) 
    {
        if (!fgets(line, sizeof(line), stdin)) 
        {
            fprintf(stderr, "Failed to read line\n");
            exit(1);
        }

        int count;
        int *row = parse_line_to_ints(line, &count);

        if (num_cols == -1) 
        {
            num_cols = count; // set columns based on first row
        } 
        else if (count != num_cols) 
        {
            fprintf(stderr, "All rows must have same number of columns\n");
            free(row);
            exit(1);
        }

        data[i] = row;
    }

    mat->data = data;
    mat->num_rows = rows;
    mat->num_cols = num_cols;

    return mat;
}


int *parse_line_to_ints(const char *line, int *count) 
{
    int *arr = NULL;
    int n = 0;

    char *copy = strdup(line);  // duplicate line so we can use strtok safely
    if (!copy) { perror("strdup"); exit(1); }

    char *token = strtok(copy, " \t\n");
    while (token) 
    {
        int num = atoi(token);  // convert to int

        int *new_arr = realloc(arr, (n+1) * sizeof(int));
        if (!new_arr) { perror("realloc"); free(copy); free(arr); exit(1); }
        arr = new_arr;

        arr[n++] = num;

        token = strtok(NULL, " \t\n");
    }

    free(copy);

    *count = n;
    return arr;
}

int *mat_elements(int expected_count)
{
    char line[MAX_LINE_LEN];
    if (fgets(line, sizeof(line), stdin)) 
    {
        int count;
        int *nums = parse_line_to_ints(line, &count);
        if (count != expected_count) {
            fprintf(stderr, "Expected %d elements, got %d\n", expected_count, count);
            free(nums);
            exit(1);
        }
        return nums; // caller must free
    }
    fprintf(stderr, "Failed to read line\n");
    exit(1);
}


matrix *copy_matrix(matrix *mat)
{
    matrix *new_mat = create_matrix(mat->num_rows, mat->num_cols);
    for (int i = 0; i < mat->num_rows; i++)
        for (int j = 0; j < mat->num_cols; j++)
            new_mat->data[i][j] = mat->data[i][j];
    return new_mat;
}

