#include "shell.h"

/**
 * create_node - creates a new node
 * @dir: directory
 * Return: pointer to new node
 */

dir_node *create_node(char *dir)
{
	dir_node *new_node;

	if (dir == NULL)
		return (NULL);
	new_node = (dir_node *)malloc(sizeof(dir_node));

	if (new_node == NULL)
	{
		perror("Could not allocate memory");
		exit(EXIT_FAILURE);
	}
	new_node->dir = dir;
	new_node->next = NULL;
	return (new_node);
}

/**
 * insertNode - inserts a new node
 * @head: head of the list
 * @dir: directory
 *
 */

void insertNode(dir_node **head, char *dir)
{
	dir_node *new_node = create_node(dir);

	if (new_node == NULL)
		return;

	if (*head == NULL)
		*head = new_node;
	else
	{
		dir_node *current = *head;

		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

/**
 * free_list - frees a node
 * @head: head of the list
 */

void free_list(dir_node *head)
{
	dir_node *current = head;

	while (current != NULL)
	{
		dir_node *temp = current;

		current = current->next;
		free(temp);
	}
}
