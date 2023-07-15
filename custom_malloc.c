#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

// Define a function pointer type for the original malloc function
typedef void* (*malloc_func)(size_t);

// Define a global function pointer to store the original malloc function
malloc_func original_malloc = NULL;

// Counter to keep track of the number of malloc calls
static int malloc_counter = 0;

// Variable to specify the index of the malloc call to simulate a failure
int fail_index = 150;

// Custom malloc function implementation
void* custom_malloc(size_t size)
{
	malloc_counter++;

	if (malloc_counter == fail_index)
		return NULL;

	// Call the original malloc function for all other malloc calls
	if (original_malloc == NULL)
		original_malloc = dlsym(RTLD_NEXT, "malloc");

	return original_malloc(size);
}

// Function to override the original malloc symbol
void* malloc(size_t size)
{
	return custom_malloc(size);
}
