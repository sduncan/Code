#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <signal.h>

#define READ 0
#define WRITE 1


//subserver method
void subserver(int socket_client, int to_server, int from_server) {

  //pipe variables
  int b, i;
  b = 0;
  int pid = getpid();
  char m_from_server[256];
  char m_from_client[256];
  
  //select variables
  int ss_max_fd; 
  int ss_j;
  fd_set ss_whatever;

  //send client's name and pid to server
  read(socket_client, m_from_client, sizeof(m_from_client));
  write(to_server, m_from_client, sizeof(m_from_client));
  write(to_server, &pid, sizeof(pid));
  
  //more middleman stuff
  while (1) {

    //set up select stuff
    FD_ZERO(&ss_whatever);
    FD_SET(from_server, &ss_whatever);
    FD_SET(socket_client, &ss_whatever);
    ss_max_fd = (socket_client > from_server ? socket_client : from_server) + 1;  

    //read and write
    ss_j = select(ss_max_fd, &ss_whatever, NULL, NULL, NULL);

    if (ss_j > 0){

      //read from client, write to server
      if(FD_ISSET(socket_client, &ss_whatever)){
        read( socket_client, m_from_client, sizeof(m_from_client));
        if ( strncmp(m_from_client, "exit", sizeof(m_from_client)) == 0){
	  break;
	}
        write(to_server, m_from_client, sizeof(m_from_client));
      }

      //read from server, write to client
      else if(FD_ISSET(from_server, &ss_whatever)){
        read(from_server, m_from_server, sizeof(m_from_server));
        write(socket_client, m_from_server, sizeof(m_from_server));
      }
    }   
  }

  close(socket_client);
}


//returns string of names of all users on server, separated by commas
char * send_online_list(char **names, int client_pids[], int last_client){
  char *list = (char *)malloc(sizeof(names));
  int p;

  //loop through all past and present clients
  for (p = 0; p < last_client; p++){

    ///filter out past clients
    if(client_pids[p] == -1)
      continue;

    //add name to string
    strncat(list, names[p], strlen(names[p]));
    if (p != last_client - 1){
      strncat(list, ", ", 2);
    }
  }
  return list;
}


//signal handler
static void sighandler( int signo ) {

  if ( signo == SIGINT ) {
    remove("upstream");
    exit(0);
  }
}


