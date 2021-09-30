// =================== Support Code =================
// Stack
//
//
//
// - Implement each of the functions to create a working stack.
// - Do not change any of the function declarations
//   - (i.e. stack_t* create_stack() should not have additional arguments)
// - Do not change any of the structs
// - You should not have any 'printf' statements in your stack functions. 
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================
#ifndef MYSTACK_H
#define MYSTACK_H

// Stores the maximum 'depth' of our stack.
// Our implementation enforces a maximum depth of our stack.
// (i.e. capacity cannot exceed MAX_DEPTH for any stack)
#define MAX_DEPTH 32

// Create a node data structure to store data within
// our stack. In our case, we will stores 'integers'
typedef struct node{
	int data;
	struct node* next;
}node_t;

// Create a stack data structure
// Our stack holds a single pointer to a node, which
// is a linked list of nodes.
typedef struct stack{
	unsigned int count;	// count keeps track of how many items
				// are in the stack.
	unsigned int capacity;	// Stores the maximum size of our stack
	node_t* head;		// head points to a node on the top of our stack.
}stack_t;

// Creates a stack
// Returns a pointer to a newly created stack.
// The stack should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The stacks fields should also be initialized to default values.
// If capacity > MAX_DEPTH than capacity = MAX_DEPTH
stack_t* create_stack(unsigned int capacity)
{
	// Modify the body of this function as needed.
	stack_t* myStack = NULL;	
	myStack = (stack_t *) malloc (sizeof(stack_t));	

	if(myStack == NULL) {
		exit(1);
	}

	if(capacity > MAX_DEPTH) {	
		capacity = MAX_DEPTH;
	}

	myStack->count = 0;
	myStack->capacity = capacity;
	myStack->head = NULL;

	return myStack;
}

// Stack Empty
// Check if the stack is empty
// Returns 1 if true (The stack is completely empty)
// Returns 0 if false (the stack has at least one element enqueued)
int stack_empty(stack_t* s)
{
	if(s == NULL) {
		exit(1);
	}

	if(s->count == 0) {
		return 1;
	}
		
	return 0;
}

// Stack Full
// Check if the stack is full
// Returns 1 if true (The Stack is completely full, i.e. equal to capacity)
// Returns 0 if false (the Stack has more space available to enqueue items)
int stack_full(stack_t* s)
{
	if(s == NULL) {
		exit(1);
	}

	if(s->count == s->capacity) {
		return 1;
	}

	return 0;
}

// Enqueue a new item
// i.e. push a new item into our data structure
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. if the Stack is full that is an error, but does not crash the program).
int stack_enqueue(stack_t* s, int item)
{
	if(s == NULL) {
		exit(1);
	}

	if(s->count == s->capacity) {
		return -1;
	}

	node_t *node = (node_t *) malloc (sizeof(node_t));
	if(node == NULL) {
		exit(1);
	}
	node->data = item;
	node->next = s->head;

	s->head = node;

	s->count++;

	return 0; // Note: you should have two return statements in this function.
}

// Dequeue an item
// Returns the item at the front of the stack and
// removes an item from the stack.
// Removing from an empty stack should crash the program, call exit(1).
int stack_dequeue(stack_t* s)
{
	if(s == NULL) {
		exit(1);
	}

	if(s->count == 0) {
		exit(1);
	}

	node_t *node = s->head;
	int data = node->data;  // Item to return	
	
	s->head = node->next; // point to new top node

	// need to free after we set the new top
	free(node); // free node we removed - ok beause we got data
	
	s->count--;
	
	return data; // Note: This line is a 'filler' so the code compiles.
}

// Stack Size
// Queries the current size of a stack
// A stack that has not been previously created will crash the program.
// (i.e. A NULL stack cannot return the size)
unsigned int stack_size(stack_t* s)
{
	if(s == NULL) {
		exit(1);
	}
	return s->count;
}

// Free stack
// Removes a stack and ALL of its elements from memory.
// This should be called before the program terminates.
void free_stack(stack_t* s)
{
	if(s == NULL) {
		return;
	}

	node_t *node = s->head;

	while(node)
	{
		node_t *next = node->next;
		// free each node
		free (node);
		node = next;
	}

	// Also free the stack
	free(s);
}

void print_stack(stack_t * s)
{
	int i = 0;
	if(s == NULL) {
		printf("NULL STACK - returning - nothing to print!\n");
		return;
	}
	
	printf("Stack Info:\n");
	printf("    count:      %d\n", s->count);
	printf("    capacity:   %d\n", s->capacity);

	node_t *node = s->head;

	while(node)
	{
		i++;
		printf("      Item %d: %d\n", i, node->data);

		node = node->next;
	}
}

#endif
