#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "linklist.h"

//Address Book function headers
struct link ** new_book();
void print_entry(struct link *p);
struct link ** add_entry(struct link **b, char *n, char*e);
struct link * search(struct link **b, char *n);
int find_index(char *n);
void print_sublist(struct link **b, char *c);
void print_book(struct link **b);
struct link ** delete_entry(struct link **b, char *n);
struct link ** free_book(struct link **b);

#endif
