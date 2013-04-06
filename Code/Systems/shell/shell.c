#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "shell.h"


/*
  ----rmSpaces----
  removes extra spaces from the command
  takes a command in the form of a string
  returns the command without any extra spaces
 */
char * rmSpaces(char *cmd) {
  char *last = cmd + strlen(cmd) - 1;
  while (*cmd == ' ')
    cmd++;
  while (*last == ' ')
    last--;
  last++;
  last = NULL;
  return cmd;
}


/*
  ----getLoc-----
  takes an integer and a command in the form of a string
  finds the location of the command
  returns location of the command
 */
char * getLoc(int x, char *cmd){
  char * loc1;
  char * loc = (char *)malloc(256);  
  if (x == 0)
    loc1 = "/bin/";
  else
    loc1 = "/usr/bin/";
  strncat(loc, loc1, strlen(loc1));
  strncat(loc, cmd, strlen(cmd));
  return loc;
}

/*
  ----execute_piping----
  takes the array of commands as a parameter
  executes the command with piping
  doesn't return anything
*/
void execute_piping(char **cmds){
  int fd1, fd2;
  int err;
  
  fd1 = dup(STDOUT_FILENO);
  dup2(STDIN_FILENO, STDOUT_FILENO);
  err = execlp(getLoc(0, cmds[0]), cmds[0], NULL);
  printf("reporting\n");
  if (err < 0)
    err = execlp(getLoc(1, cmds[0]), cmds[0], NULL);
  
  dup2(fd1, STDOUT_FILENO);
  err = execlp(getLoc(0, cmds[2]), cmds[2], NULL);
  if (err < 0)
    err = execlp(getLoc(1, cmds[2]), cmds[2], NULL);
  
}

/*
  ----execute_r_in----
  takes the array of commands
  executes the command with the proper redirection of stdin
  doesn't return anything
*/
void execute_r_in(char **cmds){
  int fd1, fd2;
  int err;
  
  fd1 = open(cmds[2], O_CREAT | O_RDWR, 0644);
  fd2 = dup(STDIN_FILENO);
  dup2(fd1, STDIN_FILENO);
  err = execlp(getLoc(0, cmds[0]), cmds[0], NULL);
  if (err < 0)
    err = execlp(getLoc(1, cmds[0]), cmds[0], NULL);
  dup2(fd2, STDIN_FILENO);
}

/*
  ----execute_r_out----
  takes the array of commands
  executes the command with the proper redirection of stdout
  doesn't return anything
*/
void execute_r_out(char **cmds){
  int fd1, fd2;
  int err;

  fd1 = open(cmds[2], O_CREAT | O_RDWR, 0644);
  fd2 = dup(STDOUT_FILENO);
  dup2(fd1, STDOUT_FILENO);
  err = execlp(getLoc(0, cmds[0]), cmds[0], NULL);
  if (err < 0)
    err = execlp(getLoc(1, cmds[0]), cmds[0], NULL);
  dup2(fd2, STDOUT_FILENO);
}

/*
  ----execute----
  takes an array of commands as a paramter 
  executes the commands
  doesn't return anything
 */
void execute(char** cmds){
  int p;
  int s;
  int err;

  p = fork();
  if (p == 0){
    if (cmds[1] && cmds[1][0] == '>'){
      execute_r_out(cmds);
    }
    else if (cmds[1] && cmds[1][0] == '<'){
      execute_r_in(cmds);
    }
    else if (cmds[1] && cmds[1][0] == '|'){
      execute_piping(cmds);
    }
    else{
      err = execvp(getLoc(0, cmds[0]), cmds);
      if (err < 0)
	err = execvp(getLoc(1, cmds[0]), cmds);
    }   
  }
  else
    wait(&s);
}


/*
  ----package----
  takes a string of input and puts it into an array of individual command parts
  returns an array of commands and their possible parameters
*/
char ** package(char *ling){
  char **cmds;
  cmds = (char **) malloc( 60 * sizeof(char *));
  char *s2;
  s2 = (char *) malloc(256);

  int i = 0;
  while(ling){
    cmds[i] = (char *) malloc(256);
    s2 = strsep(&ling, " \n");
    s2 = rmSpaces(s2);
    if (s2 && s2[0] != '\0'){
      strncpy(cmds[i], s2, 256);
      i++;
    }
  }

  //makes empty slot resulting from \n into NULL
  i = 0;
  for (i = 0; i < 60; i++){
    if (cmds[i])
      if (cmds[i][0] == '\0')
	cmds[i] = NULL;
  }

  return cmds;
}

/*
  ----prompt----
  takes no parameters
  prompts user for input
  returns and int indicating whether the prompt back is to exit (0) or not (1)
 */
int prompt(){
  int ans;
  char *ling;
  char *string;
  char exit[5] = "exit";
  ling = (char *) malloc(256);
  string = (char *) malloc(256);
  printf("DN$  ");
  fgets(ling, 256, stdin);
  if (ling != NULL){
    while(ling){
      if(strcmp(ling, exit) == 0)
	ans = 0;
      else{
	string = strsep(&ling, ";");
	execute(package(string));
	ans = 1;
      }
    }
  }
  return ans;
}
