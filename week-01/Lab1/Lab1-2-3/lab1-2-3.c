// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "chain.h"

// macros
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
int *get_input_elements();

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
void run(chain *chn) 
{
	int rows;
    scanf("%d", &rows);
    matrix *mat = get_input_initial_mat(rows);
    // chain *chn = malloc(sizeof(chain));
    insert_node_before(chn, 0, mat);

    while (TRUE)
    {
        int opcode;
        scanf("%d", &opcode);
        if (opcode == 0)
        {
            return;
        }

        switch (opcode)
        {
        case CREATE_MATRIX:
            int rows, cols;
            scanf("%d %d", &rows, &cols);
            matrix *new_mat = create_matrix(rows, cols);
            insert_node_before(chn, 0, new_mat);
            break;
        
        case ADD_ROW:
            int *row = get_input_elements();
            add_row(mat,row);
            insert_node_before(chn, 0, mat);
            break;
        
        case ADD_COLUMN:
            int *col = get_input_elements();
            add_col(mat,col);
            insert_node_before(chn, 0, mat);
            break;
        
        case INCREMENT:
            int incre_num;
            scanf("%d", &incre_num);
            increment(mat, incre_num);
            insert_node_before(chn, 0, mat);
            break;
        
        case SCALAR_MULTIPLY:
            int mul_num;
            scanf("%d", &mul_num);
            scalar_multiply(mat, mul_num);
            insert_node_before(chn, 0, mat);
            break;
        
        case SCALAR_DiVIDE:
            int div_num;
            scanf("%d", &div_num);
            scalar_divide(mat, div_num);
            insert_node_before(chn, 0, mat);
            break;
        
        case SCALAR_POWER:
            int pow_num;
            scanf("%d", &pow_num);
            scalar_power(mat, pow_num);
            insert_node_before(chn, 0, mat);
            break;
            
        case DELETE_MATRIX:
            delete_matrix(mat);
            insert_node_before(chn, 0, mat);
            break;
        
        default:
            return;
        }

    }

}

//Print the chain
void print_chain(chain * chn)
{
    node *temp = chn->head;
    do
    {
        print_matrix(temp->mat);
        temp = temp->next;
    } while (temp != chn->head);
    
    delete_list(chn);
}

matrix *get_input_initial_mat(int rows)
{
    matrix *mat = malloc(sizeof(matrix));
    int cols;
    int **data = malloc(rows*sizeof(int *));
    for (int i = 0; i < rows; i++)
    {
        data[i] = NULL;
        int j = 0;
        while (TRUE)
        {
            int tmp;
            if (scanf("%d", &tmp) != 1) 
            {
                break;
            }
            int *new_row = realloc(data[i], (j+1) * sizeof(int));
            if (!new_row) { perror("realloc"); exit(1); }
            data[i] = new_row;

            data[i][j++] = tmp;
        }
        cols = j;
    }
    mat->data = data;
    mat->num_rows = rows;
    mat->num_cols = cols;

    return mat;
}

int *get_input_elements()
{
    int *elem_arr = NULL;
    int j = 0;
    while (TRUE)
    {
        int tmp;
        if (scanf("%d", &tmp) != 1) 
        {
            break;
        }
        int *new = realloc(elem_arr, (j+1) * sizeof(int));
        if (!new) { perror("realloc"); exit(1); }
        elem_arr = new;

        elem_arr[j++] = tmp;
    }
    return elem_arr;
}

