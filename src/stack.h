#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <types.h>


extern void push(cell c, stack **s, unsigned int* sizeptr);
extern cell pop(stack **s, unsigned int* sizeptr);

extern void wipe(stack **s, unsigned int* sizeptr);
#endif // STACK_H

