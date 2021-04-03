#ifndef STACK_H
#define STACK_H

#define ACL_DEF_STACK_SIZE 50

#define ACL_STACK_OVERFLOW 1
#define ACL_STACK_UNDERFLOW 2

struct acl_stack{
	void *storage;
	size_t unit_size;
	int count;
	int size;
};

struct acl_stack *acl_create_stack(size_t unit_size, int size);
int acl_stack_pop(struct acl_stack *stack, void *out);
int acl_stack_push(struct acl_stack* stack, void *value);

#endif // STACK_H
