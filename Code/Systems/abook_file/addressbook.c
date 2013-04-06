#include <stdlib.h>
#include <stdio.h>

#include "linklist.h"
#include "addressbook.h"


/*======== struct link ** new_book()) ==========
Inputs:   
Returns: Pointer to the book
Allocates the approprite amount of memory for an address book
with 26 entries. Uses calloc to ensure all pointes are initially
NULL

10/16/09 13:59:29
jdyrlandweaver
====================*/
struct link ** new_book() {

  struct link **b;
  b = (struct link **)calloc(26, sizeof(struct link *));
  return b;
}

/*======== void print_entry() ==========
Inputs:  struct link *p 
Returns: 
Prints out a single entry if p points to a valid link
Prints "No Entry" if p is NULL

10/16/09 13:51:36
jdyrlandweaver
====================*/
void print_entry(struct link *p) {
    if (p)
      printf("%s\n\t%s\n", p->name, p->email);
    else
      printf("No entry\n");
}

/*======== int find_index() ==========
Inputs:  char *n 
Returns: int representing the approriate index for name n


10/16/09 13:52:17
jdyrlandweaver
====================*/
int find_index(char *n) {

  int index;
  if ( n[0] > 90 )
    index = n[0] - 97;
  else
    index = n[0] - 65;

  return index;
}

/*======== struct link ** add_entry() ==========
Inputs:  struct link **b
         char *n
         char *e 
Returns: Pointer to the address book
Inserts link with name n and email e into the correct
link list index

10/16/09 13:52:53
jdyrlandweaver
====================*/
struct link ** add_entry(struct link **b, char *n, char *e) {

  int index;

  //find correct place based on name
  index = find_index(n);
  //insert entry into the list.
  b[index] = insert_ordered(b[index], n, e);
 
  return b;
}

/*======== struct link * search() ==========
Inputs:  struct link **b
         char *n 
Returns: Pointer to the link with name n
         NULL if there is no such link

10/16/09 13:53:45
jdyrlandweaver
====================*/
struct link * search(struct link **b, char *n) {

  return find(b[ find_index(n) ], n);
}
  
/*======== void print_sublist() ==========
Inputs:  struct link **b
         char *c 
Returns: 
Prints the sublist for the given letter

10/16/09 13:54:11
jdyrlandweaver
====================*/
void print_sublist(struct link **b, char *c) {

  print_list( b[ find_index(c) ] );
}


/*======== void print_book() ==========
Inputs:  struct link **b 
Returns: 
Prints out the entire address book

10/16/09 13:54:50
jdyrlandweaver
====================*/
void print_book(struct link **b) {

  int i;
  for (i=0; i<26; i++)
    print_list( b[i] );
}

/*======== struct link ** delete_entry() ==========
Inputs:  struct link **b
         char *n 
Returns: Pointer to the book
Removes the link with name n if it exists, otherwise
leaves b unchanged

10/16/09 13:55:06
jdyrlandweaver
====================*/
struct link ** delete_entry(struct link **b, char *n) {

  int index = find_index(n);
  b[index] = remove_node(b[index], n);
  return b;
}

/*======== struct link ** free_book() ==========
Inputs:  struct link **b 
Returns: Pointer to the book
Frees each sublist of the book

10/16/09 13:57:26
jdyrlandweaver
====================*/
struct link ** free_book(struct link **b) {

  int i;
  for (i=0; i<26; i++) 
    free_list( b[i] );
  return b;
}
    

