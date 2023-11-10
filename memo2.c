#include "shell.h"
/**
 * free_ad - free with NULL
 * @pointer: pointer to address to dessired free
 * Return: int value 0 or 1
*/
int free_ad(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);

		*pointer = NULL;
		return (1);
	}

	return (0);
}
