// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <string.h> // includes strlen(), memcpy()
#include <ctype.h> // includes toupper(), tolower()

// user-defined header files
#include "node.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
void insert_node_before(list *lst, int index, char *word)
{	
	node *n = malloc(sizeof(node));
	n->word = word;
	if (lst->head == NULL) 
	{
		lst->head = n;
		n->next = n;
		n->prev = n;
	}
	else
	{
		node *temp = lst->head;
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

void insert_node_after(list *lst, int index, char *word)
{
	insert_node_before(lst, index + 1, word);
}

char *list_to_sentence(list *lst)
{
	int str_length = 0;
	node *temp = lst->head;
	while (temp->next != lst->head)
	{
		str_length += strlen(temp->word) + 1;
		temp = temp->next;
	}
	str_length += strlen(temp->word);

	temp = lst->head;
	char *sentence = malloc(str_length + 1);  // +1 for '\0'
	int current_index = 0;
	while (temp->next != lst->head)
	{
		int len = strlen(temp->word);
		for (int i = 0; i < len; i++) 
		{
			sentence[current_index + i] = temp->word[i];
		}
		current_index += len;
		sentence[current_index++] = ' ';
		temp = temp->next;
	}

	int len = strlen(temp->word);
	for (int i = 0; i < len; i++) 
	{
		sentence[current_index + i] = temp->word[i];
	}
	current_index += len;

	sentence[current_index] = '\0';
    return sentence; 
}

void delete_node(list *lst, int index)
{
	if (!lst->head) return;
	node *temp = lst->head;
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
        lst->head = NULL;
    } else {
        if (temp == lst->head)
		{
            lst->head = temp->next;
		}
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    free(temp->word);
    free(temp);
}

void delete_list(list *lst)
{
	// node *temp = lst->head;
	// node *previous;
	// while (temp != lst->head->prev)
	// {
	// 	previous = temp;
	// 	temp = temp->next;
	// 	free(previous->word);
	// 	free(previous);
	// }
	// free(temp->word);
	// free(temp);
	if (!lst->head) return;

    node *temp = lst->head;
    node *next_node;
    do {
        next_node = temp->next;
        free(temp->word);
        free(temp);
        temp = next_node;
    } while (temp != lst->head);
	lst->head = NULL;
}
