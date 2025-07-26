#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:
void mat_math_operation(matrix *mat, int num, char operator);
int powerOf(int num, int times);


// implementation
matrix *create_matrix(int num_rows, int num_cols)
{   
    matrix *mat = malloc(sizeof(matrix));
    mat->num_cols = num_cols;
    mat->num_rows = num_rows;
    int **data = malloc(num_rows*sizeof(int *));
    for (int i = 0; i < num_rows; i++)
    {
        data[i] = malloc(num_cols*sizeof(int));
        for (int j = 0; j < num_cols; j++)
        {
            data[i][j] = 0;
        } 
    }
    mat->data = data;
    return mat;
}

void add_row(matrix *mat, int *row)
{
    int col_count = mat->num_cols;
    int row_count = mat->num_rows;
    int **data = mat->data;
    int **tmp = realloc(data,(row_count+1)*sizeof(int *));
    if (!tmp) { perror("realloc"); exit(1); }
    data = tmp;

    data[row_count+1] = malloc(col_count*sizeof(int));
    if (!data[row_count]) { perror("malloc"); exit(1); }
    for (int i = 0; i < col_count; i++)
    {
        data[row_count][i] = row[i];
    }
    mat->data = data;
    mat->num_rows = row_count + 1;

    
}

void add_col(matrix *mat, int *col)
{
    int col_count = mat->num_cols;
    int row_count = mat->num_rows;
    int **data = mat->data;
    for (int i = 0; i < row_count; i++)
    {
        int *tmp = realloc(data[i], (col_count+1)*sizeof(int));
        if (!tmp) { perror("realloc"); exit(1); }
        data[i] = tmp;
        data[i][col_count] = col[i];
    }
    mat->data = data;
    mat->num_cols = col_count + 1;
}

void increment(matrix *mat, int num)
{
    mat_math_operation(mat, num, '+');
}

void scalar_multiply(matrix *mat, int num)
{
    mat_math_operation(mat, num, '*');
}

void scalar_divide(matrix *mat, int num)
{
    if (num == 0)
    {
        return;
    }
    mat_math_operation(mat, num, '/');
}

void scalar_power(matrix *mat, int num)
{
    mat_math_operation(mat, num, '^');
}

void delete_matrix(matrix *mat)
{
    int rows = mat->num_rows;
    for (int i = 0; i < rows; i++)
    {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

void mat_math_operation(matrix *mat, int num, char operator)
{
    int col_count = mat->num_cols;
    int row_count = mat->num_rows;
    int **data = mat->data;
    for (int i = 0; i < row_count; i++)
    {
        for (int j = 0; j < col_count; j++)
        {
            switch (operator)
            {
            case '+':
                data[i][j] += num;
                break;
            
            case '-':
                data[i][j] -= num;
                break;
            
            case '*':
                data[i][j] *= num;
                break;
            
            case '/':
                data[i][j] /= num;
                break;
            
            case '^':
                data[i][j] = powerOf(data[i][j], num);
                break;
            
            default:
                break;
            }
        }
    }
    mat->data = data;
}

int powerOf(int num, int times)
{
    int result = 1;
    for (int i = 0; i < times; i++)
    {
        result *= num;
    }
    return result;   
}

/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat) 
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            if (col_idx == mat->num_cols-1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

//Add the rest of the functions needed for the chain below
void insert_node_before(chain *chn, int index, matrix *mat)
{
    node *n = malloc(sizeof(node));
	n->mat = mat;
	if (chn->head == NULL) 
	{
		chn->head = n;
		n->next = n;
		n->prev = n;
	}
	else
	{
		node *temp = chn->head;
		if (index >= 0) 
		{
			for (int i = 0; i < index; i++)
			{
				temp = temp->next;
			}
		} else 
		{
			for (int i = 0; i < -index; i++)
			{
				temp = temp->prev;
			}
		}

		n->prev = temp->prev;
		n->next = temp;
		temp->prev->next = n;
		temp->prev = n;
    }
}

void insert_node_after(chain *chn, int index, matrix *mat)
{
	insert_node_before(chn, index + 1, mat);
}

void delete_node(chain *chn, int index)
{
    if (!chn->head) return;
	node *temp = chn->head;
	if (index > 0)
	{
		for (int i = 0; i < index; i++)
		{
			temp = temp->next;
		}
	}
	else if (index < 0)
	{
		for (int i = 0; i < abs(index); i++)
		{
			temp = temp->prev;
		}
		
	}

    if (temp->next == temp) 
	{
        chn->head = NULL;
    } else {
        if (temp == chn->head)
		{
            chn->head = temp->next;
		}
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    int **data = temp->mat->data;
    int rows = temp->mat->num_rows;
    for (int i = 0; i < rows; i++)
    {
        free(data[i]);
    }
    free(data);
    free(temp->mat);
    free(temp);
}

void delete_list(chain *chn)
{
    if (!chn->head) return;

    node *temp = chn->head;
    node *next_node;
    do {
        next_node = temp->next;
        int **data = temp->mat->data;
        int rows = temp->mat->num_rows;
        for (int i = 0; i < rows; i++)
        {
            free(data[i]);
        }
        free(data);
        free(temp->mat);
        free(temp);
        temp = next_node;
    } while (temp != chn->head);
	chn->head = NULL;
}