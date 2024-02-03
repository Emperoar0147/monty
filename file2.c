#include "monty.h"

/**
 * nop - function that acts as comments
 * @stack: head of the stack list
 * @line_number: line number of opcode
 * Return: nothing is returned
*/
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
	/* Do nothing .. a comment*/
}


/**
 * sub - function that substract top 2 node values of stack
 * @stack: head of the stack list
 * @line_number: line number of opcode
 * Return: nothing is returned
*/
void sub(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n -= (*stack)->n;
	*stack = (*stack)->next;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}



/**
 * mul_op - function that multiply top 2 node value in stack
 * @stack: head of the stack list
 * @line_number: line number of opcode
 * Return: nothing is returned
*/
void mul_op(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n *= (*stack)->n;
	*stack = (*stack)->next;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}


/**
 * add - function that add 2 node value at top of stack
 * @stack: head of the stack list
 * @line_number: line number of operation
 * Return: nothing is returned
*/
void add(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n += (*stack)->n;

	/* Pop the top element */
	temp = *stack;
	*stack = (*stack)->next;
	free(temp);

	/* Update the new top element's prev pointer to NULL */
	if (*stack != NULL)
		(*stack)->prev = NULL;
}
