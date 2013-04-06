#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

//curr must always start at the beginning

struct stack* newStack(){
  struct stack *new;
  new = (struct stack*)malloc(sizeof(struct stack));
  new->value = -1;
  new->next = NULL;
  return new;
}

void printTop(struct stack* curr){
  curr = peek(curr);
  if(!(curr->value == -1))
    printf("Value: %d \n", curr->value);
  else
    printf("This stack is empty, so there's nothing to print silly!\n");
}

struct stack* peek(struct stack *curr){
    while(curr->next)
      curr = curr->next;
    return curr;
}

void push(int n, struct stack *curr){
  struct stack *new;
  new = newStack();
  new->value = n;
  curr = peek(curr);
  curr->next = new;
}

int pop(struct stack *curr){
  struct stack *top;
  struct stack *tmp;
  top = newStack();
  tmp = newStack();
  top = peek(curr);
  tmp->value = top->value;
  tmp->next = NULL;
  if(curr->next == NULL){
    curr->value = -1;
  }
  else{
    while(!(curr->next == top))
      curr = curr->next;
    curr->next = NULL;
  }
    return tmp->value;
}

int is_empty(struct stack *curr){
  if (curr->value == -1)
    return 1;
  else
    return 0;
}

struct stack * free_stack(struct stack *p) {
  struct stack *l;
  l = newStack();
  while( p ) {
    
    l = p;
    p = p->next;
    free(l);
  }
  return p;
}
