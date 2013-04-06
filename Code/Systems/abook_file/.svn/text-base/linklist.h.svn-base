#ifndef LINKLIST_H
#define LINKLIST_H

struct link {

  char name[256];
  char email[256];
  struct link *next;
};

//Link List Function Headers
void print_list(struct link *);
struct link * insert_front(struct link *, char *, char *);
struct link * insert_ordered(struct link *, char *, char *);
struct link * free_list(struct link *);
struct link * find(struct link *, char *);    
struct link * remove_node(struct link *, char *);
struct link ** add_entry(struct link **, char *, char *);
char * return_name(struct link *);
char * return_email(struct link*);

#endif
