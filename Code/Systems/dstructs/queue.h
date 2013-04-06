#ifndef QUEUE_H
#define QUEUE_H

struct queue{
  int value;
  struct queue *next;
};

//Queue function headers
struct queue* newQueue();
void printFront(struct queue *curr);
struct queue * enqueue(int n, struct queue *curr);
int dequeue(struct queue *curr);
struct queue * peeque(struct queue *curr);
int isEmpty(struct queue *curr);
struct queue * free_queue(struct queue *p);

#endif
