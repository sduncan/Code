#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "linklist.h"

/*======== void print_list() ==========
Inputs:  struct link *p 
Returns: 
Prints the entire link list stopping at NULL

10/16/09 13:05:58
jdyrlandweaver
====================*/
void print_list(struct link *p) {

  while(p) {
    printf("%s\n\t%s\n", p->name, p->email);
    p = p->next;
  }
}

/*======== struct link * insert_front() ==========
Inputs:  struct link *p
         char *n
         char *e 
Returns: Pointer to the beginning of the list
Inserts a new link with name n and email e at the front of 
the list pointed to by p

10/16/09 13:06:36
jdyrlandweaver
====================*/
struct link * insert_front(struct link *p, char *n, char *e) {

  struct link *tmp;
  tmp = (struct link *)malloc(sizeof(struct link));
  strncpy(tmp->name, n, sizeof(tmp->name));
  strncpy(tmp->email, e, sizeof(tmp->email));
  tmp->next = p;
  p = tmp;
  
  return p;
}

/*======== struct link * insert_ordered() ==========
Inputs:  struct link *p
         char *n
         char *e 
Returns: Pointer to the beginning of the list
Inserts a new link with name n and email e in it's 
lexicographically correct position based on name

10/16/09 13:07:23
jdyrlandweaver
====================*/
struct link * insert_ordered(struct link *p, char *n, char *e) {
  
  struct link *tmp, *curr;
  curr = p;
  
  if ( !p || strcmp(n, p->name) < 0 )
    return insert_front(p, n, e);

  while ( curr->next && strcmp(n, curr->next->name) > 0 )
    curr = curr->next; 
    
  tmp = (struct link *)malloc(sizeof(struct link));
  strncpy(tmp->name, n, sizeof(tmp->name));
  strncpy(tmp->email, e, sizeof(tmp->email));
  tmp->next = curr->next;
  curr->next = tmp;

  return p;
}
			 

/*======== struct link * free_list() ==========
Inputs:  struct link *p 
Returns: Pointer to the last link
Frees the memory for every node in a linked list

10/16/09 13:08:25
jdyrlandweaver
====================*/
struct link * free_list(struct link *p) {

  struct link *l;
  while( p ) {
    
    l = p;
    p = p->next;
    free(l);
  }
  return p;
}			 

/*======== struct link * find() ==========
Inputs:  struct link *p
         char *n 
Returns: Pointer to the link with name n
         NULL if there is no such link
Searches the linked list for a link with name n

10/16/09 13:09:34
jdyrlandweaver
====================*/
struct link * find(struct link *p, char *n) {

  while(p) {
    
    if ( strncmp(n, p->name, sizeof(p->name)) == 0 )
      return p;
    p = p->next;
  }

  return NULL;
}

/*======== struct link * remove_node() ==========
Inputs:  struct link *p
         char *n 
Returns: Pointer to the beginning of the list
Removes the link with name n if such a link exists

10/16/09 13:10:14
jdyrlandweaver
====================*/
struct link * remove_node(struct link *p, char *n) {

  struct link *l;
  struct link *m;
  struct link *found;

  l = p;
  found = find(p, n);

  if (found  && found == l ) {

    l = l->next;
    p->next = NULL;
    free(p);
    return l;
  }
  else if ( found ) {

    while ( l->next != found ) {
      l = l->next;
    }
    m = l;
    l = l->next;
    m->next = l->next;
    l->next = NULL;
    free(l);
    return p;
  }

  else
    return p;
}




char * n[256];
char* return_name(struct link *p){
  strncpy(n, p->name, 256);
  return &(n);
}

char * e[256];
char* return_email(struct link *p){
  strncpy(e, p->email, 256);
  return &(e);
}
