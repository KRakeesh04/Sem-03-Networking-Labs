// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()
#include <string.h>

// user-defined header files
#include "node.h"

// macros
#define INSERT_BEFORE 1
#define INSERT_AFTER 2
#define DELETE_NODE 3
#define DELETE_LIST 4

#define START_WORD_SIZE 20
#define START_WORD_COUNT 100
#define WORDS_SEPARATOR (',')

#define TRUE 1
#define FALSE 0

// function prototypes
void print_list(list * lst); 
void run(list * lst);
int get_word_array_input(char ***word_array_ptr, int word_array_capacity);
void initialize_linked_list(list * lst, char **arr, int length);
void get_word_input(char **word_ptr);
void remove_white_space(char **word_ptr);

int main()
{
    list * lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
	run(lst);
    print_list(lst);
    free(lst);
	return 0;
}

// parse the input
void run(list *lst) 
{
    char **word_array = malloc(START_WORD_COUNT * sizeof(char *));
    int length = get_word_array_input(&word_array, START_WORD_COUNT);
    initialize_linked_list(lst, word_array, length);

    // node *temp = lst->head;
    // while (temp->next != lst->head)
    // {
    //     printf("->%s", temp->word);
    //     temp = temp->next;
    // }
    // printf("->%s", temp->word);


    while (TRUE)
    {
        int opcode;
        int index;
        char *word;

        scanf("%d",&opcode);
        if (opcode == 0)
        {
            return;
        }
        if (opcode != 4)
        {
            scanf("%d", &index);
            if (opcode != 3)
            {
                get_word_input(&word);
                remove_white_space(&word);
            }
        }
        
        switch (opcode)
        {
        case INSERT_BEFORE:
            insert_node_before(lst,index,word);
            break;
        
        case INSERT_AFTER:
            insert_node_after(lst ,index, word);
            break;
        
        case DELETE_NODE:
            delete_node(lst, index);
            break;
        
        case DELETE_LIST:
            delete_list(lst);
            break;
        
        default:
            return;
        }

    }
}

//Print the list contents
void print_list(list * lst)
{
    char *sentence;
    sentence = list_to_sentence(lst);
    printf("%s\n",sentence);
    free(sentence);
}

void initialize_linked_list(list * lst, char **arr, int count)  
{
    node *previous = NULL;
    for (int i = 0; i < count; i++)
    {
        node *temp = malloc(sizeof(node));
        temp->word = arr[i];
        temp->next = NULL;
        temp->prev = previous;

        if (previous)
            previous->next = temp;
        else
            lst->head = temp;

        previous = temp;
    }

    if (lst->head && previous) {
        previous->next = lst->head;
        lst->head->prev = previous;
    }
}

int get_word_array_input(char ***word_array_ptr, int word_array_capacity)
{
    char **word_array = *word_array_ptr;
    int current_word_count = 0;
    while (TRUE)
    {
        int word_capacity = START_WORD_SIZE;  // initial size of word
        int current_word_size = 0;
        char *word = malloc(word_capacity);
        if (!word) { perror("malloc"); exit(1); }

        char letter;
        while (TRUE)
        {
            if (scanf("%c", &letter) != 1)
            {
                break;
            }
            if (letter == WORDS_SEPARATOR || letter == '\n')
            {
                break;
            }
            if (current_word_size + 1 >= word_capacity)
            {
                word_capacity *= 2;
                char *tmp = realloc(word, word_capacity);
                if (!tmp) { perror("realloc"); exit(1); }
                word = tmp;
            }
            word[current_word_size++] = letter;
        }

        word[current_word_size] = '\0';

        // store the word in word_array
        if (current_word_count >= word_array_capacity) {
            word_array_capacity = word_array_capacity * 3 / 2;
            char **tmp2 = realloc(word_array, word_array_capacity * sizeof(char *));
            if (!tmp2) { perror("realloc"); exit(1); }
            word_array = tmp2;
            *word_array_ptr = word_array;
        }

        word_array[current_word_count++] = word;

        if (letter == '\n')
        {
            break;
        }
    }

    return current_word_count;
}

void get_word_input(char **word_ptr)
{
    int word_capacity = START_WORD_SIZE;  // initial size of word
    int current_word_size = 0;
    char *word = malloc(word_capacity);
    if (!word) { perror("malloc"); exit(1); }

    char letter;
    while (TRUE)
    {
        if (scanf("%c", &letter) != 1)
        {
            break;
        }
        if (letter == '\n')
        {
            break;
        }
        if (current_word_size + 1 >= word_capacity)
        {
            word_capacity *= 2;
            char *tmp = realloc(word, word_capacity);
            if (!tmp) { perror("realloc"); exit(1); }
            word = tmp;
        }
        word[current_word_size++] = letter;
    }

    word[current_word_size] = '\0';

    *word_ptr = word; 
}

// remove the white space before and after the word
void remove_white_space(char **word_ptr)
{
    char *word = *word_ptr;
    int start = 0, end = strlen(word) - 1;

    // find the first non-space character
    while (start <= end && (word[start] == ' ' || word[start] == '\t')) 
    {
        start++;
    }

    // find the last non-space character
    while (end >= start && (word[end] == ' ' || word[end] == '\t')) 
    {
        end--;
    }

    if (start > end) 
    {
        // word is all spaces -> make empty string
        free(word);
        *word_ptr = malloc(1);
        if (!*word_ptr) { perror("malloc"); exit(1); }
        (*word_ptr)[0] = '\0';
    } 
    else 
    {
        // word[start..end] is the trimmed word
        int new_length = end - start + 1; // excluding null terminator
        char *trimmed_word = malloc(new_length + 1);
        if (!trimmed_word) { perror("malloc"); exit(1); }

        for (int i = 0; i < new_length; i++) 
        {
            trimmed_word[i] = word[start + i];
        }
        trimmed_word[new_length] = '\0'; // null-terminate

        free(word);
        *word_ptr = trimmed_word;
    }
}
