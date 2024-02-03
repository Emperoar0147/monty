#include "monty.h"


/**
 * free_dlistint - frees a doubly linked list
 * @head: pointer to the head of the list
 * Return: nothing is returned
 */
void free_dlistint(stack_t *head)
{
	stack_t *current = head;
	stack_t *next_node;

	while (current != NULL)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
}


/**
 * pint - prints the value at the top of the stack
 * @stack: pointer to the head of the stack
 * @line_number: line number of upcode
 * Return: nothing is returned
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);

		exit(EXIT_FAILURE);
	}

	printf("%d\n", (*stack)->n);
}


/**
 * div_op - function that divides top 2 node value in stack
 * @stack: head of the stack list
 * @line_number: line number of opcode
 * Return: nothing is returned
*/
void div_op(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't div, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n /= (*stack)->n;
	*stack = (*stack)->next;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * swap - function that swap top 2 node in stack
 * @stack: head of the stack list
 * @line_number: line number of opcode
 * Return: nothing is returned
*/
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *first = NULL, *second = NULL;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	first = *stack;
	second = first->next;

	/* Update the links for the swapped nodes */
	first->next = second->next;
	second->prev = first->prev;

	/* Update the links for the nodes around the swapped nodes */
	if (first->prev != NULL)
		first->prev->next = second;
	if (second->next != NULL)
		second->next->prev = first;

	/* Update the links for the swapped nodes themselves */
	first->prev = second;
	second->next = first;

	/* Update the stack pointer to the new top of the stack */
	*stack = second;
}




/**
 * push - function that inserts a node into the stack
 * @stack: head of the stack list
 * @value: data in the node
 * Return: nothing is returned
*/
void push(stack_t **stack, int value)
{
	stack_t *new_node = malloc(sizeof(stack_t));

	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}

	new_node->n = value;
	new_node->prev = NULL;
	new_node->next = *stack;

	if (*stack != NULL)
	{
		(*stack)->prev = new_node;
	}

	*stack = new_node;
}
