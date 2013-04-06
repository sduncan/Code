#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>

int main(int argc, char **argv) {

  //socket variables
  int socket_id;
  char m_to_client[256];
  char m_from_client[256];
  int i, b;
  
  struct sockaddr_in sock;

  //select variables
  int max_fd;
  int j;
  fd_set whatever;

  //set up socket
  socket_id = socket( AF_INET, SOCK_STREAM, 0);
  sock.sin_family = AF_INET;
  inet_aton( argv[1], &(sock.sin_addr) );
  sock.sin_port = htons(24601);
  int c = connect(socket_id, (struct sockaddr *)&sock, sizeof(sock));
  printf("Server connect returned: %d\n", c);

  //send name to subserver
  char *name = argv[2];
  b = write(socket_id, name, strlen(name) + 1);

  //first message
  printf("MESSAGE ");
  fgets(m_from_client, sizeof(m_from_client), stdin);
  *(strchr(m_from_client, '\n')) = 0;
  b = write( socket_id, m_from_client, strlen(m_from_client) + 1);
  printf("MESSAGE ");

  //entered chatroom
  while (1) {
    
    //set up select stuff                                                         
    FD_ZERO(&whatever);
    FD_SET(STDIN_FILENO, &whatever);
    FD_SET(socket_id, &whatever);
    max_fd = (socket_id > STDIN_FILENO ? socket_id : STDIN_FILENO) + 1;
    

    //read and write
    j = select(max_fd, &whatever, NULL, NULL, NULL);
    
    if (j > 0){

      //read from subserver, print to STDOUT
      if (FD_ISSET(socket_id, &whatever)){
        b = read( socket_id, m_to_client, sizeof(m_to_client));
	
	//determine nature of message
	if (strncmp(m_to_client, "(Message sent)", sizeof(m_to_client)) != 0 &&
	    strncmp(m_to_client, "(Group message sent)", sizeof(m_to_client)) != 0 &&
	    strncmp(m_to_client, "(Name incorrect or unavailable)", sizeof(m_to_client)) != 0 && strncmp(m_to_client, "(online list)", 13) != 0){
	  printf("FROM FRIEND %s\n", m_to_client);
	}
	else{
	  printf("%s\n", m_to_client);
	}
        printf("MESSAGE ");
        fflush(stdout);
      }

      //read from STDIN, write to subserver
      else if (FD_ISSET(STDIN_FILENO, &whatever)){ 
        fgets(m_from_client, sizeof(m_from_client), stdin);
        *(strchr(m_from_client, '\n')) = 0;
        b = write( socket_id, m_from_client, strlen(m_from_client) + 1);
        if ( strncmp(m_from_client, "exit", sizeof(m_from_client)) == 0)
          break;
	printf("MESSAGE ");
      }
    }
  }
  
  close(socket_id);
  return 0;
}
