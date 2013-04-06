#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "mcguffin.h"

main(){

  make();
  //OPEN THE FILE  
  int fd = open("team",  O_CREAT | O_RDWR, 0644);
  //printf("fd: %d\n", fd);
  //printf("error: %s\n", strerror(errno));


  //WRITE TO THE FILE
  int index = 0;
  int b;
  char w[30];
  char n[3];
  
   while(index < 10){
    strncpy(w, get_word(index), 30);
    strncpy(n, get_num_as_string(index), 3);
    b = write(fd, w, 30);
    b = write(fd, n, 3); 
    index++;
  }

   //READ THE FILE  
  int counter = 0;
      
  while(counter < 10){
    b = lseek(fd, (33 * counter), SEEK_SET);
    b = read(fd, w, 30);
    printf("%d - Name: %s ", counter, w);
    b = read(fd, n, 3);
    printf("Number: %s \n", n);
    counter++;
  }
  
  
  //OFFER RETURNING AN ENTRY OR REMOVING AN ENTRY AND DO WHATEVER USER CHOOSES
  while(1){
  int choice = -1;
  int i = -1;
  char a[] = "Type 0 to return the index of a value or type 1 to modify an entry: \n";
  printf("%s", a);
  scanf("%d", &choice);
  if(choice == 0){
    char s[] = "What index do you want to return? : ";
    printf("%s", s);
    scanf("%d", &i);
    printf("Name: %s ", get_word(i));
    printf("Number: %s\n", get_num_as_string(i));
  }
  else{
    char s[] = "What index do you want to modify? : ";
    printf("%s", s);
    scanf("%d", &i);
    
    b = lseek(fd, 0, SEEK_SET);
    counter = 0;
    while(counter < 10){
      if(counter != i){
	strncpy(w, get_word(counter), 30);
	strncpy(n, get_num_as_string(counter), 3);
	b = write(fd, w, 30);
	b = write(fd, n, 3); 
	counter++;
      }
      else{
	strncpy(w, get_word(index), 30);
	strncpy(n, get_num_as_string(index), 3);
	b = write(fd, w, 30);
	b = write(fd, n, 3); 
	counter++; 
      }
    }
    counter = 0;
    
    while(counter < 10){
      b = lseek(fd, (33 * counter), SEEK_SET);
      b = read(fd, w, 30);
      printf("%d - Name: %s ", counter, w);
      b = read(fd, n, 3);
      printf("Number: %s \n", n);
      counter++;
    }
  }
  }
  close(fd);
  
}
