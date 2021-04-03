#include<string.h> // for memcpy
#include<malloc.h> // for malloc
#include"acl_stack.h"

#define GET_ELEMENT(s,i) (s->storage + (i * s->unit_size));

struct acl_stack *
acl_create_stack(size_t unit_size, int size)
{
	struct acl_stack *newstack;
	if (!(newstack = malloc(sizeof(struct acl_stack))))
		return NULL;

	if (!(newstack->storage = malloc(sizeof(unit_size) * size)))
		return NULL;

	newstack->unit_size = unit_size;
	newstack->count = 0;
	newstack->size = size;
	return newstack;
}

int 
acl_stack_pop(struct acl_stack *stack, void *out)
{
	if (stack->count == 0)
		return ACL_STACK_UNDERFLOW;
	
	//void *pos = stack->storage + (--stack->count * stack->unit_size);
	void *pos = GET_ELEMENT(stack,--stack->count);
	memcpy(out,pos,stack->unit_size);
	return 0;
}

int 
acl_stack_push(struct acl_stack *stack, void *value)
{
	if (stack->count == stack->size)
		return ACL_STACK_OVERFLOW;
	
	//void *pos = stack->storage + (stack->count++ * stack->unit_size);
	void *pos = GET_ELEMENT(stack,stack->count++);
	memcpy(pos,value,stack->unit_size);
	return 0;

}
