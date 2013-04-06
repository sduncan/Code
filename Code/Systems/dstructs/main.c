#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "queue.h"

int main(){
  printf("---------------------------- \n Stack Tests \n---------------------------- \n");
  struct stack *test;
  test = newStack();
  test->value = 2;
  push(3, test);
  printf("Should be 3: \t");
  printTop(test);
  pop(test);
  printf("Should be 2: \t");
  printTop(test);
  printf("Empty? Should be 0: %d \n", is_empty(test));
  pop(test);
  pop(test);
  printTop(test);
  printf("Empty? Should be 1: %d \n", is_empty(test)); 
  free_stack(test);
  printf("---------------------------- \n");
  printf("Queue Tests \n---------------------------- \n");
  struct queue *tester;
  tester = newQueue();
  enqueue(2, tester);
  printFront(tester);
  enqueue(3, tester);
  printf("Return peeque -- value should be 2: %d \n", (peeque(tester))->value);
  printf("Returned dequeue -- value should be 2: %d \n", dequeue(tester));
  printf("Empty? Should be 0: %d \n", isEmpty(tester));
  dequeue(tester);
  printf("Empty? Should be 1: %d \n", isEmpty(tester));
  printFront(tester);
  free_queue(tester);
}
