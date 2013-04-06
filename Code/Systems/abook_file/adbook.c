#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include "linklist.h"
#include "addressbook.h"


int main() {

  struct link **book;
  
  book = new_book();
  book = add_entry(book, "Eddie", "ev@pj.com");
  book = add_entry(book, "Ed", "edv@pj.com");
  book = add_entry(book, "HughJazz", "hj@gmail.com");
  book = add_entry(book, "SeymorButz", "sb@gmail.com");
  book = add_entry(book, "Fry", "fry@thefuture.com");
  book = add_entry(book, "Bender", "bitemyshinymetal@ss.com");

  //OPEN FILE
  int fd = open("book.dat",  O_CREAT | O_RDWR, 0644);

  //WRITE TO FILE

  int b;
  char n[256];
  char e[256];
  int a;
  struct link *p;
  p = (struct link *)malloc(sizeof(struct link));
  for (a=0; a<26; a++){
    p = book[a];
    while(p){
      strncpy(n, return_name(p), 256);
      strncpy(e, return_email(p), 256);
      b = write(fd, n, 256);
      b = write(fd, e, 256);
      p = p->next;
    }
  }

  book = free_book( book );
  free(book);
 
  return 0;
}


