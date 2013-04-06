#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node { 
  char name[256];
  char email[256];
  struct node *next;
}



struct insert_front(char* n, char* e,  struct lnode* front) {
  struct lnode * new;
  new = (struct lnode*)malloc( sizeof (struct lnode) );
  
  new->name = n;
  new->email = e;
  new->next = front;

  return new;
}



struct insert_order(char* n, char* e, struct lnode *front){
  struct lnode * new;
  new = (struct lnode*)malloc( sizeof (struct lnode) );
  
  new->name = n;
  new->email = e;
  
  make two pointers and set one equal to the first node and another equal to the next node so that then we can use them to iterate until one is at the node before the new node's place and the other is one after the new node's place
  struct lnode * iterator1;
  iterator1 = (struct lnode*)malloc( sizeof (struct lnode) );
  iterator1 = front;

  struct lnode * iterator2;
  iterator2 = (struct lnode*)malloc( sizeof (struct lnode) );
  iterator2 = front->next;

  
  while(strcmp(interator1->name, iterator2->name) < 0){
    iterator1 = iterator1->next;
    iterator2 = iterator2->next;
  }
  iterator1->next = new;
  new->next = iterator2;

  return new;
}



struct get(char *n, struct lnode *front){
  struct lnode *base;
  base->name = '';
  base->email = '';
  struct lnode *answer;
  answer = front;
  int boolean = 0;
  while(answer){
    boolean = strcmp(answer->name, n);
    if(boolean == 0)
      break;
  }
  if(boolean == 0)
    return answer;
  else
    return base;
}
    




void print_list(struct lnode *front) {
  while ( front ){
    printf("Name: %s\n", front->name
	   "Email: %s\n", front->email);
    front = front->next;
  }
}




int main(){
  struct lnode l1;
  struct lnode l2;
  char n1[256] = 'a';
  char n2[256] = 'b';
  char e1[256] = 'ae';
  char e2[256] = 'be';
  l1.name = n1;
  l1.name = n2;
  l1.email = e1;
  l2.email = e2;
  l1.next = &l2;
  l2.next = NULL;
  printf(print_list(&l1));
}
