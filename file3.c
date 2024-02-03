#include "monty.h"


stack_t *stack = NULL;

/**
 * execute_instruction - function that executes opcodes
 * @opcode: monty operation to be executed
 * @value: value to be pushed into the stack
 * @line_number: line number of operation
 * Return: nothing is returned
*/
void execute_instruction(char *opcode, char *value, unsigned int line_number)
{
	int numeric_value;

	if (strcmp(opcode, "push") == 0)
	{
		if (value == NULL)
		{
			fprintf(stderr, "L%d: usage: push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
		numeric_value = atoi(value);

		push(&stack, numeric_value);
	}
	else if (strcmp(opcode, "pop") == 0)
		pop(&stack, line_number);
	else if (strcmp(opcode, "pall") == 0)
		pall(&stack);
	else if (strcmp(opcode, "pint") == 0)
		pint(&stack, line_number);
	else if (strcmp(opcode, "swap") == 0)
		swap(&stack, line_number);
	else if (strcmp(opcode, "add") == 0)
		add(&stack, line_number);
	else if (strcmp(opcode, "sub") == 0)
		sub(&stack, line_number);
	else if (strcmp(opcode, "div") == 0)
		div_op(&stack, line_number);
	else if (strncmp(opcode, "#", 1) == 0)
		nop(&stack, line_number);
	else if (strcmp(opcode, "mul") == 0)
		mul_op(&stack, line_number);
	else if (strcmp(opcode, "mod") == 0)
		mod_op(&stack, line_number);
	else if (strcmp(opcode, "pchar") == 0)
		pchar(&stack, line_number);
	else if (strcmp(opcode, "pstr") == 0)
		pstr(&stack, line_number);
	else if (strcmp(opcode, "rotl") == 0)
		rotl(&stack);
	else if (strcmp(opcode, "rotr") == 0)
		rotr(&stack);
	/* Add more instructions as needed */
	else
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
		exit(EXIT_FAILURE);
	}
}


/**
 * main - start point of program execution
 * @argc: argument count passed to program
 * @argv: arguments list of arguments passed to program
 * Return: returns integer that represents success
*/

int main(int argc, char *argv[])
{
	FILE *file = NULL;
	char *line = NULL;
	size_t len = 0;
	unsigned int line_number = 0;
	char *opcode = NULL, *value = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while (getline(&line, &len, file) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n$");
		value = strtok(NULL, " \t\n");

		if (opcode != NULL)
		{
			execute_instruction(opcode, value, line_number);
		}
	}

	free_dlistint(stack);
	free(line);
	fclose(file);

	return (EXIT_SUCCESS);
}

/**
 * pop - function that frees the top node in the stack
 * @stack: head of the stack list
 * @line_number: line number of operation
 * Return: nothing is returned
*/
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}

	temp = *stack;
	*stack = temp->next;

	if (*stack != NULL)
	{
		(*stack)->prev = NULL;
	}

	free(temp);
}


/**
 * mod_op - function that carries out the modulo of the top 2 node
 * @stack: head of the stack list
 * @line_number: line number of operation
 * Return: nothing is returned
*/
void mod_op(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}

	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%u: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}

	(*stack)->next->n %= (*stack)->n;
	*stack = (*stack)->next;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}


/**
 * pall - function that prints data of node in stack
 * @stack: head of the stack list
 * Return: nothing is returned
*/
void pall(stack_t **stack)
{
	stack_t *current = *stack;

	while (current != NULL)
	{
		printf("%d\n", current->n);
		current = current->next;
	}
}

