#include <stack.h>

void push(cell c, stack **s, unsigned int* sizeptr){ //used
   stack *tmp = malloc(sizeof(stack));
   tmp->next = *s;
   tmp->c = c;
   (*sizeptr)++;
   *s = tmp;
}

cell pop(stack **s, unsigned int* sizeptr){
    stack* out;
    cell c;
    out = *s;
    *s = (*s)->next;
    c = out->c;
    (*sizeptr)--;
    free(out);
    return c;
}

void wipe(stack **s, unsigned int *sizeptr){
    while(*sizeptr > 0){
        if((*s)->next != NULL){
            pop(s, sizeptr);
        }
        else{
            (*sizeptr) = 0;
            break;
        }
    }
}
