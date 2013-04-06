#ifndef STACK_H
#define STACK_H

struct stack{
  int value;
  struct stack *next;
};

//Stack function headers
struct stack* newStack();
void printTop(struct stack *curr);
void push(int n, struct stack *curr);
int pop(struct stack *curr);
struct stack * peek(struct stack *curr);
int is_empty(struct stack *curr);
struct stack * free_stack(struct stack *p);

#endif
