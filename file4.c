#include "monty.h"

/**
 * pchar - prints the character at the top of the stack
 * @stack: pointer to the head of the stack
 * @line_number: line number of the opcode
 * Return: nothing is returned
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n < 0 || (*stack)->n > 127)
	{
		fprintf(stderr, "L%u: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%c\n", (*stack)->n);
}


/**
 * pstr - prints the string starting at the top of the stack
 * @stack: pointer to the head of the stack
 * @line_number: line number of the opcode
 * Return: nothing is returned
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *cur = *stack;

	(void)line_number;

	while (cur != NULL && cur->n != 0 && (cur->n >= 0 && cur->n <= 127))
	{
		putchar(cur->n);
		cur = cur->next;
	}

	putchar('\n');
}


/**
 * rotl - rotates the stack to the top
 * @stack: pointer to the head of the stack
 * Return: nothing is returned
 */
void rotl(stack_t **stack)
{
	stack_t *temp, *last = *stack;

	if (*stack != NULL && (*stack)->next != NULL)
	{
		temp = *stack;

		while (last->next != NULL)
			last = last->next;

		last->next = temp;
		temp->prev = last;
		*stack = temp->next;
		(*stack)->prev = NULL;
		temp->next = NULL;
	}
}




/**
 * rotr - rotates the stack to the bottom
 * @stack: pointer to the head of the stack
 * Return: nothing is returned
 */
void rotr(stack_t **stack)
{
	stack_t *temp, *last = *stack;

	if (*stack != NULL && (*stack)->next != NULL)
	{
		while (last->next != NULL)
			last = last->next;

		temp = last->prev;
		temp->next = NULL;
		last->prev = NULL;
		last->next = *stack;
		(*stack)->prev = last;
		*stack = last;
	}
}
