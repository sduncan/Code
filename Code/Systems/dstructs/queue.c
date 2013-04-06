#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

//curr must always start at the beginning

struct queue* newQueue(){
  struct queue *new;
  new = (struct queue*)malloc(sizeof(struct queue));
  new->value = -1;
  new->next = NULL;
  return new;
}

void printFront(struct queue *curr){
  if(isEmpty(curr) == 0)
    printf("Front value: %d \n", curr->value);
  else
    printf("What a silly duck-- there's nothing to print!\n");
}

struct queue * enqueue(int n, struct queue *curr){
  if(curr->value == -1)
    curr->value = n;
  struct queue *new;
  new = newQueue();
  new->value = n;
  while(curr->next)
    curr = curr->next;
  curr->next = new;
  return new;
}

int dequeue(struct queue *curr){
  struct queue *tmp;
  tmp = newQueue();
  tmp = curr;
  if(curr->next == NULL)
    curr->value = -1;
  else
    curr = curr->next;
  tmp->next = NULL;
  return tmp->value;
}

struct queue * peeque(struct queue *curr){
  return curr;
}
  
int isEmpty(struct queue *curr){
  if(curr->value == -1)
    return 1;
  else
    return 0;
}

struct queue * free_queue(struct queue *p) {
  struct queue *l;
  l = newQueue();
  while( p ) {
    
    l = p;
    p = p->next;
    free(l);
  }
  return p;
}
