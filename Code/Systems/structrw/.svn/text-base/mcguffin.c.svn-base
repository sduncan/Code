#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "mcguffin.h"

struct mcguffin* lax[26];
char name[30];
char number[3];

void make(){
  add(0, 50, "Aaron Printup");
  get_word(0);
  add(1, 66, "Alexander Kedo Hill");
  get_word(1);
  add(2, 26, "Brett Bucktooth");
  get_word(2);
  add(3, 8, "Charles Jacobs");
  get_word(3);
  add(4, 88, "Cody Jamieson");
  get_word(4);
  add(5, 19, "Craig Point");
  get_word(5);
  add(6, 9, "Delby Powless");
  get_word(6);
  add(7, 6, "Drew Bucktooth");
  get_word(7);
  add(8, 44, "Emmett Printup");
  get_word(8);
  add(9, 42, "Gewas Schindler");
  get_word(9);
  add(10, 11, "Isaiah Kicknosway");
  get_word(10);
  add(11, 10, "James Cathers");
  get_word(11);
  add(12, 4, "Jeremy Thompson");
  get_word(12);
  add(13, 22, "Jerome Haina Thompson");
  get_word(13);
  add(14, 16, "Mike Lazore");
  get_word(14);
  add(15, 20, "Mike White");
  get_word(15);
  add(16, 1, "Peter Jacobs");
  get_word(16);
  add(17, 81, "Roger Vyse");
  get_word(17);
  add(18, 17, "Ryan Burnham");
  get_word(18);
  add(19, 79, "Sid Smith");
  get_word(19);
  add(20, 18, "Spencer Lyons");
  get_word(20);
  add(21, 63, "Tom Montour");
  get_word(21);
  add(22, 2, "Marty Ward");
  get_word(22);
  add(23, 77, "Jeff Shattler");
  get_word(23);
  add(24, 61, "Ron Cogan");
  get_word(24);
}

void add(int index, int n, char* w){
  struct mcguffin* tmp;
  tmp = (struct mcguffin*)malloc(sizeof(struct mcguffin*));
  strncpy(tmp->word, w, 30);
  tmp->num = n;
  lax[index] = tmp;
}

char* get_word(int index){
  struct mcguffin* tmp;
  tmp = (struct mcguffin*)malloc(sizeof(struct mcguffin*));
  tmp = lax[index];
  strncpy(name, tmp->word, sizeof(name));
  return name;
}

char* get_num_as_string(int index){
  struct mcguffin* tmp;
  tmp = (struct mcguffin*)malloc(sizeof(struct mcguffin*));
  tmp = lax[index];
  int x;
  x = sprintf(number, "%d", tmp->num);
  return number;
}