//the giant
int main() {

  //setup
  umask(0000);
  signal(SIGINT, sighandler);

  //socket variables
  int socket_id, socket_client;
  int i, b;
  pid_t pid;
  int last_client = 0;
  int index;
  char m[256];
  struct sockaddr_in server;
  socklen_t socket_length;

  //client record variables
  int table_to_serv[20];
  int table_to_sub[20];
  int client_pids[10];
  char **names = (char **)calloc(10, sizeof(char *));
  int n;
  for (n = 0; n < 10; n++){
    names[n] = (char *)malloc(256);
  }

  //select variables
  int max_fd;
  int j;
  fd_set whatever;

  int s_max_fd;
  int s_j;
  fd_set s_whatever;


  //set up socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0);
  printf("Socket file descriptor: %d\n", socket_id);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(24601);
  i= bind( socket_id, (struct sockaddr *)&server, sizeof(server) );
  i =  listen( socket_id, 1 );
  
  //interrupt select statement when it ignores signals and tries to stop everything
  //makes a pipe whose READ end is written to constantly, preventing the select statement from slacking off
  pid_t f;
  int interrupt[2];
 
  pipe(interrupt);
  f = fork();
  if (f == 0){
    close(interrupt[READ]);
    char nothing[256] = "nothing";
    while(1){
      write(interrupt[WRITE], nothing, sizeof(nothing));
    }
    exit(0);
  }
  else{
    close(interrupt[WRITE]);
  }
  

  //chatroom behind the scenes
  while(1) {
    printf("Accepting a connection\n");

    //setup select
    FD_ZERO(&s_whatever);
    FD_SET(socket_id, &s_whatever);
    FD_SET(interrupt[READ], &s_whatever);
    s_max_fd = (socket_id > interrupt[READ] ? socket_id : interrupt[READ]) + 1;

    //sleep to prevent while loop from spazzing
    sleep(1);
    s_j = select(s_max_fd, &s_whatever, NULL, NULL, NULL);

    if (s_j > 0){

      //checks if there is request to join chatroom
      if (FD_ISSET(socket_id, &s_whatever)){
        socket_length = sizeof(server);

	//approve request
        socket_client = accept(socket_id, (struct sockaddr *)&server, &socket_length);
        printf("accepted connection %d\n",socket_client);
        
	//initiate pipes between server and subserver
        assert(pipe(&table_to_serv[last_client * 2]) == 0);
        assert(pipe(&table_to_sub[last_client * 2]) == 0);

        //initiate subserver process
        pid = fork();
        if ( pid == 0 ) {

	  //setup subserver
          close(table_to_serv[(last_client * 2) + READ]);
          close(table_to_sub[(last_client * 2) + WRITE]);

	  //subserver
          subserver(socket_client, table_to_serv[(last_client * 2) + 1], table_to_sub[last_client * 2]);         
	  
	  //get pid stuff from subserver after client exits
	  //writes pid to server to change to -1 in client_pids
	  int myPid = getpid();
	  char id[256];
	  sprintf(id, "PIDPID#%d", myPid);
	  write(table_to_serv[(last_client * 2) + 1], &id, sizeof(id));
          exit(0);
        }


	//back to server
        else {
	  
	  //setup server
          close(table_to_serv[(last_client * 2) + WRITE]);
          close(table_to_sub[(last_client * 2) + READ]);
          close(socket_client);
  
	  //gets client name, sent by subserver
	  char *name = (char *)malloc(256);
	  read(table_to_serv[last_client * 2], &m, sizeof(m));
	  strncpy(name, &m[0], sizeof(m));
	  names[last_client] = name;

	  //gets client pid, sent by subserver
	  read(table_to_serv[last_client * 2], &client_pids[last_client], sizeof(client_pids[last_client]));
	  

	  last_client++;
	}
      }
    }

    //read and write
    for(index = 0; index < last_client; index++){

      if (client_pids[index] == -1)
	continue;

      //set up select stuff
      FD_ZERO(&whatever);
      FD_SET(table_to_serv[index * 2], &whatever);
      FD_SET(interrupt[READ], &whatever);
      max_fd = (table_to_serv[index * 2] > interrupt[READ] ? table_to_serv[index * 2] : interrupt[READ]) + 1;
      
      //again, sleep to prevent while loop from going crazy
      sleep(1);
      j = select(max_fd, &whatever, NULL, NULL, NULL);
      
      if (j > 0){

	//read from subserver, write to subservers
        if (FD_ISSET(table_to_serv[index * 2], &whatever)){
          read(table_to_serv[index * 2], m, sizeof(m));
	  
	  //checks for special messages, containing #
	  char *message = (char *)malloc(256);
	  strncpy(message, &m[0], sizeof(m));
	  char *name = (char *)malloc(256);
	  name = strsep(&message, "#");
	  
	  //'PIDPID#somenumber' case
	  if (message != NULL && strncmp(name, "PIDPID", sizeof(name)) == 0){

	    //set pids of past clients to -1
	    int q;
	    for (q = 0; q < last_client; q++){
	      if (client_pids[q] == -1)
		continue;	      
	      char temp[256];
	      sprintf(temp, "%d", client_pids[q]);
	      if (strncmp(temp, message, sizeof(message)) == 0){
		client_pids[q] = -1;
	      }
	    }
	  }

	  //'online#list' case
	  //server provides client with a list of names of all online clients
	  else if (message != NULL && strncmp(message, "list", sizeof(message)) == 0){
	    char *plist = (char *)malloc(sizeof(names)); 
	    char list[256];

	    //calls send_online_list method, which puts string of names together
	    plist = send_online_list(names, client_pids, last_client);
	    sprintf(list, "(online list): %s", plist);

	    //writes table to subserver
	    write(table_to_sub[index * 2 + 1], &list, sizeof(list));
	  }

	  //'somename#somemessage' case
	  //private conversation between sender and name specified before #
	  else if (message != NULL){

	    //sends 'message sent' confirmation to sender
	    char reply[256] = "(Message sent)";
	    write(table_to_sub[index * 2 + 1], &reply, sizeof(reply));
	    	      
	    //loops through all clients to find name
	    int found = 0;
	    int k;
	    for(k = 0; k < last_client; k++){
	      if (client_pids[k] == -1)
		continue;
	      if (strncmp(name, names[k] , sizeof(name)) == 0){
		sprintf(m, "\n\t%s to you: %s", names[index], message);
		write(table_to_sub[k * 2 + 1], &m, sizeof(m));
		found = 1;
		break;
	      }
	    }

	    //if no name was found, returns apologetic message to sender
	    if (found == 0){
	      char sorry[256] = "(Name incorrect or unavailable)";
	      write(table_to_sub[index * 2 + 1], &sorry, sizeof(sorry));
	    }
	  }

	  //'broadcasting' case
	  //message is sent to all clients
	  else {

	    //sends 'group message sent' confirmation'
	    char b_reply[256] = "(Group message sent)";
	    write(table_to_sub[index * 2 + 1], &b_reply, sizeof(b_reply));
	    
	    //sends the message to all clients by the sender
	    int g;
	    for(g = 0; g < last_client; g++){
	      if (client_pids[g] == -1)
		continue;
	      if (g != index){
		sprintf(m, "\n\t%s to all: %s", names[index], name);
		write(table_to_sub[g * 2 + 1], m, sizeof(m));
	      }
	    }
	  }
        }
      }
    }

    //that's all!
    close(socket_client);
    printf("Waiting for new connection\n");
  }
}
